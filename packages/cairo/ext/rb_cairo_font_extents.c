/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo_font_extents.h"

#define _SELF  ((cairo_font_extents_t *)DATA_PTR(self))

VALUE rb_cCairo_FontExtents;

cairo_font_extents_t *
rb_v_to_cairo_font_extents_t (VALUE value)
{
  cairo_font_extents_t *xform;
  if (CLASS_OF (value) != rb_cCairo_FontExtents)
    {
      rb_raise (rb_eTypeError, "not a cairo font_extents");
    }
  Data_Get_Struct (value, cairo_font_extents_t, xform);
  return xform;
}

void
rb_free_font_extents (void *ptr)
{
  if (ptr)
    {
      free ((cairo_font_extents_t *) ptr);
    }
}

static    VALUE
rb_cairo_font_extents_new (VALUE klass)
{
  cairo_font_extents_t *font_extents;
  VALUE font_extents_v;

  font_extents = ALLOC (cairo_font_extents_t);
  font_extents->ascent        = 0.0;
  font_extents->descent       = 0.0;
  font_extents->height        = 0.0;
  font_extents->max_x_advance = 0.0;
  font_extents->max_y_advance = 0.0;

  font_extents_v = Data_Wrap_Struct (rb_cCairo_FontExtents, NULL, free, font_extents);

  return font_extents_v;
}

static    VALUE
rb_cairo_font_extents_ascent (VALUE self)
{
  return rb_float_new (_SELF->ascent);
}

static    VALUE
rb_cairo_font_extents_descent (VALUE self)
{
  return rb_float_new (_SELF->descent);
}

static    VALUE
rb_cairo_font_extents_height (VALUE self)
{
  return rb_float_new (_SELF->height);
}

static    VALUE
rb_cairo_font_extents_max_x_advance (VALUE self)
{
  return rb_float_new (_SELF->max_x_advance);
}

static    VALUE
rb_cairo_font_extents_max_y_advance (VALUE self)
{
  return rb_float_new (_SELF->max_y_advance);
}

void
Init_cairo_font_extents (void)
{
  rb_cCairo_FontExtents =
    rb_define_class_under (rb_mCairo, "FontExtents", rb_cObject);
  rb_define_singleton_method (rb_cCairo_FontExtents, "new",
                              RUBY_METHOD_FUNC (rb_cairo_font_extents_new), 0);
  rb_define_method (rb_cCairo_FontExtents, "ascent",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents_ascent), 0);
  rb_define_method (rb_cCairo_FontExtents, "descent",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents_descent), 0);
  rb_define_method (rb_cCairo_FontExtents, "height",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents_height), 0);
  rb_define_method (rb_cCairo_FontExtents, "max_x_advance",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents_max_x_advance), 0);
  rb_define_method (rb_cCairo_FontExtents, "max_y_advance",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents_max_y_advance), 0);
}
