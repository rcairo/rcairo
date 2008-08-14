/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-14 08:11:12 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_FontFace;
VALUE rb_cCairo_ToyFontFace = Qnil;
VALUE rb_cCairo_UserFontFace = Qnil;

#define _SELF  (RVAL2CRFONTFACE(self))

static inline void
cr_font_face_check_status (cairo_font_face_t *face)
{
  rb_cairo_check_status (cairo_font_face_status (face));
}

cairo_font_face_t *
rb_cairo_font_face_from_ruby_object (VALUE obj)
{
  cairo_font_face_t *face;

  if (!rb_cairo__is_kind_of (obj, rb_cCairo_FontFace))
    {
      rb_raise (rb_eTypeError,
                "not a cairo font face: %s",
                rb_cairo__inspect (obj));
    }
  Data_Get_Struct (obj, cairo_font_face_t, face);
  if (!face)
    rb_cairo_check_status (CAIRO_STATUS_NULL_POINTER);
  cr_font_face_check_status (face);
  return face;
}

static void
cr_font_face_free (void *ptr)
{
  if (ptr)
    {
      cairo_font_face_t *face = ptr;
      cairo_font_face_destroy (face);
    }
}

VALUE
rb_cairo_font_face_to_ruby_object (cairo_font_face_t *face)
{
  if (face)
    {
      VALUE klass;

      switch (cairo_font_face_get_type (face))
        {
        case CAIRO_FONT_TYPE_TOY:
          klass = rb_cCairo_ToyFontFace;
          break;
        case CAIRO_FONT_TYPE_USER:
          klass = rb_cCairo_UserFontFace;
          break;
        default:
          klass = rb_cCairo_FontFace;
          break;
        }
      cairo_font_face_reference (face);
      return Data_Wrap_Struct (klass, NULL, cr_font_face_free, face);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_font_face_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_font_face_free, NULL);
}

static VALUE
cr_toy_font_face_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_font_face_t *face;
  VALUE rb_family, rb_slant, rb_weight;
  const char *family;
  cairo_font_slant_t slant;
  cairo_font_weight_t weight;

  rb_scan_args (argc, argv, "12", &rb_family, &rb_slant, &rb_weight);

  if (rb_cairo__is_kind_of (rb_family, rb_cString))
    {
      family = RSTRING_PTR (rb_family);
    }
  else if (rb_cairo__is_kind_of (rb_family, rb_cSymbol))
    {
      family = rb_id2name (SYM2ID (rb_family));
    }
  else
    {
      rb_raise (rb_eArgError,
                "family name should be String or Symbol: %s",
                rb_cairo__inspect (rb_family));
    }

  if (NIL_P (rb_slant))
    slant = CAIRO_FONT_SLANT_NORMAL;
  else
    slant = RVAL2CRFONTSLANT (rb_slant);

  if (NIL_P (rb_weight))
    weight = CAIRO_FONT_WEIGHT_NORMAL;
  else
    weight = RVAL2CRFONTWEIGHT (rb_weight);

  face = cairo_toy_font_face_create (family, slant, weight);
  cr_font_face_check_status (face);
  DATA_PTR (self) = face;

  return Qnil;
}

static VALUE
cr_toy_font_face_get_family (VALUE self)
{
  return CSTR2RVAL (cairo_toy_font_face_get_family (_SELF));
}

static VALUE
cr_toy_font_face_get_slant (VALUE self)
{
  return INT2NUM (cairo_toy_font_face_get_slant (_SELF));
}

static VALUE
cr_toy_font_face_get_weight (VALUE self)
{
  return INT2NUM (cairo_toy_font_face_get_weight (_SELF));
}


void
Init_cairo_font (void)
{
  rb_cCairo_FontFace =
    rb_define_class_under (rb_mCairo, "FontFace", rb_cObject);
  rb_define_alloc_func (rb_cCairo_FontFace, cr_font_face_allocate);

#if CAIRO_CHECK_VERSION(1, 7, 2)
  rb_cCairo_ToyFontFace =
    rb_define_class_under (rb_mCairo, "ToyFontFace", rb_cCairo_FontFace);

  rb_define_method (rb_cCairo_ToyFontFace, "initialize",
                    cr_toy_font_face_initialize, -1);

  rb_define_method (rb_cCairo_ToyFontFace, "family",
                    cr_toy_font_face_get_family, 0);
  rb_define_method (rb_cCairo_ToyFontFace, "slant",
                    cr_toy_font_face_get_slant, 0);
  rb_define_method (rb_cCairo_ToyFontFace, "weight",
                    cr_toy_font_face_get_weight, 0);

  rb_cCairo_UserFontFace =
    rb_define_class_under (rb_mCairo, "UserFontFace", rb_cCairo_FontFace);
#endif
}
