/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"

#define _SELF  (DATA_PTR(self))

VALUE rb_cCairo_Pattern;

cairo_pattern_t *
rb_v_to_cairo_pattern_t (VALUE value)
{
  cairo_pattern_t *pattern;
  if (CLASS_OF (value) != rb_cCairo_Pattern)
    {
      rb_raise (rb_eTypeError, "not a cairo pattern");
    }
  Data_Get_Struct (value, cairo_pattern_t, pattern);
  return pattern;
}

void
rb_free_pattern (void *ptr)
{
  if (ptr)
    {
      cairo_pattern_destroy ((cairo_pattern_t *) ptr);
    }
}

void
Init_cairo_pattern (void)
{
  rb_cCairo_Pattern =
    rb_define_class_under (rb_mCairo, "Pattern", rb_cObject);
}
