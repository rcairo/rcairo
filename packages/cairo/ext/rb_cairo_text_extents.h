/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_TEXT_EXTENTS_H
#define RB_CAIRO_TEXT_EXTENTS_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_TextExtents;

void                  Init_cairo_text_extents      (void);
cairo_text_extents_t *rb_v_to_cairo_text_extents_t (VALUE value);
void                  rb_free_text_extents         (void *ptr);


#endif
