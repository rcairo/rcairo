/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo_font_face.h"

#define _SELF  (DATA_PTR(self))

VALUE rb_cCairo_FontFace;

cairo_font_face_t *
value_to_font_face (VALUE value)
{
  cairo_font_face_t *xform;
  if (CLASS_OF (value) != rb_cCairo_FontFace)
    {
      rb_raise (rb_eTypeError, "not a cairo font face");
    }
  Data_Get_Struct (value, cairo_font_face_t, xform);
  return xform;
}

void
rb_free_font_face (void *ptr)
{
  if (ptr)
    {
//      cairo_font_destroy ((cairo_font_t *) ptr);
    }
}

#if 0
static    VALUE
rb_cairo_font_extents (VALUE self,
                       VALUE font_matrix_v)
{
  cairo_matrix_t       *font_matrix = rb_v_to_cairo_matrix_t (font_matrix_v);
  cairo_font_extents_t *extents;
  cairo_status_t        status;

  extents = malloc (sizeof (cairo_font_extents_t));
  if (extents)
    {
      status = cairo_font_extents (_SELF, font_matrix, extents);
      /* XXX; check status */
      return Data_Wrap_Struct (rb_cCairo_FontExtents, NULL, rb_free_font_extents, extents);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate font extents");
      return Qundef;
    }
}

static    VALUE
rb_cairo_font_glyph_extents (VALUE self,
                             VALUE font_matrix_v,
                             VALUE glyphs_v)
{
  cairo_matrix_t       *font_matrix = rb_v_to_cairo_matrix_t (font_matrix_v);
  cairo_text_extents_t *extents;
  cairo_status_t        status;

  extents = malloc (sizeof (cairo_text_extents_t));
  if (extents)
    {
      /* XXX: unwrap glyph array */
      cairo_font_glyph_extents (_SELF, font_matrix, NULL, 0, extents);
      return Data_Wrap_Struct (rb_cCairo_TextExtents, NULL, free, extents);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate font extents");
      return Qundef;
    }
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
