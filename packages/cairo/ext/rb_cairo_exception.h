/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#ifndef RB_CAIRO_EXCEPTION_H
#define RB_CAIRO_EXCEPTION_H

#include "rb_cairo.h"

void Init_cairo_exception     ();

void rb_cairo_raise_exception (cairo_status_t  status);

#endif
