/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-05-01 11:49:43 $
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

VALUE rb_cairo__float_array (double *values, unsigned count);
void rb_cairo__glyphs_to_array (VALUE rb_array, cairo_glyph_t **glyphs, int *length);

VALUE rb_cairo__const_get (VALUE name, const char *prefix);

#endif
