/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#ifndef RB_CAIRO_CONTEXT_H
#define RB_CAIRO_CONTEXT_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_Context;

void     Init_cairo_context (void);
VALUE    rb_cairo_new_from  (cairo_t *cr);
cairo_t *rb_v_to_cairo_t    (VALUE value);
void     rb_free_context    (void *ptr);


#endif
