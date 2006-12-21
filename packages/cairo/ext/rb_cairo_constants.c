/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2006-12-21 15:34:36 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo.h"

#define CAIRO_OPERATOR_MIN CAIRO_OPERATOR_CLEAR
#define CAIRO_OPERATOR_MAX CAIRO_OPERATOR_SATURATE

#define CAIRO_ANTIALIAS_MIN CAIRO_ANTIALIAS_DEFAULT
#define CAIRO_ANTIALIAS_MAX CAIRO_ANTIALIAS_SUBPIXEL

#define CAIRO_FILL_RULE_MIN CAIRO_FILL_RULE_WINDING
#define CAIRO_FILL_RULE_MAX CAIRO_FILL_RULE_EVEN_ODD

#define CAIRO_LINE_CAP_MIN CAIRO_LINE_CAP_BUTT
#define CAIRO_LINE_CAP_MAX CAIRO_LINE_CAP_SQUARE

#define CAIRO_LINE_JOIN_MIN CAIRO_LINE_JOIN_MITER
#define CAIRO_LINE_JOIN_MAX CAIRO_LINE_JOIN_BEVEL

#define CAIRO_FONT_SLANT_MIN CAIRO_FONT_SLANT_NORMAL
#define CAIRO_FONT_SLANT_MAX CAIRO_FONT_SLANT_OBLIQUE

#define CAIRO_FONT_WEIGHT_MIN CAIRO_FONT_WEIGHT_NORMAL
#define CAIRO_FONT_WEIGHT_MAX CAIRO_FONT_WEIGHT_BOLD

#define CAIRO_SUBPIXEL_ORDER_MIN CAIRO_SUBPIXEL_ORDER_DEFAULT
#define CAIRO_SUBPIXEL_ORDER_MAX CAIRO_SUBPIXEL_ORDER_VBGR

#define CAIRO_HINT_STYLE_MIN CAIRO_HINT_STYLE_DEFAULT
#define CAIRO_HINT_STYLE_MAX CAIRO_HINT_STYLE_FULL

#define CAIRO_HINT_METRICS_MIN CAIRO_HINT_METRICS_DEFAULT
#define CAIRO_HINT_METRICS_MAX CAIRO_HINT_METRICS_OFF

#define CAIRO_PATH_MIN CAIRO_PATH_MOVE_TO
#define CAIRO_PATH_MAX CAIRO_PATH_CLOSE_PATH

#define CAIRO_CONTENT_MIN CAIRO_CONTENT_COLOR
#define CAIRO_CONTENT_MAX CAIRO_CONTENT_COLOR_ALPHA

#define CAIRO_FORMAT_MIN CAIRO_FORMAT_ARGB32
#define CAIRO_FORMAT_MAX CAIRO_FORMAT_A1

#define CAIRO_EXTEND_MIN CAIRO_EXTEND_NONE
#define CAIRO_EXTEND_MAX CAIRO_EXTEND_REFLECT

#define CAIRO_FILTER_MIN CAIRO_FILTER_FAST
#define CAIRO_FILTER_MAX CAIRO_FILTER_GAUSSIAN

#define CAIRO_SVG_VERSION_MIN CAIRO_SVG_VERSION_1_1
#define CAIRO_SVG_VERSION_MAX CAIRO_SVG_VERSION_1_2

#define DEFINE_RVAL2ENUM(name, const_name)                  \
cairo_ ## name ## _t                                        \
rb_cairo_ ## name ## _from_ruby_object (VALUE rb_ ## name)  \
{                                                           \
  cairo_ ## name ## _t name;                                \
  name = FIX2INT (rb_ ## name);                             \
  if (name < CAIRO_ ## const_name ## _MIN ||                \
      name > CAIRO_ ## const_name ## _MAX)                  \
    {                                                       \
      rb_raise (rb_eArgError,                               \
                "invalid %s: %d (expect %d <= %s <= %d)",   \
                #name, name,                                \
                CAIRO_ ## const_name ## _MIN,               \
                #name,                                      \
                CAIRO_ ## const_name ## _MAX);              \
    }                                                       \
  return name;                                              \
}

DEFINE_RVAL2ENUM(operator, OPERATOR)
DEFINE_RVAL2ENUM(antialias, ANTIALIAS)
DEFINE_RVAL2ENUM(fill_rule, FILL_RULE)
DEFINE_RVAL2ENUM(line_cap, LINE_CAP)
DEFINE_RVAL2ENUM(line_join, LINE_JOIN)
DEFINE_RVAL2ENUM(font_slant, FONT_SLANT)
DEFINE_RVAL2ENUM(font_weight, FONT_WEIGHT)
DEFINE_RVAL2ENUM(subpixel_order, SUBPIXEL_ORDER)
DEFINE_RVAL2ENUM(hint_style, HINT_STYLE)
DEFINE_RVAL2ENUM(hint_metrics, HINT_METRICS)
DEFINE_RVAL2ENUM(path_data_type, PATH)
DEFINE_RVAL2ENUM(content, CONTENT)
DEFINE_RVAL2ENUM(format, FORMAT)
DEFINE_RVAL2ENUM(extend, EXTEND)
DEFINE_RVAL2ENUM(filter, FILTER)
#if CAIRO_HAS_SVG_SURFACE
DEFINE_RVAL2ENUM(svg_version, SVG_VERSION)
#endif

void
Init_cairo_constants (void)
{
  /* cairo_operator_t */
  rb_define_const (rb_mCairo,    "OPERATOR_CLEAR",
                   INT2FIX (CAIRO_OPERATOR_CLEAR));

  rb_define_const (rb_mCairo,    "OPERATOR_SOURCE",
                   INT2FIX (CAIRO_OPERATOR_SOURCE));
  rb_define_const (rb_mCairo,    "OPERATOR_OVER",
                   INT2FIX (CAIRO_OPERATOR_OVER));
  rb_define_const (rb_mCairo,    "OPERATOR_IN",
                   INT2FIX (CAIRO_OPERATOR_IN));
  rb_define_const (rb_mCairo,    "OPERATOR_OUT",
                   INT2FIX (CAIRO_OPERATOR_OUT));
  rb_define_const (rb_mCairo,    "OPERATOR_ATOP",
                   INT2FIX (CAIRO_OPERATOR_ATOP));
  
  rb_define_const (rb_mCairo,    "OPERATOR_DEST",
                   INT2FIX (CAIRO_OPERATOR_DEST));
  rb_define_const (rb_mCairo,    "OPERATOR_DEST_OVER",
                   INT2FIX (CAIRO_OPERATOR_DEST_OVER));
  rb_define_const (rb_mCairo,    "OPERATOR_DEST_IN",
                   INT2FIX (CAIRO_OPERATOR_DEST_IN));
  rb_define_const (rb_mCairo,    "OPERATOR_DEST_OUT",
                   INT2FIX (CAIRO_OPERATOR_DEST_OUT));
  rb_define_const (rb_mCairo,    "OPERATOR_DEST_ATOP",
                   INT2FIX (CAIRO_OPERATOR_DEST_ATOP));

  rb_define_const (rb_mCairo,    "OPERATOR_XOR",
                   INT2FIX (CAIRO_OPERATOR_XOR));
  rb_define_const (rb_mCairo,    "OPERATOR_ADD",
                   INT2FIX (CAIRO_OPERATOR_ADD));
  rb_define_const (rb_mCairo,    "OPERATOR_SATURATE",
                   INT2FIX (CAIRO_OPERATOR_SATURATE));

  
  /* cairo_antialias_t */
  rb_define_const (rb_mCairo,    "ANTIALIAS_DEFAULT",
                   INT2FIX (CAIRO_ANTIALIAS_DEFAULT));
  rb_define_const (rb_mCairo,    "ANTIALIAS_NONE",
                   INT2FIX (CAIRO_ANTIALIAS_NONE));
  rb_define_const (rb_mCairo,    "ANTIALIAS_GRAY",
                   INT2FIX (CAIRO_ANTIALIAS_GRAY));
  rb_define_const (rb_mCairo,    "ANTIALIAS_SUBPIXEL",
                   INT2FIX (CAIRO_ANTIALIAS_SUBPIXEL));


  /* cairo_fill_rule_t */
  rb_define_const (rb_mCairo,    "FILL_RULE_WINDING",
                   INT2FIX (CAIRO_FILL_RULE_WINDING));
  rb_define_const (rb_mCairo,    "FILL_RULE_EVEN_ODD",
                   INT2FIX (CAIRO_FILL_RULE_EVEN_ODD));


  /* cairo_line_cap_t */
  rb_define_const (rb_mCairo,    "LINE_CAP_BUTT",
                   INT2FIX (CAIRO_LINE_CAP_BUTT));
  rb_define_const (rb_mCairo,    "LINE_CAP_ROUND",
                   INT2FIX (CAIRO_LINE_CAP_ROUND));
  rb_define_const (rb_mCairo,    "LINE_CAP_SQUARE",
                   INT2FIX (CAIRO_LINE_CAP_SQUARE));


  /* cairo_line_join_t */
  rb_define_const (rb_mCairo,    "LINE_JOIN_MITER",
                   INT2FIX (CAIRO_LINE_JOIN_MITER));
  rb_define_const (rb_mCairo,    "LINE_JOIN_ROUND",
                   INT2FIX (CAIRO_LINE_JOIN_ROUND));
  rb_define_const (rb_mCairo,    "LINE_JOIN_BEVEL",
                   INT2FIX (CAIRO_LINE_JOIN_BEVEL));


  /* cairo_font_slant_t */
  rb_define_const (rb_mCairo,    "FONT_SLANT_NORMAL",
                   INT2FIX (CAIRO_FONT_SLANT_NORMAL));
  rb_define_const (rb_mCairo,    "FONT_SLANT_ITALIC",
                   INT2FIX (CAIRO_FONT_SLANT_ITALIC));
  rb_define_const (rb_mCairo,    "FONT_SLANT_OBLIQUE",
                   INT2FIX (CAIRO_FONT_SLANT_OBLIQUE));


  /* cairo_font_weight_t */
  rb_define_const (rb_mCairo,    "FONT_WEIGHT_NORMAL",
                   INT2FIX (CAIRO_FONT_WEIGHT_NORMAL));
  rb_define_const (rb_mCairo,    "FONT_WEIGHT_BOLD",
                   INT2FIX (CAIRO_FONT_WEIGHT_BOLD));
  

  /* cairo_subpixel_order_t */
  rb_define_const (rb_mCairo,    "SUBPIXEL_ORDER_DEFAULT",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_DEFAULT));
  rb_define_const (rb_mCairo,    "SUBPIXEL_ORDER_RGB",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_RGB));
  rb_define_const (rb_mCairo,    "SUBPIXEL_ORDER_BGR",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_BGR));
  rb_define_const (rb_mCairo,    "SUBPIXEL_ORDER_VRGB",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_VRGB));
  rb_define_const (rb_mCairo,    "SUBPIXEL_ORDER_VBGR",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_VBGR));
  

  /* cairo_hint_style_t */
  rb_define_const (rb_mCairo,    "HINT_STYLE_DEFAULT",
                   INT2FIX (CAIRO_HINT_STYLE_DEFAULT));
  rb_define_const (rb_mCairo,    "HINT_STYLE_NONE",
                   INT2FIX (CAIRO_HINT_STYLE_NONE));
  rb_define_const (rb_mCairo,    "HINT_STYLE_SLIGHT",
                   INT2FIX (CAIRO_HINT_STYLE_SLIGHT));
  rb_define_const (rb_mCairo,    "HINT_STYLE_MEDIUM",
                   INT2FIX (CAIRO_HINT_STYLE_MEDIUM));
  rb_define_const (rb_mCairo,    "HINT_STYLE_FULL",
                   INT2FIX (CAIRO_HINT_STYLE_FULL));


  /* cairo_hint_metrics_t */
  rb_define_const (rb_mCairo,    "HINT_METRICS_DEFAULT",
                   INT2FIX (CAIRO_HINT_METRICS_DEFAULT));
  rb_define_const (rb_mCairo,    "HINT_METRICS_ON",
                   INT2FIX (CAIRO_HINT_METRICS_ON));
  rb_define_const (rb_mCairo,    "HINT_METRICS_OFF",
                   INT2FIX (CAIRO_HINT_METRICS_OFF));


  /* cairo_font_type_t */
  rb_define_const (rb_mCairo, "FONT_TYPE_TOY", INT2FIX(CAIRO_FONT_TYPE_TOY));
  rb_define_const (rb_mCairo, "FONT_TYPE_FT", INT2FIX(CAIRO_FONT_TYPE_FT));
  rb_define_const (rb_mCairo, "FONT_TYPE_WIN32",
                   INT2FIX(CAIRO_FONT_TYPE_WIN32));
  rb_define_const (rb_mCairo, "FONT_TYPE_ATSUI",
                   INT2FIX(CAIRO_FONT_TYPE_ATSUI));


  /* cairo_path_data_type_t */
  rb_define_const (rb_mCairo,    "PATH_MOVE_TO",
                   INT2FIX (CAIRO_PATH_MOVE_TO));
  rb_define_const (rb_mCairo,    "PATH_LINE_TO",
                   INT2FIX (CAIRO_PATH_LINE_TO));
  rb_define_const (rb_mCairo,    "PATH_CURVE_TO",
                   INT2FIX (CAIRO_PATH_CURVE_TO));
  rb_define_const (rb_mCairo,    "PATH_CLOSE_PATH",
                   INT2FIX (CAIRO_PATH_CLOSE_PATH));


  /* cairo_content_t */
  rb_define_const (rb_mCairo,    "CONTENT_COLOR",
                   INT2FIX (CAIRO_CONTENT_COLOR));
  rb_define_const (rb_mCairo,    "CONTENT_ALPHA",
                   INT2FIX (CAIRO_CONTENT_ALPHA));
  rb_define_const (rb_mCairo,    "CONTENT_COLOR_ALPHA",
                   INT2FIX (CAIRO_CONTENT_COLOR_ALPHA));


  /* cairo_surface_type_t */
  rb_define_const (rb_mCairo, "SURFACE_TYPE_IMAGE",
                   INT2FIX (CAIRO_SURFACE_TYPE_IMAGE));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_PDF",
                   INT2FIX (CAIRO_SURFACE_TYPE_PDF));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_PS",
                   INT2FIX (CAIRO_SURFACE_TYPE_PS));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_XLIB",
                   INT2FIX (CAIRO_SURFACE_TYPE_XLIB));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_XCB",
                   INT2FIX (CAIRO_SURFACE_TYPE_XCB));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_GLITZ",
                   INT2FIX (CAIRO_SURFACE_TYPE_GLITZ));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_QUARTZ",
                   INT2FIX (CAIRO_SURFACE_TYPE_QUARTZ));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_WIN32",
                   INT2FIX (CAIRO_SURFACE_TYPE_WIN32));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_BEOS",
                   INT2FIX (CAIRO_SURFACE_TYPE_BEOS));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_DIRECTFB",
                   INT2FIX (CAIRO_SURFACE_TYPE_DIRECTFB));
  rb_define_const (rb_mCairo, "SURFACE_TYPE_SVG",
                   INT2FIX (CAIRO_SURFACE_TYPE_SVG));

  /* cairo_format_t */
  rb_define_const (rb_mCairo,    "FORMAT_ARGB32",
                   INT2FIX (CAIRO_FORMAT_ARGB32));
  rb_define_const (rb_mCairo,    "FORMAT_RGB24",
                   INT2FIX (CAIRO_FORMAT_RGB24));
  rb_define_const (rb_mCairo,    "FORMAT_A8",
                   INT2FIX (CAIRO_FORMAT_A8));
  rb_define_const (rb_mCairo,    "FORMAT_A1",
                   INT2FIX (CAIRO_FORMAT_A1));
#if !CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_const (rb_mCairo,    "FORMAT_RGB16_565",
                   INT2FIX (CAIRO_FORMAT_RGB16_565));
#endif


  /* cairo_pattern_type_t */
  rb_define_const (rb_mCairo, "PATTERN_TYPE_SOLID",
                   INT2FIX (CAIRO_PATTERN_TYPE_SOLID));
  rb_define_const (rb_mCairo, "PATTERN_TYPE_SURFACE",
                   INT2FIX (CAIRO_PATTERN_TYPE_SURFACE));
  rb_define_const (rb_mCairo, "PATTERN_TYPE_LINEAR",
                   INT2FIX (CAIRO_PATTERN_TYPE_LINEAR));
  rb_define_const (rb_mCairo, "PATTERN_TYPE_RADIAL",
                   INT2FIX (CAIRO_PATTERN_TYPE_RADIAL));

  /* cairo_extend_t */
  rb_define_const (rb_mCairo,    "EXTEND_NONE",
                   INT2FIX (CAIRO_EXTEND_NONE));
  rb_define_const (rb_mCairo,    "EXTEND_REPEAT",
                   INT2FIX (CAIRO_EXTEND_REPEAT));
  rb_define_const (rb_mCairo,    "EXTEND_REFLECT",
                   INT2FIX (CAIRO_EXTEND_REFLECT));
  rb_define_const (rb_mCairo,    "EXTEND_PAD",
                   INT2FIX (CAIRO_EXTEND_PAD));


  /* cairo_filter_t */
  rb_define_const (rb_mCairo,    "FILTER_FAST",
                   INT2FIX (CAIRO_FILTER_FAST));
  rb_define_const (rb_mCairo,    "FILTER_GOOD",
                   INT2FIX (CAIRO_FILTER_GOOD));
  rb_define_const (rb_mCairo,    "FILTER_BEST",
                   INT2FIX (CAIRO_FILTER_BEST));
  rb_define_const (rb_mCairo,    "FILTER_NEAREST",
                   INT2FIX (CAIRO_FILTER_NEAREST));
  rb_define_const (rb_mCairo,    "FILTER_BILINEAR",
                   INT2FIX (CAIRO_FILTER_BILINEAR));
  rb_define_const (rb_mCairo,    "FILTER_GAUSSIAN",
                   INT2FIX (CAIRO_FILTER_GAUSSIAN));

#if CAIRO_HAS_SVG_SURFACE
  /* cairo_svg_version_t */
  rb_define_const (rb_mCairo,    "SVG_VERSION_1_1",
                   INT2FIX (CAIRO_SVG_VERSION_1_1));
  rb_define_const (rb_mCairo,    "SVG_VERSION_1_2",
                   INT2FIX (CAIRO_SVG_VERSION_1_2));
#endif
}
