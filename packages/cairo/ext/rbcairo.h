/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *
 * vim: tabstop=4 shiftwidth=4 noexpandtab :
 */

#include <ruby.h>
#include <cairo.h>

void xlib_init();
void cairo_xlib_init(void);
void constants_init(void);

extern VALUE mCairo, cCairo, cCairoSurface, cCairoMatrix, cCairoImage;
extern VALUE cDisplay, eXlib;

/* A buffer for cairo to render images into. */
typedef struct {
	char *data;
	cairo_format_t format;
	int width, height, stride;
} RCairoImage;

VALUE gen_Cairo(void);
VALUE gen_CairoMatrix(void);
VALUE gen_CairoSurface(void);

VALUE    rcairo_display_new();
Display* rcairo_display_get_display(VALUE rdpy);

VALUE    rcairo_new_from(cairo_t *cr);
VALUE    rcairo_new();
cairo_t* rcairo_get_cairo(VALUE rcairo);

void         rcairo_image_init(void);
RCairoImage* rcairo_image_get_image(VALUE vimage);

VALUE           rmatrix_new();
cairo_matrix_t* rmatrix_get_matrix(VALUE vmatrix);

VALUE            rsurface_new_from();
cairo_surface_t* rsurface_get_surface(VALUE rcairo);

