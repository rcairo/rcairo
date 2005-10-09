/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#ifndef RB_CAIRO_PRIVATE_H
#define RB_CAIRO_PRIVATE_H

VALUE cr__float_array (double *values, unsigned count);
void cr__glyphs_to_array (VALUE rb_array, cairo_glyph_t **glyphs, int *length);

#endif
