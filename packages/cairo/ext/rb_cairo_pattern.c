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

#define _SELF  (DATA_PTR(self))

VALUE rb_cCairo_Pattern;

cairo_pattern_t *
rb_v_to_cairo_pattern_t (VALUE value)
{
  cairo_pattern_t *pattern;
  if (CLASS_OF (value) != rb_cCairo_Pattern)
    {
      rb_raise (rb_eTypeError, "not a cairo pattern");
    }
  Data_Get_Struct (value, cairo_pattern_t, pattern);
  return pattern;
}

void
rb_free_pattern (void *ptr)
{
  if (ptr)
    {
      cairo_pattern_destroy ((cairo_pattern_t *) ptr);
    }
}

#if 0
VALUE
rb_cairo_pattern_wrap (cairo_pattern_t *pat)
{
  if (pat)
    {
      cairo_pattern_reference (pat);
      return Data_Wrap_Struct (rb_cCairo_Pattern, NULL, rb_free_pattern, pat);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to wrap pattern");
      return Qundef;
    }
}  

VALUE
rb_cairo_pattern_create_linear (VALUE klass,
                                VALUE x0_v, VALUE y0_v,
                                VALUE x1_v, VALUE y1_v)
{
  double x0 = NUM2DBL (x0_v);
  double y0 = NUM2DBL (y0_v);
  double x1 = NUM2DBL (x1_v);
  double y1 = NUM2DBL (y1_v);

  return rb_cairo_pattern_wrap (
    cairo_pattern_create_linear (x0, y0, x1, y1));
}

VALUE
rb_cairo_pattern_create_radial (VALUE klass,
                                VALUE cx0_v, VALUE cy0_v, VALUE radius0_v,
                                VALUE cx1_v, VALUE cy1_v, VALUE radius1_v)
{
  double cx0     = NUM2DBL (cx0_v);
  double cy0     = NUM2DBL (cy0_v);
  double radius0 = NUM2DBL (radius0_v);
  double cx1     = NUM2DBL (cx1_v);
  double cy1     = NUM2DBL (cy1_v);
  double radius1 = NUM2DBL (radius1_v);

  return rb_cairo_pattern_wrap (
    cairo_pattern_create_radial (cx0, cy0, radius0,
                                 cx1, cy1, radius1));
}

VALUE
rb_cairo_pattern_create_for_surface (VALUE klass,
                                     VALUE surface_v)
{


  return rb_cairo_pattern_wrap (
     cairo_pattern_create_for_surface (rb_v_to_cairo_surface_t (surface_v)));
}


VALUE
rb_cairo_pattern_add_color_stop (VALUE self,
                                 VALUE offset_v,
                                 VALUE red_v,
                                 VALUE green_v,
                                 VALUE blue_v,
                                 VALUE alpha_v)
{
  double offset = NUM2DBL (offset_v);
  double red    = NUM2DBL (red_v);
  double green  = NUM2DBL (green_v);
  double blue   = NUM2DBL (blue_v);
  double alpha  = NUM2DBL (alpha_v);

  cairo_pattern_add_color_stop (_SELF, offset, red, green, blue, alpha);
  return self;
}

VALUE
rb_cairo_pattern_set_matrix (VALUE self,
                             VALUE matrix_v)
{
  cairo_pattern_set_matrix (_SELF, rb_v_to_cairo_matrix_t (matrix_v));
  return self;
}

VALUE
rb_cairo_pattern_get_matrix (VALUE self)
{
  cairo_matrix_t *matrix = cairo_matrix_create ();

  if (matrix)
    {
      cairo_pattern_get_matrix (_SELF, matrix);
      return rb_cairo_matrix_wrap (matrix);
    }
  else
    {
      rb_raise (rb_eNoMemError, "matrix problem");
    }
}

static VALUE
rb_cairo_pattern_set_extend (VALUE self,
                             VALUE extend_v)
{
  cairo_extend_t extend = FIX2INT (extend_v);
  if (extend < CAIRO_EXTEND_NONE || extend > CAIRO_EXTEND_REFLECT)
    rb_raise (rb_eArgError, "invalide pattern extend type");
  cairo_pattern_set_extend (_SELF, extend);
  return self; 
}

static VALUE
rb_cairo_pattern_get_extend (VALUE self)
{
  cairo_extend_t extend = cairo_pattern_get_extend (_SELF);
  return INT2FIX (extend);
}

static VALUE
rb_cairo_pattern_set_filter (VALUE self,
                             VALUE filter_v)
{
  cairo_filter_t filter = FIX2INT (filter_v);
  if (filter < CAIRO_FILTER_FAST || filter > CAIRO_FILTER_GAUSSIAN)
    rb_raise (rb_eArgError, "invalide pattern filter type");
  cairo_pattern_set_filter (_SELF, filter);
  return self; 
}

static VALUE
rb_cairo_pattern_get_filter (VALUE self)
{
  cairo_filter_t filter = cairo_pattern_get_filter (_SELF);
  return INT2FIX (filter);
}

#endif

void
Init_cairo_pattern (void)
{
  rb_cCairo_Pattern =
    rb_define_class_under (rb_mCairo, "Pattern", rb_cObject);
#if 0 
  rb_define_singleton_method (rb_cCairo_Pattern, "create_linear",
    RUBY_METHOD_FUNC (rb_cairo_pattern_create_linear), 4);
  rb_define_singleton_method (rb_cCairo_Pattern, "create_radial",
    RUBY_METHOD_FUNC (rb_cairo_pattern_create_radial), 6);
 
  rb_define_method (rb_cCairo_Pattern, "add_color_stop",
    RUBY_METHOD_FUNC (rb_cairo_pattern_add_color_stop), 5);

  rb_define_method (rb_cCairo_Pattern, "set_matrix",
    RUBY_METHOD_FUNC (rb_cairo_pattern_set_matrix), 1);
  rb_define_method (rb_cCairo_Pattern, "get_matrix",
    RUBY_METHOD_FUNC (rb_cairo_pattern_get_matrix), 0);
    
  rb_define_method (rb_cCairo_Pattern, "set_extend",
    RUBY_METHOD_FUNC (rb_cairo_pattern_set_extend), 1);
  rb_define_method (rb_cCairo_Pattern, "get_extend",
    RUBY_METHOD_FUNC (rb_cairo_pattern_get_extend), 0);

  rb_define_method (rb_cCairo_Pattern, "set_filter",
    RUBY_METHOD_FUNC (rb_cairo_pattern_set_filter), 1);
  rb_define_method (rb_cCairo_Pattern, "get_filter",
    RUBY_METHOD_FUNC (rb_cairo_pattern_get_filter), 0);
#endif
}
