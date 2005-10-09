/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo.h"

VALUE
cr__float_array (double *values, unsigned count)
{
  VALUE result;
  int i;

  result = rb_ary_new2 (count);
  for (i = 0; i < count; i++)
    {
      rb_ary_push (result, rb_float_new (values[i]));
    }
  return result;
}

void
cr__glyphs_to_array (VALUE rb_array, cairo_glyph_t **glyphs, int *length)
{
  int i;
  
  if (!rb_obj_is_kind_of (rb_array, rb_cArray))
     rb_raise (rb_eTypeError, "expected array");

  *length = RARRAY(rb_array)->len;
  *glyphs = ALLOCA_N (cairo_glyph_t, *length);

  if (!*glyphs)
    rb_cairo_check_status (CAIRO_STATUS_NO_MEMORY);

  for (i = 0; i < *length; i++)
    {
      memcpy ((char *) &(*glyphs)[i],
              (char *) RVAL2CRGLYPH (rb_ary_entry (rb_array, i)),
              sizeof (cairo_glyph_t));
    }
}

