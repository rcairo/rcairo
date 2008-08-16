/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-16 08:16:39 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_Glyph;

#define _SELF(self)  (RVAL2CRGLYPH(self))

cairo_glyph_t *
rb_cairo_glyph_from_ruby_object (VALUE obj)
{
  cairo_glyph_t *glyph;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Glyph))
    {
      rb_raise (rb_eTypeError, "not a cairo glyph");
    }
  Data_Get_Struct (obj, cairo_glyph_t, glyph);
  return glyph;
}

static void
cr_glyph_free (void *ptr)
{
  if (ptr)
    {
      xfree (ptr);
    }
}

VALUE
rb_cairo_glyph_to_ruby_object (cairo_glyph_t *glyph)
{
  if (glyph)
    {
      cairo_glyph_t *new_glyph;

      new_glyph = ALLOC (cairo_glyph_t);
      *new_glyph = *glyph;
      return Data_Wrap_Struct (rb_cCairo_Glyph, NULL, cr_glyph_free, new_glyph);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_glyph_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_glyph_free, NULL);
}

static VALUE
cr_glyph_initialize (VALUE self, VALUE index, VALUE x, VALUE y)
{
  cairo_glyph_t *glyph;

  glyph = ALLOC (cairo_glyph_t);
  glyph->index = NUM2ULONG (index);
  glyph->x = NUM2DBL (x);
  glyph->y = NUM2DBL (y);

  DATA_PTR (self) = glyph;
  return Qnil;
}

static VALUE
cr_glyph_index (VALUE self)
{
  return ULONG2NUM (_SELF(self)->index);
}

static VALUE
cr_glyph_x (VALUE self)
{
  return rb_float_new (_SELF(self)->x);
}

static VALUE
cr_glyph_y (VALUE self)
{
  return rb_float_new (_SELF(self)->y);
}

static VALUE
cr_glyph_set_index (VALUE self, VALUE index)
{
  _SELF(self)->index = NUM2ULONG (index);
  return self;
}

static VALUE
cr_glyph_set_x (VALUE self, VALUE x)
{
  _SELF(self)->x = NUM2DBL (x);
  return self;
}

static VALUE
cr_glyph_set_y (VALUE self, VALUE y)
{
  _SELF(self)->y = NUM2DBL (y);
  return self;
}

static VALUE
cr_glyph_to_s (VALUE self)
{
  VALUE ret;

  ret = rb_str_new2 ("#<");
  rb_str_cat2 (ret, rb_class2name (CLASS_OF (self)));
  rb_str_cat2 (ret, ": ");
  rb_str_cat2 (ret, "index=");
  rb_str_concat (ret, rb_inspect (cr_glyph_index (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "x=");
  rb_str_concat (ret, rb_inspect (cr_glyph_x (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "y=");
  rb_str_concat (ret, rb_inspect (cr_glyph_y (self)));
  rb_str_cat2 (ret, ">");

  return ret;
}


void
Init_cairo_glyph (void)
{
  rb_cCairo_Glyph = rb_define_class_under (rb_mCairo, "Glyph", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Glyph, cr_glyph_allocate);

  rb_define_method (rb_cCairo_Glyph, "initialize", cr_glyph_initialize, 3);
  
  rb_define_method (rb_cCairo_Glyph, "index", cr_glyph_index, 0);
  rb_define_method (rb_cCairo_Glyph, "x", cr_glyph_x, 0);
  rb_define_method (rb_cCairo_Glyph, "y", cr_glyph_y, 0);
  rb_define_method (rb_cCairo_Glyph, "set_index", cr_glyph_set_index, 1);
  rb_define_method (rb_cCairo_Glyph, "set_x", cr_glyph_set_x, 1);
  rb_define_method (rb_cCairo_Glyph, "set_y", cr_glyph_set_y, 1);

  rb_define_method (rb_cCairo_Glyph, "to_s", cr_glyph_to_s, 0);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_Glyph);
}
