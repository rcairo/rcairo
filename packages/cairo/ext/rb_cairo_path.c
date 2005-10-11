/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2005-10-11 13:23:49 $
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"

#define _SELF(self) (RVAL2CRPATH (self))

VALUE rb_cCairo_Path;

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
      cairo_path_destroy ((cairo_path_t *) ptr);
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
cr_path_each (VALUE self)
{
  cairo_path_t *path = _SELF(self);
  int i, j;
  
  for (i = 0; i < path->num_data; i += path->data[i].header.length)
    {
      cairo_path_data_t *data = &(path->data[i]);
      cairo_path_data_type_t type;
      VALUE points;

      type = RVAL2CRPATHDATATYPE (data->header.type);
      points = rb_ary_new ();

      for (j = 1; j < data->header.length; j++)
        {
          rb_ary_push (points, rb_ary_new3 (2,
                                            rb_float_new (data[j].point.x),
                                            rb_float_new (data[j].point.y)));
        }
      rb_yield_values (2, type, points);
    }

  return self;
}


void
Init_cairo_path (void)
{
  rb_cCairo_Path = rb_define_class_under (rb_mCairo, "Path", rb_cObject);

  rb_include_module (rb_cCairo_Path, rb_mEnumerable);

  rb_define_method (rb_cCairo_Path, "each", cr_path_each, 0);
}
