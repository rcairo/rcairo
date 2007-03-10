/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2007-03-10 11:56:46 $
 *
 * Copyright 2006-2007 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"

VALUE rb_mCairo;

extern void Init_cairo_context (void);
extern void Init_cairo_path (void);
extern void Init_cairo_matrix (void);
extern void Init_cairo_surface (void);
extern void Init_cairo_constants (void);
extern void Init_cairo_exception (void);
extern void Init_cairo_font (void);
extern void Init_cairo_font_extents (void);
extern void Init_cairo_font_options (void);
extern void Init_cairo_scaled_font (void);
extern void Init_cairo_text_extents (void);
extern void Init_cairo_pattern (void);
extern void Init_cairo_glyph (void);

static ID id__add_one_arg_setter;

void
rb_cairo_def_setters (VALUE klass)
{
  rb_funcall (rb_mCairo, id__add_one_arg_setter, 1, klass);
}

void
Init_cairo ()
{
  int major, minor, micro;

  id__add_one_arg_setter = rb_intern("__add_one_arg_setter");

  rb_mCairo = rb_define_module ("Cairo");

  rb_define_const (rb_mCairo, "BUILD_VERSION",
                   rb_ary_new3 (3,
                                INT2FIX (CAIRO_VERSION_MAJOR),
                                INT2FIX (CAIRO_VERSION_MINOR),
                                INT2FIX (CAIRO_VERSION_MICRO)));

  major = cairo_version () / 10000;
  minor = (cairo_version () % 10000) / 100;
  micro = cairo_version () % 100;

  rb_define_const (rb_mCairo, "VERSION",
                   rb_ary_new3 (3,
                                INT2FIX (major),
                                INT2FIX (minor),
                                INT2FIX (micro)));

  rb_define_const (rb_mCairo, "MAJOR_VERSION", INT2FIX (major));
  rb_define_const (rb_mCairo, "MINOR_VERSION", INT2FIX (minor));
  rb_define_const (rb_mCairo, "MICRO_VERSION", INT2FIX (micro));

  rb_define_const (rb_mCairo, "BINDINGS_VERSION",
                   rb_ary_new3 (4,
                                INT2FIX (1), INT2FIX (6), INT2FIX (0), Qnil));

  Init_cairo_constants ();

  Init_cairo_context ();
  Init_cairo_path ();
  Init_cairo_matrix ();
  Init_cairo_surface ();
  Init_cairo_exception ();
  Init_cairo_font ();
  Init_cairo_font_extents ();
  Init_cairo_font_options ();
  Init_cairo_scaled_font ();
  Init_cairo_text_extents ();
  Init_cairo_pattern ();
  Init_cairo_glyph ();
}
