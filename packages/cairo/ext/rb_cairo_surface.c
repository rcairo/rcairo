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

#if CAIRO_HAS_PS_SURFACE
#include <cairo-ps.h>
#endif

#if CAIRO_HAS_PDF_SURFACE
#include <cairo-pdf.h>
#endif


VALUE rb_cCairo_Surface;
VALUE rb_cCairo_SurfaceImage;
VALUE rb_cCairo_SurfacePDF;
VALUE rb_cCairo_SurfacePS;

static ID cr_id_call;

#define _SELF  (RVAL2CRSURFACE(self))

static inline void
cr_surface_check_status (cairo_surface_t *surface)
{
  cairo_status_t status;
  status = cairo_surface_status (surface);
  if (status)
    {
      rb_cairo_raise_exception (status);
    }
}

/* write callback */
static cairo_status_t
cr_surface_write_func (void *closure, const unsigned char *data, unsigned int length)
{
  cairo_status_t status = CAIRO_STATUS_SUCCESS;
  VALUE proc = (VALUE) closure;

  if (!NIL_P(proc))
    {
      VALUE result;
      result = rb_funcall (proc, cr_id_call, rb_str_new (data, length));
      status = NUM2INT (result);
      if (status != CAIRO_STATUS_SUCCESS && status != CAIRO_STATUS_WRITE_ERROR)
        status = CAIRO_STATUS_WRITE_ERROR;
    }
  
  return status;
}

/* read callback */
static cairo_status_t
cr_surface_read_func (void *closure, unsigned char *data, unsigned int length)
{
  cairo_status_t status = CAIRO_STATUS_SUCCESS;
  VALUE proc = (VALUE)closure;
  
  if (!NIL_P(proc))
    {
      VALUE result, read_data;
      result = rb_funcall (proc, cr_id_call, INT2NUM (length));
      status = NUM2INT (rb_ary_entry (result, 0));
      read_data = rb_ary_entry (result, 1);
      if ((status != CAIRO_STATUS_SUCCESS &&
           status != CAIRO_STATUS_READ_ERROR) ||
          RSTRING (read_data)->len != length)
        status = CAIRO_STATUS_READ_ERROR;

      if (!status)
        memcpy (data, StringValuePtr (read_data), length);
    }
  
  return status;
}


/* constructor/de-constructor */
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
cr_surface_free (void *ptr)
{
  if (ptr)
    {
      cairo_surface_destroy ((cairo_surface_t *) ptr);
    }
}

VALUE
rb_cairo_surface_to_ruby_object (cairo_surface_t *surface, VALUE klass)
{
  if (surface)
    {
      cairo_surface_reference (surface);
      return Data_Wrap_Struct (klass, NULL, cr_surface_free, surface);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_surface_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_surface_free, NULL);
}

/* Surface manipulation */
static VALUE
cr_surface_create_similar (VALUE self, VALUE content, VALUE width, VALUE height)
{
  cairo_surface_t *surface;
  surface = cairo_create_similar (RVAL2CRSURFACE (self),
                                  NUM2INT (content),
                                  NUM2DBL (width),
                                  NUM2DBL (height));
  cr_surface_check_status (surface);
  return CRSURFACE2RVAL (surface, rb_obj_class (self));
}

static VALUE
cairo_surface_finish (VALUE self)
{
  cairo_surface_finish (_SELF);
  cr_surface_check_status (_SELF);
  return self;
}

#if CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_surface_write_to_png (int argc, VALUE *argv, VALUE self)
{
  cairo_status_t status;
  VALUE filename;
  int n;

  n = rb_scan_args (argc, argv, "01", &filename);

  if (n == 0)
    {
      rb_need_block();
      status = cairo_surface_write_to_png_stream (_SELF,
                                                  cr_surface_write_func,
                                                  (void *)ruby_block);
    }
  else if (TYPE(filename) != T_STRING || )
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect (filename) or (&block))");
    }
  else
    {
      status = cairo_surface_write_to_png (_SELF, StringValuePtr (filiename));
    }
  
  rb_cairo_raise_exception (status);
  return self;
}
#endif

static VALUE
cr_surface_get_font_options (VALUE self)
{
  cairo_font_options_t options;
  cairo_surface_get_font_options (_SELF, &options);
  cr_surface_check_status (_SELF);
  return CRFONTOPTIONS2RVAL (cairo_font_options_copy (&options)); /* check status!*/
}

static VALUE
cr_surface_flush (VALUE self)
{
  cairo_surface_flush (_SELF);
  cr_surface_check_status (_SELF);
  return self;
}

static VALUE
cr_surface_mark_dirty (int argc, VALUE *argv, VALUE self)
{
  VALUE x, y, width, height;
  int n;
  
  n = rb_scan_args (argc, argv, "04", &x, &y, &width, &height);

  if (n == 0)
    {
      cairo_surface_mark_dirty (_SELF);
    }
  else if (n == 4)
    {
      cairo_surface_mark_dirty_rectangle (_SELF,
                                          NUM2INT (x), NUM2INT (y),
                                          NUM2INT (width), NUM2INT (height));
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect () or (x, y, width, height))");
    }

  cr_surface_check_status (_SELF);
  return self;
}

static VALUE
cr_surface_set_device_offset (VALUE self, VALUE x_offset, VALUE y_offset)
{
  cairo_surface_set_device_offset (_SELF,
                                   NUM2DBL (x_offset),
                                   NUM2DBL (y_offset));
  cr_surface_check_status (_SELF);
  return self;
}


/* Image-surface functions */
static cairo_surface_t *
cr_surface_image_create (VALUE self, VALUE format, VALUE width, VALUE height)
{
  return cairo_image_surface_create (NUM2INT (format),
                                     NUM2INT (width),
                                     NUM2INT (height));
}

static cairo_surface_t *
cr_surface_image_create_for_data (VALUE self, VALUE data, VALUE format,
                                  VALUE width, VALUE height, VALUE stride)
{
  return cairo_image_surface_create_for_data (StringValuePtr (data),
                                              NUM2INT (format),
                                              NUM2INT (width),
                                              NUM2INT (height),
                                              NUM2INT (stride));
}

#if CAIRO_HAS_PNG_FUNCTIONS
static cairo_surface_t *
cr_surface_image_create_from_png (VALUE self, VALUE filename)
{
  return cairo_image_surface_create_from_png (StringValuePtr (filename));
}
static cairo_surface_t *
cr_surface_image_create_from_png_stream (VALUE self)
{
  return cairo_image_surface_create_from_png_stream (cr_surface_read_func,
                                                     (void *)ruby_block);
}
#endif

static VALUE
cr_surface_image_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  VALUE arg1, arg2, arg3, arg4, arg5;
  int n;
  
  n = rb_scan_args (argc, argv, "32", &arg1, &arg2, &arg3, &arg4, &arg5);

  if (n == 3)
    surface = cr_surface_image_create (self, arg1, arg2, arg3);
  else if (n == 5)
    surface =
      cr_surface_image_create_for_data (self, arg1, arg2, arg3, arg4, arg5);
#if CAIRO_HAS_PNG_FUNCTIONS
  else if (n == 0 && rb_block_given_p ())
    surface =
      cr_surface_image_create_from_png_stream (self);
  else if (n == 1)
    surface = cr_surface_image_create_from_png (self, arg1);
#endif
  else
    rb_raise (rb_eArgError,
              "invalid argument (expect "
#if CAIRO_HAS_PNG_FUNCTIONS
              "(&block), (filename) "
#endif
              "(format, width, height) or "
              "(data format width height stride))");

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  return Qnil;
}

static VALUE
cr_surface_image_get_width (VALUE self)
{
  return INT2NUM (cairo_image_surface_get_width (_SELF));
}

static VALUE
cr_surface_image_get_height (VALUE self)
{
  return INT2NUM (cairo_image_surface_get_height (_SELF));
}


#if CAIRO_HAS_PS_SURFACE
/* PS-surface functions */
static cairo_surface_t *
cr_surface_ps_create (VALUE self, VALUE filename,
                      VALUE width_in_points, VALUE height_in_points)
{
  return cairo_ps_surface_create (StringValuePtr (filename),
                                  NUM2DBL (width_in_points),
                                  NUM2DBL (height_in_points));
}

static cairo_surface_t *
cr_surface_ps_create_for_stream (VALUE self,
                                 VALUE width_in_points, VALUE height_in_points)
{
  return cairo_ps_surface_create_for_stream (cr_surface_write_func,
                                             (void *) ruby_block,
                                             NUM2DBL (width_in_points),
                                             NUM2DBL (height_in_points));
}

static VALUE
cr_surface_ps_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  VALUE arg1, arg2, arg3;
  int n;
  
  n = rb_scan_args (argc, argv, "21", &arg1, &arg2, &arg3);

  if (n == 2 && rb_block_given_p ())
    surface = cr_surface_ps_create_for_stream (self, arg1, arg2);
  else if (n == 3)
    surface = cr_surface_ps_create (self, arg1, arg2, arg3);
  else
    rb_raise (rb_eArgError,
              "invalid argument (expect "
              "(width_in_points, height_in_points, &block) or "
              "(filename, width_in_points, height_in_points))");

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  return Qnil;
}

static VALUE
cr_surface_ps_set_dpi (VALUE self, VALUE x_dpi, VALUE y_dpi)
{
  cairo_ps_surface_set_dpi (_SELF, NUM2DBL (x_dpi), NUM2DBL (y_dpi));
  cr_surface_check_status (_SELF);
  return self;
}
#endif

#if CAIRO_HAS_PDF_SURFACE
/* PDF-surface functions */
static cairo_surface_t *
cr_surface_pdf_create (VALUE self, VALUE filename,
                       VALUE width_in_points, VALUE height_in_points)
{
  return cairo_pdf_surface_create (StringValuePtr (filename),
                                   NUM2DBL (width_in_points),
                                   NUM2DBL (height_in_points));
}

static cairo_surface_t *
cr_surface_pdf_create_for_stream (VALUE self,
                                  VALUE width_in_points, VALUE height_in_points)
{
  return cairo_pdf_surface_create_for_stream (cr_surface_write_func,
                                              (void *) ruby_block,
                                              NUM2DBL (width_in_points),
                                              NUM2DBL (height_in_points));
}

static VALUE
cr_surface_pdf_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  VALUE arg1, arg2, arg3;
  int n;
  
  n = rb_scan_args (argc, argv, "21", &arg1, &arg2, &arg3);

  if (n == 2 && rb_block_given_p ())
    surface = cr_surface_pdf_create_for_stream (self, arg1, arg2);
  else if (n == 3)
    surface = cr_surface_pdf_create (self, arg1, arg2, arg3);
  else
    rb_raise (rb_eArgError,
              "invalid argument (expect "
              "(width_in_points, height_in_points, &block) or "
              "(filename, width_in_points, height_in_points))");

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  return Qnil;
}

static VALUE
cr_surface_pdf_set_dpi (VALUE self, VALUE x_dpi, VALUE y_dpi)
{
  cairo_pdf_surface_set_dpi (_SELF, NUM2DBL (x_dpi), NUM2DBL (y_dpi));
  cr_surface_check_status (_SELF);
  return self;
}
#endif

void
Init_cairo_surface (void)
{
  cr_id_call = rb_intern ("call");
  
  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Surface, cr_surface_allocate);
  
  rb_define_method (rb_cCairo_Surface, "create_similar",
                    cr_surface_create_similar, 3);
  
#if CAIRO_HAS_PNG_FUNCTIONS
  rb_define_method (rb_cCairo_Surface, "write_to_png",
                    cr_surface_write_to_png, -1);
#endif
  
  rb_define_method (rb_cCairo_Surface, "font_options",
                    cr_surface_get_font_options, 0);
  rb_define_method (rb_cCairo_Surface, "mark_dirty", cr_surface_mark_dirty, 0);
  rb_define_method (rb_cCairo_Surface, "set_device_offset",
                    cr_surface_set_device_offset, 2);

  /* Image-surface */
  rb_cCairo_SurfaceImage =
    rb_define_class_under (rb_mCairo, "SurfaceImage", rb_cCairo_Surface);
  
  rb_define_method (rb_cCairo_SurfaceImage, "initialize",
                    cr_surface_image_initialize, -1);

  rb_define_method (rb_cCairo_SurfaceImage, "width",
                    cr_surface_image_get_width, 0);
  rb_define_method (rb_cCairo_SurfaceImage, "height",
                    cr_surface_image_get_height, 0);
  
  
#if CAIRO_HAS_PS_SURFACE
  /* PS-surface */
  rb_cCairo_SurfacePS =
    rb_define_class_under (rb_mCairo, "SurfacePS", rb_cCairo_Surface);

  rb_define_method (rb_cCairo_SurfacePS, "initialize",
                    cr_surface_ps_initialize, -1);
  rb_define_method (rb_cCairo_SurfacePS, "set_dpi",
                    cr_surface_ps_set_dpi, 2);
#endif

#if CAIRO_HAS_PDF_SURFACE
  /* PDF-surface */
  rb_cCairo_SurfacePDF =
    rb_define_class_under (rb_mCairo, "SurfacePDF", rb_cCairo_Surface);

  rb_define_method (rb_cCairo_SurfacePDF, "initialize",
                    cr_surface_pdf_initialize, -1);
  rb_define_method (rb_cCairo_SurfacePDF, "set_dpi",
                    cr_surface_pdf_set_dpi, 2);
#endif
}
