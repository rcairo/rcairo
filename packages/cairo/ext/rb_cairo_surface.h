/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_SURFACE_H
#define RB_CAIRO_SURFACE_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_Surface;

void             Init_cairo_surface      (void);
cairo_surface_t *rb_v_to_cairo_surface_t (VALUE value);
void             rb_free_surface         (void *ptr);

#endif
