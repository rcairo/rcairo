/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-05-01 12:03:21 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"

VALUE rb_cCairo_FontExtents;

#define _SELF(self)  (RVAL2CRFONTEXTENTS(self))

cairo_font_extents_t *
rb_cairo_font_extents_from_ruby_object (VALUE obj)
{
  cairo_font_extents_t *extents;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_FontExtents)))
    {
      rb_raise (rb_eTypeError, "not a cairo font extents");
    }
  Data_Get_Struct (obj, cairo_font_extents_t, extents);
  return extents;
}

VALUE
rb_cairo_font_extents_to_ruby_object (cairo_font_extents_t *extents)
{
  if (extents)
    {
      cairo_font_extents_t *new_extents = ALLOC (cairo_font_extents_t);
      *new_extents = *extents;
      return Data_Wrap_Struct (rb_cCairo_FontExtents, NULL, -1, new_extents);
    }
  else
    {
      return Qnil;
    }
}

static    VALUE
cr_font_extents_ascent (VALUE self)
{
  return rb_float_new (_SELF(self)->ascent);
}

static    VALUE
cr_font_extents_descent (VALUE self)
{
  return rb_float_new (_SELF(self)->descent);
}

static    VALUE
cr_font_extents_height (VALUE self)
{
  return rb_float_new (_SELF(self)->height);
}

static    VALUE
cr_font_extents_max_x_advance (VALUE self)
{
  return rb_float_new (_SELF(self)->max_x_advance);
}

static    VALUE
cr_font_extents_max_y_advance (VALUE self)
{
  return rb_float_new (_SELF(self)->max_y_advance);
}

static VALUE
cr_font_extents_to_s (VALUE self)
{
  VALUE ret;

  ret = rb_str_new2 ("#<");
  rb_str_cat2 (ret, rb_class2name (CLASS_OF (self)));
  rb_str_cat2 (ret, ": ");
  rb_str_cat2 (ret, "ascent=");
  rb_str_concat (ret, rb_inspect (cr_font_extents_ascent (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "descent=");
  rb_str_concat (ret, rb_inspect (cr_font_extents_descent (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "height=");
  rb_str_concat (ret, rb_inspect (cr_font_extents_height (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "max_x_advance=");
  rb_str_concat (ret, rb_inspect (cr_font_extents_max_x_advance (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "max_y_advance=");
  rb_str_concat (ret, rb_inspect (cr_font_extents_max_y_advance (self)));
  rb_str_cat2 (ret, ">");

  return ret;
}


void
Init_cairo_font_extents (void)
{
  rb_cCairo_FontExtents =
    rb_define_class_under (rb_mCairo, "FontExtents", rb_cObject);

  rb_define_method (rb_cCairo_FontExtents, "ascent",
                    cr_font_extents_ascent, 0);
  rb_define_method (rb_cCairo_FontExtents, "descent",
                    cr_font_extents_descent, 0);
  rb_define_method (rb_cCairo_FontExtents, "height",
                    cr_font_extents_height, 0);
  rb_define_method (rb_cCairo_FontExtents, "max_x_advance",
                    cr_font_extents_max_x_advance, 0);
  rb_define_method (rb_cCairo_FontExtents, "max_y_advance",
                    cr_font_extents_max_y_advance, 0);

  rb_define_method (rb_cCairo_FontExtents, "to_s", cr_font_extents_to_s, 0);
}
