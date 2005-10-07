/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"

VALUE rb_mCairo;

extern void Init_cairo_context (void);
extern void Init_cairo_matrix (void);
extern void Init_cairo_surface (void);
extern void Init_cairo_constants (void);
extern void Init_cairo_exception (void);
extern void Init_cairo_font (void);
extern void Init_cairo_text_extents (void);
extern void Init_cairo_font_extents (void);
extern void Init_cairo_pattern (void);
extern void Init_cairo_glyph (void);

void
Init_cairo ()
{
  rb_mCairo = rb_define_module ("Cairo");

  Init_cairo_context ();
  Init_cairo_matrix ();
  Init_cairo_surface ();
  Init_cairo_constants ();
  Init_cairo_exception ();
  Init_cairo_font ();
  Init_cairo_text_extents ();
  Init_cairo_font_extents ();
  Init_cairo_pattern ();
  Init_cairo_glyph ();
}
