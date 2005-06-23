/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_FONT_FACE_H
#define RB_CAIRO_FONT_FACE_H

#include "rb_cairo.h"

extern VALUE rb_cCairo_FontFace;

void               Init_cairo_font_face (void);
cairo_font_face_t *value_to_font_face   (VALUE value);
void               rb_free_font_face    (void *ptr);


#endif
