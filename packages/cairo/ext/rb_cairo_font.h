/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_FONT_H
#define RB_CAIRO_FONT_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_Font;

void          Init_cairo_font (void);
cairo_font_t *value_to_font   (VALUE value);
void          rb_free_font    (void *ptr);


#endif
