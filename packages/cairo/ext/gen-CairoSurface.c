/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *           (C) 2004 Øyvind Kolås <pippin@freedesktop.org>
 *
 */

#include "rbcairo.h"

static VALUE
rcairo_surface_set_repeat (VALUE self,
                           VALUE repeat)
{
  cairo_surface_set_repeat (rsurface_get_surface(self),
                            FIX2INT(repeat));
  return Qnil;
}

static VALUE
rcairo_surface_set_matrix (VALUE self,
                           VALUE matrix)
{
  cairo_surface_set_matrix (rsurface_get_surface(self),
                            rmatrix_get_matrix(matrix));
  return Qnil;
}
static VALUE
rcairo_surface_set_filter (VALUE self,
                           VALUE filter)
{
  cairo_surface_set_filter (rsurface_get_surface(self),
                            NUM2INT(filter));
  return Qnil;
}

static VALUE
rcairo_surface_get_filter (VALUE self)
{
  return INT2FIX(cairo_surface_get_filter(rsurface_get_surface(self)));
}


VALUE gen_CairoSurface (void)
{
  cCairoSurface = rb_define_class_under(mCairo, "Surface", rb_cObject);

  rb_define_method(cCairoSurface, "set_repeat",
                                  rcairo_surface_set_repeat, 1);

  rb_define_method(cCairoSurface, "repeat=",
                                   rcairo_surface_set_repeat, 1);

  rb_define_method(cCairoSurface, "set_matrix",
                                  rcairo_surface_set_matrix, 1);

  rb_define_method(cCairoSurface, "matrix=",
                                  rcairo_surface_set_matrix, 1);

  rb_define_method(cCairoSurface, "set_filter",
                                  rcairo_surface_set_filter, 1);

  rb_define_method(cCairoSurface, "filter=",
                                  rcairo_surface_set_filter, 1);

  rb_define_method(cCairoSurface, "filter",
                                  rcairo_surface_get_filter, 0);

  return cCairoSurface;
}
