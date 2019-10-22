/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-09-26 13:52:08 $
 *
 * Copyright 2005-2019 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo.h"
#include "rb_cairo_private.h"
#include "rb_cairo_io.h"

#ifdef HAVE_RUBY_ST_H
#  include <ruby/st.h>
#else
#  include <st.h>
#endif

VALUE rb_cCairo_Context;

static ID cr_id_new;
static ID cr_id_surface, cr_id_source;
static ID cr_id_plus, cr_id_minus, cr_id_multi, cr_id_div;
static cairo_user_data_key_t cr_object_holder_key;

#define _SELF  (RVAL2CRCONTEXT(self))

static VALUE cr_get_current_point (VALUE self);

static inline void
cr_check_status (cairo_t *context)
{
  rb_cairo_check_status (cairo_status (context));
}

/* Functions for manipulating state objects */
cairo_t *
rb_cairo_context_from_ruby_object (VALUE obj)
{
  cairo_t *context;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Context))
    {
      rb_raise (rb_eTypeError, "not a cairo graphics context");
    }
  Data_Get_Struct (obj, cairo_t, context);
  if (!context)
    rb_cairo_check_status (CAIRO_STATUS_NULL_POINTER);
  return context;
}

static rb_cairo__object_holder_t *
cr_object_holder_new (VALUE object)
{
  return rb_cairo__object_holder_new (rb_cCairo_Context, object);
}

static void
cr_object_holder_free (void *ptr)
{
  rb_cairo__object_holder_free (rb_cCairo_Context, ptr);
}

static void
cr_context_free (void *ptr)
{
  if (ptr)
    {
      cairo_destroy ((cairo_t *) ptr);
    }
}

VALUE
rb_cairo_context_to_ruby_object (cairo_t *cr)
{
  if (cr)
    {
      cairo_reference (cr);
      return Data_Wrap_Struct (rb_cCairo_Context, NULL, cr_context_free, cr);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_context_free, NULL);
}

static void
cr_set_user_data (cairo_t *cr, const cairo_user_data_key_t *key,
                  void *user_data, cairo_destroy_func_t destroy)
{
#if CAIRO_CHECK_VERSION(1, 4, 0)
  cairo_set_user_data (cr, key, user_data, destroy);
#else
  cairo_surface_t *surface;
  surface = cairo_get_target (cr);
  cairo_surface_set_user_data (surface, key, user_data, destroy);
#endif
}

static VALUE
cr_destroy (VALUE self)
{
  cairo_t *cr;

  cr = _SELF;
  cr_set_user_data (cr, &cr_object_holder_key, NULL, NULL);
  cairo_destroy (cr);

  DATA_PTR (self) = NULL;
  return Qnil;
}

static VALUE
cr_destroyed (VALUE self)
{
  return CBOOL2RVAL (DATA_PTR (self) == NULL);
}

static VALUE
cr_destroy_with_destroy_check (VALUE self)
{
  if (DATA_PTR (self))
    cr_destroy (self);
  return Qnil;
}

static VALUE
cr_get_reference_count (VALUE self)
{
  cairo_t *cr;
  unsigned int  reference_count;

  cr = _SELF;
  reference_count = cairo_get_reference_count (cr);

  return UINT2NUM (reference_count);
}

static VALUE
cr_s_create (int argc, VALUE *argv, VALUE klass)
{
  VALUE rb_cr;
  rb_cr = rb_funcallv (klass, cr_id_new, argc, argv);
  if (rb_block_given_p ())
    {
      return rb_ensure (rb_yield, rb_cr,
                        cr_destroy_with_destroy_check, rb_cr);
    }
  else
    {
      return rb_cr;
    }
}

static VALUE
cr_s_wrap (VALUE self, VALUE pointer)
{
  VALUE result;
  VALUE rb_cr;
  cairo_t *cr;

  if (NIL_P (rb_cairo__cFFIPointer))
    {
      rb_raise (rb_eNotImpError,
                "%s: FFI::Pointer is required",
                rb_id2name (rb_frame_this_func ()));
    }

  if (!RTEST (rb_obj_is_kind_of (pointer, rb_cairo__cFFIPointer)))
    {
      rb_raise (rb_eArgError,
                "must be FFI::Pointer: %s",
                rb_cairo__inspect (pointer));
    }

  {
    VALUE rb_cr_address;
    rb_cr_address = rb_funcall (pointer, rb_intern ("address"), 0);
    cr = NUM2PTR (rb_cr_address);
    cr_check_status (cr);
  }

  rb_cr = rb_obj_alloc (self);
  cairo_reference (cr);
  DATA_PTR (rb_cr) = cr;
  rb_ivar_set (rb_cr, cr_id_surface, Qnil);

  if (rb_block_given_p ())
    {
      result = rb_ensure (rb_yield, rb_cr, cr_destroy_with_destroy_check, rb_cr);
    }
  else
    {
      result = rb_cr;
    }

  return result;
}

static VALUE
cr_initialize (VALUE self, VALUE target)
{
  cairo_t *cr;
  VALUE result = Qnil;

  cr = cairo_create (RVAL2CRSURFACE (target));
  cr_check_status (cr);
  rb_ivar_set (self, cr_id_surface, target);
  rb_ivar_set (self, cr_id_source, Qnil);
  if (rb_ivar_defined (target, rb_cairo__io_id_output))
    cr_set_user_data (cr,
                      &cr_object_holder_key,
                      cr_object_holder_new (self),
                      cr_object_holder_free);
  DATA_PTR (self) = cr;
  if (rb_block_given_p ())
    result = rb_ensure (rb_yield, self, cr_destroy_with_destroy_check, self);
  return result;
}

static VALUE
cr_to_ptr (VALUE self)
{
  if (NIL_P (rb_cairo__cFFIPointer))
    return Qnil;

  return rb_funcall (rb_cairo__cFFIPointer, rb_intern ("new"),
                     1, PTR2NUM (_SELF));
}

static VALUE
cr_raw_address (VALUE self)
{
  return PTR2NUM (_SELF);
}


static VALUE
cr_restore (VALUE self)
{
  cairo_restore (_SELF);
  cr_check_status (_SELF);
  return Qnil;
}

static VALUE
cr_save (VALUE self)
{
  VALUE result = Qnil;
  cairo_save (_SELF);
  cr_check_status (_SELF);
  if (rb_block_given_p ())
    {
      result = rb_ensure (rb_yield, self, cr_restore, self);
    }
  return result;
}

static VALUE
cr_pop_group (VALUE self)
{
  VALUE rb_pattern;
  cairo_pattern_t *pattern;

  pattern = cairo_pop_group (_SELF);
  cr_check_status (_SELF);
  rb_pattern = CRPATTERN2RVAL (pattern);
  cairo_pattern_destroy (pattern);
  return rb_pattern;
}

static VALUE
cr_pop_group_to_source (VALUE self)
{
  cairo_pop_group_to_source (_SELF);
  cr_check_status (_SELF);
  return Qnil;
}

static VALUE
cr_pop_group_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE to_source;
  rb_scan_args (argc, argv, "01", &to_source);
  if (RVAL2CBOOL (to_source))
    return cr_pop_group_to_source (self);
  else
    return cr_pop_group (self);
}

static VALUE
cr_push_group (int argc, VALUE *argv, VALUE self)
{
  VALUE result = Qnil;
  VALUE content, pop_to_source;
  rb_scan_args (argc, argv, "02", &content, &pop_to_source);

  if (NIL_P(content))
    cairo_push_group (_SELF);
  else
    cairo_push_group_with_content (_SELF, RVAL2CRCONTENT(content));
  cr_check_status (_SELF);

  if (rb_block_given_p ())
    {
      int state = 0;

      if (NIL_P (pop_to_source))
        pop_to_source = Qtrue;

      result = rb_protect (rb_yield, self, &state);
      if (cairo_status(_SELF) == CAIRO_STATUS_SUCCESS)
        {
          if (RVAL2CBOOL (pop_to_source))
            cr_pop_group_to_source (self);
          else
            result = cr_pop_group (self);
        }

      if (state)
        rb_jump_tag (state);
    }

  return result;
}


/* Modify state */
static VALUE
cr_set_operator (VALUE self, VALUE operator)
{
  cairo_set_operator (_SELF, RVAL2CROPERATOR (operator));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_source_rgb (int argc, VALUE *argv, VALUE self)
{
  VALUE red, green, blue;
  int n;

  n = rb_scan_args (argc, argv, "12", &red, &green, &blue);

  if (n == 1 && rb_cairo__is_kind_of (red, rb_cArray))
    {
      VALUE ary = red;
      n = (int) RARRAY_LEN (ary);
      red = rb_ary_entry (ary, 0);
      green = rb_ary_entry (ary, 1);
      blue = rb_ary_entry (ary, 2);
    }

  if (n == 3)
    {
      cairo_set_source_rgb (_SELF,
                            NUM2DBL (red),
                            NUM2DBL (green),
                            NUM2DBL (blue));
    }
  else
    {
      VALUE inspected_arg = rb_inspect (rb_ary_new4 (argc, argv));
      rb_raise (rb_eArgError,
                "invalid RGB: %s (expect "
                "(red, green, blue) or ([red, green, blue]))",
                StringValuePtr (inspected_arg));
    }
  cr_check_status (_SELF);
  rb_ivar_set (self, cr_id_source, Qnil);
  return self;
}

static VALUE
cr_set_source_rgba (int argc, VALUE *argv, VALUE self)
{
  VALUE red, green, blue, alpha;
  int n;

  n = rb_scan_args (argc, argv, "13", &red, &green, &blue, &alpha);

  if (n == 1 && rb_cairo__is_kind_of (red, rb_cArray))
    {
      VALUE ary = red;
      n = (int) RARRAY_LEN (ary);
      red = rb_ary_entry (ary, 0);
      green = rb_ary_entry (ary, 1);
      blue = rb_ary_entry (ary, 2);
      alpha = rb_ary_entry (ary, 3);
    }

  if (n == 3)
    {
      cairo_set_source_rgb (_SELF,
                            NUM2DBL (red),
                            NUM2DBL (green),
                            NUM2DBL (blue));
    }
  else if (n == 4)
    {
      cairo_set_source_rgba (_SELF,
                             NUM2DBL (red),
                             NUM2DBL (green),
                             NUM2DBL (blue),
                             NUM2DBL (alpha));
    }
  else
    {
      VALUE inspected_arg = rb_inspect (rb_ary_new4 (argc, argv));
      rb_raise (rb_eArgError,
                "invalid RGB%s: %s (expect "
                "(red, green, blue), (red, green, blue, alpha), "
                "([red, green, blue]) or ([red, green, blue, alpha]))",
                n == 4 ? "A" : "",
                StringValuePtr (inspected_arg));
    }
  cr_check_status (_SELF);
  rb_ivar_set (self, cr_id_source, Qnil);
  return self;
}

static VALUE
cr_set_source_surface (VALUE self, VALUE surface, VALUE width, VALUE height)
{
  cairo_set_source_surface (_SELF,
                            RVAL2CRSURFACE (surface),
                            NUM2DBL (width),
                            NUM2DBL (height));
  cr_check_status (_SELF);
  rb_ivar_set (self, cr_id_source, Qnil);
  return self;
}

static VALUE
cr_set_source (VALUE self, VALUE pattern)
{
  cairo_set_source (_SELF, RVAL2CRPATTERN (pattern));
  cr_check_status (_SELF);
  rb_ivar_set (self, cr_id_source, pattern);
  return self;
}

static VALUE
cr_set_source_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE arg1, arg2, arg3, arg4;
  int n;

  n = rb_scan_args (argc, argv, "13", &arg1, &arg2, &arg3, &arg4);

  if (n == 1 && rb_cairo__is_kind_of (arg1, rb_cArray))
    {
      return cr_set_source_rgba (argc, argv, self);
    }
  else if (n == 1 && rb_cairo__is_kind_of (arg1, rb_cCairo_Surface))
    {
      return cr_set_source_surface (self, arg1,
                                    rb_float_new (0),
                                    rb_float_new (0));
    }
  else if (n == 1)
    {
      return cr_set_source (self, arg1);
    }
  else if (n == 3 && rb_cairo__is_kind_of (arg1, rb_cCairo_Surface))
    {
      return cr_set_source_surface (self, arg1, arg2, arg3);
    }
  else if (n == 3 || n == 4)
    {
      return cr_set_source_rgba (argc, argv, self);
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(red, green, blue), (red, green, blue, alpha), "
                "([red, green, blue]), ([red, green, blue, alpha]), "
                "(surface), (pattern) or (surface, x, y))");
    }
}

static VALUE
cr_set_tolerance (VALUE self, VALUE tolerance)
{
  cairo_set_tolerance (_SELF, NUM2DBL (tolerance));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_antialias(VALUE self, VALUE antialias)
{
  cairo_set_antialias(_SELF, RVAL2CRANTIALIAS (antialias));
  cr_check_status(_SELF);
  return self;
}

static VALUE
cr_set_fill_rule (VALUE self, VALUE rule)
{
  cairo_set_fill_rule (_SELF, RVAL2CRFILLRULE (rule));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_line_width (VALUE self, VALUE width)
{
  cairo_set_line_width (_SELF, NUM2DBL (width));
  return self;
}

static VALUE
cr_set_line_cap (VALUE self, VALUE cap)
{
  cairo_set_line_cap (_SELF, RVAL2CRLINECAP (cap));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_line_join (VALUE self, VALUE join)
{
  cairo_set_line_join (_SELF, RVAL2CRLINEJOIN (join));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_dash (int argc, VALUE *argv, VALUE self)
{
  VALUE dash_array, rb_offset;
  double offset;
  cairo_bool_t is_num;

  rb_scan_args(argc, argv, "11", &dash_array, &rb_offset);

  is_num = rb_cairo__is_kind_of (dash_array, rb_cNumeric);
  if (!(NIL_P (dash_array) || is_num))
    {
      Check_Type (dash_array, T_ARRAY);
    }

  if (NIL_P (rb_offset))
    offset = 0.0;
  else
    offset = NUM2DBL (rb_offset);

  if (is_num)
    {
      double values[1];
      values[0] = NUM2DBL (dash_array);
      cairo_set_dash (_SELF, values, 1, offset);
    }
  else if (NIL_P (dash_array) || RARRAY_LEN (dash_array) == 0)
    {
      cairo_set_dash (_SELF, NULL, 0, offset);
    }
  else
    {
      int i, length;
      double *values;
      length = (int) RARRAY_LEN (dash_array);
      values = ALLOCA_N (double, length);
      if (!values)
        {
          rb_cairo_check_status (CAIRO_STATUS_NO_MEMORY);
        }
      for (i = 0; i < length; i++)
        {
          values[i] = NUM2DBL (RARRAY_PTR (dash_array)[i]);
        }
      cairo_set_dash (_SELF, values, length, offset);
    }

  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_miter_limit (VALUE self, VALUE limit)
{
  cairo_set_miter_limit (_SELF, NUM2DBL (limit));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_translate (VALUE self, VALUE tx, VALUE ty)
{
  cairo_translate (_SELF, NUM2DBL (tx), NUM2DBL (ty));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_scale (VALUE self, VALUE sx, VALUE sy)
{
  cairo_scale (_SELF, NUM2DBL (sx), NUM2DBL (sy));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rotate (VALUE self, VALUE radians)
{
  cairo_rotate (_SELF, NUM2DBL (radians));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_transform (VALUE self, VALUE matrix)
{
  cairo_transform (_SELF, RVAL2CRMATRIX (matrix));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_matrix (VALUE self, VALUE matrix)
{
  cairo_set_matrix (_SELF, RVAL2CRMATRIX (matrix));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_identity_matrix (VALUE self)
{
  cairo_identity_matrix (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_user_to_device (VALUE self, VALUE x, VALUE y)
{
  double pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_user_to_device (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return rb_cairo__float_array (pair, 2);
}

static VALUE
cr_user_to_device_distance (VALUE self, VALUE dx, VALUE dy)
{
  double pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_user_to_device_distance (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return rb_cairo__float_array (pair, 2);
}

static VALUE
cr_device_to_user (VALUE self, VALUE x, VALUE y)
{
  double pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_device_to_user (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return rb_cairo__float_array (pair, 2);
}

static VALUE
cr_device_to_user_distance (VALUE self, VALUE dx, VALUE dy)
{
  double pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_device_to_user_distance (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return rb_cairo__float_array (pair, 2);
}


/* Path creation functions */
static VALUE
cr_new_path (VALUE self)
{
  cairo_new_path (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_move_to (VALUE self, VALUE x, VALUE y)
{
  cairo_move_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_new_sub_path (VALUE self)
{
  cairo_new_sub_path (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_line_to (VALUE self, VALUE x, VALUE y)
{
  cairo_line_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_curve_to (VALUE self, VALUE x1, VALUE y1,
             VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  cairo_curve_to (_SELF, NUM2DBL (x1), NUM2DBL (y1),
                  NUM2DBL (x2), NUM2DBL (y2), NUM2DBL (x3), NUM2DBL (y3));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_quadratic_curve_to (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  VALUE current_point, x0, y0, cx1, cy1, cx2, cy2;

  current_point = cr_get_current_point (self);
  x0 = RARRAY_PTR (current_point)[0];
  y0 = RARRAY_PTR (current_point)[1];

  /* cx1 = x0 + 2 * ((x1 - x0) / 3.0) */
  cx1 = rb_funcall (x0, cr_id_plus, 1,
                    rb_funcall (INT2NUM(2), cr_id_multi, 1,
                                rb_funcall (rb_funcall (x1, cr_id_minus, 1, x0),
                                            cr_id_div, 1, rb_float_new (3.0))));
  /* cy1 = y0 + 2 * ((y1 - y0) / 3.0) */
  cy1 = rb_funcall (y0, cr_id_plus, 1,
                    rb_funcall (INT2NUM(2), cr_id_multi, 1,
                                rb_funcall (rb_funcall (y1, cr_id_minus, 1, y0),
                                            cr_id_div, 1, rb_float_new (3.0))));
  /* cx2 = cx1 + (x2 - x0) / 3.0 */
  cx2 = rb_funcall (cx1, cr_id_plus, 1,
                    rb_funcall (rb_funcall (x2, cr_id_minus, 1, x0),
                                cr_id_div, 1, rb_float_new (3.0)));
  /* cy2 = cy1 + (y2 - y0) / 3.0 */
  cy2 = rb_funcall (cy1, cr_id_plus, 1,
                    rb_funcall (rb_funcall (y2, cr_id_minus, 1, y0),
                                cr_id_div, 1, rb_float_new (3.0)));
  return cr_curve_to (self, cx1, cy1, cx2, cy2, x2, y2);
}

static VALUE
cr_curve_to_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE x1, y1, x2, y2, x3, y3;

  rb_scan_args (argc, argv, "42", &x1, &y1, &x2, &y2, &x3, &y3);

  if (!(argc == 4 || argc == 6))
    {
      VALUE inspected_arg = rb_inspect (rb_ary_new4 (argc, argv));
      rb_raise (rb_eArgError,
                "invalid argument: %s (expect "
                "(x1, y1, x2, y2) (quadratic) or "
                "(x1, y1, x2, y2, x3, y3) (cubic))",
                StringValuePtr (inspected_arg));
    }

  if (argc == 4)
    return cr_quadratic_curve_to (self, x1, y1, x2, y2);
  else
    return cr_curve_to (self, x1, y1, x2, y2, x3, y3);
}

static VALUE
cr_arc (VALUE self, VALUE xc, VALUE yc, VALUE radius,
        VALUE angle1, VALUE angle2)
{
  cairo_arc (_SELF, NUM2DBL (xc), NUM2DBL (yc), NUM2DBL (radius),
             NUM2DBL (angle1), NUM2DBL (angle2));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_arc_negative (VALUE self, VALUE xc, VALUE yc, VALUE radius,
                 VALUE angle1, VALUE angle2)
{
  cairo_arc_negative (_SELF, NUM2DBL (xc), NUM2DBL (yc), NUM2DBL (radius),
                      NUM2DBL (angle1), NUM2DBL (angle2));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_move_to (VALUE self, VALUE x, VALUE y)
{
  cairo_rel_move_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_line_to (VALUE self, VALUE x, VALUE y)
{
  cairo_rel_line_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_curve_to (VALUE self, VALUE dx1, VALUE dy1,
                 VALUE dx2, VALUE dy2, VALUE dx3, VALUE dy3)
{
  cairo_rel_curve_to (_SELF, NUM2DBL (dx1), NUM2DBL (dy1),
                      NUM2DBL (dx2), NUM2DBL (dy2),
                      NUM2DBL (dx3), NUM2DBL (dy3));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_quadratic_curve_to (VALUE self, VALUE dx1, VALUE dy1,
                           VALUE dx2, VALUE dy2)
{
  VALUE current_point, x0, y0;

  current_point = cr_get_current_point (self);
  x0 = RARRAY_PTR (current_point)[0];
  y0 = RARRAY_PTR (current_point)[1];
  return cr_quadratic_curve_to (self,
                                rb_funcall (dx1, cr_id_plus, 1, x0),
                                rb_funcall (dy1, cr_id_plus, 1, y0),
                                rb_funcall (dx2, cr_id_plus, 1, x0),
                                rb_funcall (dy2, cr_id_plus, 1, y0));
}

static VALUE
cr_rel_curve_to_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE dx1, dy1, dx2, dy2, dx3, dy3;

  rb_scan_args (argc, argv, "42", &dx1, &dy1, &dx2, &dy2, &dx3, &dy3);

  if (!(argc == 4 || argc == 6))
    {
      VALUE inspected_arg = rb_inspect (rb_ary_new4 (argc, argv));
      rb_raise (rb_eArgError,
                "invalid argument: %s (expect "
                "(dx1, dy1, dx2, dy2) (quadratic) or "
                "(dx1, dy1, dx2, dy2, dx3, dy3) (cubic))",
                StringValuePtr (inspected_arg));
    }

  if (argc == 4)
    return cr_rel_quadratic_curve_to (self, dx1, dy1, dx2, dy2);
  else
    return cr_rel_curve_to (self, dx1, dy1, dx2, dy2, dx3, dy3);
}

static VALUE
cr_rectangle (VALUE self, VALUE x, VALUE y, VALUE width, VALUE height)
{
  cairo_rectangle (_SELF, NUM2DBL (x), NUM2DBL (y),
                   NUM2DBL (width), NUM2DBL (height));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_close_path (VALUE self)
{
  cairo_close_path (_SELF);
  cr_check_status (_SELF);
  return self;
}

#if CAIRO_CHECK_VERSION(1, 5, 8)
static VALUE
cr_path_extents (VALUE self)
{
  double x1, y1, x2, y2;
  cairo_path_extents (_SELF, &x1, &y1, &x2, &y2);
  cr_check_status (_SELF);
  return rb_ary_new3 (4,
                      rb_float_new(x1), rb_float_new(y1),
                      rb_float_new(x2), rb_float_new(y2));
}
#endif

/* Painting functions */
static VALUE
cr_paint (VALUE self)
{
  cairo_paint (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_paint_with_alpha (VALUE self, VALUE alpha)
{
  cairo_paint_with_alpha (_SELF, NUM2DBL (alpha));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_paint_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE alpha;
  int n;

  n = rb_scan_args (argc, argv, "01", &alpha);

  if (n == 0 || (n == 1 && NIL_P (alpha)))
    {
      return cr_paint (self);
    }
  if (n == 1)
    {
      return cr_paint_with_alpha (self, alpha);
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect () or (alpha))");
    }
}

static VALUE
cr_mask(VALUE self, VALUE pattern)
{
  cairo_mask (_SELF, RVAL2CRPATTERN (pattern));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_mask_surface (VALUE self, VALUE surface, VALUE x, VALUE y)
{
  cairo_mask_surface (_SELF, RVAL2CRSURFACE (surface),
                      NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_mask_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE arg1, arg2, arg3;
  int n;

  n = rb_scan_args (argc, argv, "12", &arg1, &arg2, &arg3);

  if (n == 1)
    {
      return cr_mask (self, arg1);
    }
  else if (n == 3)
    {
      return cr_mask_surface (self, arg1, arg2, arg3);
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect (pattern) or (surface, x, y))");
    }
}

static VALUE
cr_stroke (int argc, VALUE *argv, VALUE self)
{
  VALUE preserve;

  rb_scan_args (argc, argv, "01", &preserve);

  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }

  if (RVAL2CBOOL (preserve))
    cairo_stroke_preserve (_SELF);
  else
    cairo_stroke (_SELF);

  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_fill (int argc, VALUE *argv, VALUE self)
{
  VALUE preserve;

  rb_scan_args (argc, argv, "01", &preserve);

  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }

  if (RVAL2CBOOL (preserve))
    cairo_fill_preserve (_SELF);
  else
    cairo_fill (_SELF);

  cr_check_status (_SELF);
  return self;
}


static VALUE
cr_copy_page (VALUE self)
{
  cairo_copy_page (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_show_page (VALUE self)
{
  cairo_show_page (_SELF);
  cr_check_status (_SELF);
  return self;
}

/* Insideness testing */
static VALUE
cr_in_stroke (VALUE self, VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  return CBOOL2RVAL (cairo_in_stroke (_SELF, NUM2DBL (x), NUM2DBL (y)));
}

static VALUE
cr_in_fill (VALUE self, VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  return CBOOL2RVAL (cairo_in_fill (_SELF, NUM2DBL (x), NUM2DBL (y)));
}

#if CAIRO_CHECK_VERSION(1, 10, 0)
static VALUE
cr_in_clip (VALUE self, VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  return CBOOL2RVAL (cairo_in_clip (_SELF, NUM2DBL (x), NUM2DBL (y)));
}
#endif

/* Rectangular extents */
static VALUE
cr_stroke_extents (VALUE self)
{
  double extents[4];
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_stroke_extents (_SELF, extents, extents + 1, extents + 2, extents + 3);
  return rb_cairo__float_array (extents, 4);
}

static VALUE
cr_fill_extents (VALUE self)
{
  double extents[4];
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_fill_extents (_SELF, extents, extents + 1, extents + 2, extents + 3);
  return rb_cairo__float_array (extents, 4);
}

/* Clipping */
static VALUE
cr_reset_clip (VALUE self)
{
  cairo_reset_clip (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_clip (int argc, VALUE *argv, VALUE self)
{
  VALUE preserve;

  rb_scan_args(argc, argv, "01", &preserve);

  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }

  if (RVAL2CBOOL (preserve))
    cairo_clip_preserve(_SELF);
  else
    cairo_clip (_SELF);

  cr_check_status (_SELF);
  return self;
}

#if CAIRO_CHECK_VERSION(1, 3, 0)
static VALUE
cr_clip_extents (VALUE self)
{
  double x1, y1, x2, y2;
  cairo_clip_extents (_SELF, &x1, &y1, &x2, &y2);
  cr_check_status (_SELF);
  return rb_ary_new3 (4,
                      rb_float_new (x1), rb_float_new (y1),
                      rb_float_new (x2), rb_float_new (y2));
}

static VALUE
cr_clip_rectangle_list (VALUE self)
{
  VALUE rb_rectangles;
  cairo_rectangle_list_t *rectangles;
  int i;

  rectangles = cairo_copy_clip_rectangle_list (_SELF);
  rb_cairo_check_status (rectangles->status);

  rb_rectangles = rb_ary_new2 (rectangles->num_rectangles);
  for (i = 0; i < rectangles->num_rectangles; i++) {
    VALUE argv[4];
    cairo_rectangle_t rectangle = rectangles->rectangles[i];

    argv[0] = rb_float_new (rectangle.x);
    argv[1] = rb_float_new (rectangle.y);
    argv[2] = rb_float_new (rectangle.width);
    argv[3] = rb_float_new (rectangle.height);
    rb_ary_push (rb_rectangles,
                 rb_class_new_instance (4, argv, rb_cCairo_Rectangle));
  }
  cairo_rectangle_list_destroy (rectangles);

  return rb_rectangles;
}
#endif

/* Font/Text functions */
static   VALUE
cr_select_font_face (int argc, VALUE *argv, VALUE self)
{
  VALUE rb_family, rb_slant, rb_weight;
  const char *family;
  cairo_font_slant_t slant;
  cairo_font_weight_t weight;

  rb_scan_args(argc, argv, "03", &rb_family, &rb_slant, &rb_weight);

  if (NIL_P (rb_family))
    {
      family = "";
    }
  else if (rb_cairo__is_kind_of (rb_family, rb_cString))
    {
      family = RSTRING_PTR (rb_family);
    }
  else if (rb_cairo__is_kind_of (rb_family, rb_cSymbol))
    {
      family = rb_id2name (SYM2ID (rb_family));
    }
  else
    {
      rb_raise (rb_eArgError,
                "family name should be nil, String or Symbol: %s",
                rb_cairo__inspect (rb_family));
    }

  if (NIL_P (rb_slant))
    slant = CAIRO_FONT_SLANT_NORMAL;
  else
    slant = RVAL2CRFONTSLANT (rb_slant);

  if (NIL_P (rb_weight))
    weight = CAIRO_FONT_WEIGHT_NORMAL;
  else
    weight = RVAL2CRFONTWEIGHT (rb_weight);

  cairo_select_font_face (_SELF, family, slant, weight);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_font_size (VALUE self, VALUE scale)
{
  cairo_set_font_size (_SELF, NUM2DBL (scale));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_font_matrix (VALUE self, VALUE matrix)
{
  cairo_set_font_matrix (_SELF, RVAL2CRMATRIX (matrix));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_get_font_matrix (VALUE self)
{
  cairo_matrix_t matrix;
  cairo_get_font_matrix (_SELF, &matrix);
  cr_check_status (_SELF);
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_set_font_options (VALUE self, VALUE options)
{
  cairo_set_font_options (_SELF, RVAL2CRFONTOPTIONS (options));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_get_font_options (VALUE self)
{
  cairo_font_options_t *options;
  VALUE rb_options;

  options = cairo_font_options_create ();
  rb_cairo_check_status (cairo_font_options_status (options));

  /* TODO: Use rb_ensure() */
  rb_options = CRFONTOPTIONS2RVAL (options);
  cairo_font_options_destroy (options);

  options = RVAL2CRFONTOPTIONS (rb_options);
  cairo_get_font_options (_SELF, options);
  cr_check_status (_SELF);
  rb_cairo_check_status (cairo_font_options_status (options));

  return rb_options;
}

static VALUE
cr_set_scaled_font (VALUE self, VALUE scaled_font)
{
  cairo_set_scaled_font (_SELF, RVAL2CRSCALEDFONT (scaled_font));
  cr_check_status (_SELF);
  return self;
}

#if CAIRO_CHECK_VERSION(1, 3, 16)
static VALUE
cr_get_scaled_font (VALUE self)
{
  return CRSCALEDFONT2RVAL (cairo_get_scaled_font (_SELF));
}
#endif

static VALUE
cr_show_text (VALUE self, VALUE utf8)
{
  cairo_show_text (_SELF, RVAL2CSTR (utf8));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_show_glyphs (VALUE self, VALUE rb_glyphs)
{
  int count;
  cairo_glyph_t *glyphs;

  RB_CAIRO__GLYPHS_TO_ARRAY (rb_glyphs, glyphs, count);
  cairo_show_glyphs (_SELF, glyphs, count);
  cr_check_status (_SELF);
  return self;
}

#if CAIRO_CHECK_VERSION(1, 8, 0)
static VALUE
cr_show_text_glyphs (VALUE self, VALUE rb_utf8, VALUE rb_glyphs,
                     VALUE rb_clusters, VALUE rb_cluster_flags)
{
  cairo_t *cr;
  const char *utf8;
  int utf8_len;
  cairo_glyph_t *glyphs = NULL;
  int num_glyphs = 0;
  cairo_text_cluster_t *clusters = NULL;
  int num_clusters = 0;
  cairo_text_cluster_flags_t cluster_flags;

  cr = _SELF;
  utf8 = RSTRING_PTR (rb_utf8);
  utf8_len = (int) RSTRING_LEN (rb_utf8);
  rb_cairo__glyphs_from_ruby_object (rb_glyphs, &glyphs, &num_glyphs);
  rb_cairo__text_clusters_from_ruby_object (rb_clusters,
                                            &clusters, &num_clusters);
  cluster_flags = RVAL2CRTEXTCLUSTERFLAGS (rb_cluster_flags);
  cairo_show_text_glyphs (cr, utf8, utf8_len,
                          glyphs, num_glyphs,
                          clusters, num_clusters,
                          cluster_flags);
  if (glyphs)
    cairo_glyph_free (glyphs);
  if (clusters)
    cairo_text_cluster_free (clusters);

  return self;
}
#endif

static VALUE
cr_get_font_face (VALUE self)
{
  cairo_font_face_t *face;

  face = cairo_get_font_face (_SELF);
  rb_cairo_check_status (cairo_font_face_status (face));
  return CRFONTFACE2RVAL (face);
}

static VALUE
cr_font_extents (VALUE self)
{
  cairo_font_extents_t extents;
  cairo_font_extents (_SELF, &extents);
  cr_check_status (_SELF);
  return CRFONTEXTENTS2RVAL (&extents);
}

static VALUE
cr_set_font_face (VALUE self, VALUE face)
{
  cairo_set_font_face (_SELF, NIL_P (face) ? NULL : RVAL2CRFONTFACE (face));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_text_extents (VALUE self, VALUE utf8)
{
  cairo_text_extents_t extents;
  cairo_text_extents (_SELF, StringValuePtr (utf8), &extents);
  cr_check_status (_SELF);
  return CRTEXTEXTENTS2RVAL (&extents);
}

static VALUE
cr_glyph_extents (VALUE self, VALUE rb_glyphs)
{
  cairo_text_extents_t extents;
  cairo_glyph_t *glyphs;
  int length;

  RB_CAIRO__GLYPHS_TO_ARRAY (rb_glyphs, glyphs, length);
  cairo_glyph_extents (_SELF, glyphs, length, &extents);
  cr_check_status (_SELF);
  return CRTEXTEXTENTS2RVAL (&extents);
}

static VALUE
cr_text_path (VALUE self, VALUE utf8)
{
  cairo_text_path (_SELF, StringValuePtr (utf8));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_glyph_path (VALUE self, VALUE rb_glyphs)
{
  int count;
  cairo_glyph_t *glyphs;

  RB_CAIRO__GLYPHS_TO_ARRAY (rb_glyphs, glyphs, count);
  cairo_glyph_path (_SELF, glyphs, count);
  cr_check_status (_SELF);

  return self;
}

/* Query functions */
static VALUE
cr_get_operator (VALUE self)
{
  return INT2FIX (cairo_get_operator (_SELF));
}

static VALUE
cr_get_source (VALUE self)
{
  VALUE rb_source = Qnil;
  cairo_pattern_t *source;
  source = cairo_get_source (_SELF);

  if (source)
    {
      rb_cairo_check_status (cairo_pattern_status (source));
      rb_source = rb_ivar_get (self, cr_id_source);
      if (NIL_P (rb_source) || RVAL2CRPATTERN (rb_source) != source)
        {
          rb_source = CRPATTERN2RVAL (source);
          rb_ivar_set (self, cr_id_source, rb_source);
        }
    }
  else
    {
      rb_source = Qnil;
      rb_ivar_set (self, cr_id_source, rb_source);
    }

  return rb_source;
}

static VALUE
cr_get_tolerance (VALUE self)
{
  return rb_float_new (cairo_get_tolerance (_SELF));
}

static VALUE
cr_get_antialias(VALUE self)
{
  return INT2NUM (cairo_get_antialias (_SELF));
}

#if CAIRO_CHECK_VERSION(1, 5, 10)
static VALUE
cr_has_current_point(VALUE self)
{
  return RTEST (cairo_has_current_point (_SELF));
}
#endif

static VALUE
cr_get_current_point (VALUE self)
{
  double point[2];
  cairo_get_current_point (_SELF, point, point + 1);
  return rb_cairo__float_array (point, 2);
}

static VALUE
cr_get_fill_rule (VALUE self)
{
  return INT2FIX (cairo_get_fill_rule (_SELF));
}

static VALUE
cr_get_line_width (VALUE self)
{
  return rb_float_new (cairo_get_line_width (_SELF));
}

static VALUE
cr_get_line_cap (VALUE self)
{
  return INT2FIX (cairo_get_line_cap (_SELF));
}

static VALUE
cr_get_line_join (VALUE self)
{
  return INT2FIX (cairo_get_line_join (_SELF));
}

static VALUE
cr_get_miter_limit (VALUE self)
{
  return rb_float_new (cairo_get_miter_limit (_SELF));
}

#if CAIRO_CHECK_VERSION(1, 3, 0)
static VALUE
cr_get_dash_count (VALUE self)
{
  return INT2NUM (cairo_get_dash_count (_SELF));
}

static VALUE
cr_get_dash (VALUE self)
{
  int count;
  double *dashes, offset;

  count = cairo_get_dash_count (_SELF);
  dashes = ALLOCA_N (double, count);
  cairo_get_dash (_SELF, dashes, &offset);

  return rb_ary_new3 (2,
                      rb_cairo__float_array (dashes, count),
                      rb_float_new (offset));
}
#endif

static VALUE
cr_get_matrix (VALUE self)
{
  cairo_matrix_t matrix;
  cairo_get_matrix (_SELF, &matrix);
  cr_check_status (_SELF);
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_get_target (VALUE self)
{
  cairo_surface_t *surface;
  VALUE rb_surface = Qnil;

  surface = cairo_get_target (_SELF);
  rb_cairo_check_status (cairo_surface_status (surface));

  if (RTEST (rb_ivar_defined (self, cr_id_surface)))
      rb_surface = rb_ivar_get (self, cr_id_surface);
  if (NIL_P (rb_surface) || RVAL2CRSURFACE (rb_surface) != surface)
    {
      rb_surface = CRSURFACE2RVAL (surface);
      rb_ivar_set (self, cr_id_surface, rb_surface);
    }

  return rb_surface;
}

static VALUE
cr_get_group_target (VALUE self)
{
  cairo_surface_t *surface;

  surface = cairo_get_group_target (_SELF);
  if (!surface)
    return Qnil;
  rb_cairo_check_status (cairo_surface_status (surface));
  return CRSURFACE2RVAL (surface);
}

/* Paths */
static VALUE
cr_copy_path (VALUE self)
{
  cairo_path_t *path;

  path = cairo_copy_path (_SELF);
  rb_cairo_check_status (path->status);
  return CRPATH2RVAL (path);
}

static VALUE
cr_copy_path_flat (VALUE self)
{
  cairo_path_t *path;

  path =  cairo_copy_path_flat (_SELF);
  rb_cairo_check_status (path->status);
  return CRPATH2RVAL (path);
}

static VALUE
cr_copy_append_path (VALUE self, VALUE path)
{
  cairo_append_path (_SELF, RVAL2CRPATH (path));
  cr_check_status (_SELF);
  return self;
}

#if CAIRO_CHECK_VERSION(1, 15, 4)
/* Logical structure tagging functions */
typedef struct rb_cairo_context_tag_ensure_data {
  VALUE self;
  const char *name;
} rb_cairo_context_tag_ensure_data_t;

static VALUE
cr_tag_ensure (VALUE user_data)
{
  rb_cairo_context_tag_ensure_data_t *data =
    (rb_cairo_context_tag_ensure_data_t *)user_data;
  VALUE self;

  self = data->self;
  cairo_tag_end (_SELF, data->name);
  cr_check_status (_SELF);

  return Qnil;
}

static VALUE
cr_tag (int argc, VALUE *argv, VALUE self)
{
  VALUE rb_name;
  VALUE rb_attributes;
  const char *name;
  const char *attributes = NULL;

  rb_scan_args (argc, argv, "11", &rb_name, &rb_attributes);

  name = RVAL2CSTR (rb_name);
  if (!NIL_P (rb_attributes))
    attributes = RVAL2CSTR (rb_attributes);

  cairo_tag_begin (_SELF, name, attributes);
  cr_check_status (_SELF);
  if (rb_block_given_p ())
    {
      rb_cairo_context_tag_ensure_data_t data;
      data.self = self;
      data.name = name;
      return rb_ensure (rb_yield, self,
                        cr_tag_ensure, (VALUE)&data);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_begin_tag (int argc, VALUE *argv, VALUE self)
{
  VALUE rb_name;
  VALUE rb_attributes;
  const char *name;
  const char *attributes = NULL;

  rb_scan_args (argc, argv, "11", &rb_name, &rb_attributes);

  name = RVAL2CSTR (rb_name);
  if (!NIL_P (rb_attributes))
    attributes = RVAL2CSTR (rb_attributes);

  cairo_tag_begin (_SELF, name, attributes);
  cr_check_status (_SELF);

  return Qnil;
}

static VALUE
cr_end_tag (VALUE self, VALUE rb_name)
{
  const char *name;

  name = RVAL2CSTR (rb_name);
  cairo_tag_end (_SELF, name);
  cr_check_status (_SELF);

  return Qnil;
}
#endif

static int
cr_destroy_all_guarded_contexts_at_end_iter (VALUE key, VALUE value, VALUE data)
{
  cr_destroy (key);
  return ST_CONTINUE;
}

static void
cr_destroy_all_guarded_contexts_at_end (VALUE data)
{
  rb_hash_foreach (rb_cairo__gc_guarded_objects (rb_cCairo_Context),
                   cr_destroy_all_guarded_contexts_at_end_iter,
                   Qnil);
}

void
Init_cairo_context (void)
{
  cr_id_new = rb_intern ("new");

  cr_id_surface = rb_intern ("surface");
  cr_id_source = rb_intern ("source");

  cr_id_plus = rb_intern ("+");
  cr_id_minus = rb_intern ("-");
  cr_id_multi = rb_intern ("*");
  cr_id_div = rb_intern ("/");

  rb_cCairo_Context =
    rb_define_class_under (rb_mCairo, "Context", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Context, cr_allocate);

  rb_cairo__initialize_gc_guard_holder_class (rb_cCairo_Context);
  rb_set_end_proc(cr_destroy_all_guarded_contexts_at_end, Qnil);

  rb_define_singleton_method (rb_cCairo_Context, "create", cr_s_create, -1);

  /* For integrate other libraries such as a FFI based library. */
  rb_define_singleton_method (rb_cCairo_Context, "wrap", cr_s_wrap, 1);

  /* Functions for manipulating state objects */
  rb_define_method (rb_cCairo_Context, "initialize", cr_initialize, 1);
  rb_define_method (rb_cCairo_Context, "destroy", cr_destroy, 0);
  rb_define_method (rb_cCairo_Context, "destroyed?", cr_destroyed, 0);
  rb_define_method (rb_cCairo_Context, "reference_count",
                    cr_get_reference_count, 0);

  rb_define_method (rb_cCairo_Context, "save", cr_save, 0);
  rb_define_method (rb_cCairo_Context, "restore", cr_restore, 0);
  rb_define_method (rb_cCairo_Context, "push_group", cr_push_group, -1);
  rb_define_method (rb_cCairo_Context, "pop_group", cr_pop_group_generic, -1);
  rb_define_method (rb_cCairo_Context, "pop_group_to_source",
                    cr_pop_group_to_source, 0);

  /* Modify state */
  rb_define_method (rb_cCairo_Context, "set_operator", cr_set_operator, 1);
  rb_define_method (rb_cCairo_Context, "set_source", cr_set_source_generic, -1);
  rb_define_method (rb_cCairo_Context, "set_source_rgb",
                    cr_set_source_rgb, -1);
  rb_define_method (rb_cCairo_Context, "set_source_rgba",
                    cr_set_source_rgba, -1);
  rb_define_method (rb_cCairo_Context, "set_tolerance", cr_set_tolerance, 1);
  rb_define_method (rb_cCairo_Context, "set_antialias", cr_set_antialias, 1);
  rb_define_method (rb_cCairo_Context, "set_fill_rule", cr_set_fill_rule, 1);
  rb_define_method (rb_cCairo_Context, "set_line_width", cr_set_line_width, 1);
  rb_define_method (rb_cCairo_Context, "set_line_cap", cr_set_line_cap, 1);
  rb_define_method (rb_cCairo_Context, "set_line_join", cr_set_line_join, 1);
  rb_define_method (rb_cCairo_Context, "set_dash", cr_set_dash, -1);
  rb_define_method (rb_cCairo_Context, "set_miter_limit",
                    cr_set_miter_limit, 1);

  rb_define_method (rb_cCairo_Context, "translate", cr_translate, 2);
  rb_define_method (rb_cCairo_Context, "scale", cr_scale, 2);
  rb_define_method (rb_cCairo_Context, "rotate", cr_rotate, 1);
  rb_define_method (rb_cCairo_Context, "transform", cr_transform, 1);

  rb_define_method (rb_cCairo_Context, "set_matrix", cr_set_matrix, 1);
  rb_define_method (rb_cCairo_Context, "identity_matrix",
                    cr_identity_matrix, 0);
  rb_define_method (rb_cCairo_Context, "user_to_device", cr_user_to_device, 2);
  rb_define_method (rb_cCairo_Context, "user_to_device_distance",
                    cr_user_to_device_distance, 2);
  rb_define_method (rb_cCairo_Context, "device_to_user", cr_device_to_user, 2);
  rb_define_method (rb_cCairo_Context, "device_to_user_distance",
                    cr_device_to_user_distance, 2);

  /* Path creation functions */
  rb_define_method (rb_cCairo_Context, "new_path", cr_new_path, 0);
  rb_define_method (rb_cCairo_Context, "move_to", cr_move_to, 2);
  rb_define_method (rb_cCairo_Context, "new_sub_path", cr_new_sub_path, 0);
  rb_define_method (rb_cCairo_Context, "line_to", cr_line_to, 2);
  rb_define_method (rb_cCairo_Context, "curve_to", cr_curve_to_generic, -1);
  rb_define_method (rb_cCairo_Context, "arc", cr_arc, 5);
  rb_define_method (rb_cCairo_Context, "arc_negative", cr_arc_negative, 5);
  rb_define_method (rb_cCairo_Context, "rel_move_to", cr_rel_move_to, 2);
  rb_define_method (rb_cCairo_Context, "rel_line_to", cr_rel_line_to, 2);
  rb_define_method (rb_cCairo_Context, "rel_curve_to",
                    cr_rel_curve_to_generic, -1);
  rb_define_method (rb_cCairo_Context, "rectangle", cr_rectangle, 4);
  rb_define_method (rb_cCairo_Context, "close_path", cr_close_path, 0);
#if CAIRO_CHECK_VERSION(1, 5, 8)
  rb_define_method (rb_cCairo_Context, "path_extents", cr_path_extents, 0);
#endif

  /* Painting functions */
  rb_define_method (rb_cCairo_Context, "paint", cr_paint_generic, -1);
  rb_define_method (rb_cCairo_Context, "mask", cr_mask_generic, -1);
  rb_define_method (rb_cCairo_Context, "stroke", cr_stroke, -1);
  rb_define_method (rb_cCairo_Context, "fill", cr_fill, -1);
  rb_define_method (rb_cCairo_Context, "copy_page", cr_copy_page, 0);
  rb_define_method (rb_cCairo_Context, "show_page", cr_show_page, 0);

  /* Insideness testing */
  rb_define_method (rb_cCairo_Context, "in_stroke?", cr_in_stroke, 2);
  rb_define_method (rb_cCairo_Context, "in_fill?", cr_in_fill, 2);
#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_define_method (rb_cCairo_Context, "in_clip?", cr_in_clip, 2);
#endif

  /* Rectangular extents */
  rb_define_method (rb_cCairo_Context, "stroke_extents", cr_stroke_extents, 0);
  rb_define_method (rb_cCairo_Context, "fill_extents", cr_fill_extents, 0);

  /* Clipping */
  rb_define_method (rb_cCairo_Context, "reset_clip", cr_reset_clip, 0);
  rb_define_method (rb_cCairo_Context, "clip", cr_clip, -1);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_Context, "clip_extents", cr_clip_extents, 0);
  rb_define_method (rb_cCairo_Context, "clip_rectangle_list",
                    cr_clip_rectangle_list, 0);
#endif

  /* Font/Text functions */
  rb_define_method (rb_cCairo_Context, "select_font_face",
                    cr_select_font_face, -1);
  rb_define_method (rb_cCairo_Context, "set_font_size", cr_set_font_size, 1);
  rb_define_method (rb_cCairo_Context, "set_font_matrix",
                    cr_set_font_matrix, 1);
  rb_define_method (rb_cCairo_Context, "font_matrix", cr_get_font_matrix, 0);
  rb_define_method (rb_cCairo_Context, "set_font_options",
                    cr_set_font_options, 1);
  rb_define_method (rb_cCairo_Context, "font_options", cr_get_font_options, 0);
  rb_define_method (rb_cCairo_Context, "set_font_face", cr_set_font_face, 1);
  rb_define_method (rb_cCairo_Context, "font_face", cr_get_font_face, 0);
  rb_define_method (rb_cCairo_Context, "set_scaled_font",
                    cr_set_scaled_font, 1);
#if CAIRO_CHECK_VERSION(1, 3, 16)
  rb_define_method (rb_cCairo_Context, "scaled_font", cr_get_scaled_font, 0);
#endif
  rb_define_method (rb_cCairo_Context, "show_text", cr_show_text, 1);
  rb_define_method (rb_cCairo_Context, "show_glyphs", cr_show_glyphs, 1);
#if CAIRO_CHECK_VERSION(1, 8, 0)
  rb_define_method (rb_cCairo_Context, "show_text_glyphs",
                    cr_show_text_glyphs, 4);
#endif
  rb_define_method (rb_cCairo_Context, "text_path", cr_text_path, 1);
  rb_define_method (rb_cCairo_Context, "glyph_path", cr_glyph_path, 1);
  rb_define_method (rb_cCairo_Context, "text_extents", cr_text_extents, 1);
  rb_define_method (rb_cCairo_Context, "glyph_extents", cr_glyph_extents, 1);
  rb_define_method (rb_cCairo_Context, "font_extents", cr_font_extents, 0);

  /* Query functions */
  rb_define_method (rb_cCairo_Context, "operator", cr_get_operator, 0);
  rb_define_method (rb_cCairo_Context, "source", cr_get_source, 0);
  rb_define_method (rb_cCairo_Context, "tolerance", cr_get_tolerance, 0);
  rb_define_method (rb_cCairo_Context, "antialias", cr_get_antialias, 0);
#if CAIRO_CHECK_VERSION(1, 5, 10)
  rb_define_method (rb_cCairo_Context, "have_current_point?",
                    cr_has_current_point, 0);
  rb_define_alias (rb_cCairo_Context,
                   "has_current_point?", "have_current_point?");
#endif
  rb_define_method (rb_cCairo_Context, "current_point",
                    cr_get_current_point, 0);
  rb_define_method (rb_cCairo_Context, "fill_rule", cr_get_fill_rule, 0);
  rb_define_method (rb_cCairo_Context, "line_width", cr_get_line_width, 0);
  rb_define_method (rb_cCairo_Context, "line_cap", cr_get_line_cap, 0);
  rb_define_method (rb_cCairo_Context, "line_join", cr_get_line_join, 0);
  rb_define_method (rb_cCairo_Context, "miter_limit", cr_get_miter_limit, 0);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_Context, "dash_count", cr_get_dash_count, 0);
  rb_define_method (rb_cCairo_Context, "dash", cr_get_dash, 0);
#endif
  rb_define_method (rb_cCairo_Context, "matrix", cr_get_matrix, 0);
  rb_define_method (rb_cCairo_Context, "target", cr_get_target, 0);
  rb_define_method (rb_cCairo_Context, "group_target", cr_get_group_target, 0);

  /* Paths */
  rb_define_method (rb_cCairo_Context, "copy_path", cr_copy_path, 0);
  rb_define_method (rb_cCairo_Context, "copy_path_flat", cr_copy_path_flat, 0);
  rb_define_method (rb_cCairo_Context, "append_path", cr_copy_append_path, 1);

  rb_define_method (rb_cCairo_Context, "to_ptr", cr_to_ptr, 0);

  rb_define_method (rb_cCairo_Context, "raw_address", cr_raw_address, 0);

#if CAIRO_CHECK_VERSION(1, 15, 4)
  /* Logical structure tagging functions */
  {
    VALUE rb_mCairo_Tag;

    rb_mCairo_Tag = rb_define_module_under (rb_mCairo, "Tag");
    rb_define_const (rb_mCairo_Tag, "DEST", rb_str_new_cstr (CAIRO_TAG_DEST));
    rb_define_const (rb_mCairo_Tag, "LINK", rb_str_new_cstr (CAIRO_TAG_LINK));

    rb_define_method (rb_cCairo_Context, "tag", cr_tag, -1);
    rb_define_method (rb_cCairo_Context, "begin_tag", cr_begin_tag, -1);
    rb_define_method (rb_cCairo_Context, "end_tag", cr_end_tag, 1);
  }
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_Context);
}
