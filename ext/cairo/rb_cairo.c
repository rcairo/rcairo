/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2009-12-13 11:27:45 $
 *
 * Copyright 2006-2008 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_mCairo, rb_mCairo_Color, rb_cCairo_Color_Base, rb_cCairo_Paper;

static ID id__add_one_arg_setter;

void
rb_cairo_def_setters (VALUE klass)
{
  rb_funcall (rb_mCairo, id__add_one_arg_setter, 1, klass);
}

static VALUE
rb_cairo_satisfied_version (int argc, VALUE *argv, VALUE self)
{
  VALUE major, minor, micro;

  rb_scan_args (argc, argv, "21", &major, &minor, &micro);

  if (NIL_P (micro))
    micro = UINT2NUM (0);

  return CBOOL2RVAL (CAIRO_VERSION_MAJOR > NUM2UINT(major) ||
                     (CAIRO_VERSION_MAJOR == NUM2UINT(major) &&
                      CAIRO_VERSION_MINOR > NUM2UINT(minor)) ||
                     (CAIRO_VERSION_MAJOR == NUM2UINT(major) &&
                      CAIRO_VERSION_MINOR == NUM2UINT(minor) &&
                      CAIRO_VERSION_MICRO >= NUM2UINT(micro)));
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
                                INT2FIX (RB_CAIRO_VERSION_MAJOR),
                                INT2FIX (RB_CAIRO_VERSION_MINOR),
                                INT2FIX (RB_CAIRO_VERSION_MICRO),
                                Qnil));

  rb_define_module_function (rb_mCairo, "satisfied_version?",
                             rb_cairo_satisfied_version, -1);

  rb_mCairo_Color = rb_const_get (rb_mCairo, rb_intern ("Color"));
  rb_cCairo_Color_Base = rb_const_get (rb_mCairo_Color, rb_intern ("Base"));
  rb_cCairo_Paper = rb_const_get (rb_mCairo, rb_intern ("Paper"));

  Init_cairo_private ();
  Init_cairo_io ();
  Init_cairo_constants ();

  Init_cairo_context ();
  Init_cairo_rectangle ();
  Init_cairo_path ();
  Init_cairo_matrix ();
  Init_cairo_region ();
  Init_cairo_device ();
  Init_cairo_surface ();
  Init_cairo_quartz_surface ();
  Init_cairo_exception ();
  Init_cairo_font ();
  Init_cairo_font_extents ();
  Init_cairo_font_options ();
  Init_cairo_scaled_font ();
  Init_cairo_text_extents ();
  Init_cairo_pattern ();
  Init_cairo_glyph ();
  Init_cairo_text_cluster ();
}
