/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *
 * vim: tabstop=4 shiftwidth=4 noexpandtab :
 */

#include "rbcairo.h"
#include <rubyio.h>  /* file pointers. */

VALUE mCairo, cCairo, cCairoSurface, cCairoMatrix;

cairo_t*
rcairo_get_cairo(VALUE vcairo) {
	cairo_t *cr;
	Data_Get_Struct(vcairo, cairo_t, cr);
	return cr;
}
VALUE
rcairo_new_from(cairo_t *cr) {
	cairo_reference(cr);
	return Data_Wrap_Struct(cCairo, NULL, cairo_destroy, cr);
}
VALUE
rcairo_new() {
	cairo_t *cr = cairo_create();
	return rcairo_new_from(cr);
}
static VALUE
rcairo_rcairo_new(VALUE class) {
	return rcairo_new();
}

static VALUE
rcairo_dup(VALUE vself) {
	VALUE vdest = rcairo_new();
	cairo_copy(rcairo_get_cairo(vdest), rcairo_get_cairo(vself));
	rb_iv_set(vdest, "@target_image", rb_iv_get(vself, "@target_image"));
	return vdest;
}

static VALUE
rcairo_set_target_image(VALUE vself, VALUE vimage) {
	RCairoImage *img;

	img = rcairo_image_get_image(vimage);
	rb_iv_set(vself, "@target_image", vimage);
	cairo_set_target_image(rcairo_get_cairo(vself), img->data, img->format,
	                       img->width, img->height, img->stride);
	return Qnil;
}
static VALUE
rcairo_set_target_ps(VALUE vself, VALUE vfile,
                     VALUE vwidth_inches, VALUE vheight_inches,
                     VALUE vx_pixels_per_inch, VALUE vy_pixels_per_inch) {
	OpenFile *rf;
	FILE *f;

	rb_check_type(vfile, T_FILE);
	GetOpenFile(vfile, rf);
	f = GetWriteFile(rf);

	rb_iv_set(vself, "@target_file", vfile);
	cairo_set_target_ps(rcairo_get_cairo(vself), f,
	                    NUM2DBL(vwidth_inches), NUM2DBL(vheight_inches),
	                    NUM2DBL(vx_pixels_per_inch), NUM2DBL(vy_pixels_per_inch));
	return Qnil;
}

static VALUE
rcairo_set_dash(VALUE vself, VALUE vdashes, VALUE offset) {
	rb_notimplement();
	return Qnil;
}

static VALUE
rcairo_run_pt_func(VALUE vself, VALUE pt, void (*f)(cairo_t*,double*,double*)) {
	double x = NUM2DBL(rb_ary_entry(pt, 0));
	double y = NUM2DBL(rb_ary_entry(pt, 1));
	f(rcairo_get_cairo(vself), &x, &y);
	return rb_ary_new3(2, rb_float_new(x), rb_float_new(y));
}
static VALUE
rcairo_transform_point(VALUE vself, VALUE pt) {
	return rcairo_run_pt_func(vself, pt, cairo_transform_point);
}
static VALUE
rcairo_transform_distance(VALUE vself, VALUE pt) {
	return rcairo_run_pt_func(vself, pt, cairo_transform_distance);
}
static VALUE
rcairo_inverse_transform_point(VALUE vself, VALUE pt) {
	return rcairo_run_pt_func(vself, pt, cairo_inverse_transform_point);
}
static VALUE
rcairo_inverse_transform_distance(VALUE vself, VALUE pt) {
	return rcairo_run_pt_func(vself, pt, cairo_inverse_transform_distance);
}

/* Ruby-style functions. */
static VALUE
rcairo_stack(VALUE vself) {
	cairo_t *cr = rcairo_get_cairo(vself);
	cairo_save(cr);
	rb_yield(Qnil);
	cairo_restore(cr);
	return Qnil;
}

static VALUE
rcairo_run_path_func(VALUE vself, void (*f)(cairo_t *cr)) {
	cairo_t *cr = rcairo_get_cairo(vself);
	if (rb_block_given_p()) {
		cairo_new_path(cr);
		rb_yield(Qnil);
	}
	f(cr);
	return Qnil;
}

static VALUE
rcairo_stroke(VALUE vself) {
	return rcairo_run_path_func(vself, cairo_stroke);
}

static VALUE
rcairo_fill(VALUE vself) {
	return rcairo_run_path_func(vself, cairo_fill);
}

cairo_matrix_t*
rmatrix_get_matrix(VALUE vmatrix) {
	cairo_matrix_t *cr;
	Data_Get_Struct(vmatrix, cairo_matrix_t, cr);
	return cr;
}
VALUE
rmatrix_new() {
	cairo_matrix_t *cr = cairo_matrix_create();
	//cairo_matrix_reference(cr);
	return Data_Wrap_Struct(cCairoMatrix, NULL, cairo_matrix_destroy, cr);
}
static VALUE
rmatrix_rmatrix_new(VALUE class) {
	return rmatrix_new();
}

cairo_surface_t*
rsurface_get_surface(VALUE vsurface) {
	cairo_surface_t *cr;
	Data_Get_Struct(vsurface, cairo_surface_t, cr);
	return cr;
}
VALUE
rsurface_new_from(cairo_surface_t *surf) {
	cairo_surface_reference(surf);
	return Data_Wrap_Struct(cCairoSurface, NULL, cairo_surface_destroy, surf);
}


/*static VALUE
rcairo_surface_new_for_image(VALUE class, VALUE image) {
	cairo_surface_t *surface;
	rcairoImage *img;
	Data_Get_Struct(image, rcairoImage, img);
	surface = cairo_surface_create_for_image(img->data, img->format,
	                                  img->width, img->height, img->stride);
	return Data_Wrap_Struct(cCairoSurface, NULL, cairo_surface_destroy, surface);
}*/

void
Init_cairo() {
	mCairo = rb_define_module("Cairo");

	constants_init();

	cCairo = gen_Cairo();
	rb_define_singleton_method(cCairo, "new", rcairo_rcairo_new, 0);
	rb_define_method(cCairo, "dup", rcairo_dup, 0);
	rb_define_method(cCairo, "target_image=", rcairo_set_target_image, 1);
	rb_define_method(cCairo, "set_target_ps", rcairo_set_target_ps, 5);
	rb_define_method(cCairo, "set_dash", rcairo_set_dash, 2);
	rb_define_method(cCairo, "transform_point", rcairo_transform_point, 1);
	rb_define_method(cCairo, "transform_distance", rcairo_transform_distance, 1);
	rb_define_method(cCairo, "inverse_transform_point", rcairo_inverse_transform_point, 1);
	rb_define_method(cCairo, "inverse_transform_distance", rcairo_inverse_transform_distance, 1);

	rb_define_method(cCairo, "stack", rcairo_stack, 0);
	rb_define_method(cCairo, "stroke", rcairo_stroke, 0);
	rb_define_method(cCairo, "fill", rcairo_fill, 0);

	cCairoMatrix = gen_CairoMatrix();

	cCairoSurface = gen_CairoSurface();

	xlib_init();
	rcairo_image_init();

	cCairoSurface = rb_define_class_under(mCairo, "Surface", rb_cObject);
	//rb_define_singleton_method(cCairoSurface, "new_for_image", rcairo_surface_new_for_image, 1);
}

