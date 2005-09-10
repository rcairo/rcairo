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

VALUE rb_cCairo_Surface;

#define _SELF  (RVAL2CRSURFACE(self))

static cairo_status_t
rfile_write (void         *closure,
             const char   *data,
             unsigned int  length)
{
  OpenFile *fptr;
  FILE     *fp;
  
  fptr = closure;
  fp   = GetWriteFile (fptr);

  if (rb_io_fwrite (data, length, fp) == length)
    return CAIRO_STATUS_SUCCESS;
  return CAIRO_STATUS_WRITE_ERROR;
}

static void
rfile_destroy_closure (void *closure)
{
  OpenFile *fptr;
 
  fptr = closure;
}

cairo_surface_t *
rb_cairo_surface_from_ruby_object (VALUE obj)
{
  cairo_surface_t *surface;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_Surface)))
    {
      rb_raise (rb_eTypeError, "not a cairo surface");
    }
  Data_Get_Struct (obj, cairo_surface_t, surface);
  return surface;
}

static void
rb_free_surface (void *ptr)
{
  if (ptr)
    {
      cairo_surface_destroy ((cairo_surface_t *) ptr);
    }
}

VALUE
rb_cairo_surface_to_ruby_object (cairo_surface_t *surface)
{
  if (surface)
    {
      cairo_surface_reference (surface);
      return Data_Wrap_Struct (rb_cCairo_Surface, NULL, rb_free_surface, surface);
    }
  else
    {
      return Qnil;
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
      VALUE rb_surface = CRSURFACE2RVAL (surface);
      cairo_surface_destroy (surface);
      return rb_surface;
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate surface");
      return Qundef;
    }
}


#if XXXCAIRO_HAS_PDF_SURFACE
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
#if 1
  surface = cairo_pdf_surface_create (rfile_write, rfile_destroy_closure, RFILE (port)->fptr,
                                      width_inches, height_inches,
                                      x_pixels_per_inch, y_pixels_per_inch);
#endif
#if 0
  surface = cairo_pdf_surface_create_for_file (GetWriteFile(RFILE (port)->fptr),
        width_inches, height_inches,
        x_pixels_per_inch, y_pixels_per_inch);
#endif
  
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

static    VALUE
rb_cairo_surface_finish (VALUE self)
{
  cairo_surface_finish (_SELF);
  return Qnil;
}

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

#ifdef XXXCAIRO_HAS_PS_SURFACE
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

static VALUE
rb_cairo_surface_write_to_png (VALUE self,
                               VALUE filename_v)
{
  cairo_surface_write_to_png (_SELF, STR2CSTR (filename_v));
  return self;
}

void
Init_cairo_surface (void)
{
  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);
  rb_define_singleton_method (rb_cCairo_Surface, "new",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new), 3);

  rb_define_method (rb_cCairo_Surface, "write_to_png",
                              RUBY_METHOD_FUNC (rb_cairo_surface_write_to_png), 1);
  rb_define_method (rb_cCairo_Surface, "finish",
                              RUBY_METHOD_FUNC (rb_cairo_surface_finish), 0);

#if XXXCAIRO_HAS_PDF_SURFACE
  rb_define_singleton_method (rb_cCairo_Surface, "new_pdf",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new_pdf), 5);
#endif

#ifdef CAIRO_HAS_PNG_SURFACE
  rb_define_singleton_method (rb_cCairo_Surface, "new_png",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new_png), 4);
#endif

#ifdef XXXCAIRO_HAS_PS_SURFACE
  rb_define_singleton_method (rb_cCairo_Surface, "new_ps",
                              RUBY_METHOD_FUNC (rb_cairo_surface_new_ps), 5);
#endif
}
