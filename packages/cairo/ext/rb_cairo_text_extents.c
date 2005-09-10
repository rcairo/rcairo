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

VALUE rb_cCairo_TextExtents;

#define _SELF  (RVAL2CRTEXTEXTENTS(self))

cairo_text_extents_t *
rb_cairo_text_extents_from_ruby_object (VALUE obj)
{
  cairo_text_extents_t *xform;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_TextExtents)))
    {
      rb_raise (rb_eTypeError, "not a cairo text_extents");
    }
  Data_Get_Struct (obj, cairo_text_extents_t, xform);
  return xform;
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

static    VALUE
rb_cairo_text_extents_new (VALUE klass)
{
  cairo_text_extents_t text_extents;

  text_extents.x_bearing = 0.0;
  text_extents.y_bearing = 0.0;
  text_extents.width     = 0.0;
  text_extents.height    = 0.0;
  text_extents.x_advance = 0.0;
  text_extents.y_advance = 0.0;

  return CRTEXTEXTENTS2RVAL (&text_extents);
}

static    VALUE
rb_cairo_text_extents_x_bearing (VALUE self)
{
  return rb_float_new (_SELF->x_bearing);
}

static    VALUE
rb_cairo_text_extents_y_bearing (VALUE self)
{
  return rb_float_new (_SELF->y_bearing);
}

static    VALUE
rb_cairo_text_extents_width (VALUE self)
{
  return rb_float_new (_SELF->width);
}

static    VALUE
rb_cairo_text_extents_height (VALUE self)
{
  return rb_float_new (_SELF->height);
}

static    VALUE
rb_cairo_text_extents_x_advance (VALUE self)
{
  return rb_float_new (_SELF->x_advance);
}

static    VALUE
rb_cairo_text_extents_y_advance (VALUE self)
{
  return rb_float_new (_SELF->y_advance);
}

void
Init_cairo_text_extents (void)
{
  rb_cCairo_TextExtents =
    rb_define_class_under (rb_mCairo, "TextExtents", rb_cObject);
  rb_define_singleton_method (rb_cCairo_TextExtents, "new",
                              RUBY_METHOD_FUNC (rb_cairo_text_extents_new), 0);
  rb_define_method (rb_cCairo_TextExtents, "x_bearing",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents_x_bearing), 0);
  rb_define_method (rb_cCairo_TextExtents, "y_bearing",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents_y_bearing), 0);
  rb_define_method (rb_cCairo_TextExtents, "width",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents_width), 0);
  rb_define_method (rb_cCairo_TextExtents, "height",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents_height), 0);
  rb_define_method (rb_cCairo_TextExtents, "x_advance",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents_x_advance), 0);
  rb_define_method (rb_cCairo_TextExtents, "y_advance",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents_y_advance), 0);
}
