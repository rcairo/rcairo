/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-09-19 12:56:27 $
 *
 * Copyright 2005-2019 Kouhei Sutou <kou@cozmixng.org>
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
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_ScaledFont))
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
      return Data_Wrap_Struct (rb_cCairo_ScaledFont, NULL,
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
cr_scaled_font_text_extents (VALUE self, VALUE utf8)
{
  cairo_text_extents_t extents;
  cairo_scaled_font_text_extents (_SELF (self), StringValueCStr (utf8),
                                  &extents);
  cr_scaled_font_check_status (_SELF (self));
  return CRTEXTEXTENTS2RVAL (&extents);
}

static VALUE
cr_scaled_font_glyph_extents (VALUE self, VALUE rb_glyphs)
{
  cairo_text_extents_t extents;
  cairo_glyph_t *glyphs;
  int count;

  RB_CAIRO__GLYPHS_TO_ARRAY (rb_glyphs, glyphs, count);
  cairo_scaled_font_glyph_extents (_SELF (self), glyphs, count, &extents);
  cr_scaled_font_check_status (_SELF (self));
  return CRTEXTEXTENTS2RVAL (&extents);
}

#if CAIRO_CHECK_VERSION(1, 7, 6)
static VALUE
cr_scaled_font_text_to_glyphs (VALUE self, VALUE rb_x, VALUE rb_y, VALUE rb_utf8)
{
  double x, y;
  const char *utf8;
  int utf8_len;
  cairo_glyph_t *glyphs = NULL;
  int num_glyphs;
  cairo_text_cluster_t *clusters = NULL;
  int num_clusters;
  cairo_text_cluster_flags_t cluster_flags;
  cairo_status_t status;
  VALUE rb_glyphs, rb_clusters;

  x = NUM2DBL (rb_x);
  y = NUM2DBL (rb_y);
  utf8 = RSTRING_PTR (rb_utf8);
  utf8_len = (int) RSTRING_LEN (rb_utf8);

  status = cairo_scaled_font_text_to_glyphs (_SELF (self),
                                             x, y, utf8, utf8_len,
                                             &glyphs, &num_glyphs,
                                             &clusters, &num_clusters,
                                             &cluster_flags);
  rb_cairo_check_status (status);

  rb_glyphs = rb_cairo__glyphs_to_ruby_object (glyphs, num_glyphs);
  cairo_glyph_free (glyphs);
  rb_clusters = rb_cairo__text_clusters_to_ruby_object (clusters, num_clusters);
  cairo_text_cluster_free (clusters);

  return rb_ary_new3 (3, rb_glyphs, rb_clusters, INT2NUM (cluster_flags));
}
#endif

static VALUE
cr_scaled_font_get_font_face (VALUE self)
{
  cairo_font_face_t *face;
  face = cairo_scaled_font_get_font_face (_SELF (self));
  cr_scaled_font_check_status (_SELF (self));
  return CRFONTFACE2RVAL (face);
}

static VALUE
cr_scaled_font_get_font_matrix (VALUE self)
{
  cairo_matrix_t font_matrix;
  cairo_scaled_font_get_font_matrix (_SELF (self), &font_matrix);
  cr_scaled_font_check_status (_SELF (self));
  return CRMATRIX2RVAL (&font_matrix);
}

static VALUE
cr_scaled_font_get_ctm (VALUE self)
{
  cairo_matrix_t ctm;
  cairo_scaled_font_get_font_matrix (_SELF (self), &ctm);
  cr_scaled_font_check_status (_SELF (self));
  return CRMATRIX2RVAL (&ctm);
}

static VALUE
cr_scaled_font_get_font_options (VALUE self)
{
  cairo_font_options_t *options;
  VALUE rb_options;

  options = cairo_font_options_create ();
  rb_cairo_check_status (cairo_font_options_status (options));

  /* TODO: Use rb_ensure() */
  rb_options = CRFONTOPTIONS2RVAL (options);
  cairo_font_options_destroy (options);

  options = RVAL2CRFONTOPTIONS (rb_options);
  cairo_scaled_font_get_font_options (_SELF (self), options);
  cr_scaled_font_check_status (_SELF (self));
  rb_cairo_check_status (cairo_font_options_status (options));

  return rb_options;
}

#if CAIRO_CHECK_VERSION(1, 7, 2)
static VALUE
cr_scaled_font_get_scale_matrix (VALUE self)
{
  cairo_matrix_t matrix;

  cairo_scaled_font_get_scale_matrix (_SELF (self), &matrix);
  cr_scaled_font_check_status (_SELF (self));
  return CRMATRIX2RVAL (&matrix);
}
#endif

void
Init_cairo_scaled_font (void)
{
  rb_cCairo_ScaledFont =
    rb_define_class_under (rb_mCairo, "ScaledFont", rb_cObject);

  rb_define_alloc_func (rb_cCairo_ScaledFont, cr_scaled_font_allocate);

  rb_define_method (rb_cCairo_ScaledFont, "initialize",
                    cr_scaled_font_initialize, 4);

  rb_define_method (rb_cCairo_ScaledFont, "extents", cr_scaled_font_extents, 0);
  rb_define_method (rb_cCairo_ScaledFont, "text_extents",
                    cr_scaled_font_text_extents, 1);
  rb_define_method (rb_cCairo_ScaledFont, "glyph_extents",
                    cr_scaled_font_glyph_extents, 1);
#if CAIRO_CHECK_VERSION(1, 7, 2)
  rb_define_method (rb_cCairo_ScaledFont, "text_to_glyphs",
                    cr_scaled_font_text_to_glyphs, 3);
#endif
  rb_define_method (rb_cCairo_ScaledFont, "font_face",
                    cr_scaled_font_get_font_face, 0);
  rb_define_method (rb_cCairo_ScaledFont, "font_matrix",
                    cr_scaled_font_get_font_matrix, 0);
  rb_define_method (rb_cCairo_ScaledFont, "ctm", cr_scaled_font_get_ctm, 0);
  rb_define_method (rb_cCairo_ScaledFont, "font_options",
                    cr_scaled_font_get_font_options, 0);
#if CAIRO_CHECK_VERSION(1, 7, 2)
  rb_define_method (rb_cCairo_ScaledFont, "scale_matrix",
                    cr_scaled_font_get_scale_matrix, 0);
#endif
}
