/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#ifndef RB_CAIRO_MATRIX_H
#define RB_CAIRO_MATRIX_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_Matrix;

void            Init_cairo_matrix      (void);
cairo_matrix_t *rb_v_to_cairo_matrix_t (VALUE value);
void            rb_free_matrix         (void *ptr);


#endif
