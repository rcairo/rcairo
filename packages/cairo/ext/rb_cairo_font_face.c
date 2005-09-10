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

VALUE rb_cCairo_FontFace;

#define _SELF  (RVAL2CRFONTFACE(self))

cairo_font_face_t *
rb_cairo_font_face_from_ruby_object (VALUE obj)
{
  cairo_font_face_t *xform;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_FontFace)))
    {
      rb_raise (rb_eTypeError, "not a cairo font face");
    }
  Data_Get_Struct (obj, cairo_font_face_t, xform);
  return xform;
}

VALUE
rb_cairo_font_face_to_ruby_object (cairo_font_face_t *face)
{
  if (face)
    {
      cairo_font_face_reference (face);
      return Data_Wrap_Struct (rb_cCairo_FontFace, NULL,
                               cairo_font_face_destroy, face);
    }
  else
    {
      return Qnil;
    }
}


#if 0
static    VALUE
rb_cairo_font_extents (VALUE self,
                       VALUE font_matrix_v)
{
  cairo_matrix_t       *font_matrix = RVAL2CRAMTRIX (font_matrix_v);
  cairo_font_extents_t  extents;
  cairo_status_t        status;

  status = cairo_font_extents (_SELF, font_matrix, &extents);
  if (status)
    {
      rb_cairo_raise_exception (status);
    }
  else
    {
      return CRFONTEXTENTS2RVAL (&extents);
    }
}

static    VALUE
rb_cairo_font_glyph_extents (VALUE self,
                             VALUE font_matrix_v,
                             VALUE glyphs_v)
{
  cairo_matrix_t       *font_matrix = RVAL2CRMATRIX (font_matrix_v);
  cairo_text_extents_t  extents;
  cairo_status_t        status;

  /* XXX: unwrap glyph array */
  cairo_font_glyph_extents (_SELF, font_matrix, NULL, 0, &extents);
  return CRTEXTEXTENTS2RVAL (&extents);
}
#endif


void
Init_cairo_font (void)
{
  rb_cCairo_FontFace =
    rb_define_class_under (rb_mCairo, "FontFace", rb_cObject);
  /*
    rb_define_method (rb_cCairo_Font, "extents",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents), 1);
    rb_define_method (rb_cCairo_Font, "glyph_extents",
                    RUBY_METHOD_FUNC (rb_cairo_font_extents), 2);
   */
}
