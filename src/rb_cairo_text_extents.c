/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-17 05:41:28 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_TextExtents;

#define _SELF(self)  (RVAL2CRTEXTEXTENTS(self))

cairo_text_extents_t *
rb_cairo_text_extents_from_ruby_object (VALUE obj)
{
  cairo_text_extents_t *extents;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_TextExtents))
    {
      rb_raise (rb_eTypeError, "not a cairo text_extents");
    }
  Data_Get_Struct (obj, cairo_text_extents_t, extents);
  return extents;
}

VALUE
rb_cairo_text_extents_to_ruby_object (cairo_text_extents_t *extents)
{
  if (extents)
    {
      cairo_text_extents_t *new_extents = ALLOC (cairo_text_extents_t);
      *new_extents = *extents;
      return Data_Wrap_Struct (rb_cCairo_TextExtents, NULL, -1, new_extents);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_text_extents_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, -1, NULL);
}

static VALUE
cr_text_extents_initialize (VALUE self)
{
  cairo_text_extents_t *extents;

  extents = ALLOC (cairo_text_extents_t);
  extents->x_bearing = 0.0;
  extents->y_bearing = -1.0;
  extents->width = 0.0;
  extents->height = 1.0;
  extents->x_advance = 1.0;
  extents->y_advance = 0.0;

  DATA_PTR (self) = extents;

  return Qnil;
}

static VALUE
cr_text_extents_x_bearing (VALUE self)
{
  return rb_float_new (_SELF(self)->x_bearing);
}

static VALUE
cr_text_extents_set_x_bearing (VALUE self, VALUE x_bearing)
{
  _SELF(self)->x_bearing = NUM2DBL (x_bearing);
  return Qnil;
}

static VALUE
cr_text_extents_y_bearing (VALUE self)
{
  return rb_float_new (_SELF(self)->y_bearing);
}

static VALUE
cr_text_extents_set_y_bearing (VALUE self, VALUE y_bearing)
{
  _SELF(self)->y_bearing = NUM2DBL (y_bearing);
  return Qnil;
}

static VALUE
cr_text_extents_width (VALUE self)
{
  return rb_float_new (_SELF(self)->width);
}

static VALUE
cr_text_extents_set_width (VALUE self, VALUE width)
{
  _SELF(self)->width = NUM2DBL (width);
  return Qnil;
}

static VALUE
cr_text_extents_height (VALUE self)
{
  return rb_float_new (_SELF(self)->height);
}

static VALUE
cr_text_extents_set_height (VALUE self, VALUE height)
{
  _SELF(self)->height = NUM2DBL (height);
  return Qnil;
}

static VALUE
cr_text_extents_x_advance (VALUE self)
{
  return rb_float_new (_SELF(self)->x_advance);
}

static VALUE
cr_text_extents_set_x_advance (VALUE self, VALUE x_advance)
{
  _SELF(self)->x_advance = NUM2DBL (x_advance);
  return Qnil;
}

static VALUE
cr_text_extents_y_advance (VALUE self)
{
  return rb_float_new (_SELF(self)->y_advance);
}

static VALUE
cr_text_extents_set_y_advance (VALUE self, VALUE y_advance)
{
  _SELF(self)->y_advance = NUM2DBL (y_advance);
  return Qnil;
}

static VALUE
cr_text_extents_to_s (VALUE self)
{
  VALUE ret;

  ret = rb_str_new2 ("#<");
  rb_str_cat2 (ret, rb_class2name (CLASS_OF (self)));
  rb_str_cat2 (ret, ": ");
  rb_str_cat2 (ret, "x_bearing=");
  rb_str_concat (ret, rb_inspect (cr_text_extents_x_bearing (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "y_bearing=");
  rb_str_concat (ret, rb_inspect (cr_text_extents_y_bearing (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "width=");
  rb_str_concat (ret, rb_inspect (cr_text_extents_width (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "height=");
  rb_str_concat (ret, rb_inspect (cr_text_extents_height (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "x_advance=");
  rb_str_concat (ret, rb_inspect (cr_text_extents_x_advance (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "y_advance=");
  rb_str_concat (ret, rb_inspect (cr_text_extents_y_advance (self)));
  rb_str_cat2 (ret, ">");

  return ret;
}


void
Init_cairo_text_extents (void)
{
  rb_cCairo_TextExtents =
    rb_define_class_under (rb_mCairo, "TextExtents", rb_cObject);
  rb_define_alloc_func (rb_cCairo_TextExtents, cr_text_extents_allocate);

  rb_define_method (rb_cCairo_TextExtents, "initialize",
                    cr_text_extents_initialize, 0);

  rb_define_method (rb_cCairo_TextExtents, "x_bearing",
                    cr_text_extents_x_bearing, 0);
  rb_define_method (rb_cCairo_TextExtents, "set_x_bearing",
                    cr_text_extents_set_x_bearing, 1);
  rb_define_method (rb_cCairo_TextExtents, "y_bearing",
                    cr_text_extents_y_bearing, 0);
  rb_define_method (rb_cCairo_TextExtents, "set_y_bearing",
                    cr_text_extents_set_y_bearing, 1);
  rb_define_method (rb_cCairo_TextExtents, "width",
                    cr_text_extents_width, 0);
  rb_define_method (rb_cCairo_TextExtents, "set_width",
                    cr_text_extents_set_width, 1);
  rb_define_method (rb_cCairo_TextExtents, "height",
                    cr_text_extents_height, 0);
  rb_define_method (rb_cCairo_TextExtents, "set_height",
                    cr_text_extents_set_height, 1);
  rb_define_method (rb_cCairo_TextExtents, "x_advance",
                    cr_text_extents_x_advance, 0);
  rb_define_method (rb_cCairo_TextExtents, "set_x_advance",
                    cr_text_extents_set_x_advance, 1);
  rb_define_method (rb_cCairo_TextExtents, "y_advance",
                    cr_text_extents_y_advance, 0);
  rb_define_method (rb_cCairo_TextExtents, "set_y_advance",
                    cr_text_extents_set_y_advance, 1);

  rb_define_method (rb_cCairo_TextExtents, "to_s",
                    cr_text_extents_to_s, 0);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_TextExtents);
}
