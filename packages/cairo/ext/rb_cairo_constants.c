/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo_constants.h"

void
Init_cairo_constants (void)
{
  rb_define_const (rb_mCairo,    "FONT_WEIGHT_NORMAL",
                   INT2FIX (CAIRO_FONT_WEIGHT_NORMAL));
  rb_define_const (rb_mCairo,    "FONT_WEIGHT_BOLD",
                   INT2FIX (CAIRO_FONT_WEIGHT_BOLD));
  rb_define_const (rb_mCairo,    "FONT_SLANT_NORMAL",
                   INT2FIX (CAIRO_FONT_SLANT_NORMAL));
  rb_define_const (rb_mCairo,    "FONT_SLANT_ITALIC",
                   INT2FIX (CAIRO_FONT_SLANT_ITALIC));
  rb_define_const (rb_mCairo,    "FONT_SLANT_OBLIQUE",
                   INT2FIX (CAIRO_FONT_SLANT_OBLIQUE));

  rb_define_const (rb_mCairo,    "FORMAT_ARGB32",
                   INT2FIX (CAIRO_FORMAT_ARGB32));
  rb_define_const (rb_mCairo,    "FORMAT_RGB24",
                   INT2FIX (CAIRO_FORMAT_RGB24));
  rb_define_const (rb_mCairo,    "FORMAT_A8",
                   INT2FIX (CAIRO_FORMAT_A8));
  rb_define_const (rb_mCairo,    "FORMAT_A1",
                   INT2FIX (CAIRO_FORMAT_A1));

  rb_define_const (rb_mCairo,    "FILL_RULE_WINDING",
                   INT2FIX (CAIRO_FILL_RULE_WINDING));
  rb_define_const (rb_mCairo,    "FILL_RULE_EVEN_ODD",
                   INT2FIX (CAIRO_FILL_RULE_EVEN_ODD));

  rb_define_const (rb_mCairo,    "LINE_CAP_BUTT",
                   INT2FIX (CAIRO_LINE_CAP_BUTT));
  rb_define_const (rb_mCairo,    "LINE_CAP_ROUND",
                   INT2FIX (CAIRO_LINE_CAP_ROUND));
  rb_define_const (rb_mCairo,    "LINE_CAP_SQUARE",
                   INT2FIX (CAIRO_LINE_CAP_SQUARE));

  rb_define_const (rb_mCairo,    "LINE_JOIN_MITER",
                   INT2FIX (CAIRO_LINE_JOIN_MITER));
  rb_define_const (rb_mCairo,    "LINE_JOIN_ROUND",
                   INT2FIX (CAIRO_LINE_JOIN_ROUND));
  rb_define_const (rb_mCairo,    "LINE_JOIN_BEVEL",
                   INT2FIX (CAIRO_LINE_JOIN_BEVEL));

  rb_define_const (rb_mCairo,    "OPERATOR_CLEAR",
                   INT2FIX (CAIRO_OPERATOR_CLEAR));
  rb_define_const (rb_mCairo,    "OPERATOR_SRC",
                   INT2FIX (CAIRO_OPERATOR_SRC));
  rb_define_const (rb_mCairo,    "OPERATOR_DST",
                   INT2FIX (CAIRO_OPERATOR_DST));
  rb_define_const (rb_mCairo,    "OPERATOR_OVER",
                   INT2FIX (CAIRO_OPERATOR_OVER));
  rb_define_const (rb_mCairo,    "OPERATOR_OVER_REVERSE",
                   INT2FIX (CAIRO_OPERATOR_OVER_REVERSE));
  rb_define_const (rb_mCairo,    "OPERATOR_IN",
                   INT2FIX (CAIRO_OPERATOR_IN));
  rb_define_const (rb_mCairo,    "OPERATOR_IN_REVERSE",
                   INT2FIX (CAIRO_OPERATOR_IN_REVERSE));
  rb_define_const (rb_mCairo,    "OPERATOR_OUT",
                   INT2FIX (CAIRO_OPERATOR_OUT));
  rb_define_const (rb_mCairo,    "OPERATOR_OUT_REVERSE",
                   INT2FIX (CAIRO_OPERATOR_OUT_REVERSE));
  rb_define_const (rb_mCairo,    "OPERATOR_ATOP",
                   INT2FIX (CAIRO_OPERATOR_ATOP));
  rb_define_const (rb_mCairo,    "OPERATOR_ATOP_REVERSE",
                   INT2FIX (CAIRO_OPERATOR_ATOP_REVERSE));
  rb_define_const (rb_mCairo,    "OPERATOR_XOR",
                   INT2FIX (CAIRO_OPERATOR_XOR));
  rb_define_const (rb_mCairo,    "OPERATOR_ADD",
                   INT2FIX (CAIRO_OPERATOR_ADD));
  rb_define_const (rb_mCairo,    "OPERATOR_SATURATE",
                   INT2FIX (CAIRO_OPERATOR_SATURATE));
}
