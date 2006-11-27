/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2006-11-27 14:35:52 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_H
#define RB_CAIRO_H

#include <cairo.h>

#if CAIRO_HAS_PS_SURFACE
#  include <cairo-ps.h>
#endif

#if CAIRO_HAS_PDF_SURFACE
#  include <cairo-pdf.h>
#endif

#if CAIRO_HAS_SVG_SURFACE
#  include <cairo-svg.h>
#endif

#define CAIRO_CHECK_VERSION(major, minor, micro)    \
    (CAIRO_VERSION_MAJOR > (major) || \
     (CAIRO_VERSION_MAJOR == (major) && CAIRO_VERSION_MINOR > (minor)) || \
     (CAIRO_VERSION_MAJOR == (major) && CAIRO_VERSION_MINOR == (minor) && \
      CAIRO_VERSION_MICRO >= (micro)))

#include "ruby.h"

#if defined(RUBY_CAIRO_PLATFORM_WIN32) && !defined(RUBY_CAIRO_STATIC_COMPILATION)
#  ifdef RUBY_CAIRO_COMPILATION
#    define RUBY_CAIRO_VAR __declspec(dllexport)
#  else
#    define RUBY_CAIRO_VAR extern __declspec(dllimport)
#  endif
#else
#  define RUBY_CAIRO_VAR extern
#endif

RUBY_CAIRO_VAR VALUE rb_mCairo;
RUBY_CAIRO_VAR VALUE rb_cCairo_Context;
RUBY_CAIRO_VAR VALUE rb_cCairo_Path;
RUBY_CAIRO_VAR VALUE rb_cCairo_Matrix;
RUBY_CAIRO_VAR VALUE rb_cCairo_Pattern;
RUBY_CAIRO_VAR VALUE rb_cCairo_SolidPattern;
RUBY_CAIRO_VAR VALUE rb_cCairo_SurfacePattern;
RUBY_CAIRO_VAR VALUE rb_cCairo_GradientPattern;
RUBY_CAIRO_VAR VALUE rb_cCairo_LinearPattern;
RUBY_CAIRO_VAR VALUE rb_cCairo_RadialPattern;
RUBY_CAIRO_VAR VALUE rb_cCairo_FontFace;
RUBY_CAIRO_VAR VALUE rb_cCairo_FontExtents;
RUBY_CAIRO_VAR VALUE rb_cCairo_FontOptions;
RUBY_CAIRO_VAR VALUE rb_cCairo_ScaledFont;
RUBY_CAIRO_VAR VALUE rb_cCairo_TextExtents;
RUBY_CAIRO_VAR VALUE rb_cCairo_Glyph;
RUBY_CAIRO_VAR VALUE rb_cCairo_Surface;

#define RVAL2CRCONTEXT(obj)     (rb_cairo_context_from_ruby_object(obj))
#define CRCONTEXT2RVAL(cr)      (rb_cairo_context_to_ruby_object(cr))

#define RVAL2CRPATH(obj)        (rb_cairo_path_from_ruby_object(obj))
#define CRPATH2RVAL(path)       (rb_cairo_path_to_ruby_object(path))

#define RVAL2CRMATRIX(obj)      (rb_cairo_matrix_from_ruby_object(obj))
#define CRMATRIX2RVAL(matrix)   (rb_cairo_matrix_to_ruby_object(matrix))

#define RVAL2CRPATTERN(obj)     (rb_cairo_pattern_from_ruby_object(obj))
#define CRPATTERN2RVAL(pattern, klass) (rb_cairo_pattern_to_ruby_object(pattern, klass))

#define RVAL2CRFONTFACE(obj)    (rb_cairo_font_face_from_ruby_object(obj))
#define CRFONTFACE2RVAL(face)   (rb_cairo_font_face_to_ruby_object(face))

#define RVAL2CRFONTEXTENTS(obj) (rb_cairo_font_extents_from_ruby_object(obj))
#define CRFONTEXTENTS2RVAL(ext) (rb_cairo_font_extents_to_ruby_object(ext))

#define RVAL2CRFONTOPTIONS(obj) (rb_cairo_font_options_from_ruby_object(obj))
#define CRFONTOPTIONS2RVAL(ext) (rb_cairo_font_options_to_ruby_object(ext))

#define RVAL2CRSCALEDFONT(obj) (rb_cairo_scaled_font_from_ruby_object(obj))
#define CRSCALEDFONT2RVAL(ext) (rb_cairo_scaled_font_to_ruby_object(ext))

#define RVAL2CRTEXTEXTENTS(obj) (rb_cairo_text_extents_from_ruby_object(obj))
#define CRTEXTEXTENTS2RVAL(ext) (rb_cairo_text_extents_to_ruby_object(ext))

#define RVAL2CRGLYPH(obj)       (rb_cairo_glyph_from_ruby_object(obj))
#define CRGLYPH2RVAL(glyph)     (rb_cairo_glyph_to_ruby_object(glyph))

#define RVAL2CRSURFACE(obj)     (rb_cairo_surface_from_ruby_object(obj))
#define CRSURFACE2RVAL(surface) (rb_cairo_surface_to_ruby_object(surface))

cairo_t              *rb_cairo_context_from_ruby_object      (VALUE obj);
VALUE                 rb_cairo_context_to_ruby_object        (cairo_t *cr);

cairo_path_t         *rb_cairo_path_from_ruby_object         (VALUE obj);
VALUE                 rb_cairo_path_to_ruby_object           (cairo_path_t *path);

cairo_matrix_t       *rb_cairo_matrix_from_ruby_object       (VALUE obj);
VALUE                 rb_cairo_matrix_to_ruby_object         (cairo_matrix_t *matrix);

cairo_pattern_t      *rb_cairo_pattern_from_ruby_object      (VALUE obj);
VALUE                 rb_cairo_pattern_to_ruby_object        (cairo_pattern_t *pat, VALUE klass);

cairo_font_face_t    *rb_cairo_font_face_from_ruby_object    (VALUE obj);
VALUE                 rb_cairo_font_face_to_ruby_object      (cairo_font_face_t *face);

cairo_font_extents_t *rb_cairo_font_extents_from_ruby_object (VALUE obj);
VALUE                 rb_cairo_font_extents_to_ruby_object   (cairo_font_extents_t *extents);

cairo_font_options_t *rb_cairo_font_options_from_ruby_object (VALUE obj);
VALUE                 rb_cairo_font_options_to_ruby_object   (cairo_font_options_t *options);

cairo_scaled_font_t  *rb_cairo_scaled_font_from_ruby_object  (VALUE obj);
VALUE                 rb_cairo_scaled_font_to_ruby_object    (cairo_scaled_font_t *options);

cairo_text_extents_t *rb_cairo_text_extents_from_ruby_object (VALUE obj);
VALUE                 rb_cairo_text_extents_to_ruby_object   (cairo_text_extents_t *extents);

cairo_glyph_t        *rb_cairo_glyph_from_ruby_object        (VALUE obj);
VALUE                 rb_cairo_glyph_to_ruby_object          (cairo_glyph_t *glyph);

cairo_surface_t      *rb_cairo_surface_from_ruby_object      (VALUE obj);
VALUE                 rb_cairo_surface_to_ruby_object        (cairo_surface_t *surface);


#define RVAL2CROPERATOR(obj)      (rb_cairo_operator_from_ruby_object(obj))
#define RVAL2CRANTIALIAS(obj)     (rb_cairo_antialias_from_ruby_object(obj))
#define RVAL2CRFILLRULE(obj)      (rb_cairo_fill_rule_from_ruby_object(obj))
#define RVAL2CRLINECAP(obj)       (rb_cairo_line_cap_from_ruby_object(obj))
#define RVAL2CRLINEJOIN(obj)      (rb_cairo_line_join_from_ruby_object(obj))
#define RVAL2CRFONTSLANT(obj)     (rb_cairo_font_slant_from_ruby_object(obj))
#define RVAL2CRFONTWEIGHT(obj)    (rb_cairo_font_weight_from_ruby_object(obj))
#define RVAL2CRSUBPIXELORDER(obj) (rb_cairo_subpixel_order_from_ruby_object(obj))
#define RVAL2CRHINTSTYLE(obj)     (rb_cairo_hint_style_from_ruby_object(obj))
#define RVAL2CRHINTMETRICS(obj)   (rb_cairo_hint_metrics_from_ruby_object(obj))
#define RVAL2CRPATHDATATYPE(obj)  (rb_cairo_path_data_type_from_ruby_object(obj))
#define RVAL2CRCONTENT(obj)       (rb_cairo_content_from_ruby_object(obj))
#define RVAL2CRFORMAT(obj)        (rb_cairo_format_from_ruby_object(obj))
#define RVAL2CREXTEND(obj)        (rb_cairo_extend_from_ruby_object(obj))
#define RVAL2CRFILTER(obj)        (rb_cairo_filter_from_ruby_object(obj))
#if CAIRO_HAS_SVG_SURFACE
#define RVAL2CRSVGVERSION(obj)    (rb_cairo_svg_version_from_ruby_object(obj))
#endif

cairo_operator_t       rb_cairo_operator_from_ruby_object       (VALUE obj);
cairo_antialias_t      rb_cairo_antialias_from_ruby_object      (VALUE obj);
cairo_fill_rule_t      rb_cairo_fill_rule_from_ruby_object      (VALUE obj);
cairo_line_cap_t       rb_cairo_line_cap_from_ruby_object       (VALUE obj);
cairo_line_join_t      rb_cairo_line_join_from_ruby_object      (VALUE obj);
cairo_font_slant_t     rb_cairo_font_slant_from_ruby_object     (VALUE obj);
cairo_font_weight_t    rb_cairo_font_weight_from_ruby_object    (VALUE obj);
cairo_subpixel_order_t rb_cairo_subpixel_order_from_ruby_object (VALUE obj);
cairo_hint_style_t     rb_cairo_hint_style_from_ruby_object     (VALUE obj);
cairo_hint_metrics_t   rb_cairo_hint_metrics_from_ruby_object   (VALUE obj);
cairo_path_data_type_t rb_cairo_path_data_type_from_ruby_object (VALUE obj);
cairo_content_t        rb_cairo_content_from_ruby_object        (VALUE obj);
cairo_format_t         rb_cairo_format_from_ruby_object         (VALUE obj);
cairo_extend_t         rb_cairo_extend_from_ruby_object         (VALUE obj);
cairo_filter_t         rb_cairo_filter_from_ruby_object         (VALUE obj);
#if CAIRO_HAS_SVG_SURFACE
cairo_svg_version_t    rb_cairo_svg_version_from_ruby_object    (VALUE obj);
#endif

void rb_cairo_check_status (cairo_status_t status);


#define RB_CAIRO_DEF_SETTERS(klass) rb_cairo_def_setters(klass);
void rb_cairo_def_setters (VALUE klass);

#endif
