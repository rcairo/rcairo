/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#define _SELF  ((cairo_text_extents_t *)DATA_PTR(self))

#include "rb_cairo_text_extents.h"

VALUE rb_cCairo_TextExtents;

cairo_text_extents_t *
rb_v_to_cairo_text_extents_t (VALUE value)
{
  cairo_text_extents_t *xform;
  if (CLASS_OF (value) != rb_cCairo_TextExtents)
    {
      rb_raise (rb_eTypeError, "not a cairo text_extents");
    }
  Data_Get_Struct (value, cairo_text_extents_t, xform);
  return xform;
}

void
rb_free_text_extents (void *ptr)
{
  if (ptr)
    {
      free ((cairo_text_extents_t *) ptr);
    }
}

static    VALUE
rb_cairo_text_extents_new (VALUE klass)
{
  cairo_text_extents_t *text_extents;
  VALUE text_extents_v;

  text_extents = ALLOC (cairo_text_extents_t);
  text_extents->x_bearing = 0.0;
  text_extents->y_bearing = 0.0;
  text_extents->width     = 0.0;
  text_extents->height    = 0.0;
  text_extents->x_advance = 0.0;
  text_extents->y_advance = 0.0;

  text_extents_v = Data_Wrap_Struct (rb_cCairo_TextExtents, NULL, free, text_extents);

  return text_extents_v;
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
