/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *
 * vim: tabstop=4 shiftwidth=4 noexpandtab :
 */

#include "shared.h"

#include "cairo-xlib.h"

VALUE mXlib, eXlib, cDisplay, cWindow;

VALUE
rcairo_display_new() {
	Display *dpy;
	VALUE obj;

	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		rb_raise(eXlib, "XOpenDisplay: Unable to open display");
		return Qnil;
	}

	obj = Data_Wrap_Struct(cDisplay, 0, 0, dpy);
	rb_iv_set(obj, "@windows", rb_hash_new());
	rb_iv_set(obj, "@quit", Qfalse);

	return obj;
}
Display*
rcairo_display_get_display(VALUE rdpy) {
	Display *dpy;
	Data_Get_Struct(rdpy, Display, dpy);
	return dpy;
}

static VALUE
display_new(VALUE class) {
	return rcairo_display_new();
}

static VALUE
display_xconnection(VALUE self) {
	Display *dpy;
	Data_Get_Struct(self, Display, dpy);
	return INT2FIX(ConnectionNumber(dpy));
}
static VALUE
display_width(VALUE self) {
	Display *dpy;
	Data_Get_Struct(self, Display, dpy);
	return INT2FIX(DisplayWidth(dpy, 0));
}
static VALUE
display_height(VALUE self) {
	Display *dpy;
	Data_Get_Struct(self, Display, dpy);
	return INT2FIX(DisplayHeight(dpy, 0));
}

static void
redraw(VALUE vwin, Display *dpy, Window win) {
	XClearWindow(dpy, win);
	rb_funcall(vwin, rb_intern("draw"), 0);
}

static VALUE
display_loop(VALUE vself) {
	Display *dpy = rcairo_display_get_display(vself);
	XEvent xev;
	VALUE vwindows, vwin;

	vwindows = rb_iv_get(vself, "@windows");

	while (rb_iv_get(vself, "@quit") == Qfalse) {
		XNextEvent(dpy, &xev);

		switch(xev.type) {
		case KeyPress: {
			XKeyEvent *kev = &xev.xkey;
			unsigned int sym = XKeycodeToKeysym(dpy, kev->keycode, 0);
			vwin = rb_hash_aref(vwindows, INT2FIX(kev->window));
			if (vwin == Qnil)
				continue;
			if (sym > 255) sym = 0;
			rb_funcall(vwin, rb_intern("keypress"), 1, INT2FIX(sym));
			redraw(vwin, dpy, kev->window);
		} break;
		case ConfigureNotify: {
			XConfigureEvent *cev = &xev.xconfigure;
			vwin = rb_hash_aref(vwindows, INT2FIX(cev->window));
			if (vwin == Qnil)
				continue;
			rb_iv_set(vwin, "@width", INT2FIX(cev->width));
			rb_iv_set(vwin, "@height", INT2FIX(cev->height));
			rb_funcall(vwin, rb_intern("resize"), 0);
		} break;
		case Expose: {
			XExposeEvent *eev = &xev.xexpose;
			vwin = rb_hash_aref(vwindows, INT2FIX(eev->window));
			if (vwin == Qnil)
				continue;
			if (eev->count == 0)
				redraw(vwin, dpy, eev->window);
		} break;
		}
	}

	XCloseDisplay(dpy);

	return Qnil;
}

static VALUE
display_quit(VALUE vself) {
	rb_iv_set(vself, "@quit", Qtrue);
	return Qnil;
}

void
xlib_set_size_hints(Display *dpy, Window win, int width, int height) {
	XSizeHints hnt = {0};

	hnt.flags = USSize | PSize | PMinSize | PMaxSize;
	hnt.width      = width;
	hnt.min_width  = width;
	hnt.max_width  = width;
	hnt.height     = height;
	hnt.min_height = height;
	hnt.max_height = height;
	XSetWMNormalHints(dpy, win, &hnt);
}

static VALUE
window_create(VALUE vdpy, VALUE vwidth, VALUE vheight, VALUE vbg) {
	Display *dpy;
	Window root, win;
	int scr;
	int width, height;
	unsigned long color;

	dpy = rcairo_display_get_display(vdpy);

	XSynchronize(dpy, 1);
	root = DefaultRootWindow(dpy);
	scr = DefaultScreen(dpy);
	width = FIX2INT(vwidth);
	height = FIX2INT(vheight);

	if (vbg == Qtrue)
		color = WhitePixel(dpy, scr);
	else
		color = BlackPixel(dpy, scr);
	
	win = XCreateSimpleWindow(dpy, root, 0, 0,
	                          width, height, 0,
	                          color, color);
	
	XSelectInput(dpy, win,
		 KeyPressMask
		 |StructureNotifyMask
		 |ExposureMask);

	XMapWindow(dpy, win);
	return INT2FIX(win);
}

static VALUE
window_init(VALUE vself, VALUE vdpy, VALUE vwidth, VALUE vheight, VALUE vbg) {
	VALUE vwin, vcairo;

	rb_iv_set(vself, "@dpy", vdpy);
	vwin = window_create(vdpy, vwidth, vheight, vbg);
	rb_hash_aset(rb_iv_get(vdpy, "@windows"), vwin, vself);
	rb_iv_set(vself, "@win", vwin);

	vcairo = rcairo_new();
	rb_iv_set(vself, "@cairo", vcairo);
	cairo_set_target_drawable(rcairo_get_cairo(vcairo),
	                          rcairo_display_get_display(vdpy),
							  FIX2INT(vwin));

	return vself;
}

static VALUE
window_nop(VALUE vself) {
	return Qnil;
}

void
xlib_init() {
	VALUE mXlib = rb_define_module_under(mCairo, "Xlib");
	eXlib = rb_define_class_under(mXlib, "Exception", rb_eException);
	cDisplay = rb_define_class_under(mXlib, "Display", rb_cObject);
	rb_define_singleton_method(cDisplay, "new", display_new, 0);
	rb_define_method(cDisplay, "xconnection", display_xconnection, 0);
	rb_define_method(cDisplay, "width", display_width, 0);
	rb_define_method(cDisplay, "height", display_height, 0);
	rb_define_method(cDisplay, "mainloop", display_loop, 0);
	rb_define_method(cDisplay, "quit", display_quit, 0);

	cWindow = rb_define_class_under(mXlib, "Window", rb_cObject);
	rb_define_method(cWindow, "initialize", window_init, 4);
	rb_define_method(cWindow, "draw", window_nop, -1);
	rb_define_method(cWindow, "resize", window_nop, -1);
	rb_define_method(cWindow, "keypress", window_nop, -1);
}

Display*
xlib_dpy_from_rb(VALUE display) {
	Display *dpy;
	Data_Get_Struct(display, Display, dpy);
	return dpy;
}
