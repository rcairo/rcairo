/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_H
#define RB_CAIRO_H

#include <cairo-features.h>
#include <cairo.h>

#include "ruby.h"

extern VALUE rb_mCairo;
extern VALUE rb_cCairo_Context;
extern VALUE rb_cCairo_Matrix;
extern VALUE rb_cCairo_Pattern;
extern VALUE rb_cCairo_FontFace;
extern VALUE rb_cCairo_FontExtents;
extern VALUE rb_cCairo_TextExtents;
extern VALUE rb_cCairo_Glyph;
extern VALUE rb_cCairo_Surface;

#define RVAL2CRCONTEXT(obj)     (rb_cairo_context_from_ruby_object(obj))
#define CRCONTEXT2RVAL(cr)      (rb_cairo_context_to_ruby_object(cr))

#define RVAL2CRMATRIX(obj)      (rb_cairo_matrix_from_ruby_object(obj))
#define CRMATRIX2RVAL(matrix)   (rb_cairo_matrix_to_ruby_object(matrix))

#define RVAL2CRPATTERN(obj)     (rb_cairo_pattern_from_ruby_object(obj))
#define CRPATTERN2RVAL(pattern) (rb_cairo_pattern_to_ruby_object(pattern))

#define RVAL2CRFONTFACE(obj)    (rb_cairo_font_face_from_ruby_object(obj))
#define CRFONTFACE2RVAL(face)   (rb_cairo_font_face_to_ruby_object(face))

#define RVAL2CRFONTEXTENTS(obj) (rb_cairo_font_extents_from_ruby_object(obj))
#define CRFONTEXTENTS2RVAL(ext) (rb_cairo_font_extents_to_ruby_object(ext))

#define RVAL2CRTEXTEXTENTS(obj) (rb_cairo_text_extents_from_ruby_object(obj))
#define CRTEXTEXTENTS2RVAL(ext) (rb_cairo_text_extents_to_ruby_object(ext))

#define RVAL2CRGLYPH(obj)       (rb_cairo_glyph_from_ruby_object(obj))
#define CRGLYPH2RVAL(glyph)     (rb_cairo_glyph_to_ruby_object(glyph))

#define RVAL2CRSURFACE(obj)     (rb_cairo_surface_from_ruby_object(obj))
#define CRSURFACE2RVAL(surface) (rb_cairo_surface_to_ruby_object(surface))

cairo_t              *rb_cairo_context_from_ruby_object      (VALUE obj);
VALUE                 rb_cairo_context_to_ruby_object        (cairo_t *cr);

cairo_matrix_t       *rb_cairo_matrix_from_ruby_object       (VALUE obj);
VALUE                 rb_cairo_matrix_to_ruby_object         (cairo_matrix_t *matrix);

cairo_pattern_t      *rb_cairo_pattern_from_ruby_object      (VALUE obj);
VALUE                 rb_cairo_pattern_to_ruby_object        (cairo_pattern_t *pat);

cairo_font_face_t    *rb_cairo_font_face_from_ruby_object    (VALUE obj);
VALUE                 rb_cairo_font_face_to_ruby_object      (cairo_font_face_t *face);

cairo_font_extents_t *rb_cairo_font_extents_from_ruby_object (VALUE obj);
VALUE                 rb_cairo_font_extents_to_ruby_object   (cairo_font_extents_t *extents);

cairo_text_extents_t *rb_cairo_text_extents_from_ruby_object (VALUE obj);
VALUE                 rb_cairo_text_extents_to_ruby_object   (cairo_text_extents_t *extents);

cairo_glyph_t        *rb_cairo_glyph_from_ruby_object        (VALUE obj);
VALUE                 rb_cairo_glyph_to_ruby_object          (cairo_glyph_t *glyph);

cairo_surface_t      *rb_cairo_surface_from_ruby_object      (VALUE obj);
VALUE                 rb_cairo_surface_to_ruby_object        (cairo_surface_t *surface);



void rb_cairo_raise_exception (cairo_status_t status);

#endif
