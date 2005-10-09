/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_ScaledFont;

#define _SELF(self)  (RVAL2CRSCALEDFONT(self))

static inline void
cr_scaled_font_check_status (cairo_scaled_font_t *font)
{
  rb_cairo_check_status (cairo_scaled_font_status (font));
}

cairo_scaled_font_t *
rb_cairo_scaled_font_from_ruby_object (VALUE obj)
{
  cairo_scaled_font_t *font;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_ScaledFont)))
    {
      rb_raise (rb_eTypeError, "not a cairo scaled font");
    }
  Data_Get_Struct (obj, cairo_scaled_font_t, font);
  return font;
}

static void
cr_scaled_font_free (void *ptr)
{
  if (ptr)
    {
      cairo_scaled_font_destroy ((cairo_scaled_font_t *) ptr);
    }
}

VALUE
rb_cairo_scaled_font_to_ruby_object (cairo_scaled_font_t *font)
{
  if (font)
    {
      cairo_scaled_font_reference (font);
      return Data_Wrap_Struct (rb_cCairo_FontFace, NULL,
                               cr_scaled_font_free, font);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_scaled_font_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_scaled_font_free, NULL);
}

static VALUE
cr_scaled_font_initialize (VALUE self, VALUE face, VALUE matrix,
                           VALUE ctm, VALUE options)
{
  cairo_scaled_font_t *font;

  font = cairo_scaled_font_create (RVAL2CRFONTFACE (face),
                                   RVAL2CRMATRIX (matrix),
                                   RVAL2CRMATRIX (ctm),
                                   RVAL2CRFONTOPTIONS (options));
  cr_scaled_font_check_status (font);
  DATA_PTR (self) = font;
  return Qnil;
}

static VALUE
cr_scaled_font_extents (VALUE self)
{
  cairo_font_extents_t extents;
  cairo_scaled_font_extents (_SELF (self), &extents);
  cr_scaled_font_check_status (_SELF (self));
  return CRFONTEXTENTS2RVAL (&extents);
}

static VALUE
cr_scaled_font_glyph_extents (VALUE self, VALUE rb_glyphs)
{
  cairo_text_extents_t extents;
  cairo_glyph_t *glyphs;
  int count;

  cr__glyphs_to_array (rb_glyphs, &glyphs, &count);
  cairo_scaled_font_glyph_extents (_SELF (self), glyphs, count, &extents);
  cr_scaled_font_check_status (_SELF (self));
  return CRTEXTEXTENTS2RVAL (&extents);
}

void
Init_cairo_scaled_font (void)
{
  rb_cCairo_ScaledFont =
    rb_define_class_under (rb_mCairo, "ScaledFont", rb_cObject);

  rb_define_alloc_func (rb_cCairo_ScaledFont, cr_scaled_font_allocate);

  rb_define_method (rb_cCairo_ScaledFont, "initialize",
                    cr_scaled_font_initialize, 4);

  rb_define_method (rb_cCairo_ScaledFont, "extents",
                    cr_scaled_font_extents, 0);
  rb_define_method (rb_cCairo_ScaledFont, "glyph_extents",
                    cr_scaled_font_glyph_extents, 1);
}
