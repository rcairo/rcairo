/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-05-18 14:07:48 $
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo.h"
#include "rb_cairo_private.h"

static ID id_normalize_const_name;

VALUE
rb_cairo__float_array (double *values, unsigned count)
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
rb_cairo__glyphs_to_array (VALUE rb_array, cairo_glyph_t *glyphs, int length)
{
  int i;

  for (i = 0; i < length; i++)
    {
      memcpy ((char *) &glyphs[i],
              (char *) RVAL2CRGLYPH (rb_ary_entry (rb_array, i)),
              sizeof (cairo_glyph_t));
    }
}

VALUE
rb_cairo__const_get (VALUE name, const char *prefix)
{
  VALUE rb_normalized_name;
  char *const_name, *normalized_name;
  size_t prefix_len, normalized_name_len;

  rb_normalized_name = rb_funcall (rb_mCairo, id_normalize_const_name, 1, name);
  normalized_name = RVAL2CSTR (rb_normalized_name);

  prefix_len = strlen (prefix);
  normalized_name_len = strlen (normalized_name);

  const_name = ALLOCA_N (char, prefix_len + normalized_name_len + 1);
  strncpy (const_name, prefix, prefix_len);
  strncpy (const_name + prefix_len, normalized_name, normalized_name_len);
  const_name[prefix_len + normalized_name_len] = '\0';

  return rb_const_get (rb_mCairo, rb_intern (const_name));
}

cairo_bool_t
rb_cairo__is_kind_of (VALUE object, VALUE klass)
{
  return RVAL2CBOOL (rb_obj_is_kind_of (object, klass));
}


void
Init_cairo_private (void)
{
  id_normalize_const_name = rb_intern ("normalize_const_name");
}
