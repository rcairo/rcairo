/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo_glyph.h"

VALUE rb_cCairo_Glyph;

#define _SELF  ((cairo_glyph_t *)DATA_PTR(self))

cairo_glyph_t *
rb_v_to_cairo_glyph_t (VALUE value)
{
  cairo_glyph_t *xform;
  if (CLASS_OF (value) != rb_cCairo_Glyph)
    {
      rb_raise (rb_eTypeError, "not a cairo glyph");
    }
  Data_Get_Struct (value, cairo_glyph_t, xform);
  return xform;
}

void
rb_free_glyph (void *ptr)
{
  if (ptr)
    {
      free ((cairo_glyph_t *) ptr);
    }
}

static    VALUE
rb_cairo_glyph_new (VALUE klass)
{
  cairo_glyph_t *glyph;
  VALUE glyph_v;

  glyph = ALLOC (cairo_glyph_t);
  glyph->index = 0;
  glyph->x     = 0.0;
  glyph->y     = 0.0;

  glyph_v = Data_Wrap_Struct (rb_cCairo_Glyph, NULL, free, glyph);

  return glyph_v;
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
