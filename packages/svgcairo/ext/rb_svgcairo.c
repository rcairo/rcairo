/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include <svg-cairo.h>
#include <ruby.h>
#include "rb_cairo.h"

VALUE rb_mSVG_Cairo;
VALUE rb_cSVG_Cairo_Context;

#define _SELF  ((svg_cairo_t *)DATA_PTR(self))

static svg_cairo_t *
rb_v_to_svg_cairo_t (VALUE value)
{
  svg_cairo_t *xform;
  if (CLASS_OF (value) != rb_cSVG_Cairo_Context)
    {
      rb_raise (rb_eTypeError, "not a cairo glyph");
    }
  Data_Get_Struct (value, svg_cairo_t, xform);
  return xform;
}

static void
rb_free_svgcairo_context (void *ptr)
{
  if (ptr)
    {
      svg_cairo_destroy ((svg_cairo_t *) ptr);
    }
}

static    VALUE
rb_svgcairo_context_new (VALUE klass)
{
  svg_cairo_t *context;

  svg_cairo_create (&context);

  return Data_Wrap_Struct (rb_cSVG_Cairo_Context, NULL, rb_free_svgcairo_context, context);
}

static    VALUE
rb_svgcairo_context_parse (VALUE self, VALUE filename_v)
{
  svg_cairo_parse (_SELF, STR2CSTR (filename_v));
  return self;
}

static    VALUE
rb_svgcairo_context_parse_buffer (VALUE self, VALUE buffer_v)
{
  int len = strlen (STR2CSTR (buffer_v));
  svg_cairo_parse_buffer (_SELF, STR2CSTR (buffer_v), len);
  return self;
}

static    VALUE
rb_svgcairo_context_render (VALUE self, VALUE cairo_context_v)
{
  svg_cairo_render (_SELF, rb_v_to_cairo_t (cairo_context_v));
  return self;
}

static    VALUE
rb_svgcairo_context_get_width (VALUE self)
{
  int width, height;
  svg_cairo_get_size (_SELF, &width, &height);
  return INT2NUM(width);
}

static    VALUE
rb_svgcairo_context_get_height (VALUE self)
{
  int width, height;
  svg_cairo_get_size (_SELF, &width, &height);
  return INT2NUM(height);
}

static void
Init_svgcairo_context (void)
{
   rb_cSVG_Cairo_Context =
     rb_define_class_under (rb_mSVG_Cairo, "Context", rb_cObject);
  rb_define_singleton_method (rb_cSVG_Cairo_Context, "new",
                              RUBY_METHOD_FUNC (rb_svgcairo_context_new), 0);
  rb_define_method (rb_cSVG_Cairo_Context, "parse_file",
                    RUBY_METHOD_FUNC (rb_svgcairo_context_parse), 1);
  rb_define_method (rb_cSVG_Cairo_Context, "parse_string",
                    RUBY_METHOD_FUNC (rb_svgcairo_context_parse_buffer), 1);
  rb_define_method (rb_cSVG_Cairo_Context, "render",
                    RUBY_METHOD_FUNC (rb_svgcairo_context_render), 1);
  rb_define_method (rb_cSVG_Cairo_Context, "width",
                    RUBY_METHOD_FUNC (rb_svgcairo_context_get_width), 0);
  rb_define_method (rb_cSVG_Cairo_Context, "height",
                    RUBY_METHOD_FUNC (rb_svgcairo_context_get_height), 0);
}

void
Init_svgcairo ()
{
  rb_mSVG_Cairo = rb_define_module ("SVG_Cairo");

  Init_svgcairo_context ();
}
