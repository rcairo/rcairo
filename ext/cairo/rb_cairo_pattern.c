/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-06-12 10:59:54 $
 *
 * Copyright 2012-2019 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_Pattern;
VALUE rb_cCairo_SolidPattern;
VALUE rb_cCairo_SurfacePattern;
VALUE rb_cCairo_GradientPattern;
VALUE rb_cCairo_LinearPattern;
VALUE rb_cCairo_RadialPattern;
VALUE rb_cCairo_MeshPattern;
VALUE rb_cCairo_RasterSourcePattern;

static ID id_parse, id_to_rgb, id_to_a, id_inspect, id_new, id_call;

#define _SELF(self)  (RVAL2CRPATTERN(self))

#if CAIRO_CHECK_VERSION(1, 11, 4)
#  define RB_CAIRO_HAS_MESH_PATTERN
#  define RB_CAIRO_HAS_RASTER_SOURCE_PATTERN
#endif

static VALUE
cr_color_parse (VALUE color)
{
  return rb_funcall (rb_mCairo_Color, id_parse, 1, color);
}

static inline void
cr_pattern_check_status (cairo_pattern_t *pattern)
{
  rb_cairo_check_status (cairo_pattern_status (pattern));
}

static VALUE
cr_pattern_get_klass (cairo_pattern_t *pattern)
{
  VALUE klass;
  cairo_pattern_type_t type;

  type = cairo_pattern_get_type (pattern);
  switch (type)
    {
    case CAIRO_PATTERN_TYPE_SOLID:
      klass = rb_cCairo_SolidPattern;
      break;
    case CAIRO_PATTERN_TYPE_SURFACE:
      klass = rb_cCairo_SurfacePattern;
      break;
    case CAIRO_PATTERN_TYPE_LINEAR:
      klass = rb_cCairo_LinearPattern;
      break;
    case CAIRO_PATTERN_TYPE_RADIAL:
      klass = rb_cCairo_RadialPattern;
      break;
#if CAIRO_CHECK_VERSION(1, 11, 4)
    case CAIRO_PATTERN_TYPE_MESH:
      klass = rb_cCairo_MeshPattern;
      break;
    case CAIRO_PATTERN_TYPE_RASTER_SOURCE:
      klass = rb_cCairo_RasterSourcePattern;
      break;
#endif
    default:
      rb_raise (rb_eArgError, "unknown pattern type: %d", type);
      break;
    }

  return klass;
}

static VALUE
cr_pattern_solid_supported_p (VALUE klass)
{
  return Qtrue;
}

static VALUE
cr_pattern_surface_supported_p (VALUE klass)
{
  return Qtrue;
}

static VALUE
cr_pattern_gradient_supported_p (VALUE klass)
{
  return Qtrue;
}

static VALUE
cr_pattern_linear_supported_p (VALUE klass)
{
  return Qtrue;
}

static VALUE
cr_pattern_radial_supported_p (VALUE klass)
{
  return Qtrue;
}

static VALUE
cr_pattern_mesh_supported_p (VALUE klass)
{
#ifdef RB_CAIRO_HAS_MESH_PATTERN
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_pattern_raster_source_supported_p (VALUE klass)
{
#ifdef RB_CAIRO_HAS_RASTER_SOURCE_PATTERN
  return Qtrue;
#else
  return Qfalse;
#endif
}

cairo_pattern_t *
rb_cairo_pattern_from_ruby_object (VALUE obj)
{
  cairo_pattern_t *pattern;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Pattern))
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
rb_cairo_pattern_to_ruby_object (cairo_pattern_t *pattern)
{
  if (pattern)
    {
      VALUE klass;
      klass = cr_pattern_get_klass (pattern);
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
cr_pattern_initialize (int argc, VALUE *argv, VALUE self)
{
  rb_raise(rb_eNotImpError,
           "%s class instantiation isn't supported on this cairo installation",
           rb_obj_classname(self));

  return Qnil;
}

static VALUE
cr_solid_pattern_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE red, green, blue, alpha;
  int n;
  cairo_pattern_t *pattern;

  n = rb_scan_args (argc, argv, "13", &red, &green, &blue, &alpha);

  if (n == 1)
    {
      VALUE color = red;

      color = cr_color_parse (color);
      if (rb_cairo__is_kind_of (color, rb_cCairo_Color_Base))
        red = rb_funcall (rb_funcall (color, id_to_rgb, 0), id_to_a, 0);
    }

  if (n == 1 && rb_cairo__is_kind_of (red, rb_cArray) &&
      (RARRAY_LEN (red) == 3 || RARRAY_LEN (red) == 4))
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
      VALUE inspected;

      inspected = rb_funcall (argc == 1 ? red : rb_ary_new4 (argc, argv),
                              id_inspect, 0);
      rb_raise (rb_eArgError,
                "invalid argument: %s (expect "
                "(color_name), "
                "(color_hex_triplet), "
                "(Cairo::Color::RGB), "
                "(Cairo::Color::CMYK), "
                "(Cairo::Color::HSV), "
                "(red, green, blue), "
                "([red, green, blue]), "
                "(red, green, blue, alpha) or "
                "([red, green, blue, alpha])"
                ")",
                RVAL2CSTR (inspected));
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
cr_gradient_pattern_add_color_stop_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE offset, red, green, blue, alpha;
  int n;

  n = rb_scan_args (argc, argv, "23", &offset, &red, &green, &blue, &alpha);

  if (n == 2)
    {
      VALUE color = red;

      color = cr_color_parse (color);
      if (rb_cairo__is_kind_of (color, rb_cCairo_Color_Base))
        red = rb_funcall (rb_funcall (color, id_to_rgb, 0), id_to_a, 0);
    }

  if (n == 2 && rb_cairo__is_kind_of (red, rb_cArray))
    {
      VALUE ary = red;
      n = (int) RARRAY_LEN (ary) + 1;

      red = rb_ary_entry (ary, 0);
      green = rb_ary_entry (ary, 1);
      blue = rb_ary_entry (ary, 2);
      alpha = rb_ary_entry (ary, 3);
    }

  if (n == 4 || (n == 5 && NIL_P (alpha)))
    {
      cairo_pattern_add_color_stop_rgb (_SELF (self), NUM2DBL (offset),
                                        NUM2DBL (red), NUM2DBL (green),
                                        NUM2DBL (blue));
    }
  else if (n == 5)
    {
      cairo_pattern_add_color_stop_rgba (_SELF (self), NUM2DBL (offset),
                                         NUM2DBL (red), NUM2DBL (green),
                                         NUM2DBL (blue), NUM2DBL (alpha));
    }
  else
    {
      VALUE inspected;

      inspected = rb_funcall (rb_ary_new4 (argc, argv), id_inspect, 0);
      rb_raise (rb_eArgError,
                "invalid argument: %s (expect "
                "(offset, color_name), "
                "(offset, color_hex_triplet), "
                "(offset, Cairo::Color::RGB), "
                "(offset, Cairo::Color::CMYK), "
                "(offset, Cairo::Color::HSV), "
                "(offset, red, green, blue), "
                "(offset, [red, green, blue]), "
                "(offset, red, green, blue, alpha) or "
                "(offset, [red, green, blue, alpha])"
                ")",
                RVAL2CSTR (inspected));
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

static VALUE
cr_pattern_set_extend (VALUE self, VALUE extend)
{
  cairo_pattern_set_extend (_SELF (self), RVAL2CREXTEND (extend));
  cr_pattern_check_status (_SELF (self));
  return self;
}

static VALUE
cr_pattern_get_extend (VALUE self)
{
  return INT2NUM (cairo_pattern_get_extend (_SELF (self)));
}

static VALUE
cr_pattern_set_filter (VALUE self, VALUE filter)
{
  cairo_pattern_set_filter (_SELF (self), RVAL2CRFILTER (filter));
  cr_pattern_check_status (_SELF (self));
  return self;
}

static VALUE
cr_pattern_get_filter (VALUE self)
{
  return INT2NUM (cairo_pattern_get_filter (_SELF (self)));
}

#if CAIRO_CHECK_VERSION(1, 3, 0)
static VALUE
cr_solid_pattern_get_rgba (VALUE self)
{
  double red, green, blue, alpha;

  rb_cairo_check_status (cairo_pattern_get_rgba (_SELF (self),
                                                 &red, &green, &blue, &alpha));
  return rb_ary_new3 (4,
                      rb_float_new (red), rb_float_new (green),
                      rb_float_new (blue), rb_float_new (alpha));
}

static VALUE
cr_solid_pattern_get_color (VALUE self)
{
  return cr_color_parse (cr_solid_pattern_get_rgba (self));
}

static VALUE
cr_surface_pattern_get_surface (VALUE self)
{
  cairo_surface_t *surface;

  rb_cairo_check_status (cairo_pattern_get_surface (_SELF (self), &surface));
  return CRSURFACE2RVAL (surface);
}

static VALUE
cr_gradient_pattern_get_color_stop_rgba (VALUE self, VALUE index)
{
  cairo_status_t status;
  double offset, red, green, blue, alpha;

  status = cairo_pattern_get_color_stop_rgba (_SELF (self), NUM2INT (index),
                                              &offset, &red, &green, &blue,
                                              &alpha);
  rb_cairo_check_status (status);
  return rb_ary_new3 (5, rb_float_new (offset),
                      rb_float_new (red), rb_float_new (green),
                      rb_float_new (blue), rb_float_new (alpha));
}

static VALUE
cr_gradient_pattern_get_color_stop_color (VALUE self, VALUE index)
{
  VALUE result, offset, rgba;

  result = cr_gradient_pattern_get_color_stop_rgba (self, index);
  offset = rb_ary_shift (result);
  rgba = result;

  return rb_ary_new3 (2, offset, cr_color_parse (rgba));
}

static VALUE
cr_gradient_pattern_get_color_stop_count (VALUE self)
{
  cairo_status_t status;
  int count;

  status = cairo_pattern_get_color_stop_count (_SELF (self), &count);
  rb_cairo_check_status (status);
  return INT2NUM (count);
}

static VALUE
cr_linear_pattern_get_linear_points (VALUE self)
{
  cairo_status_t status;
  double x0, y0, x1, y1;

  status = cairo_pattern_get_linear_points (_SELF (self), &x0, &y0, &x1, &y1);
  rb_cairo_check_status (status);
  return rb_ary_new3 (4,
                      rb_float_new (x0), rb_float_new (y0),
                      rb_float_new (x1), rb_float_new (y1));
}

static VALUE
cr_radial_pattern_get_radial_circles (VALUE self)
{
  cairo_status_t status;
  double x0, y0, r0, x1, y1, r1;

  status = cairo_pattern_get_radial_circles (_SELF (self),
                                             &x0, &y0, &r0,
                                             &x1, &y1, &r1);
  rb_cairo_check_status (status);
  return rb_ary_new3 (2,
                      rb_ary_new3 (3,
                                   rb_float_new (x0),
                                   rb_float_new (y0),
                                   rb_float_new (r0)),
                      rb_ary_new3 (3,
                                   rb_float_new (x1),
                                   rb_float_new (y1),
                                   rb_float_new (r1)));
}
#endif

/* Cairo::SurfacePattern */
/* none */

#ifdef RB_CAIRO_HAS_MESH_PATTERN
/* Cairo::MeshPattern */
static VALUE
cr_mesh_pattern_initialize (VALUE self)
{
  cairo_pattern_t *pattern;

  pattern = cairo_pattern_create_mesh ();
  cr_pattern_check_status (pattern);
  DATA_PTR (self) = pattern;
  return Qnil;
}

static VALUE
cr_mesh_pattern_end_patch (VALUE self)
{
  cairo_pattern_t *pattern;

  pattern = _SELF (self);
  cairo_mesh_pattern_end_patch (pattern);
  cr_pattern_check_status (pattern);
  return self;
}

static VALUE
cr_mesh_pattern_begin_patch (VALUE self)
{
  cairo_pattern_t *pattern;

  pattern = _SELF (self);
  cairo_mesh_pattern_begin_patch (pattern);
  cr_pattern_check_status (pattern);
  if (rb_block_given_p ())
    return rb_ensure (rb_yield, self, cr_mesh_pattern_end_patch, self);
  else
    return self;
}

static VALUE
cr_mesh_pattern_curve_to (VALUE self,
                          VALUE x1, VALUE y1,
                          VALUE x2, VALUE y2,
                          VALUE x3, VALUE y3)
{
  cairo_pattern_t *pattern;

  pattern = _SELF (self);
  cairo_mesh_pattern_curve_to (pattern,
                               NUM2DBL (x1), NUM2DBL (y1),
                               NUM2DBL (x2), NUM2DBL (y2),
                               NUM2DBL (x3), NUM2DBL (y3));
  cr_pattern_check_status (pattern);
  return self;
}

static VALUE
cr_mesh_pattern_line_to (VALUE self, VALUE x, VALUE y)
{
  cairo_pattern_t *pattern;

  pattern = _SELF (self);
  cairo_mesh_pattern_line_to (pattern, NUM2DBL (x), NUM2DBL (y));
  cr_pattern_check_status (pattern);
  return self;
}

static VALUE
cr_mesh_pattern_move_to (VALUE self, VALUE x, VALUE y)
{
  cairo_pattern_t *pattern;

  pattern = _SELF (self);
  cairo_mesh_pattern_move_to (pattern, NUM2DBL (x), NUM2DBL (y));
  cr_pattern_check_status (pattern);
  return self;
}

static VALUE
cr_mesh_pattern_set_control_point (VALUE self, VALUE rb_nth_point,
                                   VALUE rb_x, VALUE rb_y)
{
  cairo_pattern_t *pattern;
  unsigned int nth_point;

  pattern = _SELF (self);
  nth_point = NUM2UINT (rb_nth_point);
  if (nth_point <= 3)
    {
      cairo_mesh_pattern_set_control_point (pattern, nth_point,
                                            NUM2DBL (rb_x), NUM2DBL (rb_y));
    }
  else
    {
      VALUE inspected;

      inspected = rb_funcall (rb_ary_new3 (3, rb_nth_point, rb_x, rb_y),
                              id_inspect, 0);
      rb_raise (rb_eArgError, "nth_point must be 0, 1, 2 or 3: <%u>: <%s>",
                nth_point, RVAL2CSTR (inspected));
    }
  cr_pattern_check_status (pattern);
  return self;
}

static VALUE
cr_mesh_pattern_set_corner_color_generic (int argc, VALUE *argv, VALUE self)
{
  cairo_pattern_t *pattern;
  VALUE rb_nth_corner, rb_red, rb_green, rb_blue, rb_alpha;
  unsigned int nth_corner;
  double red, green, blue, alpha;

  rb_scan_args (argc, argv, "41",
                &rb_nth_corner, &rb_red, &rb_green, &rb_blue, &rb_alpha);

  nth_corner = NUM2UINT (rb_nth_corner);
  if (nth_corner > 3)
    {
      VALUE inspected;

      inspected = rb_funcall (rb_ary_new4 (argc, argv), id_inspect, 0);
      rb_raise (rb_eArgError, "nth_corner must be 0, 1, 2 or 3: <%u>: <%s>",
                nth_corner, RVAL2CSTR (inspected));
    }

  pattern = _SELF (self);
  red = NUM2DBL (rb_red);
  green = NUM2DBL (rb_green);
  blue = NUM2DBL (rb_blue);
  if (NIL_P (rb_alpha))
    {
      cairo_mesh_pattern_set_corner_color_rgb (pattern, nth_corner,
                                               red, green, blue);
    }
  else
    {
      alpha = NUM2DBL (rb_alpha);
      cairo_mesh_pattern_set_corner_color_rgba (pattern, nth_corner,
                                                red, green, blue, alpha);
    }
  cr_pattern_check_status (pattern);
  return self;
}

static VALUE
cr_mesh_pattern_get_patch_count (VALUE self)
{
  cairo_pattern_t *pattern;
  unsigned int count;
  cairo_status_t status;

  pattern = _SELF (self);
  status = cairo_mesh_pattern_get_patch_count (pattern, &count);
  rb_cairo_check_status (status);
  return UINT2NUM (count);
}

static VALUE
cr_mesh_pattern_get_path (VALUE self, VALUE nth_patch)
{
  cairo_pattern_t *pattern;
  cairo_path_t *path;

  pattern = _SELF (self);
  path = cairo_mesh_pattern_get_path (pattern, NUM2UINT (nth_patch));
  rb_cairo_check_status (path->status);
  return CRPATH2RVAL (path);
}

static VALUE
cr_mesh_pattern_get_corner_color (VALUE self,
                                  VALUE rb_nth_patch, VALUE rb_nth_corner)
{
  cairo_pattern_t *pattern;
  unsigned int nth_patch, nth_corner;
  double red, green, blue, alpha;
  cairo_status_t status;

  nth_patch = NUM2UINT (rb_nth_patch);
  nth_corner = NUM2UINT (rb_nth_corner);
  if (nth_corner > 3)
    {
      VALUE inspected;

      inspected = rb_funcall (rb_ary_new3 (2, rb_nth_patch, rb_nth_corner),
                              id_inspect, 0);
      rb_raise (rb_eArgError, "nth_corner must be 0, 1, 2 or 3: <%u>: <%s>",
                nth_corner, RVAL2CSTR (inspected));
    }

  pattern = _SELF (self);
  status = cairo_mesh_pattern_get_corner_color_rgba (pattern,
                                                     nth_patch, nth_corner,
                                                     &red,
                                                     &green,
                                                     &blue,
                                                     &alpha);
  rb_cairo_check_status (status);
  return rb_ary_new3 (4,
                      rb_float_new (red), rb_float_new (green),
                      rb_float_new (blue), rb_float_new (alpha));
}

static VALUE
cr_mesh_pattern_get_control_point (VALUE self,
                                   VALUE rb_nth_patch, VALUE rb_nth_point)
{
  cairo_pattern_t *pattern;
  unsigned int nth_patch, nth_point;
  double x, y;
  cairo_status_t status;

  nth_patch = NUM2UINT (rb_nth_patch);
  nth_point = NUM2UINT (rb_nth_point);
  if (nth_point > 3)
    {
      VALUE inspected;

      inspected = rb_funcall (rb_ary_new3 (2, rb_nth_patch, rb_nth_point),
                              id_inspect, 0);
      rb_raise (rb_eArgError, "nth_point must be 0, 1, 2 or 3: <%u>: <%s>",
                nth_point, RVAL2CSTR (inspected));
    }

  pattern = _SELF (self);
  status = cairo_mesh_pattern_get_control_point (pattern,
                                                 nth_patch, nth_point,
                                                 &x, &y);
  rb_cairo_check_status (status);
  return rb_ary_new3 (2, rb_float_new (x), rb_float_new (y));
}
#endif

#ifdef RB_CAIRO_HAS_RASTER_SOURCE_PATTERN
/* Cairo::RasterSourcePattern */
static cairo_surface_t *
cr_raster_source_acquire_callback (cairo_pattern_t *pattern,
                                   void *callback_data,
                                   cairo_surface_t *target,
                                   const cairo_rectangle_int_t *extents)
{
  VALUE rb_pattern;
  VALUE rb_acquire;
  cairo_surface_t *acquired_surface = NULL;

  rb_pattern = POINTER2RVAL (callback_data);
  rb_acquire = rb_iv_get (rb_pattern, "@acquire");
  if (!NIL_P (rb_acquire))
    {
      VALUE rb_acquired_surface;
      VALUE rb_target;
      VALUE rb_extents;

      rb_target = CRSURFACE2RVAL (target);
      rb_extents = rb_funcall (rb_cCairo_Rectangle, id_new, 4,
                               INT2NUM (extents->x),
                               INT2NUM (extents->y),
                               INT2NUM (extents->width),
                               INT2NUM (extents->height));
      rb_acquired_surface = rb_funcall (rb_acquire, id_call, 3,
                                        rb_pattern, rb_target, rb_extents);
      if (!NIL_P (rb_acquired_surface))
        acquired_surface = RVAL2CRSURFACE (rb_acquired_surface);
    }

  return acquired_surface;
}

static void
cr_raster_source_release_callback (cairo_pattern_t *pattern,
                                   void *callback_data,
                                   cairo_surface_t *surface)
{
  VALUE rb_pattern;
  VALUE rb_release;
  VALUE rb_surface;

  rb_pattern = POINTER2RVAL (callback_data);
  rb_release = rb_iv_get (rb_pattern, "@release");
  if (NIL_P (rb_release))
    return;

  rb_surface = CRSURFACE2RVAL (surface);
  rb_funcall (rb_release, id_call, 2, rb_pattern, rb_surface);
}

typedef struct cr_raster_source_notify_callback_data
{
  VALUE pattern;
  VALUE callback;
  cairo_status_t status;
} cr_raster_source_notify_callback_data_t;

static VALUE
cr_raster_source_notify_callback_body (VALUE data)
{
  cr_raster_source_notify_callback_data_t* callback_data;

  callback_data = RVAL2POINTER (data);
  rb_funcall (callback_data->callback, id_call, 1, callback_data->pattern);
  return Qnil;
}

static VALUE
cr_raster_source_notify_callback_rescue (VALUE data, VALUE exception)
{
  cr_raster_source_notify_callback_data_t *callback_data;

  callback_data = RVAL2POINTER (data);
  callback_data->status = rb_cairo__exception_to_status (exception);

  if (callback_data->status == (cairo_status_t)-1)
    rb_exc_raise (exception);

  return Qnil;
}

static cairo_status_t
cr_raster_source_snapshot_callback (cairo_pattern_t *pattern,
                                    void *callback_data)
{
  VALUE rb_pattern;
  VALUE rb_snapshot;
  cr_raster_source_notify_callback_data_t data;

  rb_pattern = POINTER2RVAL (callback_data);
  rb_snapshot = rb_iv_get (rb_pattern, "@snapshot");
  if (NIL_P (rb_snapshot))
    return CAIRO_STATUS_SUCCESS;

  data.pattern = rb_pattern;
  data.callback = rb_snapshot;
  data.status = CAIRO_STATUS_SUCCESS;
  rb_rescue2 (cr_raster_source_notify_callback_body,
              POINTER2RVAL (&data),
              cr_raster_source_notify_callback_rescue,
              POINTER2RVAL (&data),
              rb_eException);
  return data.status;
}

static cairo_status_t
cr_raster_source_copy_callback (cairo_pattern_t *pattern,
                                void *callback_data,
                                const cairo_pattern_t *other)
{
  VALUE rb_pattern;
  VALUE rb_copy;
  cr_raster_source_notify_callback_data_t data;

  rb_pattern = POINTER2RVAL (callback_data);
  rb_copy = rb_iv_get (rb_pattern, "@copy");
  if (NIL_P (rb_copy))
    return CAIRO_STATUS_SUCCESS;

  data.pattern = rb_pattern;
  data.callback = rb_copy;
  data.status = CAIRO_STATUS_SUCCESS;
  rb_rescue2 (cr_raster_source_notify_callback_body,
              POINTER2RVAL (&data),
              cr_raster_source_notify_callback_rescue,
              POINTER2RVAL (&data),
              rb_eException);
  return data.status;
}

static void
cr_raster_source_finish_callback (cairo_pattern_t *pattern, void *callback_data)
{
  VALUE rb_pattern;
  VALUE rb_finish;

  rb_pattern = POINTER2RVAL (callback_data);
  rb_finish = rb_iv_get (rb_pattern, "@finish");
  if (NIL_P (rb_finish))
    return;

  rb_funcall (rb_finish, id_call, 1, rb_pattern);
}

static VALUE
cr_raster_source_pattern_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_pattern_t *pattern;
  cairo_content_t content;
  int width, height;
  VALUE arg1, arg2, arg3;

  rb_scan_args (argc, argv, "21", &arg1, &arg2, &arg3);

  if (argc == 2)
    {
      content = CAIRO_CONTENT_COLOR_ALPHA;
      width = NUM2INT (arg1);
      height = NUM2INT (arg2);
    }
  else
    {
      content = RVAL2CRCONTENT (arg1);
      width = NUM2INT (arg2);
      height = NUM2INT (arg3);
    }

  pattern = cairo_pattern_create_raster_source (RVAL2POINTER (self),
                                                content, width, height);
  cr_pattern_check_status (pattern);

  DATA_PTR (self) = pattern;
  rb_iv_set (self, "@acquire", Qnil);
  rb_iv_set (self, "@release", Qnil);
  rb_iv_set (self, "@snapshot", Qnil);
  rb_iv_set (self, "@copy", Qnil);
  rb_iv_set (self, "@finish", Qnil);

  cairo_raster_source_pattern_set_acquire (pattern,
                                           cr_raster_source_acquire_callback,
                                           cr_raster_source_release_callback);
  cairo_raster_source_pattern_set_snapshot (pattern,
                                            cr_raster_source_snapshot_callback);
  cairo_raster_source_pattern_set_copy (pattern,
                                        cr_raster_source_copy_callback);
  cairo_raster_source_pattern_set_finish (pattern,
                                          cr_raster_source_finish_callback);

  return Qnil;
}

static VALUE
cr_raster_source_pattern_acquire (VALUE self)
{
  if (!rb_block_given_p ())
    {
      VALUE inspected;

      inspected = rb_funcall (self, id_inspect, 0);
      rb_raise (rb_eArgError, "acquire block is missing: %s",
                RVAL2CSTR (inspected));
    }

  rb_iv_set (self, "@acquire", rb_block_proc ());

  return self;
}

static VALUE
cr_raster_source_pattern_release (VALUE self)
{
  if (!rb_block_given_p ())
    {
      VALUE inspected;

      inspected = rb_funcall (self, id_inspect, 0);
      rb_raise (rb_eArgError, "release block is missing: %s",
                RVAL2CSTR (inspected));
    }

  rb_iv_set (self, "@release", rb_block_proc ());

  return self;
}

static VALUE
cr_raster_source_pattern_snapshot (VALUE self)
{
  if (!rb_block_given_p ())
    {
      VALUE inspected;

      inspected = rb_funcall (self, id_inspect, 0);
      rb_raise (rb_eArgError, "snapshot block is missing: %s",
                RVAL2CSTR (inspected));
    }

  rb_iv_set (self, "@snapshot", rb_block_proc ());

  return self;
}

static VALUE
cr_raster_source_pattern_copy (VALUE self)
{
  if (!rb_block_given_p ())
    {
      VALUE inspected;

      inspected = rb_funcall (self, id_inspect, 0);
      rb_raise (rb_eArgError, "copy block is missing: %s",
                RVAL2CSTR (inspected));
    }

  rb_iv_set (self, "@copy", rb_block_proc ());

  return self;
}

static VALUE
cr_raster_source_pattern_finish (VALUE self)
{
  if (!rb_block_given_p ())
    {
      VALUE inspected;

      inspected = rb_funcall (self, id_inspect, 0);
      rb_raise (rb_eArgError, "finish block is missing: %s",
                RVAL2CSTR (inspected));
    }

  rb_iv_set (self, "@finish", rb_block_proc ());

  return self;
}
#endif

void
Init_cairo_pattern (void)
{
  id_parse = rb_intern ("parse");
  id_to_rgb = rb_intern ("to_rgb");
  id_to_a = rb_intern ("to_a");
  id_inspect = rb_intern ("inspect");
  id_new = rb_intern ("new");
  id_call = rb_intern ("call");

  rb_cCairo_Pattern =
    rb_define_class_under (rb_mCairo, "Pattern", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Pattern, cr_pattern_allocate);

  rb_define_singleton_method (rb_cCairo_Pattern, "solid_supported?",
                              cr_pattern_solid_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Pattern, "surface_supported?",
                              cr_pattern_surface_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Pattern, "gradient_supported?",
                              cr_pattern_gradient_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Pattern, "linear_supported?",
                              cr_pattern_linear_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Pattern, "radial_supported?",
                              cr_pattern_radial_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Pattern, "mesh_supported?",
                              cr_pattern_mesh_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Pattern, "raster_source_supported?",
                              cr_pattern_raster_source_supported_p, 0);

  rb_define_method (rb_cCairo_Pattern, "initialize", cr_pattern_initialize, -1);

  rb_define_method (rb_cCairo_Pattern, "set_matrix", cr_pattern_set_matrix, 1);
  rb_define_method (rb_cCairo_Pattern, "matrix", cr_pattern_get_matrix, 0);
  rb_define_method (rb_cCairo_Pattern, "set_extend", cr_pattern_set_extend, 1);
  rb_define_alias (rb_cCairo_Pattern, "__extend__", "extend");
  rb_define_method (rb_cCairo_Pattern, "extend", cr_pattern_get_extend, 0);
  rb_define_method (rb_cCairo_Pattern, "set_filter", cr_pattern_set_filter, 1);
  rb_define_method (rb_cCairo_Pattern, "filter", cr_pattern_get_filter, 0);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_Pattern);

  rb_cCairo_SolidPattern =
    rb_define_class_under (rb_mCairo, "SolidPattern", rb_cCairo_Pattern);

  rb_define_method (rb_cCairo_SolidPattern, "initialize",
                    cr_solid_pattern_initialize, -1);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_SolidPattern, "rgba",
                    cr_solid_pattern_get_rgba, 0);
  rb_define_method (rb_cCairo_SolidPattern, "color",
                    cr_solid_pattern_get_color, 0);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_SolidPattern);

  rb_cCairo_SurfacePattern =
    rb_define_class_under (rb_mCairo, "SurfacePattern", rb_cCairo_Pattern);

  rb_define_method (rb_cCairo_SurfacePattern, "initialize",
                    cr_surface_pattern_initialize, 1);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_SurfacePattern, "surface",
                    cr_surface_pattern_get_surface, 0);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_SurfacePattern);

  rb_cCairo_GradientPattern =
    rb_define_class_under (rb_mCairo, "GradientPattern", rb_cCairo_Pattern);

  rb_define_method (rb_cCairo_GradientPattern, "add_color_stop",
                    cr_gradient_pattern_add_color_stop_generic, -1);
  rb_define_alias (rb_cCairo_GradientPattern,
                   "add_color_stop_rgb", "add_color_stop");
  rb_define_alias (rb_cCairo_GradientPattern,
                   "add_color_stop_rgba", "add_color_stop");
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_GradientPattern, "get_color_stop_rgba",
                    cr_gradient_pattern_get_color_stop_rgba, 1);
  rb_define_method (rb_cCairo_GradientPattern, "get_color_stop_color",
                    cr_gradient_pattern_get_color_stop_color, 1);
  rb_define_method (rb_cCairo_GradientPattern, "color_stop_count",
                    cr_gradient_pattern_get_color_stop_count, 0);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_GradientPattern);

  rb_cCairo_LinearPattern =
    rb_define_class_under (rb_mCairo, "LinearPattern",
                           rb_cCairo_GradientPattern);

  rb_define_method (rb_cCairo_LinearPattern, "initialize",
                    cr_linear_pattern_initialize, 4);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_LinearPattern, "points",
                    cr_linear_pattern_get_linear_points, 0);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_LinearPattern);

  rb_cCairo_RadialPattern =
    rb_define_class_under (rb_mCairo, "RadialPattern",
                           rb_cCairo_GradientPattern);

  rb_define_method (rb_cCairo_RadialPattern, "initialize",
                    cr_radial_pattern_initialize, 6);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_method (rb_cCairo_RadialPattern, "circles",
                    cr_radial_pattern_get_radial_circles, 0);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_RadialPattern);

  rb_cCairo_MeshPattern =
    rb_define_class_under (rb_mCairo, "MeshPattern",
                           rb_cCairo_Pattern);
#ifdef RB_CAIRO_HAS_MESH_PATTERN
  rb_define_method (rb_cCairo_MeshPattern, "initialize",
                    cr_mesh_pattern_initialize, 0);
  rb_define_method (rb_cCairo_MeshPattern, "begin_patch",
                    cr_mesh_pattern_begin_patch, 0);
  rb_define_method (rb_cCairo_MeshPattern, "end_patch",
                    cr_mesh_pattern_end_patch, 0);
  rb_define_method (rb_cCairo_MeshPattern, "curve_to",
                    cr_mesh_pattern_curve_to, 6);
  rb_define_method (rb_cCairo_MeshPattern, "line_to",
                    cr_mesh_pattern_line_to, 2);
  rb_define_method (rb_cCairo_MeshPattern, "move_to",
                    cr_mesh_pattern_move_to, 2);
  rb_define_method (rb_cCairo_MeshPattern, "set_control_point",
                    cr_mesh_pattern_set_control_point, 3);
  rb_define_method (rb_cCairo_MeshPattern, "set_corner_color",
                    cr_mesh_pattern_set_corner_color_generic, -1);
  rb_define_alias (rb_cCairo_MeshPattern,
                   "set_corner_color_rgb", "set_corner_color");
  rb_define_alias (rb_cCairo_MeshPattern,
                   "set_corner_color_rgba", "set_corner_color");
  rb_define_method (rb_cCairo_MeshPattern, "patch_count",
                    cr_mesh_pattern_get_patch_count, 0);
  rb_define_method (rb_cCairo_MeshPattern, "get_path",
                    cr_mesh_pattern_get_path, 1);
  rb_define_method (rb_cCairo_MeshPattern, "get_corner_color",
                    cr_mesh_pattern_get_corner_color, 2);
  rb_define_method (rb_cCairo_MeshPattern, "get_control_point",
                    cr_mesh_pattern_get_control_point, 2);
#endif
  RB_CAIRO_DEF_SETTERS (rb_cCairo_MeshPattern);

  rb_cCairo_RasterSourcePattern =
    rb_define_class_under (rb_mCairo, "RasterSourcePattern",
                           rb_cCairo_Pattern);
#ifdef RB_CAIRO_HAS_RASTER_SOURCE_PATTERN
  rb_define_method (rb_cCairo_RasterSourcePattern, "initialize",
                    cr_raster_source_pattern_initialize, -1);
  rb_define_method (rb_cCairo_RasterSourcePattern, "acquire",
                    cr_raster_source_pattern_acquire, 0);
  rb_define_method (rb_cCairo_RasterSourcePattern, "release",
                    cr_raster_source_pattern_release, 0);
  rb_define_method (rb_cCairo_RasterSourcePattern, "snapshot",
                    cr_raster_source_pattern_snapshot, 0);
  rb_define_method (rb_cCairo_RasterSourcePattern, "copy",
                    cr_raster_source_pattern_copy, 0);
  rb_define_method (rb_cCairo_RasterSourcePattern, "finish",
                    cr_raster_source_pattern_finish, 0);
#endif
  RB_CAIRO_DEF_SETTERS (rb_cCairo_RasterSourcePattern);
}
