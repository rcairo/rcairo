/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2005-10-10 15:40:26 $
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
VALUE rb_cCairo_ImageSurface;
VALUE rb_cCairo_PDFSurface;
VALUE rb_cCairo_PSSurface;

static ID cr_id_read;
static ID cr_id_write;
static cairo_user_data_key_t klass_key;

#define _SELF  (RVAL2CRSURFACE(self))

static inline void
cr_surface_check_status (cairo_surface_t *surface)
{
  rb_cairo_check_status (cairo_surface_status (surface));
}

static void
cr_surface_set_klass (cairo_surface_t *surface, VALUE klass)
{
  cairo_status_t status;
  status = cairo_surface_set_user_data (surface, &klass_key,
                                        (void *)klass, NULL);
  rb_cairo_check_status (status);
}

static VALUE
cr_surface_get_klass (cairo_surface_t *surface)
{
  VALUE klass = (VALUE)cairo_surface_get_user_data (surface, &klass_key);
  if (!klass)
    {
      rb_raise (rb_eArgError, "[BUG] uninitialized surface for Ruby");
    }
  return klass;
}

/* read/write callback */
typedef struct cr_io_callback_closure {
  VALUE target;
  VALUE error;
} cr_io_callback_closure_t;

static VALUE
cr_surface_io_func_rescue (VALUE io_closure)
{
  cr_io_callback_closure_t *closure;
  closure = (cr_io_callback_closure_t *)io_closure;
  closure->error = ruby_errinfo;
  return Qnil;
}

/* write callback */
static VALUE
cr_surface_write_func_invoke (VALUE info)
{
  VALUE output, data;
  long written_bytes;
  unsigned int length;
  
  output = rb_ary_entry(info, 0);
  data = rb_ary_entry(info, 1);

  rb_funcall (output, cr_id_write, 1, data);
  return Qnil;
  
  length = RSTRING (data)->len;
  while (length != 0)
    {
      VALUE rb_written_bytes = rb_funcall (output, cr_id_write, 1, data);
      written_bytes = NUM2LONG (rb_written_bytes);
      data = rb_str_substr (data, written_bytes,
                            RSTRING (data)->len - written_bytes);
      length -= written_bytes;
    }
  
  return Qnil;
}

static cairo_status_t
cr_surface_write_func (void *write_closure,
                       const unsigned char *data, unsigned int length)
{
  cr_io_callback_closure_t *closure;
  VALUE args;

  closure = (cr_io_callback_closure_t *)write_closure;
  args = rb_ary_new3 (2,
                      closure->target,
                      rb_str_new ((const char *)data, length));
  rb_rescue2 (cr_surface_write_func_invoke, args,
              cr_surface_io_func_rescue, (VALUE) closure, rb_eException,
              (VALUE)0);
  
  if (NIL_P (closure->error))
    return CAIRO_STATUS_SUCCESS;
  else
    return CAIRO_STATUS_WRITE_ERROR;
}

/* read callback */
static VALUE
cr_surface_read_func_invoke (VALUE info)
{
  VALUE input, result;
  unsigned int length, rest;
  unsigned char *data;
  
  input = rb_ary_entry (info, 0);
  length = NUM2UINT (rb_ary_entry (info, 1));
  data = (unsigned char *) rb_ary_entry (info, 2);
  
  result = rb_str_new2 ("");
  rest = length;

  for (rest = length; rest != 0; rest = length - RSTRING (result)->len)
    {
      rb_str_concat (result, rb_funcall (input, cr_id_read, 1, INT2NUM (rest)));
    }

  memcpy ((void *)data, (const void *)StringValuePtr (result), length);

  return Qnil;
}

static cairo_status_t
cr_surface_read_func (void *read_closure,
                      unsigned char *data, unsigned int length)
{
  cr_io_callback_closure_t *closure;
  VALUE args;

  closure = (cr_io_callback_closure_t *)read_closure;
  args = rb_ary_new3 (3, closure->target, UINT2NUM (length), (VALUE) data);
  rb_rescue2 (cr_surface_read_func_invoke, args,
              cr_surface_io_func_rescue, (VALUE) closure, rb_eException,
              (VALUE)0);
  
  if (NIL_P (closure->error))
    return CAIRO_STATUS_SUCCESS;
  else
    return CAIRO_STATUS_READ_ERROR;
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
  cr_surface_set_klass (surface, rb_obj_class (obj));
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
rb_cairo_surface_to_ruby_object (cairo_surface_t *surface)
{
  if (surface)
    {
      VALUE klass = cr_surface_get_klass (surface);
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
cr_surface_create_similar (VALUE self, VALUE rb_content,
                           VALUE width, VALUE height)
{
  cairo_surface_t *surface;
  cairo_content_t content;

  content = NUM2INT (rb_content);

  if (content < CAIRO_CONTENT_COLOR ||
      content > CAIRO_CONTENT_COLOR_ALPHA)
    {
        rb_raise (rb_eArgError, "invalid content");
    }

  surface = cairo_surface_create_similar (RVAL2CRSURFACE (self), content,
                                          NUM2INT (width), NUM2INT (height));
  cr_surface_check_status (surface);
  cr_surface_set_klass (surface, rb_obj_class (self));
  return CRSURFACE2RVAL (surface);
}

static VALUE
cr_surface_finish (VALUE self)
{
  cairo_surface_finish (_SELF);
  cr_surface_check_status (_SELF);
  return self;
}

#if CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_image_surface_write_to_png_stream (VALUE self, VALUE target)
{
  cairo_status_t status;
  cr_io_callback_closure_t closure;

  closure.target = target;
  closure.error = Qnil;

  status = cairo_surface_write_to_png_stream (_SELF, cr_surface_write_func,
                                              (void *)&closure);
  if (!NIL_P (closure.error))
    rb_exc_raise (closure.error);

  rb_cairo_check_status (status);
  return self;
}

static VALUE
cr_image_surface_write_to_png_stream_invoke (VALUE info)
{
  return cr_image_surface_write_to_png_stream (rb_ary_entry (info, 0),
                                               rb_ary_entry (info, 1));
}

static VALUE
cr_image_surface_write_to_png (VALUE self, VALUE filename)
{
  VALUE info, file;

  file = rb_file_open (StringValuePtr (filename), "wb");
  info = rb_ary_new3 (2, self, file);
  return rb_ensure (cr_image_surface_write_to_png_stream_invoke, info,
                    rb_io_close, file);
}

static VALUE
cr_image_surface_write_to_png_generic (VALUE self, VALUE target)
{
  if (rb_respond_to (target, cr_id_write))
    return cr_image_surface_write_to_png_stream (self, target);
  else
    return cr_image_surface_write_to_png (self, target);
}
#endif

static VALUE
cr_surface_get_font_options (VALUE self)
{
  cairo_font_options_t *options = NULL;
  cairo_surface_get_font_options (_SELF, options);
  cr_surface_check_status (_SELF);
  options = cairo_font_options_copy (options);
  rb_cairo_check_status (cairo_font_options_status (options));
  return CRFONTOPTIONS2RVAL (options);
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
#if CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_image_surface_create_from_png_stream (VALUE target)
{
  cr_io_callback_closure_t closure;
  cairo_surface_t *surface;

  closure.target = target;
  closure.error = Qnil;
  
  surface = cairo_image_surface_create_from_png_stream (cr_surface_read_func,
                                                        (void *)&closure);
  if (!NIL_P (closure.error))
    rb_exc_raise (closure.error);
  
  return (VALUE)surface;
}

static VALUE
cr_image_surface_create_from_png (VALUE filename)
{
  VALUE file;
  file = rb_file_open (StringValuePtr (filename), "rb");
  
  return rb_ensure (cr_image_surface_create_from_png_stream, file,
                    rb_io_close, file);
}

static VALUE
cr_image_surface_create_from_png_generic (VALUE self, VALUE target)
{
  cairo_surface_t *surface;
  if (rb_respond_to (target, cr_id_read))
    surface = (cairo_surface_t *)cr_image_surface_create_from_png_stream (target);
  else
    surface = (cairo_surface_t *)cr_image_surface_create_from_png (target);

  cr_surface_check_status (surface);
  return CRSURFACE2RVAL (surface);
}
#endif


static cairo_surface_t *
cr_image_surface_create (VALUE self, VALUE format, VALUE width, VALUE height)
{
  return cairo_image_surface_create (NUM2INT (format),
                                     NUM2INT (width),
                                     NUM2INT (height));
}

static cairo_surface_t *
cr_image_surface_create_for_data (VALUE self, VALUE rb_data, VALUE rb_format,
                                  VALUE width, VALUE height, VALUE stride)
{
  unsigned char *data;
  cairo_format_t format;

  format = NUM2INT (rb_format);

  if (format < CAIRO_FORMAT_ARGB32 ||
      format < CAIRO_FORMAT_A1)
    {
      rb_raise (rb_eArgError, "invalid format");
    }

  data = (unsigned char *)StringValuePtr (rb_data);
  
  return cairo_image_surface_create_for_data (data,
                                              format,
                                              NUM2INT (width),
                                              NUM2INT (height),
                                              NUM2INT (stride));
}

static VALUE
cr_image_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  VALUE arg1, arg2, arg3, arg4, arg5;
  int n;
  
  n = rb_scan_args (argc, argv, "32", &arg1, &arg2, &arg3, &arg4, &arg5);

  if (n == 3)
    surface = cr_image_surface_create (self, arg1, arg2, arg3);
  else if (n == 5)
    surface =
      cr_image_surface_create_for_data (self, arg1, arg2, arg3, arg4, arg5);
  else
    rb_raise (rb_eArgError,
              "invalid argument (expect "
              "(format, width, height) or "
              "(data, format, width, height, stride))");

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  return Qnil;
}

static VALUE
cr_image_surface_get_width (VALUE self)
{
  return INT2NUM (cairo_image_surface_get_width (_SELF));
}

static VALUE
cr_image_surface_get_height (VALUE self)
{
  return INT2NUM (cairo_image_surface_get_height (_SELF));
}

#if CAIRO_HAS_PS_SURFACE
/* PS-surface functions */
static VALUE
cr_ps_surface_create_for_stream (VALUE info)
{
  VALUE self, input, width_in_points, height_in_points;
  cr_io_callback_closure_t closure;
  cairo_surface_t *surface;

  self = rb_ary_entry (info, 0);
  input = rb_ary_entry (info, 1);
  width_in_points = rb_ary_entry (info, 2);
  height_in_points = rb_ary_entry (info, 3);
  
  closure.target = input;
  closure.error = Qnil;
  
  surface = cairo_ps_surface_create_for_stream (cr_surface_write_func,
                                                (void *) &closure,
                                                NUM2DBL (width_in_points),
                                                NUM2DBL (height_in_points));
  if (!NIL_P (closure.error))
    rb_exc_raise (closure.error);
  
  return (VALUE)surface;
}

static VALUE
cr_ps_surface_create (VALUE self, VALUE filename,
                       VALUE width_in_points, VALUE height_in_points)
{
  VALUE file, info;
  
  file = rb_file_open (StringValuePtr (filename), "rb");
  info = rb_ary_new3 (4, self, file, width_in_points, height_in_points);
  return rb_ensure (cr_ps_surface_create_for_stream, info,
                    rb_io_close, file);
}

static VALUE
cr_ps_surface_initialize (VALUE self, VALUE target,
                           VALUE width_in_points, VALUE height_in_points)
{
  cairo_surface_t *surface;
  
  if (rb_respond_to (target, cr_id_read))
    {
      VALUE info;
      info = rb_ary_new3 (4, self, target, width_in_points, height_in_points);
      surface = (cairo_surface_t *)cr_ps_surface_create_for_stream (info);
    }
  else
    {
      surface = (cairo_surface_t *)cr_ps_surface_create (self, target,
                                                         width_in_points,
                                                         height_in_points);
    }
  
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  return Qnil;
}

static VALUE
cr_ps_surface_set_dpi (VALUE self, VALUE x_dpi, VALUE y_dpi)
{
  cairo_ps_surface_set_dpi (_SELF, NUM2DBL (x_dpi), NUM2DBL (y_dpi));
  cr_surface_check_status (_SELF);
  return self;
}
#endif

#if CAIRO_HAS_PDF_SURFACE
/* PDF-surface functions */
static VALUE
cr_pdf_surface_create_for_stream (VALUE info)
{
  VALUE self, input, width_in_points, height_in_points;
  cr_io_callback_closure_t closure;
  cairo_surface_t *surface;

  self = rb_ary_entry (info, 0);
  input = rb_ary_entry (info, 1);
  width_in_points = rb_ary_entry (info, 2);
  height_in_points = rb_ary_entry (info, 3);
  
  closure.target = input;
  closure.error = Qnil;
  
  surface = cairo_pdf_surface_create_for_stream (cr_surface_write_func,
                                                 (void *) &closure,
                                                 NUM2DBL (width_in_points),
                                                 NUM2DBL (height_in_points));
  if (!NIL_P (closure.error))
    rb_exc_raise (closure.error);
  
  return (VALUE)surface;
}

static VALUE
cr_pdf_surface_create (VALUE self, VALUE filename,
                       VALUE width_in_points, VALUE height_in_points)
{
  VALUE file, info;
  
  file = rb_file_open (StringValuePtr (filename), "rb");
  info = rb_ary_new3 (4, self, file, width_in_points, height_in_points);
  return rb_ensure (cr_pdf_surface_create_for_stream, info,
                    rb_io_close, file);
}

static VALUE
cr_pdf_surface_initialize (VALUE self, VALUE target,
                           VALUE width_in_points, VALUE height_in_points)
{
  cairo_surface_t *surface;
  
  if (rb_respond_to (target, cr_id_read))
    {
      VALUE info;
      info = rb_ary_new3 (4, self, target, width_in_points, height_in_points);
      surface = (cairo_surface_t *)cr_pdf_surface_create_for_stream (info);
    }
  else
    {
      surface = (cairo_surface_t *)cr_pdf_surface_create (self, target,
                                                          width_in_points,
                                                          height_in_points);
    }
  
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  return Qnil;
}

static VALUE
cr_pdf_surface_set_dpi (VALUE self, VALUE x_dpi, VALUE y_dpi)
{
  cairo_pdf_surface_set_dpi (_SELF, NUM2DBL (x_dpi), NUM2DBL (y_dpi));
  cr_surface_check_status (_SELF);
  return self;
}
#endif

void
Init_cairo_surface (void)
{
  cr_id_read = rb_intern ("read");
  cr_id_write = rb_intern ("write");
  
  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Surface, cr_surface_allocate);
  
  rb_define_method (rb_cCairo_Surface, "create_similar",
                    cr_surface_create_similar, 3);
  rb_define_method (rb_cCairo_Surface, "finish", cr_surface_finish, 0);
  
  rb_define_method (rb_cCairo_Surface, "font_options",
                    cr_surface_get_font_options, 0);
  rb_define_method (rb_cCairo_Surface, "flush", cr_surface_flush, 0);
  rb_define_method (rb_cCairo_Surface, "mark_dirty", cr_surface_mark_dirty, 0);
  rb_define_method (rb_cCairo_Surface, "set_device_offset",
                    cr_surface_set_device_offset, 2);

  /* Image-surface */
  rb_cCairo_ImageSurface =
    rb_define_class_under (rb_mCairo, "ImageSurface", rb_cCairo_Surface);
  
#if CAIRO_HAS_PNG_FUNCTIONS
  rb_define_singleton_method (rb_cCairo_ImageSurface, "from_png",
                              cr_image_surface_create_from_png_generic, 1);
#endif
  
  rb_define_method (rb_cCairo_ImageSurface, "initialize",
                    cr_image_surface_initialize, -1);

  rb_define_method (rb_cCairo_ImageSurface, "width",
                    cr_image_surface_get_width, 0);
  rb_define_method (rb_cCairo_ImageSurface, "height",
                    cr_image_surface_get_height, 0);
  
#if CAIRO_HAS_PNG_FUNCTIONS
  rb_define_method (rb_cCairo_ImageSurface, "write_to_png",
                    cr_image_surface_write_to_png_generic, 1);
#endif

  
#if CAIRO_HAS_PS_SURFACE
  /* PS-surface */
  rb_cCairo_PSSurface =
    rb_define_class_under (rb_mCairo, "PSSurface", rb_cCairo_Surface);

  rb_define_method (rb_cCairo_PSSurface, "initialize",
                    cr_ps_surface_initialize, 3);
  rb_define_method (rb_cCairo_PSSurface, "set_dpi",
                    cr_ps_surface_set_dpi, 2);
#endif

#if CAIRO_HAS_PDF_SURFACE
  /* PDF-surface */
  rb_cCairo_PDFSurface =
    rb_define_class_under (rb_mCairo, "PDFSurface", rb_cCairo_Surface);

  rb_define_method (rb_cCairo_PDFSurface, "initialize",
                    cr_pdf_surface_initialize, 3);
  rb_define_method (rb_cCairo_PDFSurface, "set_dpi",
                    cr_pdf_surface_set_dpi, 2);
#endif
}
