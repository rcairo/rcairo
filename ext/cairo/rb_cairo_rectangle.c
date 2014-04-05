/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005-2014 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo.h"

VALUE rb_cCairo_Rectangle;

#define _SELF  ((cairo_rectangle_int_t *)DATA_PTR (self))

#if CAIRO_CHECK_VERSION(1, 10, 0)
static VALUE
cr_rectangle_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, xfree, NULL);
}

static VALUE
cr_rectangle_initialize (VALUE self, VALUE x, VALUE y,
                         VALUE width, VALUE height)
{
  cairo_rectangle_int_t *rectangle;

  rectangle = ALLOC (cairo_rectangle_int_t);
  DATA_PTR (self) = rectangle;

  rectangle->x = NUM2INT (x);
  rectangle->y = NUM2INT (y);
  rectangle->width = NUM2INT (width);
  rectangle->height = NUM2INT (height);

  return Qnil;
}

#  define DEFINE_RECTANGLE_ACCESSOR(name)               \
static VALUE                                            \
cr_rectangle_get_ ## name (VALUE self)                  \
{                                                       \
  return INT2NUM (_SELF->name);                         \
}                                                       \
                                                        \
static VALUE                                            \
cr_rectangle_set_ ## name (VALUE self, VALUE value)     \
{                                                       \
  _SELF->name = NUM2INT (value);                        \
  return self;                                          \
}

DEFINE_RECTANGLE_ACCESSOR(x)
DEFINE_RECTANGLE_ACCESSOR(y)
DEFINE_RECTANGLE_ACCESSOR(width)
DEFINE_RECTANGLE_ACCESSOR(height)

#  undef DEFINE_RECTANGLE_ACCESSOR
#endif

void
Init_cairo_rectangle (void)
{
#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_cCairo_Rectangle =
    rb_define_class_under (rb_mCairo, "Rectangle", rb_cObject);
  rb_define_alloc_func (rb_cCairo_Rectangle, cr_rectangle_allocate);

  rb_define_method (rb_cCairo_Rectangle, "initialize",
                    cr_rectangle_initialize, 4);

  rb_define_method (rb_cCairo_Rectangle, "x",  cr_rectangle_get_x, 0);
  rb_define_method (rb_cCairo_Rectangle, "x=", cr_rectangle_set_x, 1);
  rb_define_method (rb_cCairo_Rectangle, "y",  cr_rectangle_get_y, 0);
  rb_define_method (rb_cCairo_Rectangle, "y=", cr_rectangle_set_y, 1);
  rb_define_method (rb_cCairo_Rectangle, "width",  cr_rectangle_get_width, 0);
  rb_define_method (rb_cCairo_Rectangle, "width=", cr_rectangle_set_width, 1);
  rb_define_method (rb_cCairo_Rectangle, "height",  cr_rectangle_get_height, 0);
  rb_define_method (rb_cCairo_Rectangle, "height=", cr_rectangle_set_height, 1);
#endif
}
