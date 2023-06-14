/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-09-19 12:56:27 $
 *
 * Copyright 2005-2023 Sutou Kouhei <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"

#define _SELF(self) (RVAL2CRFONTOPTIONS(self))

VALUE rb_cCairo_FontOptions;

static void
cr_options_free (void *ptr)
{
  cairo_font_options_destroy ((cairo_font_options_t *) ptr);
}

static const rb_data_type_t cr_font_options_type = {
  "Cairo::FontOptions",
  {
    NULL,
    cr_options_free,
  },
  NULL,
  NULL,
  RUBY_TYPED_FREE_IMMEDIATELY,
};

static inline void
cr_options_check_status (cairo_font_options_t *options)
{
  rb_cairo_check_status (cairo_font_options_status (options));
}

cairo_font_options_t *
rb_cairo_font_options_from_ruby_object (VALUE obj)
{
  cairo_font_options_t *options;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_FontOptions))
    {
      rb_raise (rb_eTypeError, "not a cairo font options");
    }
  TypedData_Get_Struct (obj,
                        cairo_font_options_t,
                        &cr_font_options_type,
                        options);
  return options;
}

VALUE
rb_cairo_font_options_to_ruby_object (cairo_font_options_t *options)
{
  if (options)
    {
      cairo_font_options_t *copied_options;
      copied_options = cairo_font_options_copy (options);
      cr_options_check_status (copied_options);
      return TypedData_Wrap_Struct (rb_cCairo_FontOptions,
                                    &cr_font_options_type,
                                    copied_options);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_options_allocate (VALUE klass)
{
  return TypedData_Wrap_Struct (klass, &cr_font_options_type, NULL);
}

static VALUE
cr_options_create (VALUE self)
{
  cairo_font_options_t *options;

  options = cairo_font_options_create ();
  cr_options_check_status (options);
  RTYPEDDATA_DATA (self) = options;
  return Qnil;
}

static VALUE
cr_options_copy (VALUE self)
{
  return CRFONTOPTIONS2RVAL (_SELF (self));
}

static VALUE
cr_options_merge (VALUE self, VALUE other)
{
  cairo_font_options_merge (_SELF (self), _SELF (other));
  return self;
}

static VALUE
cr_options_equal (VALUE self, VALUE other)
{
  if (!rb_cairo__is_kind_of (other, rb_cCairo_FontOptions))
    return Qfalse;

  return CBOOL2RVAL (cairo_font_options_equal (_SELF (self), _SELF (other)));
}

static VALUE
cr_options_hash (VALUE self)
{
  return ULONG2NUM (cairo_font_options_hash (_SELF (self)));
}

static VALUE
cr_options_set_antialias (VALUE self, VALUE antialias)
{
  cairo_font_options_set_antialias (_SELF (self), RVAL2CRANTIALIAS (antialias));
  return self;
}

static VALUE
cr_options_get_antialias (VALUE self)
{
  return INT2NUM (cairo_font_options_get_antialias (_SELF (self)));
}

static VALUE
cr_options_set_subpixel_order (VALUE self, VALUE subpixel_order)
{
  cairo_font_options_set_subpixel_order (_SELF (self),
                                         RVAL2CRSUBPIXELORDER (subpixel_order));
  return self;
}

static VALUE
cr_options_get_subpixel_order (VALUE self)
{
  return INT2NUM (cairo_font_options_get_subpixel_order (_SELF (self)));
}

static VALUE
cr_options_set_hint_style (VALUE self, VALUE hint_style)
{
  cairo_font_options_set_hint_style (_SELF (self),
                                     RVAL2CRHINTSTYLE (hint_style));
  return self;
}

static VALUE
cr_options_get_hint_style (VALUE self)
{
  return INT2NUM (cairo_font_options_get_hint_style (_SELF (self)));
}

static VALUE
cr_options_set_hint_metrics (VALUE self, VALUE hint_metrics)
{
  cairo_font_options_set_hint_metrics (_SELF (self),
                                       RVAL2CRHINTMETRICS (hint_metrics));
  return self;
}

static VALUE
cr_options_get_hint_metrics (VALUE self)
{
  return INT2NUM (cairo_font_options_get_hint_metrics (_SELF (self)));
}

#if CAIRO_CHECK_VERSION(1, 15, 12)
static VALUE
cr_options_set_variations (VALUE self, VALUE variations)
{
  cairo_font_options_set_variations (_SELF (self),
                                     RVAL2CSTR (variations));
  return self;
}

static VALUE
cr_options_get_variations (VALUE self)
{
  const char *variations;

  variations = cairo_font_options_get_variations (_SELF (self));
  if (!variations)
    return Qnil;

  return CSTR2RVAL (variations);
}
#endif

#if CAIRO_CHECK_VERSION(1, 17, 8)
static VALUE
cr_options_set_color_mode (VALUE self, VALUE mode)
{
  cairo_font_options_set_color_mode (_SELF (self),
                                     RVAL2CRCOLORMODE (mode));
  return self;
}

static VALUE
cr_options_get_color_mode (VALUE self)
{
  return INT2NUM (cairo_font_options_get_color_mode (_SELF (self)));
}

static VALUE
cr_options_set_color_palette (VALUE self, VALUE index)
{
  cairo_font_options_set_color_palette (_SELF (self),
                                        NUM2UINT (index));
  return self;
}

static VALUE
cr_options_get_color_palette (VALUE self)
{
  return UINT2NUM (cairo_font_options_get_color_palette (_SELF (self)));
}

static VALUE
cr_options_set_custom_palette_color (VALUE self,
                                     VALUE index,
                                     VALUE red,
                                     VALUE green,
                                     VALUE blue,
                                     VALUE alpha)
{
  cairo_font_options_set_custom_palette_color (_SELF (self),
                                               NUM2UINT (index),
                                               NUM2DBL (red),
                                               NUM2DBL (green),
                                               NUM2DBL (blue),
                                               NUM2DBL (alpha));
  return self;
}
#endif

void
Init_cairo_font_options (void)
{
  rb_cCairo_FontOptions =
    rb_define_class_under (rb_mCairo, "FontOptions", rb_cObject);

  rb_define_alloc_func (rb_cCairo_FontOptions, cr_options_allocate);

  rb_define_method (rb_cCairo_FontOptions, "initialize", cr_options_create, 0);

  rb_define_method (rb_cCairo_FontOptions, "dup", cr_options_copy, 0);
  rb_define_method (rb_cCairo_FontOptions, "merge!", cr_options_merge, 1);
  rb_define_alias (rb_cCairo_FontOptions, "update", "merge!");
  rb_define_method (rb_cCairo_FontOptions, "==", cr_options_equal, 1);
  rb_define_method (rb_cCairo_FontOptions, "eql?", cr_options_equal, 1);
  rb_define_method (rb_cCairo_FontOptions, "hash", cr_options_hash, 0);
  rb_define_method (rb_cCairo_FontOptions, "set_antialias",
                    cr_options_set_antialias, 1);
  rb_define_method (rb_cCairo_FontOptions, "antialias",
                    cr_options_get_antialias, 0);
  rb_define_method (rb_cCairo_FontOptions, "set_subpixel_order",
                    cr_options_set_subpixel_order, 1);
  rb_define_method (rb_cCairo_FontOptions, "subpixel_order",
                    cr_options_get_subpixel_order, 0);
  rb_define_method (rb_cCairo_FontOptions, "set_hint_style",
                    cr_options_set_hint_style, 1);
  rb_define_method (rb_cCairo_FontOptions, "hint_style",
                    cr_options_get_hint_style, 0);
  rb_define_method (rb_cCairo_FontOptions, "set_hint_metrics",
                    cr_options_set_hint_metrics, 1);
  rb_define_method (rb_cCairo_FontOptions, "hint_metrics",
                    cr_options_get_hint_metrics, 0);
#if CAIRO_CHECK_VERSION(1, 15, 12)
  rb_define_method (rb_cCairo_FontOptions, "set_variations",
                    cr_options_set_variations, 1);
  rb_define_method (rb_cCairo_FontOptions, "variations",
                    cr_options_get_variations, 0);
#endif
#if CAIRO_CHECK_VERSION(1, 17, 8)
  rb_define_method (rb_cCairo_FontOptions, "set_color_mode",
                    cr_options_set_color_mode, 1);
  rb_define_method (rb_cCairo_FontOptions, "color_mode",
                    cr_options_get_color_mode, 0);
  rb_define_method (rb_cCairo_FontOptions, "set_color_palette",
                    cr_options_set_color_palette, 1);
  rb_define_method (rb_cCairo_FontOptions, "color_palette",
                    cr_options_get_color_palette, 0);
  rb_define_method (rb_cCairo_FontOptions, "set_custom_palette_color",
                    cr_options_set_custom_palette_color, 5);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_FontOptions);
}
