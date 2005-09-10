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

VALUE rb_cCairo_FontExtents;

#define _SELF  (RVAL2CRFONTEXTENTS(self))

cairo_font_extents_t *
rb_cairo_font_extents_from_ruby_object (VALUE obj)
{
  cairo_font_extents_t *xform;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_FontExtents)))
    {
      rb_raise (rb_eTypeError, "not a cairo font_extents");
    }
  Data_Get_Struct (obj, cairo_font_extents_t, xform);
  return xform;
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
rb_cairo_font_extents_new (VALUE klass)
{
  cairo_font_extents_t font_extents;

  font_extents.ascent        = 0.0;
  font_extents.descent       = 0.0;
  font_extents.height        = 0.0;
  font_extents.max_x_advance = 0.0;
  font_extents.max_y_advance = 0.0;

  return CRFONTEXTENTS2RVAL (&font_extents);
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
