/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *           (C) 2004 Øyvind Kolås <pippin@freedesktop.org>
 */

#include "rbcairo.h"

static void
init_cairo_fill_rule(void)
{
  VALUE mCairoFillRule = rb_define_module_under(mCairo, "FillRule");

  rb_define_const(mCairoFillRule, "WINDING", INT2NUM(CAIRO_FILL_RULE_WINDING));
  rb_define_const(mCairoFillRule, "EVEN_ODD", INT2NUM(CAIRO_FILL_RULE_EVEN_ODD));
}

static void
init_cairo_format(void)
{
  VALUE mCairoFormat = rb_define_module_under(mCairo, "Format");
  rb_define_const(mCairoFormat, "ARGB32", INT2NUM(CAIRO_FORMAT_ARGB32));
  rb_define_const(mCairoFormat, "RGB24", INT2NUM(CAIRO_FORMAT_RGB24));
  rb_define_const(mCairoFormat, "A8", INT2NUM(CAIRO_FORMAT_A8));
  rb_define_const(mCairoFormat, "A1", INT2NUM(CAIRO_FORMAT_A1));
}

static void
init_cairo_filter(void)
{
  VALUE mCairoFilter = rb_define_module_under(mCairo, "Filter");
  rb_define_const(mCairoFilter, "FAST", INT2NUM(CAIRO_FILTER_FAST));
  rb_define_const(mCairoFilter, "GOOD", INT2NUM(CAIRO_FILTER_GOOD));
  rb_define_const(mCairoFilter, "BEST", INT2NUM(CAIRO_FILTER_BEST));
  rb_define_const(mCairoFilter, "NEAREST", INT2NUM(CAIRO_FILTER_NEAREST));
  rb_define_const(mCairoFilter, "BILINEAR", INT2NUM(CAIRO_FILTER_BILINEAR));
  rb_define_const(mCairoFilter, "GAUSSIAN", INT2NUM(CAIRO_FILTER_GAUSSIAN));
}

static void
init_cairo_status(void)
{
  VALUE mCairoStatus = rb_define_module_under(mCairo, "Status");
  rb_define_const(mCairoStatus, "SUCCESS", INT2NUM(CAIRO_STATUS_SUCCESS));
  rb_define_const(mCairoStatus, "NO_MEMORY", INT2NUM(CAIRO_STATUS_NO_MEMORY));
  rb_define_const(mCairoStatus, "INVALID_RESTORE", INT2NUM(CAIRO_STATUS_INVALID_RESTORE));
  rb_define_const(mCairoStatus, "INVALID_POP_GROUP", INT2NUM(CAIRO_STATUS_INVALID_POP_GROUP));
  rb_define_const(mCairoStatus, "NO_CURRENT_POINT", INT2NUM(CAIRO_STATUS_NO_CURRENT_POINT));
  rb_define_const(mCairoStatus, "INVALID_MATRIX", INT2NUM(CAIRO_STATUS_INVALID_MATRIX));
  rb_define_const(mCairoStatus, "NO_TARGET_SURFACE", INT2NUM(CAIRO_STATUS_NO_TARGET_SURFACE));
  rb_define_const(mCairoStatus, "NULL_POINTER", INT2NUM(CAIRO_STATUS_NULL_POINTER));
}

static void
init_cairo_line_join(void)
{
  VALUE mCairoLineJoin = rb_define_module_under(mCairo, "LineJoin");
  rb_define_const(mCairoLineJoin, "MITER", INT2NUM(CAIRO_LINE_JOIN_MITER));
  rb_define_const(mCairoLineJoin, "ROUND", INT2NUM(CAIRO_LINE_JOIN_ROUND));
  rb_define_const(mCairoLineJoin, "BEVEL", INT2NUM(CAIRO_LINE_JOIN_BEVEL));
}

static void
init_cairo_line_cap(void)
{
  VALUE mCairoLineCap = rb_define_module_under(mCairo, "LineCap");
  rb_define_const(mCairoLineCap, "BUTT", INT2NUM(CAIRO_LINE_CAP_BUTT));
  rb_define_const(mCairoLineCap, "ROUND", INT2NUM(CAIRO_LINE_CAP_ROUND));
  rb_define_const(mCairoLineCap, "SQUARE", INT2NUM(CAIRO_LINE_CAP_SQUARE));
}

static void
init_cairo_operator(void)
{
  VALUE mCairoOperator = rb_define_module_under(mCairo, "Operator");
  rb_define_const(mCairoOperator, "CLEAR", INT2NUM(CAIRO_OPERATOR_CLEAR));
  rb_define_const(mCairoOperator, "SRC", INT2NUM(CAIRO_OPERATOR_SRC));
  rb_define_const(mCairoOperator, "DST", INT2NUM(CAIRO_OPERATOR_DST));
  rb_define_const(mCairoOperator, "OVER", INT2NUM(CAIRO_OPERATOR_OVER));
  rb_define_const(mCairoOperator, "OVER_REVERSE", INT2NUM(CAIRO_OPERATOR_OVER_REVERSE));
  rb_define_const(mCairoOperator, "IN", INT2NUM(CAIRO_OPERATOR_IN));
  rb_define_const(mCairoOperator, "IN_REVERSE", INT2NUM(CAIRO_OPERATOR_IN_REVERSE));
  rb_define_const(mCairoOperator, "OUT", INT2NUM(CAIRO_OPERATOR_OUT));
  rb_define_const(mCairoOperator, "OUT_REVERSE", INT2NUM(CAIRO_OPERATOR_OUT_REVERSE));
  rb_define_const(mCairoOperator, "ATOP", INT2NUM(CAIRO_OPERATOR_ATOP));
  rb_define_const(mCairoOperator, "ATOP_REVERSE", INT2NUM(CAIRO_OPERATOR_ATOP_REVERSE));
  rb_define_const(mCairoOperator, "XOR", INT2NUM(CAIRO_OPERATOR_XOR));
  rb_define_const(mCairoOperator, "ADD", INT2NUM(CAIRO_OPERATOR_ADD));
  rb_define_const(mCairoOperator, "SATURATE", INT2NUM(CAIRO_OPERATOR_SATURATE));
}

static void
init_cairo_extend(void) 
{
  VALUE mCairoExtend = rb_define_module_under(mCairo, "Extend");
  rb_define_const(mCairoExtend, "NONE", INT2NUM(CAIRO_EXTEND_NONE));
  rb_define_const(mCairoExtend, "REPEAT", INT2NUM(CAIRO_EXTEND_REPEAT));
  rb_define_const(mCairoExtend, "REFLECT", INT2NUM(CAIRO_EXTEND_REFLECT));
}

static void
init_cairo_font_weight(void)
{
  VALUE mCairoFontWeight = rb_define_module_under(mCairo, "FontWeight");
  rb_define_const(mCairoFontWeight, "NORMAL", INT2NUM(CAIRO_FONT_WEIGHT_NORMAL));
  rb_define_const(mCairoFontWeight, "BOLD", INT2NUM(CAIRO_FONT_WEIGHT_BOLD));
}

static void
init_cairo_font_slant(void)
{
  VALUE mCairoFontSlant = rb_define_module_under(mCairo, "FontSlant");
  rb_define_const(mCairoFontSlant, "NORMAL", INT2NUM(CAIRO_FONT_SLANT_NORMAL));
  rb_define_const(mCairoFontSlant, "ITALIC", INT2NUM(CAIRO_FONT_SLANT_ITALIC));
  rb_define_const(mCairoFontSlant, "OBLIQUE", INT2NUM(CAIRO_FONT_SLANT_OBLIQUE));
}

void
constants_init(void)
{
  init_cairo_fill_rule();
  init_cairo_format();
  init_cairo_filter();
  init_cairo_status();
  init_cairo_line_join();
  init_cairo_line_cap();
  init_cairo_operator();
  init_cairo_extend();
  init_cairo_font_weight();
  init_cairo_font_slant();
}
