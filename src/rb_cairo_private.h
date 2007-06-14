/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-06-14 12:23:45 $
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#ifndef RB_CAIRO_PRIVATE_H
#define RB_CAIRO_PRIVATE_H

#define CR_TRUE 1
#define CR_FALSE 0

#define CSTR2RVAL(str) rb_str_new2(str)
#define RVAL2CSTR(str) StringValueCStr(str)

#define CBOOL2RVAL(bool) (bool ? Qtrue : Qfalse)
#define RVAL2CBOOL(bool) RTEST(bool)

#ifndef RSTRING_LEN
#  define RSTRING_LEN(string) (RSTRING(string)->len)
#endif

#ifdef HAVE_RB_ERRINFO
#  define RB_ERRINFO (rb_errinfo())
#else
#  define RB_ERRINFO (ruby_errinfo)
#endif

extern void Init_cairo_private (void);
extern void Init_cairo_constants (void);

extern void Init_cairo_context (void);
extern void Init_cairo_path (void);
extern void Init_cairo_matrix (void);
extern void Init_cairo_surface (void);
extern void Init_cairo_exception (void);
extern void Init_cairo_font (void);
extern void Init_cairo_font_extents (void);
extern void Init_cairo_font_options (void);
extern void Init_cairo_scaled_font (void);
extern void Init_cairo_text_extents (void);
extern void Init_cairo_pattern (void);
extern void Init_cairo_glyph (void);

#define RB_CAIRO__GLYPHS_TO_ARRAY(rb_array, glyphs, length)     \
do                                                              \
  {                                                             \
    Check_Type (rb_array, T_ARRAY);                             \
    length = RARRAY (rb_array)->len;                            \
    glyphs = ALLOCA_N (cairo_glyph_t, length);                  \
                                                                \
    if (!glyphs)                                                \
      rb_cairo_check_status (CAIRO_STATUS_NO_MEMORY);           \
                                                                \
    rb_cairo__glyphs_to_array (rb_array, glyphs, length);       \
  } while (0)

VALUE rb_cairo__float_array (double *values, unsigned count);
void rb_cairo__glyphs_to_array (VALUE rb_array, cairo_glyph_t *glyphs, int length);

VALUE rb_cairo__const_get (VALUE name, const char *prefix);
cairo_bool_t rb_cairo__is_kind_of (VALUE object, VALUE klass);

#endif
