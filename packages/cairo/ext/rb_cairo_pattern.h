/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_PATTERN_H
#define RB_CAIRO_PATTERN_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_Pattern;

void             Init_cairo_pattern      (void);
cairo_pattern_t *rb_v_to_cairo_pattern_t (VALUE value);
void             rb_free_pattern         (void *ptr);


#endif
