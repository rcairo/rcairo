/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#ifndef RB_CAIRO_H
#define RB_CAIRO_H

#include <cairo-features.h>
#include <cairo.h>

#include "ruby.h"

extern VALUE rb_mCairo;

#include "rb_cairo_constants.h"
#include "rb_cairo_context.h"
#include "rb_cairo_exception.h"
#include "rb_cairo_matrix.h"
#include "rb_cairo_pattern.h"
#include "rb_cairo_font.h"
#include "rb_cairo_font_extents.h"
#include "rb_cairo_text_extents.h"
#include "rb_cairo_glyph.h"
#include "rb_cairo_surface.h"

#endif
