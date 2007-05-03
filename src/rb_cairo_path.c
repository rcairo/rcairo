/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-05-03 02:03:06 $
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

static ID id_new, id_x, id_y, id_type, id_points;

static VALUE
cr_point_initialize (VALUE self, VALUE x, VALUE y)
{
  rb_ivar_set (self, id_x, x);
  rb_ivar_set (self, id_y, y);
  return Qnil;
}

static VALUE
cr_point_to_a (VALUE self)
{
  return rb_ary_new3 (2, rb_ivar_get (self, id_x), rb_ivar_get (self, id_y));
}

static VALUE
cr_path_data_initialize (VALUE self, VALUE type, VALUE points)
{
  rb_ivar_set (self, id_type, type);
  rb_ivar_set (self, id_points, points);
  return Qnil;
}

static VALUE
cr_path_data_to_a (VALUE self)
{
  return rb_ary_new3 (2,
                      rb_ivar_get (self, id_type),
                      rb_ivar_get (self, id_points));
}

static VALUE
cr_path_data_to_ruby_object (cairo_path_data_t *data)
{
  int i;
  VALUE points;

  points = rb_ary_new ();
  for (i = 1; i < data->header.length; i++)
    {
      rb_ary_push (points, rb_funcall (rb_cCairo_Point, id_new, 2,
                                       rb_float_new (data[i].point.x),
                                       rb_float_new (data[i].point.y)));
    }

  return rb_funcall (rb_cCairo_PathData, id_new, 2,
                     INT2FIX (data->header.type), points);
}

cairo_path_t *
rb_cairo_path_from_ruby_object (VALUE obj)
{
  cairo_path_t *path;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_Path)))
    {
      rb_raise (rb_eTypeError, "not a cairo path");
    }
  Data_Get_Struct (obj, cairo_path_t, path);
  return path;
}

static void
cr_path_free (void *ptr)
{
  if (ptr)
    {
      cairo_path_destroy ((cairo_path_t *)ptr);
    }
}

VALUE
rb_cairo_path_to_ruby_object (cairo_path_t *path)
{
  if (path)
    {
      return Data_Wrap_Struct (rb_cCairo_Path, NULL, cr_path_free, path);
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

static VALUE
cr_path_ref (VALUE self, VALUE index)
{
  cairo_path_t *path = _SELF(self);
  int i, requested_index, real_index;

#warning FIXME: support negative index
  requested_index = NUM2INT(index);
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

void
Init_cairo_path (void)
{
  id_new = rb_intern ("new");

  id_x = rb_intern ("@x");
  id_y = rb_intern ("@y");
  id_type = rb_intern ("@type");
  id_points = rb_intern ("@points");

  rb_cCairo_Point = rb_define_class_under (rb_mCairo, "Point", rb_cObject);
  rb_define_attr (rb_cCairo_Point, "x", CR_TRUE, CR_FALSE);
  rb_define_attr (rb_cCairo_Point, "y", CR_TRUE, CR_FALSE);
  rb_define_method (rb_cCairo_Point, "initialize", cr_point_initialize, 2);

  rb_define_method (rb_cCairo_Point, "to_a", cr_point_to_a, 0);
  rb_define_alias (rb_cCairo_Point, "to_ary", "to_a");


  rb_cCairo_PathData = rb_define_class_under (rb_mCairo, "PathData", rb_cObject);

  rb_define_attr (rb_cCairo_PathData, "type", CR_TRUE, CR_FALSE);
  rb_define_attr (rb_cCairo_PathData, "points", CR_TRUE, CR_FALSE);
  rb_define_method (rb_cCairo_PathData, "initialize",
                    cr_path_data_initialize, 2);

  rb_define_method (rb_cCairo_PathData, "to_a", cr_path_data_to_a, 0);
  rb_define_alias (rb_cCairo_PathData, "to_ary", "to_a");


  rb_cCairo_Path = rb_define_class_under (rb_mCairo, "Path", rb_cObject);
  rb_define_alloc_func (rb_cCairo_Path, cr_path_allocate);

  rb_include_module (rb_cCairo_Path, rb_mEnumerable);

  rb_define_method (rb_cCairo_Path, "initialize", cr_path_initialize, 0);

  rb_define_method (rb_cCairo_Path, "[]", cr_path_ref, 1);

  rb_define_method (rb_cCairo_Path, "each", cr_path_each, 0);
}
