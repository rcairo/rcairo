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

VALUE rb_cCairo_Glyph;

#define _SELF  (RVAL2CRGLYPH(self))

cairo_glyph_t *
rb_cairo_glyph_from_ruby_object (VALUE obj)
{
  cairo_glyph_t *xform;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_Glyph)))
    {
      rb_raise (rb_eTypeError, "not a cairo glyph");
    }
  Data_Get_Struct (obj, cairo_glyph_t, xform);
  return xform;
}

VALUE
rb_cairo_glyph_to_ruby_object (cairo_glyph_t *glyph)
{
  if (glyph)
    {
      cairo_glyph_t *new_glyph = ALLOC (cairo_glyph_t);
      *new_glyph = *glyph;
      return Data_Wrap_Struct (rb_cCairo_Glyph, NULL, -1, new_glyph);
    }
  else
    {
      return Qnil;
    }
}

static    VALUE
rb_cairo_glyph_new (VALUE klass)
{
  cairo_glyph_t glyph;

  glyph.index = 0;
  glyph.x     = 0.0;
  glyph.y     = 0.0;

  return CRGLYPH2RVAL (&glyph);
}

static    VALUE
rb_cairo_glyph_index (VALUE self)
{
  return INT2NUM(_SELF->index);
}

static    VALUE
rb_cairo_glyph_x (VALUE self)
{
  return rb_float_new (_SELF->x);
}

static    VALUE
rb_cairo_glyph_y (VALUE self)
{
  return rb_float_new (_SELF->y);
}

static    VALUE
rb_cairo_glyph_set_index (VALUE self,
                          VALUE index_v)
{
  _SELF->index = NUM2ULONG (index_v);
  return self;
}

static    VALUE
rb_cairo_glyph_set_x (VALUE self,
                      VALUE x_v)
{
  _SELF->x = NUM2DBL (x_v);
  return self;
}

static    VALUE
rb_cairo_glyph_set_y (VALUE self,
                      VALUE y_v)
{
  _SELF->y = NUM2DBL (y_v);
  return self;
}



void
Init_cairo_glyph (void)
{
  rb_cCairo_Glyph =
    rb_define_class_under (rb_mCairo, "Glyph", rb_cObject);
  rb_define_singleton_method (rb_cCairo_Glyph, "new",
                              RUBY_METHOD_FUNC (rb_cairo_glyph_new), 0);
  rb_define_method (rb_cCairo_Glyph, "index",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_index), 0);
  rb_define_method (rb_cCairo_Glyph, "x",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_x), 0);
  rb_define_method (rb_cCairo_Glyph, "y",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_y), 0);
  rb_define_method (rb_cCairo_Glyph, "index=",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_set_index), 1);
  rb_define_method (rb_cCairo_Glyph, "x=",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_set_x), 1);
  rb_define_method (rb_cCairo_Glyph, "y=",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_set_y), 1);
}
