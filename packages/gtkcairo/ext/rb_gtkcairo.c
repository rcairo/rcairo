/* ruby-gtkcairo - Ruby bindings for GtkCairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *           (c) 2004 Øyvind Kolås <pippin@freedesktop.org>
 *
 */

#include "ruby.h"
#include "rbgtk.h"
#include "rb_cairo.h"

#include <gtkcairo.h>

static VALUE cGtkCairo;

static    VALUE
get_cairo (VALUE self)
{
  GtkCairo *gtkcairo = RVAL2GOBJ (self);
  cairo_t  *cairo    = gtk_cairo_get_cairo (gtkcairo);
  VALUE     rbcairo  = rb_cairo_new_from (cairo);

  return rbcairo;
}

void
Init_gtkcairo ()
{
  /* define a "Gtk" class under module "Cairo".
   * cGtkCairo = G_DEF_CLASS(gtk_cairo_get_type(), "Gtk", mCairo); */

  /* define a "CairoWidget" class under module "Gtk". */
  cGtkCairo = G_DEF_CLASS (gtk_cairo_get_type (), "CairoWidget", mGtk);
  rb_define_method (cGtkCairo, "cairo", get_cairo, 0);
}
