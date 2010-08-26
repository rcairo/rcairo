/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-04-04 03:52:31 $
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"

#define _SELF(self) (RVAL2CRPATH (self))

VALUE rb_cCairo_Point;
VALUE rb_cCairo_Path;
VALUE rb_cCairo_PathData;
VALUE rb_cCairo_PathMoveTo;
VALUE rb_cCairo_PathLineTo;
VALUE rb_cCairo_PathCurveTo;
VALUE rb_cCairo_PathClosePath;

static ID id_new, id_current_path;
static ID id_at_x, id_at_y, id_at_type, id_at_points, id_at_context;

static VALUE
cr_point_new (VALUE x, VALUE y)
{
  return rb_funcall (rb_cCairo_Point, id_new, 2, x, y);
}

static VALUE
cr_point_initialize (VALUE self, VALUE x, VALUE y)
{
  rb_ivar_set (self, id_at_x, x);
  rb_ivar_set (self, id_at_y, y);
  return Qnil;
}

static VALUE
cr_point_to_a (VALUE self)
{
  return rb_ary_new3 (2,
                      rb_ivar_get (self, id_at_x),
                      rb_ivar_get (self, id_at_y));
}

static VALUE
cr_path_data_initialize (VALUE self, VALUE type, VALUE points)
{
  rb_ivar_set (self, id_at_type, type);
  rb_ivar_set (self, id_at_points, points);
  return Qnil;
}

static VALUE
cr_path_data_move_to_p (VALUE self)
{
  return CBOOL2RVAL (RVAL2CRPATHDATATYPE (rb_ivar_get (self, id_at_type)) ==
                     CAIRO_PATH_MOVE_TO);
}

static VALUE
cr_path_data_line_to_p (VALUE self)
{
  return CBOOL2RVAL (RVAL2CRPATHDATATYPE (rb_ivar_get (self, id_at_type)) ==
                     CAIRO_PATH_LINE_TO);
}

static VALUE
cr_path_data_curve_to_p (VALUE self)
{
  return CBOOL2RVAL (RVAL2CRPATHDATATYPE (rb_ivar_get (self, id_at_type)) ==
                     CAIRO_PATH_CURVE_TO);
}

static VALUE
cr_path_data_close_path_p (VALUE self)
{
  return CBOOL2RVAL (RVAL2CRPATHDATATYPE (rb_ivar_get (self, id_at_type)) ==
                     CAIRO_PATH_CLOSE_PATH);
}

static VALUE
cr_path_data_each (VALUE self)
{
  return rb_ary_each (rb_ivar_get (self, id_at_points));
}


static VALUE
cr_path_data_to_a (VALUE self)
{
  return rb_ary_new3 (2,
                      rb_ivar_get (self, id_at_type),
                      rb_ivar_get (self, id_at_points));
}

static VALUE
cr_path_data_to_ruby_object (cairo_path_data_t *data)
{
  VALUE rb_data = Qnil;

  switch (data->header.type)
    {
    case CAIRO_PATH_MOVE_TO:
      rb_data = rb_funcall (rb_cCairo_PathMoveTo, id_new, 2,
                            rb_float_new (data[1].point.x),
                            rb_float_new (data[1].point.y));
      break;
    case CAIRO_PATH_LINE_TO:
      rb_data = rb_funcall (rb_cCairo_PathLineTo, id_new, 2,
                            rb_float_new (data[1].point.x),
                            rb_float_new (data[1].point.y));
      break;
    case CAIRO_PATH_CURVE_TO:
      rb_data = rb_funcall (rb_cCairo_PathCurveTo, id_new, 6,
                            rb_float_new (data[1].point.x),
                            rb_float_new (data[1].point.y),
                            rb_float_new (data[2].point.x),
                            rb_float_new (data[2].point.y),
                            rb_float_new (data[3].point.x),
                            rb_float_new (data[3].point.y));
      break;
    case CAIRO_PATH_CLOSE_PATH:
      rb_data = rb_funcall (rb_cCairo_PathClosePath, id_new, 0);
      break;
    }

  return rb_data;
}


static VALUE
cr_path_move_to_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE point, x, y;
  VALUE super_argv[2];

  rb_scan_args (argc, argv, "11", &x, &y);

  if (argc == 1)
    point = x;
  else
    point = cr_point_new (x, y);

  super_argv[0] = INT2NUM (CAIRO_PATH_MOVE_TO);
  super_argv[1] = rb_ary_new3 (1, point);
  rb_call_super (2, super_argv);
  return Qnil;
}

static VALUE
cr_path_line_to_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE point, x, y;
  VALUE super_argv[2];

  rb_scan_args (argc, argv, "11", &x, &y);

  if (argc == 1)
    point = x;
  else
    point = cr_point_new (x, y);

  super_argv[0] = INT2NUM (CAIRO_PATH_LINE_TO);
  super_argv[1] = rb_ary_new3 (1, point);
  rb_call_super (2, super_argv);
  return Qnil;
}

static VALUE
cr_path_curve_to_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE point1, point2, point3, x1, y1, x2, y2, x3, y3;
  VALUE super_argv[2];

  rb_scan_args (argc, argv, "33", &x1, &y1, &x2, &y2, &x3, &y3);

  if (argc == 3)
    {
      point1 = x1;
      point2 = y1;
      point3 = x2;
    }
  else if (argc == 6)
    {
      point1 = cr_point_new (x1, y1);
      point2 = cr_point_new (x2, y2);
      point3 = cr_point_new (x3, y3);
    }
  else
    {
      VALUE inspected_arg = rb_inspect (rb_ary_new4 (argc, argv));
      rb_raise (rb_eArgError,
                "invalid argument: %s (expect "
                "(point1, point2, point3) or "
                "(x1, y1, x2, y2, x3, y3))",
                StringValuePtr (inspected_arg));
    }

  super_argv[0] = INT2NUM (CAIRO_PATH_CURVE_TO);
  super_argv[1] = rb_ary_new3 (3, point1, point2, point3);
  rb_call_super (2, super_argv);
  return Qnil;
}

static VALUE
cr_path_close_path_initialize (VALUE self)
{
  VALUE super_argv[2];
  super_argv[0] = INT2NUM (CAIRO_PATH_CLOSE_PATH);
  super_argv[1] = rb_ary_new ();
  rb_call_super (2, super_argv);
  return Qnil;
}


static void
cr_path_free (void *ptr)
{
  if (ptr)
    {
      cairo_path_destroy ((cairo_path_t *)ptr);
    }
}

cairo_path_t *
rb_cairo_path_from_ruby_object (VALUE obj)
{
  VALUE context;
  cairo_t *cr;
  cairo_path_t *path, *copied_path;

  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Path))
    {
      rb_raise (rb_eTypeError, "not a cairo path");
    }
  Data_Get_Struct (obj, cairo_path_t, path);

  context = rb_ivar_get (obj, id_at_context);
  if (NIL_P (context))
    return path;

  cr = RVAL2CRCONTEXT (context);
  if (cairo_status (cr) != CAIRO_STATUS_SUCCESS)
    return path;

  copied_path = cairo_copy_path (cr);
  rb_ivar_set (obj, id_current_path, CRPATH2RVAL (copied_path));
  return copied_path;
}

static void
cr_path_ensure_internal_context (VALUE rb_path, cairo_path_t *path)
{
  cairo_surface_t *surface;
  cairo_t *cr;

  if (!NIL_P (rb_ivar_get (rb_path, id_at_context)))
    return;

  surface = cairo_image_surface_create (CAIRO_FORMAT_A1, 1, 1);
  cr = cairo_create (surface);
  if (path->num_data > 0)
    cairo_append_path (cr, path);
  rb_cairo_check_status (cairo_status (cr));
  rb_ivar_set (rb_path, id_at_context, CRCONTEXT2RVAL (cr));
  cairo_destroy (cr);
}

VALUE
rb_cairo_path_to_ruby_object (cairo_path_t *path)
{
  if (path)
    {
      VALUE rb_path;
      rb_path = Data_Wrap_Struct (rb_cCairo_Path, NULL, cr_path_free, path);
      cr_path_ensure_internal_context (rb_path, path);
      return rb_path;
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_path_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_path_free, NULL);
}

static VALUE
cr_path_initialize (VALUE self)
{
  cairo_path_t *path;

  path = ALLOC(cairo_path_t);
  path->status = CAIRO_STATUS_SUCCESS;
  path->data = NULL;
  path->num_data = 0;

  DATA_PTR (self) = path;
  cr_path_ensure_internal_context (self, path);

  return Qnil;
}

static VALUE
cr_path_empty_p (VALUE self)
{
  cairo_path_t *path = _SELF (self);

  return CBOOL2RVAL (path->num_data == 0);
}

static int
cairo_path_get_size (cairo_path_t *path)
{
  int i, size;

  for (i = 0, size = 0; i < path->num_data; i += path->data[i].header.length)
    size++;

  return size;
}

static VALUE
cr_path_size (VALUE self)
{
  cairo_path_t *path = _SELF (self);
  return INT2NUM (cairo_path_get_size (path));
}

static VALUE
cr_path_ref (VALUE self, VALUE index)
{
  cairo_path_t *path = _SELF (self);
  int i, requested_index, real_index;

  requested_index = NUM2INT (index);
  if (requested_index < 0)
    {
      requested_index += cairo_path_get_size (path);
      if (requested_index < 0)
        return Qnil;
    }


  for (i = 0, real_index = 0; i < requested_index; i++)
    {
      if (real_index >= path->num_data)
        return Qnil;
      real_index += path->data[real_index].header.length;
    }

  if (real_index < path->num_data)
    return cr_path_data_to_ruby_object (&path->data[real_index]);
  else
    return Qnil;
}

static VALUE
cr_path_each (VALUE self)
{
  cairo_path_t *path = _SELF(self);
  int i;

  for (i = 0; i < path->num_data; i += path->data[i].header.length)
    {
      rb_yield (cr_path_data_to_ruby_object (&(path->data[i])));
    }

  return self;
}

void
Init_cairo_path (void)
{
  id_new = rb_intern ("new");
  id_current_path = rb_intern ("current_path");

  id_at_x = rb_intern ("@x");
  id_at_y = rb_intern ("@y");
  id_at_type = rb_intern ("@type");
  id_at_points = rb_intern ("@points");
  id_at_context = rb_intern ("@context");

  rb_cCairo_Point = rb_define_class_under (rb_mCairo, "Point", rb_cObject);
  rb_define_attr (rb_cCairo_Point, "x", CR_TRUE, CR_FALSE);
  rb_define_attr (rb_cCairo_Point, "y", CR_TRUE, CR_FALSE);
  rb_define_method (rb_cCairo_Point, "initialize", cr_point_initialize, 2);

  rb_define_method (rb_cCairo_Point, "to_a", cr_point_to_a, 0);
  rb_define_alias (rb_cCairo_Point, "to_ary", "to_a");


  rb_cCairo_PathData = rb_define_class_under (rb_mCairo, "PathData", rb_cObject);

  rb_include_module (rb_cCairo_PathData, rb_mEnumerable);

  rb_define_attr (rb_cCairo_PathData, "type", CR_TRUE, CR_FALSE);
  rb_define_attr (rb_cCairo_PathData, "points", CR_TRUE, CR_FALSE);
  rb_define_method (rb_cCairo_PathData, "initialize",
                    cr_path_data_initialize, 2);

  rb_define_method (rb_cCairo_PathData, "move_to?", cr_path_data_move_to_p, 0);
  rb_define_method (rb_cCairo_PathData, "line_to?", cr_path_data_line_to_p, 0);
  rb_define_method (rb_cCairo_PathData, "curve_to?",
                    cr_path_data_curve_to_p, 0);
  rb_define_method (rb_cCairo_PathData, "close_path?",
                    cr_path_data_close_path_p, 0);

  rb_define_method (rb_cCairo_PathData, "each", cr_path_data_each, 0);

  rb_define_method (rb_cCairo_PathData, "to_a", cr_path_data_to_a, 0);
  rb_define_alias (rb_cCairo_PathData, "to_ary", "to_a");


  rb_cCairo_PathMoveTo =
    rb_define_class_under (rb_mCairo, "PathMoveTo", rb_cCairo_PathData);
  rb_define_method (rb_cCairo_PathMoveTo, "initialize",
                    cr_path_move_to_initialize, -1);

  rb_cCairo_PathLineTo =
    rb_define_class_under (rb_mCairo, "PathLineTo", rb_cCairo_PathData);
  rb_define_method (rb_cCairo_PathLineTo, "initialize",
                    cr_path_line_to_initialize, -1);

  rb_cCairo_PathCurveTo =
    rb_define_class_under (rb_mCairo, "PathCurveTo", rb_cCairo_PathData);
  rb_define_method (rb_cCairo_PathCurveTo, "initialize",
                    cr_path_curve_to_initialize, -1);

  rb_cCairo_PathClosePath =
    rb_define_class_under (rb_mCairo, "PathClosePath", rb_cCairo_PathData);
  rb_define_method (rb_cCairo_PathClosePath, "initialize",
                    cr_path_close_path_initialize, 0);


  rb_cCairo_Path = rb_define_class_under (rb_mCairo, "Path", rb_cObject);
  rb_define_alloc_func (rb_cCairo_Path, cr_path_allocate);

  rb_include_module (rb_cCairo_Path, rb_mEnumerable);

  rb_define_method (rb_cCairo_Path, "initialize", cr_path_initialize, 0);

  rb_define_method (rb_cCairo_Path, "empty?", cr_path_empty_p, 0);
  rb_define_method (rb_cCairo_Path, "size", cr_path_size, 0);
  rb_define_alias (rb_cCairo_Path, "length", "size");
  rb_define_method (rb_cCairo_Path, "[]", cr_path_ref, 1);

  rb_define_method (rb_cCairo_Path, "each", cr_path_each, 0);
}
