/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-05-20 02:45:40 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_mCairo_Operator;
VALUE rb_mCairo_Antialias;
VALUE rb_mCairo_FillRule;
VALUE rb_mCairo_LineCap;
VALUE rb_mCairo_LineJoin;
VALUE rb_mCairo_FontSlant;
VALUE rb_mCairo_FontWeight;
VALUE rb_mCairo_SubpixelOrder;
VALUE rb_mCairo_HintStyle;
VALUE rb_mCairo_HintMetrics;
VALUE rb_mCairo_FontType;
VALUE rb_mCairo_PathDataType;
VALUE rb_mCairo_Content;
VALUE rb_mCairo_SurfaceType;
VALUE rb_mCairo_Format;
VALUE rb_mCairo_PatternType;
VALUE rb_mCairo_Extend;
VALUE rb_mCairo_Filter;
VALUE rb_mCairo_SVGVersion;

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

#define DEFINE_RVAL2ENUM(name, const_name)                      \
cairo_ ## name ## _t                                            \
rb_cairo_ ## name ## _from_ruby_object (VALUE rb_ ## name)      \
{                                                               \
  cairo_ ## name ## _t name;                                    \
                                                                \
  if (!rb_cairo__is_kind_of (rb_ ## name, rb_cNumeric))         \
    rb_ ## name = rb_cairo__const_get (rb_ ## name,             \
                                       # const_name "_");       \
                                                                \
  name = FIX2INT (rb_ ## name);                                 \
  if (name < CAIRO_ ## const_name ## _MIN ||                    \
      name > CAIRO_ ## const_name ## _MAX)                      \
    {                                                           \
      rb_raise (rb_eArgError,                                   \
                "invalid %s: %d (expect %d <= %s <= %d)",       \
                #name, name,                                    \
                CAIRO_ ## const_name ## _MIN,                   \
                #name,                                          \
                CAIRO_ ## const_name ## _MAX);                  \
    }                                                           \
  return name;                                                  \
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
  rb_mCairo_Operator = rb_define_module_under (rb_mCairo, "Operator");
  rb_define_const (rb_mCairo_Operator,    "CLEAR",
                   INT2FIX (CAIRO_OPERATOR_CLEAR));

  rb_define_const (rb_mCairo_Operator,    "SOURCE",
                   INT2FIX (CAIRO_OPERATOR_SOURCE));
  rb_define_const (rb_mCairo_Operator,    "OVER",
                   INT2FIX (CAIRO_OPERATOR_OVER));
  rb_define_const (rb_mCairo_Operator,    "IN",
                   INT2FIX (CAIRO_OPERATOR_IN));
  rb_define_const (rb_mCairo_Operator,    "OUT",
                   INT2FIX (CAIRO_OPERATOR_OUT));
  rb_define_const (rb_mCairo_Operator,    "ATOP",
                   INT2FIX (CAIRO_OPERATOR_ATOP));

  rb_define_const (rb_mCairo_Operator,    "DEST",
                   INT2FIX (CAIRO_OPERATOR_DEST));
  rb_define_const (rb_mCairo_Operator,    "DEST_OVER",
                   INT2FIX (CAIRO_OPERATOR_DEST_OVER));
  rb_define_const (rb_mCairo_Operator,    "DEST_IN",
                   INT2FIX (CAIRO_OPERATOR_DEST_IN));
  rb_define_const (rb_mCairo_Operator,    "DEST_OUT",
                   INT2FIX (CAIRO_OPERATOR_DEST_OUT));
  rb_define_const (rb_mCairo_Operator,    "DEST_ATOP",
                   INT2FIX (CAIRO_OPERATOR_DEST_ATOP));

  rb_define_const (rb_mCairo_Operator,    "XOR",
                   INT2FIX (CAIRO_OPERATOR_XOR));
  rb_define_const (rb_mCairo_Operator,    "ADD",
                   INT2FIX (CAIRO_OPERATOR_ADD));
  rb_define_const (rb_mCairo_Operator,    "SATURATE",
                   INT2FIX (CAIRO_OPERATOR_SATURATE));


  /* cairo_antialias_t */
  rb_mCairo_Antialias = rb_define_module_under (rb_mCairo, "Antialias");
  rb_define_const (rb_mCairo_Antialias,    "DEFAULT",
                   INT2FIX (CAIRO_ANTIALIAS_DEFAULT));
  rb_define_const (rb_mCairo_Antialias,    "NONE",
                   INT2FIX (CAIRO_ANTIALIAS_NONE));
  rb_define_const (rb_mCairo_Antialias,    "GRAY",
                   INT2FIX (CAIRO_ANTIALIAS_GRAY));
  rb_define_const (rb_mCairo_Antialias,    "SUBPIXEL",
                   INT2FIX (CAIRO_ANTIALIAS_SUBPIXEL));


  /* cairo_fill_rule_t */
  rb_mCairo_FillRule = rb_define_module_under (rb_mCairo, "FillRule");
  rb_define_const (rb_mCairo_FillRule,     "WINDING",
                   INT2FIX (CAIRO_FILL_RULE_WINDING));
  rb_define_const (rb_mCairo_FillRule,     "EVEN_ODD",
                   INT2FIX (CAIRO_FILL_RULE_EVEN_ODD));


  /* cairo_line_cap_t */
  rb_mCairo_LineCap = rb_define_module_under (rb_mCairo, "LineCap");
  rb_define_const (rb_mCairo_LineCap,     "BUTT",
                   INT2FIX (CAIRO_LINE_CAP_BUTT));
  rb_define_const (rb_mCairo_LineCap,     "ROUND",
                   INT2FIX (CAIRO_LINE_CAP_ROUND));
  rb_define_const (rb_mCairo_LineCap,     "SQUARE",
                   INT2FIX (CAIRO_LINE_CAP_SQUARE));


  /* cairo_line_join_t */
  rb_mCairo_LineJoin = rb_define_module_under (rb_mCairo, "LineJoin");
  rb_define_const (rb_mCairo_LineJoin,     "MITER",
                   INT2FIX (CAIRO_LINE_JOIN_MITER));
  rb_define_const (rb_mCairo_LineJoin,     "ROUND",
                   INT2FIX (CAIRO_LINE_JOIN_ROUND));
  rb_define_const (rb_mCairo_LineJoin,     "BEVEL",
                   INT2FIX (CAIRO_LINE_JOIN_BEVEL));


  /* cairo_font_slant_t */
  rb_mCairo_FontSlant = rb_define_module_under (rb_mCairo, "FontSlant");
  rb_define_const (rb_mCairo_FontSlant,     "NORMAL",
                   INT2FIX (CAIRO_FONT_SLANT_NORMAL));
  rb_define_const (rb_mCairo_FontSlant,     "ITALIC",
                   INT2FIX (CAIRO_FONT_SLANT_ITALIC));
  rb_define_const (rb_mCairo_FontSlant,     "OBLIQUE",
                   INT2FIX (CAIRO_FONT_SLANT_OBLIQUE));


  /* cairo_font_weight_t */
  rb_mCairo_FontWeight = rb_define_module_under (rb_mCairo, "FontWeight");
  rb_define_const (rb_mCairo_FontWeight,     "NORMAL",
                   INT2FIX (CAIRO_FONT_WEIGHT_NORMAL));
  rb_define_const (rb_mCairo_FontWeight,     "BOLD",
                   INT2FIX (CAIRO_FONT_WEIGHT_BOLD));


  /* cairo_subpixel_order_t */
  rb_mCairo_SubpixelOrder = rb_define_module_under (rb_mCairo, "SubpixelOrder");
  rb_define_const (rb_mCairo_SubpixelOrder,     "DEFAULT",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_DEFAULT));
  rb_define_const (rb_mCairo_SubpixelOrder,     "RGB",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_RGB));
  rb_define_const (rb_mCairo_SubpixelOrder,     "BGR",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_BGR));
  rb_define_const (rb_mCairo_SubpixelOrder,     "VRGB",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_VRGB));
  rb_define_const (rb_mCairo_SubpixelOrder,     "VBGR",
                   INT2FIX (CAIRO_SUBPIXEL_ORDER_VBGR));


  /* cairo_hint_style_t */
  rb_mCairo_HintStyle = rb_define_module_under (rb_mCairo, "HintStyle");
  rb_define_const (rb_mCairo_HintStyle,     "DEFAULT",
                   INT2FIX (CAIRO_HINT_STYLE_DEFAULT));
  rb_define_const (rb_mCairo_HintStyle,     "NONE",
                   INT2FIX (CAIRO_HINT_STYLE_NONE));
  rb_define_const (rb_mCairo_HintStyle,     "SLIGHT",
                   INT2FIX (CAIRO_HINT_STYLE_SLIGHT));
  rb_define_const (rb_mCairo_HintStyle,     "MEDIUM",
                   INT2FIX (CAIRO_HINT_STYLE_MEDIUM));
  rb_define_const (rb_mCairo_HintStyle,     "FULL",
                   INT2FIX (CAIRO_HINT_STYLE_FULL));


  /* cairo_hint_metrics_t */
  rb_mCairo_HintMetrics = rb_define_module_under (rb_mCairo, "HintMetrics");
  rb_define_const (rb_mCairo_HintMetrics,     "DEFAULT",
                   INT2FIX (CAIRO_HINT_METRICS_DEFAULT));
  rb_define_const (rb_mCairo_HintMetrics,     "ON",
                   INT2FIX (CAIRO_HINT_METRICS_ON));
  rb_define_const (rb_mCairo_HintMetrics,     "OFF",
                   INT2FIX (CAIRO_HINT_METRICS_OFF));


  /* cairo_font_type_t */
  rb_mCairo_FontType = rb_define_module_under (rb_mCairo, "FontType");
  rb_define_const (rb_mCairo_FontType,     "TOY",
                   INT2FIX (CAIRO_FONT_TYPE_TOY));
  rb_define_const (rb_mCairo_FontType,     "FT",
                   INT2FIX (CAIRO_FONT_TYPE_FT));
  rb_define_const (rb_mCairo_FontType,     "WIN32",
                   INT2FIX (CAIRO_FONT_TYPE_WIN32));
  rb_define_const (rb_mCairo_FontType,     "ATSUI",
                   INT2FIX (CAIRO_FONT_TYPE_ATSUI));


  /* cairo_path_data_type_t */
  rb_mCairo_PathDataType = rb_define_module_under (rb_mCairo, "PathDataType");
  rb_define_const (rb_mCairo_PathDataType, "MOVE_TO",
                   INT2FIX (CAIRO_PATH_MOVE_TO));
  rb_define_const (rb_mCairo_PathDataType, "LINE_TO",
                   INT2FIX (CAIRO_PATH_LINE_TO));
  rb_define_const (rb_mCairo_PathDataType, "CURVE_TO",
                   INT2FIX (CAIRO_PATH_CURVE_TO));
  rb_define_const (rb_mCairo_PathDataType, "CLOSE_PATH",
                   INT2FIX (CAIRO_PATH_CLOSE_PATH));


  /* cairo_content_t */
  rb_mCairo_Content = rb_define_module_under (rb_mCairo, "Content");
  rb_define_const (rb_mCairo_Content,    "COLOR",
                   INT2FIX (CAIRO_CONTENT_COLOR));
  rb_define_const (rb_mCairo_Content,    "ALPHA",
                   INT2FIX (CAIRO_CONTENT_ALPHA));
  rb_define_const (rb_mCairo_Content,    "COLOR_ALPHA",
                   INT2FIX (CAIRO_CONTENT_COLOR_ALPHA));


  /* cairo_surface_type_t */
  rb_mCairo_SurfaceType = rb_define_module_under (rb_mCairo, "SurfaceType");
  rb_define_const (rb_mCairo_SurfaceType,     "IMAGE",
                   INT2FIX (CAIRO_SURFACE_TYPE_IMAGE));
  rb_define_const (rb_mCairo_SurfaceType,     "PDF",
                   INT2FIX (CAIRO_SURFACE_TYPE_PDF));
  rb_define_const (rb_mCairo_SurfaceType,     "PS",
                   INT2FIX (CAIRO_SURFACE_TYPE_PS));
  rb_define_const (rb_mCairo_SurfaceType,     "XLIB",
                   INT2FIX (CAIRO_SURFACE_TYPE_XLIB));
  rb_define_const (rb_mCairo_SurfaceType,     "XCB",
                   INT2FIX (CAIRO_SURFACE_TYPE_XCB));
  rb_define_const (rb_mCairo_SurfaceType,     "GLITZ",
                   INT2FIX (CAIRO_SURFACE_TYPE_GLITZ));
  rb_define_const (rb_mCairo_SurfaceType,     "QUARTZ",
                   INT2FIX (CAIRO_SURFACE_TYPE_QUARTZ));
  rb_define_const (rb_mCairo_SurfaceType,     "WIN32",
                   INT2FIX (CAIRO_SURFACE_TYPE_WIN32));
  rb_define_const (rb_mCairo_SurfaceType,     "BEOS",
                   INT2FIX (CAIRO_SURFACE_TYPE_BEOS));
  rb_define_const (rb_mCairo_SurfaceType,     "DIRECTFB",
                   INT2FIX (CAIRO_SURFACE_TYPE_DIRECTFB));
  rb_define_const (rb_mCairo_SurfaceType,     "SVG",
                   INT2FIX (CAIRO_SURFACE_TYPE_SVG));
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_const (rb_mCairo_SurfaceType,     "OS2",
                   INT2FIX (CAIRO_SURFACE_TYPE_OS2));
#endif

  /* cairo_format_t */
  rb_mCairo_Format = rb_define_module_under (rb_mCairo, "Format");
  rb_define_const (rb_mCairo_Format,    "ARGB32",
                   INT2FIX (CAIRO_FORMAT_ARGB32));
  rb_define_const (rb_mCairo_Format,    "RGB24",
                   INT2FIX (CAIRO_FORMAT_RGB24));
  rb_define_const (rb_mCairo_Format,    "A8",
                   INT2FIX (CAIRO_FORMAT_A8));
  rb_define_const (rb_mCairo_Format,    "A1",
                   INT2FIX (CAIRO_FORMAT_A1));
#if !CAIRO_CHECK_VERSION(1, 3, 0)
  rb_define_const (rb_mCairo_Format,    "RGB16_565",
                   INT2FIX (CAIRO_FORMAT_RGB16_565));
#endif


  /* cairo_pattern_type_t */
  rb_mCairo_PatternType = rb_define_module_under (rb_mCairo, "PatternType");
  rb_define_const (rb_mCairo_PatternType,     "SOLID",
                   INT2FIX (CAIRO_PATTERN_TYPE_SOLID));
  rb_define_const (rb_mCairo_PatternType,     "SURFACE",
                   INT2FIX (CAIRO_PATTERN_TYPE_SURFACE));
  rb_define_const (rb_mCairo_PatternType,     "LINEAR",
                   INT2FIX (CAIRO_PATTERN_TYPE_LINEAR));
  rb_define_const (rb_mCairo_PatternType,     "RADIAL",
                   INT2FIX (CAIRO_PATTERN_TYPE_RADIAL));

  /* cairo_extend_t */
  rb_mCairo_Extend = rb_define_module_under (rb_mCairo, "Extend");
  rb_define_const (rb_mCairo_Extend,    "NONE",
                   INT2FIX (CAIRO_EXTEND_NONE));
  rb_define_const (rb_mCairo_Extend,    "REPEAT",
                   INT2FIX (CAIRO_EXTEND_REPEAT));
  rb_define_const (rb_mCairo_Extend,    "REFLECT",
                   INT2FIX (CAIRO_EXTEND_REFLECT));
  rb_define_const (rb_mCairo_Extend,    "PAD",
                   INT2FIX (CAIRO_EXTEND_PAD));


  /* cairo_filter_t */
  rb_mCairo_Filter = rb_define_module_under (rb_mCairo, "Filter");
  rb_define_const (rb_mCairo_Filter,    "FAST",
                   INT2FIX (CAIRO_FILTER_FAST));
  rb_define_const (rb_mCairo_Filter,    "GOOD",
                   INT2FIX (CAIRO_FILTER_GOOD));
  rb_define_const (rb_mCairo_Filter,    "BEST",
                   INT2FIX (CAIRO_FILTER_BEST));
  rb_define_const (rb_mCairo_Filter,    "NEAREST",
                   INT2FIX (CAIRO_FILTER_NEAREST));
  rb_define_const (rb_mCairo_Filter,    "BILINEAR",
                   INT2FIX (CAIRO_FILTER_BILINEAR));
  rb_define_const (rb_mCairo_Filter,    "GAUSSIAN",
                   INT2FIX (CAIRO_FILTER_GAUSSIAN));

#if CAIRO_HAS_SVG_SURFACE
  /* cairo_svg_version_t */
  rb_mCairo_SVGVersion = rb_define_module_under (rb_mCairo, "SVGVersion");
  rb_define_const (rb_mCairo_SVGVersion, "VERSION_1_1",
                   INT2FIX (CAIRO_SVG_VERSION_1_1));
  rb_define_const (rb_mCairo_SVGVersion, "VERSION_1_2",
                   INT2FIX (CAIRO_SVG_VERSION_1_2));
#endif
}
