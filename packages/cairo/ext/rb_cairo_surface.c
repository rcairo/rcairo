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
#include "rubyio.h"

#ifdef CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>
#endif

#ifdef CAIRO_HAS_PNG_SURFACE
#include <cairo-png.h>
#endif

#ifdef CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>
#endif

#define _SELF  (DATA_PTR(self))

VALUE rb_cCairo_Surface;

cairo_surface_t *
rb_v_to_cairo_surface_t (VALUE value)
{
  cairo_surface_t *surface;
  if (CLASS_OF (value) != rb_cCairo_Surface)
    {
      rb_raise (rb_eTypeError, "not a cairo surface");
    }
  Data_Get_Struct (value, cairo_surface_t, surface);
  return surface;
}

void
rb_free_surface (void *ptr)
{
  if (ptr)
    {
      cairo_surface_destroy ((cairo_surface_t *) ptr);
    }
}

static    VALUE
rb_cairo_surface_new (VALUE klass,
                      VALUE format_v,
                      VALUE width_v, VALUE height_v)
{
  cairo_surface_t *surface;
  int       format;
  int       width;
  int       height;

  format = NUM2INT (format_v);
  width = NUM2INT (width_v);
  height = NUM2INT (height_v);

  if (format < CAIRO_FORMAT_ARGB32 || format > CAIRO_FORMAT_A1)
    {
      rb_raise (rb_eArgError, "invalid bitmap format");
    }
  if (width < 0)
    {
      rb_raise (rb_eArgError, "width must be positive");
    }
  if (height < 0)
    {
      rb_raise (rb_eArgError, "height must be positive");
    }

  surface =
    cairo_image_surface_create ((cairo_format_t) format, width, height);
  if (surface)
    {
      return Data_Wrap_Struct (rb_cCairo_Surface, NULL, rb_free_surface,
                               surface);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate surface");
      return Qundef;
    }
}

#ifdef CAIRO_HAS_PDF_SURFACE
static    VALUE
rb_cairo_surface_new_pdf (VALUE klass,
                          VALUE port,
                          VALUE width_inches_v,      VALUE height_inches_v,
                          VALUE x_pixels_per_inch_v, VALUE y_pixels_per_inch_v)
{
  cairo_surface_t *surface;
  double    width_inches;
  double    height_inches;
  double    x_pixels_per_inch;
  double    y_pixels_per_inch;

  Check_Type (port, T_FILE);
  rb_io_check_writable (RFILE (port)->fptr);

  width_inches = NUM2DBL (width_inches_v);
  height_inches = NUM2DBL (height_inches_v);
  x_pixels_per_inch = NUM2DBL (x_pixels_per_inch_v);
  y_pixels_per_inch = NUM2DBL (y_pixels_per_inch_v);

  if (width_inches < 0)
    {
      rb_raise (rb_eArgError, "width_inches must be positive");
    }
  if (height_inches < 0)
    {
      rb_raise (rb_eArgError, "height_inches must be positive");
    }

  surface = cairo_pdf_surface_create (GetWriteFile (RFILE (port)->fptr),
                                      width_inches, height_inches,
                                      x_pixels_per_inch, y_pixels_per_inch);
  if (surface)
    {
      return Data_Wrap_Struct (rb_cCairo_Surface, NULL, rb_free_surface,
                               surface);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate surface");
      return Qundef;
    }
}
#endif

#ifdef CAIRO_HAS_PNG_SURFACE
static    VALUE
rb_cairo_surface_new_png (VALUE klass,
                          VALUE port,
                          VALUE format_v,
                          VALUE width_v, VALUE height_v)
{
  cairo_surface_t *surface;
  int       format;
  int       width;
  int       height;

  Check_Type (port, T_FILE);
  rb_io_check_writable (RFILE (port)->fptr);

  format = NUM2INT (format_v);
  width = NUM2INT (width_v);
  height = NUM2INT (height_v);

  if (format < CAIRO_FORMAT_ARGB32 || format > CAIRO_FORMAT_A1)
    {
      rb_raise (rb_eArgError, "invalid bitmap format");
    }
  if (width < 0)
    {
      rb_raise (rb_eArgError, "width must be positive");
    }
  if (height < 0)
    {
      rb_raise (rb_eArgError, "height must be positive");
    }

  surface =
    cairo_png_surface_create (GetWriteFile (RFILE (port)->fptr),
                              (cairo_format_t) format, width, height);
  if (surface)
    {
      return Data_Wrap_Struct (rb_cCairo_Surface, NULL, rb_free_surface,
                               surface);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate surface");
      return Qundef;
    }
}
#endif

#ifdef CAIRO_HAS_PS_SURFACE
static    VALUE
rb_cairo_surface_new_ps (VALUE klass,
                         VALUE port,
                         VALUE width_inches_v, VALUE height_inches_v,
                         VALUE x_pixels_per_inch_v, VALUE y_pixels_per_inch_v)
{
  cairo_surface_t *surface;
  double    width_inches;
  double    height_inches;
  double    x_pixels_per_inch;
  double    y_pixels_per_inch;

  Check_Type (port, T_FILE);
  rb_io_check_writable (RFILE (port)->fptr);

  width_inches = NUM2DBL (width_inches_v);
  height_inches = NUM2DBL (height_inches_v);
  x_pixels_per_inch = NUM2DBL (x_pixels_per_inch_v);
  y_pixels_per_inch = NUM2DBL (y_pixels_per_inch_v);

  if (width_inches < 0)
    {
      rb_raise (rb_eArgError, "width_inches must be positive");
    }
  if (height_inches < 0)
    {
      rb_raise (rb_eArgError, "height_inches must be positive");
    }

  surface = cairo_ps_surface_create (GetWriteFile (RFILE (port)->fptr),
                                     width_inches, height_inches,
                                     x_pixels_per_inch, y_pixels_per_inch);
  if (surface)
    {
      return Data_Wrap_Struct (rb_cCairo_Surface, NULL, rb_free_surface,
                               surface);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate surface");
      return Qundef;
    }
}
#endif


void
Init_cairo_surface (void)
{
  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);
  rb_define_singleton_method (rb_cCairo_Surface, "new",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new), 3);

#ifdef CAIRO_HAS_PDF_SURFACE
  rb_define_singleton_method (rb_cCairo_Surface, "new_pdf",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new_pdf), 5);
#endif

#ifdef CAIRO_HAS_PNG_SURFACE
  rb_define_singleton_method (rb_cCairo_Surface, "new_png",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new_png), 4);
#endif

#ifdef CAIRO_HAS_PDF_SURFACE
  rb_define_singleton_method (rb_cCairo_Surface, "new_ps",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new_ps), 5);
#endif
}
