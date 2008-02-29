/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-02-29 23:54:13 $
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

#if CAIRO_HAS_WIN32_SURFACE
#  define OpenFile OpenFile_win32
#  include <cairo-win32.h>
#  undef OpenFile
#endif

#if CAIRO_HAS_QUARTZ_SURFACE
#  include <cairo-quartz.h>
#endif

#define CAIRO_CHECK_VERSION(major, minor, micro)    \
    (CAIRO_VERSION_MAJOR > (major) || \
     (CAIRO_VERSION_MAJOR == (major) && CAIRO_VERSION_MINOR > (minor)) || \
     (CAIRO_VERSION_MAJOR == (major) && CAIRO_VERSION_MINOR == (minor) && \
      CAIRO_VERSION_MICRO >= (micro)))

#include "ruby.h"

#if defined(__cplusplus)
#  define RB_CAIRO_BEGIN_DECLS extern "C" {
#  define RB_CAIRO_END_DECLS }
#else
#  define RB_CAIRO_BEGIN_DECLS
#  define RB_CAIRO_END_DECLS
#endif

RB_CAIRO_BEGIN_DECLS

#if defined(RUBY_CAIRO_PLATFORM_WIN32) && !defined(RB_CAIRO_PLATFORM_WIN32)
#  define RB_CAIRO_PLATFORM_WIN32 RUBY_CAIRO_PLATFORM_WIN32
#endif

#if defined(RUBY_CAIRO_STATIC_COMPILATION) && !defined(RB_CAIRO_STATIC_COMPILATION)
#  define RB_CAIRO_STATIC_COMPILATION RUBY_CAIRO_STATIC_COMPILATION
#endif

#if defined(RB_CAIRO_PLATFORM_WIN32) && !defined(RB_CAIRO_STATIC_COMPILATION)
#  ifdef RB_CAIRO_COMPILATION
#    define RB_CAIRO_VAR __declspec(dllexport)
#  else
#    define RB_CAIRO_VAR extern __declspec(dllimport)
#  endif
#else
#  define RB_CAIRO_VAR extern
#endif

RB_CAIRO_VAR VALUE rb_mCairo;
RB_CAIRO_VAR VALUE rb_cCairo_Context;
RB_CAIRO_VAR VALUE rb_cCairo_Point;
RB_CAIRO_VAR VALUE rb_cCairo_Path;
RB_CAIRO_VAR VALUE rb_cCairo_PathData;
RB_CAIRO_VAR VALUE rb_cCairo_PathMoveTo;
RB_CAIRO_VAR VALUE rb_cCairo_PathLineTo;
RB_CAIRO_VAR VALUE rb_cCairo_PathCurveTo;
RB_CAIRO_VAR VALUE rb_cCairo_PathClosePath;
RB_CAIRO_VAR VALUE rb_cCairo_Matrix;
RB_CAIRO_VAR VALUE rb_cCairo_Pattern;
RB_CAIRO_VAR VALUE rb_cCairo_SolidPattern;
RB_CAIRO_VAR VALUE rb_cCairo_SurfacePattern;
RB_CAIRO_VAR VALUE rb_cCairo_GradientPattern;
RB_CAIRO_VAR VALUE rb_cCairo_LinearPattern;
RB_CAIRO_VAR VALUE rb_cCairo_RadialPattern;
RB_CAIRO_VAR VALUE rb_cCairo_FontFace;
RB_CAIRO_VAR VALUE rb_cCairo_FontExtents;
RB_CAIRO_VAR VALUE rb_cCairo_FontOptions;
RB_CAIRO_VAR VALUE rb_cCairo_ScaledFont;
RB_CAIRO_VAR VALUE rb_cCairo_TextExtents;
RB_CAIRO_VAR VALUE rb_cCairo_Glyph;
RB_CAIRO_VAR VALUE rb_cCairo_Surface;
RB_CAIRO_VAR VALUE rb_cCairo_ImageSurface;
RB_CAIRO_VAR VALUE rb_cCairo_PDFSurface;
RB_CAIRO_VAR VALUE rb_cCairo_PSSurface;
RB_CAIRO_VAR VALUE rb_cCairo_SVGSurface;
RB_CAIRO_VAR VALUE rb_cCairo_Win32Surface;
RB_CAIRO_VAR VALUE rb_cCairo_Win32PrintingSurface;
/* For backward compatibility*/
#define rb_cCairo_WIN32Surface rb_cCairo_Win32Surface
RB_CAIRO_VAR VALUE rb_cCairo_QuartzSurface;
RB_CAIRO_VAR VALUE rb_cCairo_QuartzImageSurface;

RB_CAIRO_VAR VALUE rb_mCairo_Operator;
RB_CAIRO_VAR VALUE rb_mCairo_Antialias;
RB_CAIRO_VAR VALUE rb_mCairo_FillRule;
RB_CAIRO_VAR VALUE rb_mCairo_LineCap;
RB_CAIRO_VAR VALUE rb_mCairo_LineJoin;
RB_CAIRO_VAR VALUE rb_mCairo_FontSlant;
RB_CAIRO_VAR VALUE rb_mCairo_FontWeight;
RB_CAIRO_VAR VALUE rb_mCairo_SubpixelOrder;
RB_CAIRO_VAR VALUE rb_mCairo_HintStyle;
RB_CAIRO_VAR VALUE rb_mCairo_HintMetrics;
RB_CAIRO_VAR VALUE rb_mCairo_FontType;
RB_CAIRO_VAR VALUE rb_mCairo_PathDataType;
RB_CAIRO_VAR VALUE rb_mCairo_Content;
RB_CAIRO_VAR VALUE rb_mCairo_SurfaceType;
RB_CAIRO_VAR VALUE rb_mCairo_Format;
RB_CAIRO_VAR VALUE rb_mCairo_PatternType;
RB_CAIRO_VAR VALUE rb_mCairo_Extend;
RB_CAIRO_VAR VALUE rb_mCairo_Filter;
RB_CAIRO_VAR VALUE rb_mCairo_SVGVersion;
RB_CAIRO_VAR VALUE rb_mCairo_Color;
RB_CAIRO_VAR VALUE rb_cCairo_Color_Base;


#define RVAL2CRCONTEXT(obj)     (rb_cairo_context_from_ruby_object(obj))
#define CRCONTEXT2RVAL(cr)      (rb_cairo_context_to_ruby_object(cr))

#define RVAL2CRPATH(obj)        (rb_cairo_path_from_ruby_object(obj))
#define CRPATH2RVAL(path)       (rb_cairo_path_to_ruby_object(path))

#define RVAL2CRMATRIX(obj)      (rb_cairo_matrix_from_ruby_object(obj))
#define CRMATRIX2RVAL(matrix)   (rb_cairo_matrix_to_ruby_object(matrix))

#define RVAL2CRPATTERN(obj)     (rb_cairo_pattern_from_ruby_object(obj))
#define CRPATTERN2RVAL(pattern) (rb_cairo_pattern_to_ruby_object(pattern))

#define RVAL2CRFONTFACE(obj)    (rb_cairo_font_face_from_ruby_object(obj))
#define CRFONTFACE2RVAL(face)   (rb_cairo_font_face_to_ruby_object(face))

#define RVAL2CRFONTEXTENTS(obj) (rb_cairo_font_extents_from_ruby_object(obj))
#define CRFONTEXTENTS2RVAL(ext) (rb_cairo_font_extents_to_ruby_object(ext))

#define RVAL2CRFONTOPTIONS(obj) (rb_cairo_font_options_from_ruby_object(obj))
#define CRFONTOPTIONS2RVAL(opt) (rb_cairo_font_options_to_ruby_object(opt))

#define RVAL2CRSCALEDFONT(obj)  (rb_cairo_scaled_font_from_ruby_object(obj))
#define CRSCALEDFONT2RVAL(font) (rb_cairo_scaled_font_to_ruby_object(font))

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
VALUE                 rb_cairo_pattern_to_ruby_object        (cairo_pattern_t *pat);

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
#if CAIRO_HAS_PS_SURFACE
#  if CAIRO_CHECK_VERSION(1, 5, 2)
#define RVAL2CRPSLEVEL(obj)       (rb_cairo_ps_level_from_ruby_object(obj))
#  endif
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
#if CAIRO_HAS_PS_SURFACE
#  if CAIRO_CHECK_VERSION(1, 5, 2)
cairo_ps_level_t       rb_cairo_ps_level_from_ruby_object       (VALUE obj);
#  endif
#endif

void rb_cairo_check_status (cairo_status_t status);


#define RB_CAIRO_DEF_SETTERS(klass) rb_cairo_def_setters(klass);
void rb_cairo_def_setters (VALUE klass);

RB_CAIRO_END_DECLS

#endif
