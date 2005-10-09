/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"

VALUE rb_cCairo_Pattern;
VALUE rb_cCairo_SolidPattern;
VALUE rb_cCairo_SurfacePattern;
VALUE rb_cCairo_GradientPattern;
VALUE rb_cCairo_LinearPattern;
VALUE rb_cCairo_RadialPattern;

#define _SELF(self)  (RVAL2CRPATTERN(self))

static inline void
cr_pattern_check_status (cairo_pattern_t *pattern)
{
  rb_cairo_check_status (cairo_pattern_status (pattern));
}

cairo_pattern_t *
rb_cairo_pattern_from_ruby_object (VALUE obj)
{
  cairo_pattern_t *pattern;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_Pattern)))
    {
      rb_raise (rb_eTypeError, "not a cairo pattern");
    }
  Data_Get_Struct (obj, cairo_pattern_t, pattern);
  return pattern;
}

static void
cr_pattern_free (void *ptr)
{
  if (ptr)
    {
      cairo_pattern_destroy ((cairo_pattern_t *) ptr);
    }
}

VALUE
rb_cairo_pattern_to_ruby_object (cairo_pattern_t *pattern, VALUE klass)
{
  if (pattern)
    {
      cairo_pattern_reference (pattern);
      return Data_Wrap_Struct (klass, NULL, cr_pattern_free, pattern);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_pattern_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_pattern_free, NULL);
}

static VALUE
cr_pattern_initialize (VALUE self)
{
  rb_raise (rb_eTypeError, "abstract class");
  return Qnil;
}

static VALUE
cr_solid_pattern_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE red, green, blue, alpha;
  int n;
  cairo_pattern_t *pattern;

  n = rb_scan_args (argc, argv, "13", &red, &green, &blue, &alpha);
  
  if (n == 1 && rb_obj_is_kind_of (red, rb_cArray) &&
      (RARRAY (red)->len == 3 || RARRAY (red)->len == 4))
    {
      VALUE ary = red;
      n = RARRAY (ary)->len;
      
      red = rb_ary_entry (ary, 0);
      green = rb_ary_entry (ary, 1);
      blue = rb_ary_entry (ary, 2);
      alpha = rb_ary_entry (ary, 3);
    }

  if (n == 3)
    {
      pattern = cairo_pattern_create_rgb (NUM2DBL (red),
                                          NUM2DBL (green),
                                          NUM2DBL (blue));
    }
  else if (n == 4)
    {
      pattern = cairo_pattern_create_rgba (NUM2DBL (red),
                                           NUM2DBL (green),
                                           NUM2DBL (blue),
                                           NUM2DBL (alpha));
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(red, green, blue), "
                "([red, green, blue]), "
                "(red, green, blue, alpha) or "
                "([red, green, blue, alpha])"
                ")");
    }
  
  cr_pattern_check_status (pattern);
  DATA_PTR (self) = pattern;
  return Qnil;
}

static VALUE
cr_surface_pattern_initialize (VALUE self, VALUE surface)
{
  cairo_pattern_t *pattern;

  pattern = cairo_pattern_create_for_surface (RVAL2CRSURFACE (surface));
  cr_pattern_check_status (pattern);
  DATA_PTR (self) = pattern;
  return Qnil;
}

static VALUE
cr_linear_pattern_initialize (VALUE self, VALUE x0, VALUE y0,
                              VALUE x1, VALUE y1)
{
  cairo_pattern_t *pattern;

  pattern = cairo_pattern_create_linear (NUM2DBL (x0), NUM2DBL (y0),
                                         NUM2DBL (x1), NUM2DBL (y1));
  cr_pattern_check_status (pattern);
  DATA_PTR (self) = pattern;
  return Qnil;
}

static VALUE
cr_radial_pattern_initialize (VALUE self, VALUE cx0, VALUE cy0, VALUE radius0,
                              VALUE cx1, VALUE cy1, VALUE radius1)
{
  cairo_pattern_t *pattern;

  pattern = cairo_pattern_create_radial (NUM2DBL (cx0), NUM2DBL (cy0),
                                         NUM2DBL (radius0),
                                         NUM2DBL (cx1), NUM2DBL (cy1),
                                         NUM2DBL (radius1));
  cr_pattern_check_status (pattern);
  DATA_PTR (self) = pattern;
  return Qnil;
}

/* Cairo::GradientPattern */
static VALUE
cr_gradient_pattern_add_color_stop (int argc, VALUE *argv, VALUE self)
{
  VALUE offset, red, green, blue, alpha;
  int n;
  
  n = rb_scan_args (argc, argv, "23", &offset, &red, &green, &blue, &alpha);

  if (n == 2 && rb_obj_is_kind_of (red, rb_cArray) &&
      (RARRAY (red)->len == 3 || RARRAY (red)->len == 4))
    {
      VALUE ary = red;
      n = RARRAY (ary)->len;
      
      red = rb_ary_entry (ary, 0);
      green = rb_ary_entry (ary, 1);
      blue = rb_ary_entry (ary, 2);
      alpha = rb_ary_entry (ary, 3);
    }

  if (n == 3)
    {
      cairo_pattern_add_color_stop_rgb (_SELF (self), NUM2DBL (offset),
                                        NUM2DBL (red), NUM2DBL (green),
                                        NUM2DBL (blue));
    }
  else if (n == 4)
    {
      cairo_pattern_add_color_stop_rgba (_SELF (self), NUM2DBL (offset),
                                         NUM2DBL (red), NUM2DBL (green),
                                         NUM2DBL (blue), NUM2DBL (alpha));
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(offset, red, green, blue), "
                "(offset, [red, green, blue]), "
                "(offset, red, green, blue, alpha) or "
                "(offset, [red, green, blue, alpha])"
                ")");
    }

  cr_pattern_check_status (_SELF (self));
  return self;
}


/* Cairo::Pattern */
static VALUE
cr_pattern_set_matrix (VALUE self, VALUE matrix)
{
  cairo_pattern_set_matrix (_SELF (self), RVAL2CRMATRIX (matrix));
  cr_pattern_check_status (_SELF (self));
  return self;
}

static VALUE
cr_pattern_get_matrix (VALUE self)
{
  cairo_matrix_t matrix;
  cairo_pattern_get_matrix (_SELF (self), &matrix);
  cr_pattern_check_status (_SELF (self));
  return CRMATRIX2RVAL (&matrix);
}

/* Cairo::SurfacePattern */
static VALUE
cr_surface_pattern_set_extend (VALUE self, VALUE rb_extend)
{
  cairo_extend_t extend;
  extend = NUM2INT (rb_extend);
  if (extend < CAIRO_EXTEND_NONE ||
      extend > CAIRO_EXTEND_REFLECT)
    {
      rb_raise (rb_eArgError, "invalide pattern extend type");
    }

  cairo_pattern_set_extend (_SELF (self), extend);
  cr_pattern_check_status (_SELF (self));
  return self;
}

static VALUE
cr_surface_pattern_get_extend (VALUE self)
{
  return INT2NUM (cairo_pattern_get_extend (_SELF (self)));
}

static VALUE
cr_surface_pattern_set_filter (VALUE self, VALUE rb_filter)
{
  cairo_filter_t filter;
  filter = NUM2INT (rb_filter);
  if (filter < CAIRO_FILTER_FAST ||
      filter > CAIRO_FILTER_GAUSSIAN)
    {
      rb_raise (rb_eArgError, "invalide pattern filter type");
    }

  cairo_pattern_set_filter (_SELF (self), filter);
  cr_pattern_check_status (_SELF (self));
  return self;
}

static VALUE
cr_surface_pattern_get_filter (VALUE self)
{
  return INT2NUM (cairo_pattern_get_filter (_SELF (self)));
}

void
Init_cairo_pattern (void)
{
  rb_cCairo_Pattern =
    rb_define_class_under (rb_mCairo, "Pattern", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Pattern, cr_pattern_allocate);

  rb_define_method (rb_cCairo_Pattern, "initialize", cr_pattern_initialize, 0);
  
  rb_define_method (rb_cCairo_Pattern, "set_matrix", cr_pattern_set_matrix, 1);
  rb_define_method (rb_cCairo_Pattern, "matrix", cr_pattern_get_matrix, 0);
  
  rb_cCairo_SolidPattern =
    rb_define_class_under (rb_mCairo, "SolidPattern", rb_cCairo_Pattern);

  rb_define_method (rb_cCairo_SolidPattern, "initialize",
                    cr_solid_pattern_initialize, -1);

  rb_cCairo_SurfacePattern =
    rb_define_class_under (rb_mCairo, "SurfacePattern", rb_cCairo_Pattern);
  
  rb_define_method (rb_cCairo_SurfacePattern, "initialize",
                    cr_surface_pattern_initialize, 1);

  rb_define_method (rb_cCairo_SurfacePattern, "set_extend",
                    cr_surface_pattern_set_extend, 1);
  rb_define_method (rb_cCairo_SurfacePattern, "extend",
                    cr_surface_pattern_get_extend, 0);
  rb_define_method (rb_cCairo_SurfacePattern, "set_filter",
                    cr_surface_pattern_set_filter, 1);
  rb_define_method (rb_cCairo_SurfacePattern, "filter",
                    cr_surface_pattern_get_filter, 0);

  rb_cCairo_GradientPattern =
    rb_define_class_under (rb_mCairo, "GradientPattern", rb_cCairo_Pattern);

  rb_define_method (rb_cCairo_GradientPattern, "add_color_stop",
                    cr_gradient_pattern_add_color_stop, -1);

  rb_cCairo_LinearPattern =
    rb_define_class_under (rb_mCairo, "LinearPattern",
                           rb_cCairo_GradientPattern);

  rb_define_method (rb_cCairo_LinearPattern, "initialize",
                    cr_linear_pattern_initialize, 4);

  rb_cCairo_RadialPattern =
    rb_define_class_under (rb_mCairo, "RadialPattern",
                           rb_cCairo_GradientPattern);

  rb_define_method (rb_cCairo_RadialPattern, "initialize",
                    cr_radial_pattern_initialize, 6);
}
