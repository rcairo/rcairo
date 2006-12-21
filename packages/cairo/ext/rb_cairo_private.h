/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2006-12-21 15:34:36 $
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

VALUE rb_cairo__float_array (double *values, unsigned count);
void rb_cairo__glyphs_to_array (VALUE rb_array, cairo_glyph_t **glyphs, int *length);

#endif
