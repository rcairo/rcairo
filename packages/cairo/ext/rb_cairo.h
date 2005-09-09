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

VALUE    rb_cairo_new_from  (cairo_t *cr);
cairo_t *rb_v_to_cairo_t    (VALUE value);
void     rb_free_context    (void *ptr);

void rb_cairo_raise_exception (cairo_status_t  status);

cairo_matrix_t *rb_v_to_cairo_matrix_t (VALUE value);
VALUE           rb_cairo_matrix_wrap   (cairo_matrix_t *matrix);
void            rb_free_matrix         (void *ptr);

VALUE            rb_cairo_pattern_wrap   (cairo_pattern_t *pat);
cairo_pattern_t *rb_v_to_cairo_pattern_t (VALUE value);
void             rb_free_pattern         (void *ptr);

cairo_font_face_t *value_to_font_face   (VALUE value);
void               rb_free_font_face    (void *ptr);

cairo_font_extents_t *rb_v_to_cairo_font_extents_t (VALUE value);
void                  rb_free_font_extents         (void *ptr);

cairo_text_extents_t *rb_v_to_cairo_text_extents_t (VALUE value);
void                  rb_free_text_extents         (void *ptr);

cairo_glyph_t *rb_v_to_cairo_glyph_t (VALUE value);
void           rb_free_glyph         (void *ptr);

cairo_surface_t *rb_v_to_cairo_surface_t (VALUE value);
void             rb_free_surface         (void *ptr);

#endif
