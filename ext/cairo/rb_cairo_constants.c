/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-09-19 12:56:27 $
 *
 * Copyright 2005-2019 Kouhei Sutou <kou@cozmixng.org>
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
VALUE rb_mCairo_PathDataType;
VALUE rb_mCairo_Content;
VALUE rb_mCairo_Format;
VALUE rb_mCairo_Extend;
VALUE rb_mCairo_Filter;
VALUE rb_mCairo_SVGVersion = Qnil;
VALUE rb_mCairo_PSLevel = Qnil;
VALUE rb_mCairo_TextClusterFlag = Qnil;
VALUE rb_mCairo_PDFVersion = Qnil;
VALUE rb_mCairo_ScriptMode = Qnil;
VALUE rb_mCairo_MimeType = Qnil;
VALUE rb_mCairo_RegionOverlap = Qnil;
VALUE rb_mCairo_PDFOutlineFlags = Qnil;
VALUE rb_mCairo_PDFMetadata = Qnil;
VALUE rb_mCairo_SVGUnit = Qnil;

#define CAIRO_OPERATOR_MIN CAIRO_OPERATOR_CLEAR
#if CAIRO_CHECK_VERSION(1, 10, 0)
#  define CAIRO_OPERATOR_MAX CAIRO_OPERATOR_HSL_LUMINOSITY
#else
#  define CAIRO_OPERATOR_MAX CAIRO_OPERATOR_SATURATE
#endif

#define CAIRO_ANTIALIAS_MIN CAIRO_ANTIALIAS_DEFAULT
#if CAIRO_CHECK_VERSION(1, 11, 4)
#  define CAIRO_ANTIALIAS_MAX CAIRO_ANTIALIAS_BEST
#else
#  define CAIRO_ANTIALIAS_MAX CAIRO_ANTIALIAS_SUBPIXEL
#endif

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
#define CAIRO_HINT_METRICS_MAX CAIRO_HINT_METRICS_ON

#define CAIRO_PATH_MIN CAIRO_PATH_MOVE_TO
#define CAIRO_PATH_MAX CAIRO_PATH_CLOSE_PATH

#define CAIRO_CONTENT_MIN CAIRO_CONTENT_COLOR
#define CAIRO_CONTENT_MAX CAIRO_CONTENT_COLOR_ALPHA

#if CAIRO_CHECK_VERSION(1, 10, 0)
#  define CAIRO_FORMAT_MIN CAIRO_FORMAT_INVALID
#else
#  define CAIRO_FORMAT_MIN CAIRO_FORMAT_ARGB32
#endif
#if CAIRO_CHECK_VERSION(1, 17, 2)
#  define CAIRO_FORMAT_MAX CAIRO_FORMAT_RGBA128F
#elif CAIRO_CHECK_VERSION(1, 11, 4)
#  define CAIRO_FORMAT_MAX CAIRO_FORMAT_RGB30
#else
#  define CAIRO_FORMAT_MAX CAIRO_FORMAT_RGB16_565
#endif

#define CAIRO_EXTEND_MIN CAIRO_EXTEND_NONE
#define CAIRO_EXTEND_MAX CAIRO_EXTEND_PAD

#define CAIRO_FILTER_MIN CAIRO_FILTER_FAST
#define CAIRO_FILTER_MAX CAIRO_FILTER_GAUSSIAN

#define CAIRO_SVG_VERSION_MIN CAIRO_SVG_VERSION_1_1
#define CAIRO_SVG_VERSION_MAX CAIRO_SVG_VERSION_1_2

#define CAIRO_PS_LEVEL_MIN CAIRO_PS_LEVEL_2
#define CAIRO_PS_LEVEL_MAX CAIRO_PS_LEVEL_3

#define CAIRO_PDF_VERSION_MIN CAIRO_PDF_VERSION_1_4
#define CAIRO_PDF_VERSION_MAX CAIRO_PDF_VERSION_1_5

#define CAIRO_TEXT_CLUSTER_FLAG_MIN 0
#define CAIRO_TEXT_CLUSTER_FLAG_MAX CAIRO_TEXT_CLUSTER_FLAG_BACKWARD

#if CAIRO_CHECK_VERSION(1, 11, 4)
#  define CAIRO_SCRIPT_MODE_MIN CAIRO_SCRIPT_MODE_ASCII
#  define CAIRO_SCRIPT_MODE_MAX CAIRO_SCRIPT_MODE_BINARY
#else
#  define CAIRO_SCRIPT_MODE_MIN CAIRO_SCRIPT_MODE_BINARY
#  define CAIRO_SCRIPT_MODE_MAX CAIRO_SCRIPT_MODE_ASCII
#endif


#define CAIRO_REGION_OVERLAP_MIN CAIRO_REGION_OVERLAP_IN
#define CAIRO_REGION_OVERLAP_MAX CAIRO_REGION_OVERLAP_PART

#if CAIRO_CHECK_VERSION(1, 15, 5)
#  define CAIRO_PDF_OUTLINE_FLAGS_MIN CAIRO_PDF_OUTLINE_FLAG_OPEN
#  define CAIRO_PDF_OUTLINE_FLAGS_MAX CAIRO_PDF_OUTLINE_FLAG_ITALIC
#else
#  define CAIRO_PDF_OUTLINE_FLAGS_MIN CAIRO_BOOKMARK_FLAG_OPEN
#  define CAIRO_PDF_OUTLINE_FLAGS_MAX CAIRO_BOOKMARK_FLAG_ITALIC
#endif

#define CAIRO_PDF_METADATA_MIN CAIRO_PDF_METADATA_TITLE
#define CAIRO_PDF_METADATA_MAX CAIRO_PDF_METADATA_MOD_DATE

#define CAIRO_SVG_UNIT_MIN CAIRO_SVG_UNIT_USER
#define CAIRO_SVG_UNIT_MAX CAIRO_SVG_UNIT_PERCENT

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
#ifdef CAIRO_HAS_SVG_SURFACE
DEFINE_RVAL2ENUM(svg_version, SVG_VERSION)
#endif

#ifdef CAIRO_HAS_PS_SURFACE
#  if CAIRO_CHECK_VERSION(1, 5, 2)
DEFINE_RVAL2ENUM(ps_level, PS_LEVEL)
#define PS_LEVEL_ENUM_DEFINED 1
#  endif
#endif

#ifdef CAIRO_HAS_PDF_SURFACE
#  if CAIRO_CHECK_VERSION(1, 10, 0)
DEFINE_RVAL2ENUM(pdf_version, PDF_VERSION)
#define PDF_VERSION_ENUM_DEFINED 1
#  endif
#endif

#if CAIRO_CHECK_VERSION(1, 7, 6)
DEFINE_RVAL2ENUM(text_cluster_flags, TEXT_CLUSTER_FLAG)
#endif

#ifdef CAIRO_HAS_SCRIPT_SURFACE
DEFINE_RVAL2ENUM(script_mode, SCRIPT_MODE)
#endif

#if CAIRO_CHECK_VERSION(1, 10, 0)
DEFINE_RVAL2ENUM(region_overlap, REGION_OVERLAP)
#endif

#if CAIRO_CHECK_VERSION(1, 15, 4)
DEFINE_RVAL2ENUM(pdf_outline_flags, PDF_OUTLINE_FLAGS)
DEFINE_RVAL2ENUM(pdf_metadata, PDF_METADATA)
#endif

#if CAIRO_CHECK_VERSION(1, 15, 10)
DEFINE_RVAL2ENUM(svg_unit, SVG_UNIT)
#endif

#if defined(RB_CAIRO_PLATFORM_WIN32) && !defined(PS_LEVEL_ENUM_DEFINED)
void
rb_cairo_ps_level_from_ruby_object (VALUE rb_ps_level)
{
  /* dummy */
}
#endif


#ifdef CAIRO_HAS_SVG_SURFACE
static VALUE
cr_svg_get_versions (VALUE self)
{
  VALUE rb_versions;
  int i, num_versions;
  cairo_svg_version_t const *versions;

  cairo_svg_get_versions (&versions, &num_versions);

  rb_versions = rb_ary_new2 (num_versions);

  for (i = 0; i < num_versions; i++)
    {
      rb_ary_push (rb_versions, INT2NUM (versions[i]));
    }

  return rb_versions;
}

static VALUE
cr_svg_version_to_string (int argc, VALUE *argv, VALUE self)
{
  if (argc == 0)
    {
      return rb_call_super (argc, argv);
    }
  else
    {
      VALUE version;
      const char *ver_str;
      rb_scan_args (argc, argv, "1", &version);
      ver_str = cairo_svg_version_to_string (RVAL2CRSVGVERSION(version));
      return rb_str_new2 (ver_str);
    }
}
#endif

#if CAIRO_CHECK_VERSION(1, 5, 8)
static VALUE
cr_format_stride_for_width (VALUE self, VALUE format, VALUE width)
{
  return INT2NUM (cairo_format_stride_for_width (RVAL2CRFORMAT (format),
                                                 NUM2INT (width)));
}
#endif

#ifdef CAIRO_HAS_PS_SURFACE
#  if CAIRO_CHECK_VERSION(1, 5, 8)
static VALUE
cr_ps_get_levels (VALUE self)
{
  VALUE rb_levels;
  const cairo_ps_level_t *levels;
  int i, n_levels;

  cairo_ps_get_levels (&levels, &n_levels);

  rb_levels = rb_ary_new2 (n_levels);
  for (i = 0; i < n_levels; i++)
    {
      rb_ary_push (rb_levels, INT2NUM (levels[i]));
    }

  return rb_levels;
}

static VALUE
cr_ps_level_to_string (int argc, VALUE *argv, VALUE self)
{
  if (argc == 0)
    {
      return rb_call_super (argc, argv);
    }
  else
    {
      VALUE level;
      rb_scan_args (argc, argv, "1", &level);
      return rb_str_new2 (cairo_ps_level_to_string (RVAL2CRPSLEVEL (level)));
    }
}
#  endif
#endif

#ifdef CAIRO_HAS_PDF_SURFACE
#  if CAIRO_CHECK_VERSION(1, 10, 0)
static VALUE
cr_pdf_get_versions (VALUE self)
{
  VALUE rb_versions;
  const cairo_pdf_version_t *versions;
  int i, n_versions;

  cairo_pdf_get_versions (&versions, &n_versions);

  rb_versions = rb_ary_new2 (n_versions);
  for (i = 0; i < n_versions; i++)
    {
      rb_ary_push (rb_versions, INT2NUM (versions[i]));
    }

  return rb_versions;
}

static VALUE
cr_pdf_version_to_string (int argc, VALUE *argv, VALUE self)
{
  if (argc == 0)
    {
      return rb_call_super (argc, argv);
    }
  else
    {
      VALUE version;
      rb_scan_args (argc, argv, "1", &version);
      return rb_str_new2 (cairo_pdf_version_to_string (RVAL2CRPDFVERSION (version)));
    }
}
#  endif
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

#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_define_const (rb_mCairo_Operator,    "MULTIPLY",
                   INT2FIX (CAIRO_OPERATOR_MULTIPLY));
  rb_define_const (rb_mCairo_Operator,    "SCREEN",
                   INT2FIX (CAIRO_OPERATOR_SCREEN));
  rb_define_const (rb_mCairo_Operator,    "OVERLAY",
                   INT2FIX (CAIRO_OPERATOR_OVERLAY));
  rb_define_const (rb_mCairo_Operator,    "DARKEN",
                   INT2FIX (CAIRO_OPERATOR_DARKEN));
  rb_define_const (rb_mCairo_Operator,    "LIGHTEN",
                   INT2FIX (CAIRO_OPERATOR_LIGHTEN));
  rb_define_const (rb_mCairo_Operator,    "COLOR_DODGE",
                   INT2FIX (CAIRO_OPERATOR_COLOR_DODGE));
  rb_define_const (rb_mCairo_Operator,    "COLOR_BURN",
                   INT2FIX (CAIRO_OPERATOR_COLOR_BURN));
  rb_define_const (rb_mCairo_Operator,    "HARD_LIGHT",
                   INT2FIX (CAIRO_OPERATOR_HARD_LIGHT));
  rb_define_const (rb_mCairo_Operator,    "SOFT_LIGHT",
                   INT2FIX (CAIRO_OPERATOR_SOFT_LIGHT));
  rb_define_const (rb_mCairo_Operator,    "DIFFERENCE",
                   INT2FIX (CAIRO_OPERATOR_DIFFERENCE));
  rb_define_const (rb_mCairo_Operator,    "EXCLUSION",
                   INT2FIX (CAIRO_OPERATOR_EXCLUSION));
  rb_define_const (rb_mCairo_Operator,    "HSL_HUE",
                   INT2FIX (CAIRO_OPERATOR_HSL_HUE));
  rb_define_const (rb_mCairo_Operator,    "HSL_SATURATION",
                   INT2FIX (CAIRO_OPERATOR_HSL_SATURATION));
  rb_define_const (rb_mCairo_Operator,    "HSL_COLOR",
                   INT2FIX (CAIRO_OPERATOR_HSL_COLOR));
  rb_define_const (rb_mCairo_Operator,    "HSL_LUMINOSITY",
                   INT2FIX (CAIRO_OPERATOR_HSL_LUMINOSITY));
#endif

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
#if CAIRO_CHECK_VERSION(1, 11, 4)
  rb_define_const (rb_mCairo_Antialias,    "FAST",
                   INT2FIX (CAIRO_ANTIALIAS_FAST));
  rb_define_const (rb_mCairo_Antialias,    "GOOD",
                   INT2FIX (CAIRO_ANTIALIAS_GOOD));
  rb_define_const (rb_mCairo_Antialias,    "BEST",
                   INT2FIX (CAIRO_ANTIALIAS_BEST));
#endif


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


  /* cairo_format_t */
  rb_mCairo_Format = rb_define_module_under (rb_mCairo, "Format");
#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_define_const (rb_mCairo_Format,    "INVALID",
                   INT2FIX (CAIRO_FORMAT_INVALID));
#endif
  rb_define_const (rb_mCairo_Format,    "ARGB32",
                   INT2FIX (CAIRO_FORMAT_ARGB32));
  rb_define_const (rb_mCairo_Format,    "RGB24",
                   INT2FIX (CAIRO_FORMAT_RGB24));
  rb_define_const (rb_mCairo_Format,    "A8",
                   INT2FIX (CAIRO_FORMAT_A8));
  rb_define_const (rb_mCairo_Format,    "A1",
                   INT2FIX (CAIRO_FORMAT_A1));
  rb_define_const (rb_mCairo_Format,    "RGB16_565",
                   INT2FIX (CAIRO_FORMAT_RGB16_565));
#if CAIRO_CHECK_VERSION(1, 11, 4)
  rb_define_const (rb_mCairo_Format,    "RGB30",
                   INT2FIX (CAIRO_FORMAT_RGB30));
#endif
#if CAIRO_CHECK_VERSION(1, 17, 2)
  rb_define_const (rb_mCairo_Format,    "RGB96F",
                   INT2FIX (CAIRO_FORMAT_RGB96F));
  rb_define_const (rb_mCairo_Format,    "RGBA128F",
                   INT2FIX (CAIRO_FORMAT_RGBA128F));
#endif

#if CAIRO_CHECK_VERSION(1, 5, 8)
  rb_define_singleton_method (rb_mCairo_Format, "stride_for_width",
                              cr_format_stride_for_width, 2);
#endif


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

#ifdef CAIRO_HAS_SVG_SURFACE
  /* cairo_svg_version_t */
  rb_mCairo_SVGVersion = rb_define_module_under (rb_mCairo, "SVGVersion");
  rb_define_const (rb_mCairo_SVGVersion, "VERSION_1_1",
                   INT2FIX (CAIRO_SVG_VERSION_1_1));
  rb_define_const (rb_mCairo_SVGVersion, "VERSION_1_2",
                   INT2FIX (CAIRO_SVG_VERSION_1_2));

  rb_define_singleton_method (rb_mCairo_SVGVersion, "list",
                              cr_svg_get_versions, 0);
  rb_define_singleton_method (rb_mCairo_SVGVersion, "name",
                              cr_svg_version_to_string, -1);
#endif

#ifdef CAIRO_HAS_PS_SURFACE
#  if CAIRO_CHECK_VERSION(1, 5, 2)
  /* cairo_ps_level_t */
  rb_mCairo_PSLevel = rb_define_module_under (rb_mCairo, "PSLevel");
  rb_define_const (rb_mCairo_PSLevel, "LEVEL_2", INT2FIX (CAIRO_PS_LEVEL_2));
  rb_define_const (rb_mCairo_PSLevel, "LEVEL_3", INT2FIX (CAIRO_PS_LEVEL_3));

  rb_define_singleton_method (rb_mCairo_PSLevel, "list",
                              cr_ps_get_levels, 0);
  rb_define_singleton_method (rb_mCairo_PSLevel, "name",
                              cr_ps_level_to_string, -1);
#  endif
#endif

#ifdef CAIRO_HAS_PDF_SURFACE
#  if CAIRO_CHECK_VERSION(1, 10, 0)
  /* cairo_pdf_version_t */
  rb_mCairo_PDFVersion = rb_define_module_under (rb_mCairo, "PDFVersion");
  rb_define_const (rb_mCairo_PDFVersion, "VERSION_1_4",
                   INT2FIX (CAIRO_PDF_VERSION_1_4));
  rb_define_const (rb_mCairo_PDFVersion, "VERSION_1_5",
                   INT2FIX (CAIRO_PDF_VERSION_1_5));

  rb_define_singleton_method (rb_mCairo_PDFVersion, "list",
                              cr_pdf_get_versions, 0);
  rb_define_singleton_method (rb_mCairo_PDFVersion, "name",
                              cr_pdf_version_to_string, -1);
#  endif
#endif

#if CAIRO_CHECK_VERSION(1, 7, 6)
  /* cairo_text_cluster_flags_t */
  rb_mCairo_TextClusterFlag =
    rb_define_module_under (rb_mCairo, "TextClusterFlag");
  rb_define_const (rb_mCairo_TextClusterFlag, "BACKWARD",
                   INT2FIX (CAIRO_TEXT_CLUSTER_FLAG_BACKWARD));
#endif

#ifdef CAIRO_HAS_SCRIPT_SURFACE
  /* cairo_script_mode_t */
  rb_mCairo_ScriptMode = rb_define_module_under (rb_mCairo, "ScriptMode");
  rb_define_const (rb_mCairo_ScriptMode, "BINARY",
                   INT2FIX (CAIRO_SCRIPT_MODE_BINARY));
  rb_define_const (rb_mCairo_ScriptMode, "ASCII",
                   INT2FIX (CAIRO_SCRIPT_MODE_ASCII));
#endif

#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_mCairo_MimeType = rb_define_module_under (rb_mCairo, "MimeType");

  rb_define_const (rb_mCairo_MimeType, "JPEG",
                   rb_str_new2 (CAIRO_MIME_TYPE_JPEG));
  rb_define_const (rb_mCairo_MimeType, "PNG",
                   rb_str_new2 (CAIRO_MIME_TYPE_PNG));
  rb_define_const (rb_mCairo_MimeType, "JP2",
                   rb_str_new2 (CAIRO_MIME_TYPE_JP2));
  rb_define_const (rb_mCairo_MimeType, "URI",
                   rb_str_new2 (CAIRO_MIME_TYPE_URI));
#endif
#if CAIRO_CHECK_VERSION(1, 11, 4)
  rb_define_const (rb_mCairo_MimeType, "UNIQUE_ID",
                   rb_str_new2 (CAIRO_MIME_TYPE_UNIQUE_ID));
#endif
#if CAIRO_CHECK_VERSION(1, 14, 0)
  rb_define_const (rb_mCairo_MimeType, "JBIG2",
                   rb_str_new2 (CAIRO_MIME_TYPE_JBIG2));
  rb_define_const (rb_mCairo_MimeType, "JBIG2_GLOBAL",
                   rb_str_new2 (CAIRO_MIME_TYPE_JBIG2_GLOBAL));
  rb_define_const (rb_mCairo_MimeType, "JBIG2_GLOBAL_ID",
                   rb_str_new2 (CAIRO_MIME_TYPE_JBIG2_GLOBAL_ID));
#endif
#if CAIRO_CHECK_VERSION(1, 15, 10)
  rb_define_const (rb_mCairo_MimeType, "CCITT_FAX",
                   rb_str_new_cstr (CAIRO_MIME_TYPE_CCITT_FAX));
  rb_define_const (rb_mCairo_MimeType, "CCITT_FAX_PARAMS",
                   rb_str_new_cstr (CAIRO_MIME_TYPE_CCITT_FAX_PARAMS));
  rb_define_const (rb_mCairo_MimeType, "EPS",
                   rb_str_new_cstr (CAIRO_MIME_TYPE_EPS));
  rb_define_const (rb_mCairo_MimeType, "EPS_PARAMS",
                   rb_str_new_cstr (CAIRO_MIME_TYPE_EPS_PARAMS));
#endif

#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_mCairo_RegionOverlap = rb_define_module_under (rb_mCairo, "RegionOverlap");

  rb_define_const (rb_mCairo_RegionOverlap, "IN",
                   INT2FIX (CAIRO_REGION_OVERLAP_IN));
  rb_define_const (rb_mCairo_RegionOverlap, "OUT",
                   INT2FIX (CAIRO_REGION_OVERLAP_OUT));
  rb_define_const (rb_mCairo_RegionOverlap, "PART",
                   INT2FIX (CAIRO_REGION_OVERLAP_PART));
#endif

#if CAIRO_CHECK_VERSION(1, 15, 4)
  rb_mCairo_PDFOutlineFlags =
    rb_define_module_under (rb_mCairo, "PDFOutlineFlags");
#  if CAIRO_CHECK_VERSION(1, 15, 5)
  rb_define_const (rb_mCairo_PDFOutlineFlags, "OPEN",
                   INT2NUM (CAIRO_PDF_OUTLINE_FLAG_OPEN));
  rb_define_const (rb_mCairo_PDFOutlineFlags, "BOLD",
                   INT2NUM (CAIRO_PDF_OUTLINE_FLAG_BOLD));
  rb_define_const (rb_mCairo_PDFOutlineFlags, "ITALIC",
                   INT2NUM (CAIRO_PDF_OUTLINE_FLAG_ITALIC));
#  else
  rb_define_const (rb_mCairo_PDFOutlineFlags, "OPEN",
                   INT2NUM (CAIRO_BOOKMARK_FLAG_OPEN));
  rb_define_const (rb_mCairo_PDFOutlineFlags, "BOLD",
                   INT2NUM (CAIRO_BOOKMARK_FLAG_BOLD));
  rb_define_const (rb_mCairo_PDFOutlineFlags, "ITALIC",
                   INT2NUM (CAIRO_BOOKMARK_FLAG_ITALIC));
#  endif

  rb_mCairo_PDFMetadata =
    rb_define_module_under (rb_mCairo, "PDFMetadata");
  rb_define_const (rb_mCairo_PDFMetadata, "TITLE",
                   INT2NUM (CAIRO_PDF_METADATA_TITLE));
  rb_define_const (rb_mCairo_PDFMetadata, "AUTHOR",
                   INT2NUM (CAIRO_PDF_METADATA_AUTHOR));
  rb_define_const (rb_mCairo_PDFMetadata, "SUBJECT",
                   INT2NUM (CAIRO_PDF_METADATA_SUBJECT));
  rb_define_const (rb_mCairo_PDFMetadata, "KEYWORDS",
                   INT2NUM (CAIRO_PDF_METADATA_KEYWORDS));
  rb_define_const (rb_mCairo_PDFMetadata, "CREATOR",
                   INT2NUM (CAIRO_PDF_METADATA_CREATOR));
  rb_define_const (rb_mCairo_PDFMetadata, "CREATE_DATE",
                   INT2NUM (CAIRO_PDF_METADATA_CREATE_DATE));
  rb_define_const (rb_mCairo_PDFMetadata, "MOD_DATE",
                   INT2NUM (CAIRO_PDF_METADATA_MOD_DATE));
#endif

#if CAIRO_CHECK_VERSION(1, 15, 10)
  rb_mCairo_SVGUnit =
    rb_define_module_under (rb_mCairo, "SVGUnit");
  rb_define_const (rb_mCairo_SVGUnit, "USER",
                   INT2NUM (CAIRO_SVG_UNIT_USER));
  rb_define_const (rb_mCairo_SVGUnit, "EM",
                   INT2NUM (CAIRO_SVG_UNIT_EM));
  rb_define_const (rb_mCairo_SVGUnit, "EX",
                   INT2NUM (CAIRO_SVG_UNIT_EX));
  rb_define_const (rb_mCairo_SVGUnit, "PX",
                   INT2NUM (CAIRO_SVG_UNIT_PX));
  rb_define_const (rb_mCairo_SVGUnit, "IN",
                   INT2NUM (CAIRO_SVG_UNIT_IN));
  rb_define_const (rb_mCairo_SVGUnit, "CM",
                   INT2NUM (CAIRO_SVG_UNIT_CM));
  rb_define_const (rb_mCairo_SVGUnit, "MM",
                   INT2NUM (CAIRO_SVG_UNIT_MM));
  rb_define_const (rb_mCairo_SVGUnit, "PT",
                   INT2NUM (CAIRO_SVG_UNIT_PT));
  rb_define_const (rb_mCairo_SVGUnit, "PC",
                   INT2NUM (CAIRO_SVG_UNIT_PC));
  rb_define_const (rb_mCairo_SVGUnit, "PERCENT",
                   INT2NUM (CAIRO_SVG_UNIT_PERCENT));
#endif
}
