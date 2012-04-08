/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-11-01 14:23:14 $
 *
 * Copyright 2005-2012 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"
#include "rb_cairo_io.h"

#ifdef HAVE_RUBY_ST_H
#  include <ruby/st.h>
#else
#  include <st.h>
#endif

#if CAIRO_CHECK_VERSION(1, 5, 2)
#  define RB_CAIRO_HAS_WIN32_PRINTING_SURFACE_TYPE
#endif

#if CAIRO_CHECK_VERSION(1, 5, 12)
#  define RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE_TYPE
#endif

#ifdef CAIRO_HAS_WIN32_SURFACE
#  define OpenFile OpenFile_win32
#  include <cairo-win32.h>
#  undef OpenFile
#  ifdef RB_CAIRO_HAS_WIN32_PRINTING_SURFACE_TYPE
#    define RB_CAIRO_HAS_WIN32_PRINTING_SURFACE
#  endif
#endif

#ifdef HAVE_RUBY_IO_H
#  include <ruby/io.h>
#else
#  include <rubyio.h>
#endif

#ifdef CAIRO_HAS_QUARTZ_SURFACE
#  ifndef HAVE_TYPE_ENUM_RUBY_VALUE_TYPE
enum ruby_value_type {
  RUBY_T_DATA = T_DATA
};
#  endif
#  undef T_DATA
#  include <cairo-quartz.h>
#  define T_DATA RUBY_T_DATA
#  ifdef HAVE_RUBY_COCOA
#    define RB_CAIRO_HAS_QUARTZ_SURFACE
#    ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE_TYPE
#      define RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE
#    endif
#  endif
#endif

#ifdef CAIRO_HAS_XML_SURFACE
#  include <cairo-xml.h>
#endif

#ifdef CAIRO_HAS_TEE_SURFACE
#  include <cairo-tee.h>
#endif

#if defined(CAIRO_HAS_GL_SURFACE) || defined(CAIRO_HAS_GLESV2_SURFACE)
#  define RB_CAIRO_HAS_GL_SURFACE
#endif

#ifdef RB_CAIRO_HAS_GL_SURFACE
#  include <cairo-gl.h>
#endif

VALUE rb_cCairo_Surface;
VALUE rb_cCairo_ImageSurface;
VALUE rb_cCairo_PDFSurface = Qnil;
VALUE rb_cCairo_PSSurface = Qnil;
VALUE rb_cCairo_XLibSurface = Qnil;
VALUE rb_cCairo_XCBSurface = Qnil;
VALUE rb_cCairo_SVGSurface = Qnil;
VALUE rb_cCairo_Win32Surface = Qnil;
VALUE rb_cCairo_Win32PrintingSurface = Qnil;
VALUE rb_cCairo_QuartzSurface = Qnil;
VALUE rb_cCairo_QuartzImageSurface = Qnil;
VALUE rb_cCairo_ScriptSurface = Qnil;
VALUE rb_cCairo_QtSurface = Qnil;
VALUE rb_cCairo_RecordingSurface = Qnil;
VALUE rb_cCairo_VGSurface = Qnil;
VALUE rb_cCairo_GLSurface = Qnil;
VALUE rb_cCairo_GLTextureSurface = Qnil;
VALUE rb_cCairo_DRMSurface = Qnil;
VALUE rb_cCairo_TeeSurface = Qnil;
VALUE rb_cCairo_XMLSurface = Qnil;
VALUE rb_cCairo_SkiaSurface = Qnil;
VALUE rb_cCairo_SubSurface = Qnil;
VALUE rb_cCairo_CoglSurface = Qnil;

static ID cr_id_parse;
static ID cr_id_size;
static ID cr_id_set_unit;
static cairo_user_data_key_t cr_closure_key;
static cairo_user_data_key_t cr_object_holder_key;
static cairo_user_data_key_t cr_finished_key;

#define _SELF  (RVAL2CRSURFACE(self))

static VALUE
cr_paper_parse (VALUE paper_description)
{
  return rb_funcall (rb_cCairo_Paper, cr_id_parse, 2, paper_description, Qtrue);
}

static void
cr_paper_to_size_in_points (VALUE paper_description, VALUE *width, VALUE *height)
{
  VALUE paper, size;

  paper = cr_paper_parse (paper_description);
  size = rb_funcall (paper, cr_id_size, 1, rb_str_new2 ("pt"));
  *width = RARRAY_PTR (size)[0];
  *height = RARRAY_PTR (size)[1];
}

static inline void
cr_surface_check_status (cairo_surface_t *surface)
{
  rb_cairo_check_status (cairo_surface_status (surface));
}

static VALUE
cr_surface_get_klass (cairo_surface_t *surface)
{
  VALUE klass;
  cairo_surface_type_t type;

  type = cairo_surface_get_type (surface);
  switch (type)
    {
    case CAIRO_SURFACE_TYPE_IMAGE:
      klass = rb_cCairo_ImageSurface;
      break;
    case CAIRO_SURFACE_TYPE_PDF:
      klass = rb_cCairo_PDFSurface;
      break;
    case CAIRO_SURFACE_TYPE_PS:
      klass = rb_cCairo_PSSurface;
      break;
    case CAIRO_SURFACE_TYPE_XLIB:
      klass = rb_cCairo_XLibSurface;
      break;
    case CAIRO_SURFACE_TYPE_XCB:
      klass = rb_cCairo_XCBSurface;
      break;
    case CAIRO_SURFACE_TYPE_QUARTZ:
      klass = rb_cCairo_QuartzSurface;
      break;
    case CAIRO_SURFACE_TYPE_WIN32:
      klass = rb_cCairo_Win32Surface;
      break;
    case CAIRO_SURFACE_TYPE_SVG:
      klass = rb_cCairo_SVGSurface;
      break;
#ifdef RB_CAIRO_HAS_WIN32_PRINTING_SURFACE_TYPE
    case CAIRO_SURFACE_TYPE_WIN32_PRINTING:
      klass = rb_cCairo_Win32PrintingSurface;
      break;
#endif
#ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE_TYPE
    case CAIRO_SURFACE_TYPE_QUARTZ_IMAGE:
      klass = rb_cCairo_QuartzImageSurface;
      break;
#endif
#if CAIRO_CHECK_VERSION(1, 10, 0)
    case CAIRO_SURFACE_TYPE_SCRIPT:
      klass = rb_cCairo_ScriptSurface;
      break;
    case CAIRO_SURFACE_TYPE_QT:
      klass = rb_cCairo_QtSurface;
      break;
    case CAIRO_SURFACE_TYPE_RECORDING:
      klass = rb_cCairo_RecordingSurface;
      break;
    case CAIRO_SURFACE_TYPE_VG:
      klass = rb_cCairo_VGSurface;
      break;
    case CAIRO_SURFACE_TYPE_GL:
      klass = rb_cCairo_GLSurface;
      break;
    case CAIRO_SURFACE_TYPE_DRM:
      klass = rb_cCairo_DRMSurface;
      break;
    case CAIRO_SURFACE_TYPE_TEE:
      klass = rb_cCairo_TeeSurface;
      break;
    case CAIRO_SURFACE_TYPE_XML:
      klass = rb_cCairo_XMLSurface;
      break;
    case CAIRO_SURFACE_TYPE_SKIA:
      klass = rb_cCairo_SkiaSurface;
      break;
    case CAIRO_SURFACE_TYPE_SUBSURFACE:
      klass = rb_cCairo_SubSurface;
      break;
#endif
#if CAIRO_CHECK_VERSION(1, 11, 4)
    case CAIRO_SURFACE_TYPE_COGL:
      klass = rb_cCairo_CoglSurface;
      break;
#endif
    default:
      klass = rb_cCairo_Surface;
      break;
    }

  if (NIL_P (klass))
    rb_raise (rb_eArgError, "unknown source type: %d", type);

  return klass;
}

static VALUE
cr_surface_image_supported_p (VALUE klass)
{
  return Qtrue;
}

static VALUE
cr_surface_pdf_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_PDF_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_ps_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_PS_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_quartz_supported_p (VALUE klass)
{
#ifdef RB_CAIRO_HAS_QUARTZ_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_win32_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_WIN32_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_svg_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_SVG_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_win32_printing_supported_p (VALUE klass)
{
#ifdef RB_CAIRO_HAS_WIN32_PRINTING_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_quartz_image_supported_p (VALUE klass)
{
#ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_script_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_SCRIPT_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_recording_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_RECORDING_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_gl_supported_p (VALUE klass)
{
#ifdef RB_CAIRO_HAS_GL_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_gl_texture_supported_p (VALUE klass)
{
  return cr_surface_gl_supported_p(klass);
}

static VALUE
cr_surface_tee_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_TEE_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_surface_xml_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_XML_SURFACE
  return Qtrue;
#else
  return Qfalse;
#endif
}

/* constructor/de-constructor */
cairo_surface_t *
rb_cairo_surface_from_ruby_object (VALUE obj)
{
  cairo_surface_t *surface;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Surface))
    {
      rb_raise (rb_eTypeError, "not a cairo surface");
    }
  Data_Get_Struct (obj, cairo_surface_t, surface);
  if (!surface)
    rb_cairo_check_status (CAIRO_STATUS_NULL_POINTER);
  return surface;
}

static rb_cairo__object_holder_t *
cr_object_holder_new (VALUE object)
{
  return rb_cairo__object_holder_new (rb_cCairo_Surface, object);
}

static void
cr_object_holder_free (void *ptr)
{
  rb_cairo__object_holder_free (rb_cCairo_Surface, ptr);
}

static void
cr_surface_free (void *ptr)
{
  cairo_surface_t *surface = ptr;

  if (surface)
    cairo_surface_destroy (surface);
}

VALUE
rb_cairo_surface_to_ruby_object (cairo_surface_t *surface)
{
  if (surface)
    {
      VALUE klass;
      klass = cr_surface_get_klass (surface);
      cairo_surface_reference (surface);
      return Data_Wrap_Struct (klass, NULL, cr_surface_free, surface);
    }
  else
    {
      return Qnil;
    }
}

VALUE
rb_cairo_surface_to_ruby_object_with_destroy (cairo_surface_t *surface)
{
  VALUE rb_surface;

  rb_surface = rb_cairo_surface_to_ruby_object (surface);
  if (surface)
    cairo_surface_destroy (surface);

  return rb_surface;
}

static VALUE
cr_surface_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_surface_free, NULL);
}

static VALUE
cr_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  rb_raise(rb_eNotImpError,
           "%s class creation isn't supported on this cairo installation",
           rb_obj_classname(self));

  return Qnil;
}

/* Surface manipulation */
static VALUE
cr_surface_destroy (VALUE self)
{
  cairo_surface_t *surface;

  surface = _SELF;
  cairo_surface_destroy (surface);
  DATA_PTR (self) = NULL;

  return self;
}

static VALUE
cr_surface_finish (VALUE self)
{
  cairo_surface_t *surface;
  rb_cairo__io_callback_closure_t *closure;

  surface = _SELF;
  closure = cairo_surface_get_user_data (surface, &cr_closure_key);

  cairo_surface_finish (surface);
  cairo_surface_set_user_data (surface, &cr_finished_key, (void *)CR_TRUE, NULL);
  cairo_surface_set_user_data (surface, &cr_object_holder_key, NULL, NULL);

  if (closure && !NIL_P (closure->error))
    rb_exc_raise (closure->error);
  cr_surface_check_status (surface);

  return self;
}

static void
yield_and_finish (VALUE self)
{
  cairo_surface_t *surface;

  rb_yield (self);

  surface = _SELF;
  if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS)
    return;
  if (cairo_surface_get_user_data (surface, &cr_finished_key))
    return;

  cr_surface_finish (self);
}

static VALUE
cr_surface_create_similar (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface, *similar_surface;
  cairo_content_t content;
  int width, height;
  VALUE arg1, arg2, arg3;

  rb_scan_args (argc, argv, "21", &arg1, &arg2, &arg3);

  surface = _SELF;
  if (argc == 2)
    {
      content = cairo_surface_get_content (surface);
      width = NUM2INT (arg1);
      height = NUM2INT (arg2);
    }
  else
    {
      content = RVAL2CRCONTENT (arg1);
      width = NUM2INT (arg2);
      height = NUM2INT (arg3);
    }

  similar_surface = cairo_surface_create_similar (surface, content,
                                                  width, height);
  cr_surface_check_status (similar_surface);
  return CRSURFACE2RVAL_WITH_DESTROY (similar_surface);
}

#if CAIRO_CHECK_VERSION(1, 11, 4)
static VALUE
cr_surface_create_similar_image (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface, *similar_image;
  cairo_format_t format;
  int width, height;
  VALUE arg1, arg2, arg3;

  rb_scan_args (argc, argv, "21", &arg1, &arg2, &arg3);

  surface = _SELF;
  if (argc == 2)
    {
      if (cairo_surface_get_type (surface) == CAIRO_SURFACE_TYPE_IMAGE)
        {
          format = cairo_image_surface_get_format (surface);
        }
      else
        {
          format = CAIRO_FORMAT_ARGB32;
        }
      width = NUM2INT (arg1);
      height = NUM2INT (arg2);
    }
  else
    {
      format = RVAL2CRFORMAT (arg1);
      width = NUM2INT (arg2);
      height = NUM2INT (arg3);
    }

  similar_image = cairo_surface_create_similar_image (surface, format,
                                                      width, height);
  cr_surface_check_status (similar_image);
  return CRSURFACE2RVAL_WITH_DESTROY (similar_image);
}

static VALUE
cr_surface_map_to_image (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface, *mapped_image;
  cairo_rectangle_int_t extents_value;
  cairo_rectangle_int_t *extents = NULL;
  VALUE rb_extents;

  rb_scan_args (argc, argv, "01", &rb_extents);

  surface = _SELF;
  if (!NIL_P (rb_extents))
    {
      extents = &extents_value;
      if (rb_cairo__is_kind_of (rb_extents, rb_cCairo_Rectangle))
        {
          extents->x = NUM2INT (rb_iv_get (rb_extents, "@x"));
          extents->y = NUM2INT (rb_iv_get (rb_extents, "@y"));
          extents->width = NUM2INT (rb_iv_get (rb_extents, "@width"));
          extents->height = NUM2INT (rb_iv_get (rb_extents, "@height"));
        }
      else
        {
          VALUE *values;
          rb_extents = rb_convert_type (rb_extents, T_ARRAY, "Array", "to_ary");
          values = RARRAY_PTR (rb_extents);
          extents->x = NUM2INT (values[0]);
          extents->y = NUM2INT (values[1]);
          extents->height = NUM2INT (values[2]);
          extents->width = NUM2INT (values[3]);
        }
    }

  mapped_image = cairo_surface_map_to_image (surface, extents);
  cr_surface_check_status (mapped_image);
  return CRSURFACE2RVAL_WITH_DESTROY (mapped_image);
}

static VALUE
cr_surface_unmap_image (VALUE self, VALUE rb_mapped_image)
{
  cairo_surface_t *surface, *mapped_image;

  surface = _SELF;
  mapped_image = RVAL2CRSURFACE (rb_mapped_image);
  cairo_surface_unmap_image (surface, mapped_image);
  return Qnil;
}
#endif

#if CAIRO_CHECK_VERSION(1, 10, 0)
static VALUE
cr_surface_destroy_with_destroy_check (VALUE self)
{
  if (DATA_PTR (self))
    cr_surface_destroy (self);
  return Qnil;
}

static VALUE
cr_surface_create_sub_rectangle_surface (VALUE self, VALUE x, VALUE y,
                                         VALUE width, VALUE height)
{
  VALUE rb_surface;
  cairo_surface_t *surface;

  surface = cairo_surface_create_for_rectangle (RVAL2CRSURFACE (self),
                                                NUM2DBL (x),
                                                NUM2DBL (y),
                                                NUM2DBL (width),
                                                NUM2INT (height));
  cr_surface_check_status (surface);
  rb_surface = CRSURFACE2RVAL_WITH_DESTROY (surface);
  if (rb_block_given_p ())
    return rb_ensure (rb_yield, rb_surface,
                      cr_surface_destroy_with_destroy_check, rb_surface);
  else
    return rb_surface;
}

static VALUE
cr_surface_get_device (VALUE self)
{
  return CRDEVICE2RVAL (cairo_surface_get_device (_SELF));
}
#endif

static VALUE
cr_surface_get_content (VALUE self)
{
  return INT2NUM (cairo_surface_get_content (_SELF));
}


#ifdef CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_surface_write_to_png_stream (VALUE self, VALUE target)
{
  cairo_status_t status;
  rb_cairo__io_callback_closure_t closure;

  closure.target = target;
  closure.error = Qnil;

  status = cairo_surface_write_to_png_stream (_SELF,
                                              rb_cairo__io_write_func,
                                              (void *)&closure);
  if (!NIL_P (closure.error))
    rb_exc_raise (closure.error);

  rb_cairo_check_status (status);
  return self;
}

static VALUE
cr_surface_write_to_png (VALUE self, VALUE filename)
{
  cairo_status_t status;
  status = cairo_surface_write_to_png (_SELF, StringValueCStr (filename));
  rb_cairo_check_status (status);
  return self;
}

static VALUE
cr_surface_write_to_png_generic (VALUE self, VALUE target)
{
  if (rb_respond_to (target, rb_cairo__io_id_write))
    return cr_surface_write_to_png_stream (self, target);
  else
    return cr_surface_write_to_png (self, target);
}
#endif

#if CAIRO_CHECK_VERSION(1, 10, 0)
static VALUE
cr_surface_get_mime_data (VALUE self, VALUE mime_type)
{
  cairo_surface_t *surface;
  const unsigned char *data;
  unsigned long length;

  surface = _SELF;
  cairo_surface_get_mime_data (surface, StringValueCStr (mime_type),
                               &data, &length);
  if (data)
    return rb_str_new ((const char *)data, length);
  else
    return Qnil;
}

static VALUE
cr_surface_set_mime_data (VALUE self, VALUE rb_mime_type, VALUE rb_data)
{
  cairo_status_t status;
  cairo_surface_t *surface;
  const char *mime_type;

  surface = _SELF;
  mime_type = StringValueCStr (rb_mime_type);
  if (NIL_P (rb_data))
    {
      status = cairo_surface_set_mime_data (surface, mime_type,
                                            NULL, 0, NULL, NULL);
    }
  else
    {
      const char *raw_data;
      unsigned char *data;
      unsigned long length;

      raw_data = StringValuePtr (rb_data);
      length = RSTRING_LEN (rb_data);
      data = xmalloc (length);
      memcpy (data, raw_data, length);
      status = cairo_surface_set_mime_data (surface, mime_type,
                                            data, length,
                                            xfree, data);
    }
  rb_cairo_check_status (status);
  return Qnil;
}
#endif

#if CAIRO_CHECK_VERSION(1, 11, 4)
static VALUE
cr_surface_supported_mime_type_p (VALUE self, VALUE rb_mime_type)
{
  cairo_surface_t *surface;
  const char *mime_type;
  cairo_bool_t supported_p;

  surface = _SELF;
  mime_type = StringValueCStr (rb_mime_type);
  supported_p = cairo_surface_supports_mime_type (surface, mime_type);
  return CBOOL2RVAL (supported_p);
}
#endif

static VALUE
cr_surface_get_font_options (VALUE self)
{
  cairo_font_options_t *options = cairo_font_options_create();
  cairo_surface_get_font_options (_SELF, options);
  cr_surface_check_status (_SELF);
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
      int i;
      VALUE args;

      args = rb_ary_new2 (n);
      for (i = 0; i < n; i++)
        {
          rb_ary_push (args, argv[i]);
        }

      rb_raise (rb_eArgError,
                "invalid argument (expect () or (x, y, width, height)): %s",
                rb_cairo__inspect (args));
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

static VALUE
cr_surface_get_device_offset (VALUE self)
{
  double x_offset, y_offset;

  cairo_surface_get_device_offset (_SELF, &x_offset, &y_offset);
  cr_surface_check_status (_SELF);
  return rb_ary_new3 (2, rb_float_new (x_offset), rb_float_new (y_offset));
}

static VALUE
cr_surface_set_fallback_resolution (VALUE self,
                                    VALUE x_pixels_per_inch,
                                    VALUE y_pixels_per_inch)
{
  cairo_surface_set_fallback_resolution (_SELF,
                                         NUM2DBL (x_pixels_per_inch),
                                         NUM2DBL (y_pixels_per_inch));
  cr_surface_check_status (_SELF);
  return self;
}

#if CAIRO_CHECK_VERSION(1, 7, 2)
static VALUE
cr_surface_get_fallback_resolution (VALUE self)
{
  double x_pixels_per_inch, y_pixels_per_inch;

  cairo_surface_get_fallback_resolution (_SELF,
                                         &x_pixels_per_inch,
                                         &y_pixels_per_inch);
  cr_surface_check_status (_SELF);
  return rb_ary_new3 (2,
                      rb_float_new (x_pixels_per_inch),
                      rb_float_new (y_pixels_per_inch));
}
#endif


#if CAIRO_CHECK_VERSION(1, 5, 2)
static VALUE
cr_surface_copy_page (VALUE self)
{
  cairo_surface_copy_page (_SELF);
  cr_surface_check_status (_SELF);
  return self;
}

static VALUE
cr_surface_show_page (VALUE self)
{
  cairo_surface_show_page (_SELF);
  cr_surface_check_status (_SELF);
  return self;
}
#endif

/* image surface functions */
#ifdef CAIRO_HAS_PNG_FUNCTIONS
static cairo_surface_t *
cr_image_surface_create_from_png_stream (VALUE target)
{
  rb_cairo__io_callback_closure_t closure;
  cairo_surface_t *surface;

  closure.target = target;
  closure.error = Qnil;

  surface = cairo_image_surface_create_from_png_stream (rb_cairo__io_read_func,
                                                        (void *)&closure);
  if (!NIL_P (closure.error))
    rb_exc_raise (closure.error);

  return surface;
}

static cairo_surface_t *
cr_image_surface_create_from_png (VALUE filename)
{
  return cairo_image_surface_create_from_png (StringValueCStr (filename));
}

static VALUE
cr_image_surface_create_from_png_generic (VALUE klass, VALUE target)
{
  VALUE rb_surface;
  cairo_surface_t *surface;

  if (rb_respond_to (target, rb_cairo__io_id_read))
    surface = cr_image_surface_create_from_png_stream (target);
  else
    surface = cr_image_surface_create_from_png (target);

  cr_surface_check_status (surface);
  rb_surface = cr_surface_allocate (klass);
  DATA_PTR (rb_surface) = surface;
  return rb_surface;
}
#endif

static cairo_surface_t *
cr_image_surface_create (VALUE self, VALUE format, VALUE width, VALUE height)
{
  cairo_format_t cr_format;
  cr_format = NIL_P (format) ? CAIRO_FORMAT_ARGB32 : RVAL2CRFORMAT (format);
  return cairo_image_surface_create (cr_format,
                                     NUM2INT (width),
                                     NUM2INT (height));
}

static cairo_surface_t *
cr_image_surface_create_for_data (VALUE self, VALUE rb_data, VALUE format,
                                  VALUE width, VALUE height, VALUE stride)
{
  unsigned char *data;

  data = (unsigned char *)StringValuePtr (rb_data);

  return cairo_image_surface_create_for_data (data,
                                              RVAL2CRFORMAT (format),
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

  n = rb_scan_args (argc, argv, "23", &arg1, &arg2, &arg3, &arg4, &arg5);

  if (n == 2)
    surface = cr_image_surface_create (self, Qnil, arg1, arg2);
  else if (n == 3)
    surface = cr_image_surface_create (self, arg1, arg2, arg3);
  else if (n == 5)
    surface =
      cr_image_surface_create_for_data (self, arg1, arg2, arg3, arg4, arg5);
  else
    rb_raise (rb_eArgError,
              "invalid argument (expect "
              "(width, height) or "
              "(format, width, height) or "
              "(data, format, width, height, stride)): %s",
              rb_cairo__inspect (rb_ary_new3 (4, arg1, arg2, arg3, arg4)));

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_image_surface_get_data (VALUE self)
{
  unsigned char *data;
  cairo_surface_t *surface;

  surface = _SELF;
  data = cairo_image_surface_get_data (surface);

  if (data)
    return rb_str_new ((const char *)data,
                       cairo_image_surface_get_stride (surface) *
                       cairo_image_surface_get_height (surface));
  else
    return Qnil;
}

static VALUE
cr_image_surface_get_format (VALUE self)
{
  return INT2NUM (cairo_image_surface_get_format (_SELF));
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

static VALUE
cr_image_surface_get_stride (VALUE self)
{
  return INT2NUM (cairo_image_surface_get_stride (_SELF));
}

/* printing surfaces */
#define DEFINE_SURFACE(type)                                            \
static VALUE                                                            \
cr_ ## type ## _surface_initialize (int argc, VALUE *argv, VALUE self)  \
{                                                                       \
  VALUE target, rb_width_in_points, rb_height_in_points;                \
  VALUE arg2, arg3;                                                     \
  cairo_surface_t *surface;                                             \
  double width_in_points, height_in_points;                             \
                                                                        \
  rb_scan_args (argc, argv, "21", &target, &arg2, &arg3);               \
  if (argc == 2)                                                        \
    {                                                                   \
      VALUE paper;                                                      \
                                                                        \
      paper = arg2;                                                     \
      cr_paper_to_size_in_points (paper,                                \
                                  &rb_width_in_points,                  \
                                  &rb_height_in_points);                \
    }                                                                   \
  else                                                                  \
    {                                                                   \
      rb_width_in_points = arg2;                                        \
      rb_height_in_points = arg3;                                       \
    }                                                                   \
                                                                        \
  width_in_points = NUM2DBL (rb_width_in_points);                       \
  height_in_points = NUM2DBL (rb_height_in_points);                     \
                                                                        \
  if (rb_respond_to (target, rb_cairo__io_id_write))                    \
    {                                                                   \
      rb_cairo__io_callback_closure_t *closure;                         \
                                                                        \
      closure = rb_cairo__io_closure_new (target);                      \
      surface =                                                         \
        cairo_ ## type ## _surface_create_for_stream (                  \
          rb_cairo__io_write_func,                                      \
          (void *) closure,                                             \
          width_in_points,                                              \
          height_in_points);                                            \
                                                                        \
      if (cairo_surface_status (surface))                               \
        {                                                               \
          rb_cairo__io_closure_destroy (closure);                       \
        }                                                               \
      else                                                              \
        {                                                               \
          rb_ivar_set (self, rb_cairo__io_id_output, target);           \
          cairo_surface_set_user_data (surface, &cr_closure_key,        \
                                       closure,                         \
                                       rb_cairo__io_closure_free);      \
          cairo_surface_set_user_data (surface, &cr_object_holder_key,  \
                                       cr_object_holder_new (self),     \
                                       cr_object_holder_free);          \
        }                                                               \
    }                                                                   \
  else                                                                  \
    {                                                                   \
      surface =                                                         \
        cairo_ ## type ## _surface_create (StringValueCStr (target),    \
                                           width_in_points,             \
                                           height_in_points);           \
    }                                                                   \
                                                                        \
  cr_surface_check_status (surface);                                    \
  DATA_PTR (self) = surface;                                            \
  if (rb_block_given_p ())                                              \
    yield_and_finish (self);                                            \
  return Qnil;                                                          \
}

#define DEFINE_SURFACE_SET_SIZE(type)                                   \
static VALUE                                                            \
cr_ ## type ## _surface_set_size (int argc, VALUE *argv, VALUE self)    \
{                                                                       \
  VALUE arg1, arg2;                                                     \
  VALUE width_in_points, height_in_points;                              \
                                                                        \
  rb_scan_args(argc, argv, "11", &arg1, &arg2);                         \
  if (argc == 1)                                                        \
    {                                                                   \
      VALUE paper;                                                      \
                                                                        \
      paper = arg1;                                                     \
      cr_paper_to_size_in_points (paper,                                \
                                  &width_in_points,                     \
                                  &height_in_points);                   \
    }                                                                   \
  else                                                                  \
    {                                                                   \
      width_in_points = arg1;                                           \
      height_in_points = arg2;                                          \
    }                                                                   \
                                                                        \
  cairo_ ## type ## _surface_set_size (_SELF,                           \
                                       NUM2DBL (width_in_points),       \
                                       NUM2DBL (height_in_points));     \
  cr_surface_check_status (_SELF);                                      \
  return Qnil;                                                          \
}

#ifdef CAIRO_HAS_PDF_SURFACE
/* PDF-surface functions */
DEFINE_SURFACE(pdf)
DEFINE_SURFACE_SET_SIZE(pdf)

#  if CAIRO_CHECK_VERSION(1, 10, 0)
static VALUE
cr_pdf_surface_restrict_to_version (VALUE self, VALUE version)
{
  cairo_pdf_surface_restrict_to_version (_SELF, RVAL2CRPDFVERSION (version));
  cr_surface_check_status (_SELF);
  return Qnil;
}
#  endif
#endif

#ifdef CAIRO_HAS_PS_SURFACE
/* PS-surface functions */
DEFINE_SURFACE(ps)
DEFINE_SURFACE_SET_SIZE(ps)

static VALUE
cr_ps_surface_dsc_comment (VALUE self, VALUE comment)
{
  cairo_ps_surface_dsc_comment (_SELF, StringValueCStr (comment));
  cr_surface_check_status (_SELF);
  return Qnil;
}

static VALUE
cr_ps_surface_dsc_begin_setup (VALUE self)
{
  cairo_ps_surface_dsc_begin_setup (_SELF);
  cr_surface_check_status (_SELF);
  if (rb_block_given_p ())
    return rb_yield (self);
  else
    return Qnil;
}

static VALUE
cr_ps_surface_dsc_begin_page_setup (VALUE self)
{
  cairo_ps_surface_dsc_begin_page_setup (_SELF);
  cr_surface_check_status (_SELF);
  if (rb_block_given_p ())
    return rb_yield (self);
  else
    return Qnil;
}

#  if CAIRO_CHECK_VERSION(1, 5, 2)
static VALUE
cr_ps_surface_restrict_to_level (VALUE self, VALUE level)
{
  cairo_ps_surface_restrict_to_level (_SELF, RVAL2CRPSLEVEL (level));
  cr_surface_check_status (_SELF);
  return Qnil;
}

static VALUE
cr_ps_surface_get_eps (VALUE self)
{
  return cairo_ps_surface_get_eps (_SELF) ? Qtrue : Qfalse;
}

static VALUE
cr_ps_surface_set_eps (VALUE self, VALUE eps)
{
  cairo_ps_surface_set_eps (_SELF, RTEST (eps));
  cr_surface_check_status (_SELF);
  return Qnil;
}
#  endif
#endif

#ifdef RB_CAIRO_HAS_QUARTZ_SURFACE
/* Quartz-surface functions */
#include <objc/objc-runtime.h>

BOOL rbobj_to_nsobj (VALUE obj, id* nsobj);
VALUE ocid_to_rbobj (VALUE context_obj, id ocid);

static VALUE
cr_quartz_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  id objc_object = nil;
  CGContextRef context;
  unsigned int width, height;
  cairo_surface_t *surface = NULL;
  cairo_format_t format = CAIRO_FORMAT_ARGB32;
  VALUE arg1, arg2, arg3, rb_width, rb_height;
  static VALUE rb_cOSXCGContextRef = Qnil;

  rb_scan_args (argc, argv, "21", &arg1, &arg2, &arg3);

  if (argc == 2)
    {
      rb_width = arg1;
      rb_height = arg2;
    }
  else
    {
      switch (TYPE (arg1))
        {
        case T_NIL:
          break;
        case T_STRING:
        case T_SYMBOL:
        case T_FIXNUM:
          format = RVAL2CRFORMAT (arg1);
          break;
        default:
          if (NIL_P (rb_cOSXCGContextRef))
            rb_cOSXCGContextRef =
              rb_const_get (rb_const_get (rb_cObject, rb_intern ("OSX")),
                            rb_intern ("CGContextRef"));

          if (RTEST (rb_obj_is_kind_of (arg1, rb_cOSXCGContextRef)))
            rbobj_to_nsobj (arg1, &objc_object);
          else
            rb_raise (rb_eArgError,
                      "invalid argument (expect "
                      "(width, height), "
                      "(format, width, height) or "
                      "(cg_context, width, height)): %s",
                      rb_cairo__inspect (rb_ary_new3 (3, arg1, arg2, arg3)));
          break;
        }

      rb_width = arg2;
      rb_height = arg3;
    }

  width = NUM2UINT (rb_width);
  height = NUM2UINT (rb_height);

  if (objc_object == nil)
    {
      surface = cairo_quartz_surface_create (format, width, height);
    }
  else
    {
      context = (CGContextRef)objc_object;
      surface =
        cairo_quartz_surface_create_for_cg_context (context, width, height);
    }

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_quartz_surface_get_cg_context (VALUE self)
{
  CGContextRef context;
  id objc_object;

  context = cairo_quartz_surface_get_cg_context (_SELF);
  objc_object = (id)context;
  return ocid_to_rbobj (Qnil, objc_object);
}
#endif

#ifdef CAIRO_HAS_WIN32_SURFACE
/* Win32 surface functions */

/* from dl/dl.h (ruby 1.9) */
#  if SIZEOF_LONG == SIZEOF_VOIDP
#    define PTR2NUM(x)   (ULONG2NUM((unsigned long)(x)))
#    define NUM2PTR(x)   ((void *)(NUM2ULONG(x)))
#  else
#    define PTR2NUM(x)   (ULL2NUM((unsigned long long)(x)))
#    define NUM2PTR(x)   ((void *)(NUM2ULL(x)))
#  endif

static VALUE
cr_win32_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface = NULL;
  VALUE arg1, arg2, arg3, arg4;
  VALUE hdc, format, width, height;

  rb_scan_args (argc, argv, "13", &arg1, &arg2, &arg3, &arg4);

  switch (argc)
    {
    case 1:
      hdc = arg1;
      surface = cairo_win32_surface_create (NUM2PTR (hdc));
      break;
    case 2:
      width = arg1;
      height = arg2;
      surface = cairo_win32_surface_create_with_dib (CAIRO_FORMAT_ARGB32,
                                                     NUM2INT (width),
                                                     NUM2INT (height));
      break;
    case 3:
      if (NIL_P (arg1) ||
          (rb_cairo__is_kind_of (arg1, rb_cNumeric) &&
           NUM2INT (arg1) != CAIRO_FORMAT_RGB24))
        {
#  if CAIRO_CHECK_VERSION(1, 4, 0)
          HDC win32_hdc;
          hdc = arg1;
          width = arg2;
          height = arg3;
          win32_hdc = NIL_P (hdc) ? NULL : NUM2PTR (hdc);
          surface = cairo_win32_surface_create_with_ddb (win32_hdc,
                                                         CAIRO_FORMAT_RGB24,
                                                         NUM2INT (width),
                                                         NUM2INT (height));
#  else
          rb_raise (rb_eArgError,
                    "Cairo::Win32Surface.new(hdc, width, height) "
                    "is available since cairo >= 1.4.0");
#  endif
        }
      else
        {
          format = arg1;
          width = arg2;
          height = arg3;
          surface = cairo_win32_surface_create_with_dib (RVAL2CRFORMAT (format),
                                                         NUM2INT (width),
                                                         NUM2INT (height));
        }
      break;
    case 4:
      {
#  if CAIRO_CHECK_VERSION(1, 4, 0)
        HDC win32_hdc;
        hdc = arg1;
        format = arg2;
        width = arg3;
        height = arg4;
        win32_hdc = NIL_P (hdc) ? NULL : (HDC) NUM2UINT (hdc);
        surface = cairo_win32_surface_create_with_ddb (win32_hdc,
                                                       RVAL2CRFORMAT (format),
                                                       NUM2INT (width),
                                                       NUM2INT (height));
#  else
        rb_raise (rb_eArgError,
                  "Cairo::Win32Surface.new(hdc, format, width, height) "
                  "is available since cairo >= 1.4.0");
#  endif
      }
      break;
    }

  if (!surface)
    rb_cairo_check_status (CAIRO_STATUS_INVALID_FORMAT);
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_win32_surface_get_hdc (VALUE self)
{
  HDC hdc;

  hdc = cairo_win32_surface_get_dc (_SELF);
  if (!hdc)
    return Qnil;
  else
    return PTR2NUM (hdc);
}

#  if CAIRO_CHECK_VERSION(1, 4, 0)
static VALUE
cr_win32_surface_get_image (VALUE self)
{
  cairo_surface_t *surface;

  surface = cairo_win32_surface_get_image (_SELF);
  if (!surface)
    return Qnil;
  cr_surface_check_status (surface);
  return CRSURFACE2RVAL (surface);
}
#  endif
#endif

#ifdef CAIRO_HAS_SVG_SURFACE
/* SVG-surface functions */
DEFINE_SURFACE(svg)

static VALUE
cr_svg_surface_restrict_to_version (VALUE self, VALUE version)
{
  cairo_svg_surface_restrict_to_version (_SELF, RVAL2CRSVGVERSION (version));
  cr_surface_check_status (_SELF);
  return Qnil;
}
#endif

#ifdef RB_CAIRO_HAS_WIN32_PRINTING_SURFACE
/* Win32 printing surface functions */
static VALUE
cr_win32_printing_surface_initialize (VALUE self, VALUE hdc)
{
  cairo_surface_t *surface = NULL;

  surface = cairo_win32_printing_surface_create (NUM2PTR (hdc));
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}
#endif

#ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE
/* Quartz image surface functions */
static VALUE
cr_quartz_image_surface_initialize (VALUE self, VALUE image_surface)
{
  cairo_surface_t *surface;

  surface = cairo_quartz_image_surface_create (RVAL2CRSURFACE (image_surface));
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_quartz_image_surface_get_image (VALUE self)
{
  cairo_surface_t *surface;

  surface = cairo_quartz_image_surface_get_image (_SELF);
  if (!surface)
    return Qnil;
  cr_surface_check_status (surface);
  return CRSURFACE2RVAL (surface);
}
#endif

#ifdef CAIRO_HAS_SCRIPT_SURFACE
/* script surface functions */
static VALUE
cr_script_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface = NULL, *target = NULL;
  cairo_device_t *device;
  double width = 0.0, height = 0.0;
  cairo_content_t content = CAIRO_CONTENT_COLOR_ALPHA;
  VALUE arg1, arg2, arg3, arg4;

  rb_scan_args (argc, argv, "22", &arg1, &arg2, &arg3, &arg4);

  device = RVAL2CRDEVICE (arg1);
  if (argc == 2)
    {
      target = RVAL2CRSURFACE (arg2);
    }
  else
    {
      width = NUM2DBL (arg2);
      height = NUM2DBL (arg3);
      switch (TYPE (arg4))
        {
        case T_NIL:
          break;
        case T_STRING:
        case T_SYMBOL:
        case T_FIXNUM:
          content = RVAL2CRCONTENT (arg4);
          break;
        default:
          rb_raise (rb_eArgError,
                    "invalid argument (expect "
                    "(device, width, height), "
                    "(device, width, height, content) or "
                    "(device, surface)): %s",
                    rb_cairo__inspect (rb_ary_new4 (argc, argv)));
          break;
        }
    }

  if (target)
    surface = cairo_script_surface_create_for_target (device, target);
  else
    surface = cairo_script_surface_create (device, content, width, height);

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}
#endif

#ifdef CAIRO_HAS_RECORDING_SURFACE
/* recording surface functions */
static VALUE
cr_recording_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  VALUE arg1, arg2, arg3, arg4, arg5;
  cairo_surface_t *surface;
  cairo_content_t content = CAIRO_CONTENT_COLOR_ALPHA;
  cairo_rectangle_t extents;
  const char *error_message =
    "invalid argument (expect "
    "(x, y, width, height), "
    "([x, y, width, height]),"
    "(x, y, width, height, content) or "
    "([x, y, width, height], content)): %s";

  rb_scan_args (argc, argv, "14", &arg1, &arg2, &arg3, &arg4, &arg5);
  if (argc == 1 || argc == 2)
    {
      VALUE rb_extents;

      rb_extents = rb_check_array_type (arg1);
      if (RARRAY_LEN (rb_extents) != 4)
        rb_raise (rb_eArgError, error_message, rb_cairo__inspect (arg1));
      extents.x = NUM2DBL (RARRAY_PTR (rb_extents)[0]);
      extents.y = NUM2DBL (RARRAY_PTR (rb_extents)[1]);
      extents.width = NUM2DBL (RARRAY_PTR (rb_extents)[2]);
      extents.height = NUM2DBL (RARRAY_PTR (rb_extents)[3]);
      if (!NIL_P (arg2))
        content = RVAL2CRCONTENT (arg2);
    }
  else if (argc == 4 || argc == 5)
    {
      extents.x = NUM2DBL (arg1);
      extents.y = NUM2DBL (arg2);
      extents.width = NUM2DBL (arg3);
      extents.height = NUM2DBL (arg4);
      if (!NIL_P (arg5))
        content = RVAL2CRCONTENT (arg5);
    }
  else
    {
      rb_raise (rb_eArgError, error_message,
                rb_cairo__inspect (rb_ary_new4 (argc, argv)));
    }

  surface = cairo_recording_surface_create (content, &extents);
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_recording_surface_get_ink_extents (VALUE self)
{
  cairo_surface_t *surface;
  double x, y, width, height;

  surface = _SELF;
  cairo_recording_surface_ink_extents (surface, &x, &y, &width, &height);
  cr_surface_check_status (surface);
  return rb_ary_new3 (4,
                      rb_float_new (x), rb_float_new (y),
                      rb_float_new (width), rb_float_new (height));
}

#  if CAIRO_CHECK_VERSION(1, 11, 4)
static VALUE
cr_recording_surface_get_extents (VALUE self)
{
  cairo_surface_t *surface;
  cairo_rectangle_t extents;

  surface = _SELF;
  cairo_recording_surface_get_extents (surface, &extents);
  cr_surface_check_status (surface);
  return rb_ary_new3 (4,
                      rb_float_new (extents.x),
                      rb_float_new (extents.y),
                      rb_float_new (extents.width),
                      rb_float_new (extents.height));
}
#  endif
#endif

#ifdef RB_CAIRO_HAS_GL_SURFACE
/* GL surface functions */
static VALUE
cr_gl_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  cairo_device_t *device;
  int width, height;
  cairo_content_t content = CAIRO_CONTENT_COLOR_ALPHA;
  VALUE rb_device, rb_width, rb_height, rb_content;

  rb_scan_args (argc, argv, "31",
                &rb_device, &rb_width, &rb_height, &rb_content);

  device = RVAL2CRDEVICE (rb_device);
  width = NUM2INT (rb_width);
  height = NUM2INT (rb_height);
  switch (TYPE (rb_content))
    {
    case T_NIL:
      break;
    case T_STRING:
    case T_SYMBOL:
    case T_FIXNUM:
      content = RVAL2CRCONTENT (rb_content);
      break;
    default:
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(device, width, height) or "
                "(device, width, height, content)): %s",
                rb_cairo__inspect (rb_ary_new4 (argc, argv)));
      break;
    }

  surface = cairo_gl_surface_create (device, content, width, height);

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_gl_texture_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  cairo_device_t *device;
  unsigned int texture;
  int width, height;
  cairo_content_t content = CAIRO_CONTENT_COLOR_ALPHA;
  VALUE rb_device, rb_texture, rb_width, rb_height, rb_content;

  rb_scan_args (argc, argv, "41",
                &rb_device, &rb_texture, &rb_width, &rb_height, &rb_content);

  device = RVAL2CRDEVICE (rb_device);
  texture = NUM2UINT (rb_texture);
  width = NUM2INT (rb_width);
  height = NUM2INT (rb_height);
  switch (TYPE (rb_content))
    {
    case T_NIL:
      break;
    case T_STRING:
    case T_SYMBOL:
    case T_FIXNUM:
      content = RVAL2CRCONTENT (rb_content);
      break;
    default:
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(device, texture, width, height) or "
                "(device, texture, width, height, content)): %s",
                rb_cairo__inspect (rb_ary_new4 (argc, argv)));
      break;
    }

  surface = cairo_gl_surface_create_for_texture (device, content,
                                                 texture,
                                                 width,
                                                 height);

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_gl_surface_set_size (VALUE self, VALUE width, VALUE height)
{
  cairo_surface_t *surface = NULL;

  surface = _SELF;
  cairo_gl_surface_set_size (surface, NUM2INT (width), NUM2INT (height));
  cr_surface_check_status (surface);
  return Qnil;
}

static VALUE
cr_gl_surface_get_width (VALUE self)
{
  return INT2NUM (cairo_gl_surface_get_width (_SELF));
}

static VALUE
cr_gl_surface_get_height (VALUE self)
{
  return INT2NUM (cairo_gl_surface_get_height (_SELF));
}

static VALUE
cr_gl_surface_swap_buffers (VALUE self)
{
  cairo_surface_t *surface = NULL;

  surface = _SELF;
  cairo_gl_surface_swapbuffers (surface);
  cr_surface_check_status (surface);
  return Qnil;
}
#endif

#ifdef CAIRO_HAS_TEE_SURFACE
/* tee surface functions */
static VALUE
cr_tee_surface_initialize (VALUE self, VALUE master)
{
  cairo_surface_t *surface = NULL;

  surface = cairo_tee_surface_create (RVAL2CRSURFACE (master));
  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  rb_iv_set (self, "surfaces", rb_ary_new3 (1, master));
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_tee_surface_add (VALUE self, VALUE target)
{
  cairo_surface_t *surface = NULL;

  surface = _SELF;
  cairo_tee_surface_add (surface, RVAL2CRSURFACE (target));
  cr_surface_check_status (surface);
  rb_ary_push (rb_iv_get (self, "surfaces"), target);
  return Qnil;
}

static VALUE
cr_tee_surface_shift_operator (VALUE self, VALUE target)
{
  cr_tee_surface_add (self, target);
  return self;
}

static VALUE
cr_tee_surface_remove (VALUE self, VALUE target_or_index)
{
  cairo_surface_t *surface = NULL, *target;
  VALUE rb_surfaces;
  int i;

  surface = _SELF;
  if (rb_cairo__is_kind_of (target_or_index, rb_cCairo_Surface))
    {
      target = RVAL2CRSURFACE (target_or_index);
    }
  else
    {
      VALUE index;

      index = rb_check_to_integer (target_or_index, "to_int");
      if (NIL_P (index))
        rb_raise (rb_eArgError,
                  "invalid argument (expect (surface) or (index)): %s",
                  rb_cairo__inspect (target_or_index));
      target = cairo_tee_surface_index (surface, NUM2INT (index));
    }
  cairo_tee_surface_remove (surface, target);
  cr_surface_check_status (surface);

  rb_surfaces = rb_iv_get (self, "surfaces");
  for (i = 0; i < RARRAY_LEN (rb_surfaces); i++)
    {
      VALUE rb_marked_surface;
      cairo_surface_t *marked_surface;

      rb_marked_surface = RARRAY_PTR (rb_surfaces)[i];
      marked_surface = RVAL2CRSURFACE (rb_marked_surface);
      if (marked_surface == target)
        {
          rb_ary_delete (rb_surfaces, rb_marked_surface);
          break;
        }
    }

  return Qnil;
}

static VALUE
cr_tee_surface_array_reference (VALUE self, VALUE index)
{
  cairo_surface_t *surface = NULL, *target;

  surface = _SELF;
  index = rb_Integer (index);
  target = cairo_tee_surface_index (surface, NUM2UINT (index));
  cr_surface_check_status (surface);
  cr_surface_check_status (target);
  return CRSURFACE2RVAL (target);
}
#endif

#ifdef CAIRO_HAS_XML_SURFACE
/* XML surface functions */
static VALUE
cr_xml_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_surface_t *surface;
  cairo_device_t *device;
  double width, height;
  cairo_content_t content = CAIRO_CONTENT_COLOR_ALPHA;
  VALUE rb_device, rb_width, rb_height, rb_content;

  rb_scan_args (argc, argv, "31",
                &rb_device, &rb_width, &rb_height, &rb_content);

  device = RVAL2CRDEVICE (rb_device);
  width = NUM2DBL (rb_width);
  height = NUM2DBL (rb_height);
  switch (TYPE (rb_content))
    {
    case T_NIL:
      break;
    case T_STRING:
    case T_SYMBOL:
    case T_FIXNUM:
      content = RVAL2CRCONTENT (rb_content);
      break;
    default:
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(device, width, height) or "
                "(device, width, height, content)): %s",
                rb_cairo__inspect (rb_ary_new4 (argc, argv)));
      break;
    }

  surface = cairo_xml_surface_create (device, content, width, height);

  cr_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    yield_and_finish (self);
  return Qnil;
}
#endif

static int
cr_finish_all_guarded_surfaces_at_end_iter (VALUE key, VALUE value, VALUE data)
{
  cr_surface_finish (key);
  return ST_CONTINUE;
}

static void
cr_finish_all_guarded_surfaces_at_end (VALUE data)
{
  rb_hash_foreach (rb_cairo__gc_guarded_objects (rb_cCairo_Surface),
                   cr_finish_all_guarded_surfaces_at_end_iter,
                   Qnil);
}

void
Init_cairo_surface (void)
{
  cr_id_parse = rb_intern ("parse");
  cr_id_size = rb_intern ("size");
  cr_id_set_unit = rb_intern ("unit=");

  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);
  rb_define_alloc_func (rb_cCairo_Surface, cr_surface_allocate);

  rb_cairo__initialize_gc_guard_holder_class (rb_cCairo_Surface);
  rb_set_end_proc(cr_finish_all_guarded_surfaces_at_end, Qnil);

  rb_define_singleton_method (rb_cCairo_Surface, "image_supported?",
                              cr_surface_image_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "pdf_supported?",
                              cr_surface_pdf_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "ps_supported?",
                              cr_surface_ps_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "quartz_supported?",
                              cr_surface_quartz_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "win32_supported?",
                              cr_surface_win32_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "svg_supported?",
                              cr_surface_svg_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "win32_printing_supported?",
                              cr_surface_win32_printing_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "quartz_image_supported?",
                              cr_surface_quartz_image_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "script_supported?",
                              cr_surface_script_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "recording_supported?",
                              cr_surface_recording_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "gl_supported?",
                              cr_surface_gl_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "gl_texture_supported?",
                              cr_surface_gl_texture_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "tee_supported?",
                              cr_surface_tee_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_Surface, "xml_supported?",
                              cr_surface_xml_supported_p, 0);

  rb_define_method (rb_cCairo_Surface, "initialize",
                    cr_surface_initialize, -1);

  rb_define_method (rb_cCairo_Surface, "create_similar",
                    cr_surface_create_similar, -1);
#if CAIRO_CHECK_VERSION(1, 11, 4)
  rb_define_method (rb_cCairo_Surface, "create_similar_image",
                    cr_surface_create_similar_image, -1);
  rb_define_method (rb_cCairo_Surface, "map_to_image",
                    cr_surface_map_to_image, -1);
  rb_define_method (rb_cCairo_Surface, "unmap_image",
                    cr_surface_unmap_image, 1);
#endif
#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_define_method (rb_cCairo_Surface, "sub_rectangle_surface",
                    cr_surface_create_sub_rectangle_surface, 4);
  rb_define_method (rb_cCairo_Surface, "device",
                    cr_surface_get_device, 0);
#endif
  rb_define_method (rb_cCairo_Surface, "destroy", cr_surface_destroy, 0);
  rb_define_method (rb_cCairo_Surface, "finish", cr_surface_finish, 0);
  rb_define_method (rb_cCairo_Surface, "content", cr_surface_get_content, 0);

#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_define_method (rb_cCairo_Surface, "get_mime_data",
                    cr_surface_get_mime_data, 1);
  rb_define_method (rb_cCairo_Surface, "set_mime_data",
                    cr_surface_set_mime_data, 2);
#endif
#if CAIRO_CHECK_VERSION(1, 11, 4)
  rb_define_method (rb_cCairo_Surface, "supported_mime_type?",
                    cr_surface_supported_mime_type_p, 1);
#endif


  rb_define_method (rb_cCairo_Surface, "font_options",
                    cr_surface_get_font_options, 0);
  rb_define_method (rb_cCairo_Surface, "flush", cr_surface_flush, 0);
  rb_define_method (rb_cCairo_Surface, "mark_dirty", cr_surface_mark_dirty, -1);
  rb_define_method (rb_cCairo_Surface, "set_device_offset",
                    cr_surface_set_device_offset, 2);
  rb_define_method (rb_cCairo_Surface, "device_offset",
                    cr_surface_get_device_offset, 0);
  rb_define_method (rb_cCairo_Surface, "set_fallback_resolution",
                    cr_surface_set_fallback_resolution, 2);
#if CAIRO_CHECK_VERSION(1, 7, 2)
  rb_define_method (rb_cCairo_Surface, "fallback_resolution",
                    cr_surface_get_fallback_resolution, 0);
#endif
#if CAIRO_CHECK_VERSION(1, 5, 2)
  rb_define_method (rb_cCairo_Surface, "copy_page",
                    cr_surface_copy_page, 2);
  rb_define_method (rb_cCairo_Surface, "show_page",
                    cr_surface_show_page, 2);
#endif

#ifdef CAIRO_HAS_PNG_FUNCTIONS
  rb_define_method (rb_cCairo_Surface, "write_to_png",
                    cr_surface_write_to_png_generic, 1);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_Surface);

  /* image surface */
  rb_cCairo_ImageSurface =
    rb_define_class_under (rb_mCairo, "ImageSurface", rb_cCairo_Surface);

#ifdef CAIRO_HAS_PNG_FUNCTIONS
  rb_define_singleton_method (rb_cCairo_ImageSurface, "from_png",
                              cr_image_surface_create_from_png_generic, 1);
#endif

  rb_define_method (rb_cCairo_ImageSurface, "initialize",
                    cr_image_surface_initialize, -1);

  rb_define_method (rb_cCairo_ImageSurface, "data",
                    cr_image_surface_get_data, 0);
  rb_define_method (rb_cCairo_ImageSurface, "format",
                    cr_image_surface_get_format, 0);
  rb_define_method (rb_cCairo_ImageSurface, "width",
                    cr_image_surface_get_width, 0);
  rb_define_method (rb_cCairo_ImageSurface, "height",
                    cr_image_surface_get_height, 0);
  rb_define_method (rb_cCairo_ImageSurface, "stride",
                    cr_image_surface_get_stride, 0);

  /* PDF surface */
  rb_cCairo_PDFSurface =
    rb_define_class_under (rb_mCairo, "PDFSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_PDF_SURFACE
  rb_define_method (rb_cCairo_PDFSurface, "initialize",
                    cr_pdf_surface_initialize, -1);

  rb_define_method (rb_cCairo_PDFSurface, "set_size",
                    cr_pdf_surface_set_size, -1);

#  if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_define_method (rb_cCairo_PDFSurface, "restrict_to_version",
                    cr_pdf_surface_restrict_to_version, 1);
#  endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_PDFSurface);
#endif

  /* PS surface */
  rb_cCairo_PSSurface =
    rb_define_class_under (rb_mCairo, "PSSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_PS_SURFACE
  rb_define_method (rb_cCairo_PSSurface, "initialize",
                    cr_ps_surface_initialize, -1);
  rb_define_method (rb_cCairo_PSSurface, "set_size", cr_ps_surface_set_size, -1);
  rb_define_method (rb_cCairo_PSSurface, "dsc_comment",
                    cr_ps_surface_dsc_comment, 1);
  rb_define_method (rb_cCairo_PSSurface, "dsc_begin_setup",
                    cr_ps_surface_dsc_begin_setup, 0);
  rb_define_method (rb_cCairo_PSSurface, "dsc_begin_page_setup",
                    cr_ps_surface_dsc_begin_page_setup, 0);

#  if CAIRO_CHECK_VERSION(1, 5, 2)
  rb_define_method (rb_cCairo_PSSurface, "restrict_to_level",
                    cr_ps_surface_restrict_to_level, 1);
  rb_define_method (rb_cCairo_PSSurface, "eps?", cr_ps_surface_get_eps, 0);
  rb_define_method (rb_cCairo_PSSurface, "set_eps", cr_ps_surface_set_eps, 1);
#  endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_PSSurface);
#endif

  /* XLib surface */
  rb_cCairo_XLibSurface =
    rb_define_class_under (rb_mCairo, "XLibSurface", rb_cCairo_Surface);

  /* XCB surface */
  rb_cCairo_XCBSurface =
    rb_define_class_under (rb_mCairo, "XCBSurface", rb_cCairo_Surface);

  /* Quartz surface */
  rb_cCairo_QuartzSurface =
    rb_define_class_under (rb_mCairo, "QuartzSurface", rb_cCairo_Surface);
#ifdef RB_CAIRO_HAS_QUARTZ_SURFACE
  rb_define_method (rb_cCairo_QuartzSurface, "initialize",
                    cr_quartz_surface_initialize, -1);
  rb_define_method (rb_cCairo_QuartzSurface, "cg_context",
                    cr_quartz_surface_get_cg_context, 0);
#endif

  /* Win32 surface */
  rb_cCairo_Win32Surface =
    rb_define_class_under (rb_mCairo, "Win32Surface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_WIN32_SURFACE
  rb_define_method (rb_cCairo_Win32Surface, "initialize",
                    cr_win32_surface_initialize, -1);
  rb_define_method (rb_cCairo_Win32Surface, "hdc",
                    cr_win32_surface_get_hdc, 0);
#  if CAIRO_CHECK_VERSION(1, 4, 0)
  rb_define_method (rb_cCairo_Win32Surface, "image",
                    cr_win32_surface_get_image, 0);
#  endif
#endif

  /* SVG surface */
  rb_cCairo_SVGSurface =
    rb_define_class_under (rb_mCairo, "SVGSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_SVG_SURFACE
  rb_define_method (rb_cCairo_SVGSurface, "initialize",
                    cr_svg_surface_initialize, -1);
  rb_define_method (rb_cCairo_SVGSurface, "restrict_to_version",
                    cr_svg_surface_restrict_to_version, 1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_SVGSurface);
#endif

  /* Win32 printing surface */
  rb_cCairo_Win32PrintingSurface =
    rb_define_class_under (rb_mCairo, "Win32PrintingSurface", rb_cCairo_Surface);
#ifdef RB_CAIRO_HAS_WIN32_PRINTING_SURFACE
  rb_define_method (rb_cCairo_Win32PrintingSurface, "initialize",
                    cr_win32_printing_surface_initialize, -1);
  rb_define_method (rb_cCairo_Win32PrintingSurface, "hdc",
                    cr_win32_surface_get_hdc, 0);
#endif

  /* Quartz image surface */
  rb_cCairo_QuartzImageSurface =
    rb_define_class_under (rb_mCairo, "QuartzImageSurface", rb_cCairo_Surface);
#ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE
  rb_define_method (rb_cCairo_QuartzImageSurface, "initialize",
                    cr_quartz_image_surface_initialize, 1);
  rb_define_method (rb_cCairo_QuartzImageSurface, "image",
                    cr_quartz_image_surface_get_image, 0);
#endif

  /* script surface */
  rb_cCairo_ScriptSurface =
    rb_define_class_under (rb_mCairo, "ScriptSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_SCRIPT_SURFACE
  rb_define_method (rb_cCairo_ScriptSurface, "initialize",
                    cr_script_surface_initialize, -1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_ScriptSurface);
#endif

  /* Qt surface */
  rb_cCairo_QtSurface =
    rb_define_class_under (rb_mCairo, "QtSurface", rb_cCairo_Surface);

  /* recording surface */
  rb_cCairo_RecordingSurface =
    rb_define_class_under (rb_mCairo, "RecordingSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_RECORDING_SURFACE
  rb_define_method (rb_cCairo_RecordingSurface, "initialize",
                    cr_recording_surface_initialize, -1);

  rb_define_method (rb_cCairo_RecordingSurface, "ink_extents",
                    cr_recording_surface_get_ink_extents, 0);
#  if CAIRO_CHECK_VERSION(1, 11, 4)
  rb_define_method (rb_cCairo_RecordingSurface, "extents",
                    cr_recording_surface_get_extents, 0);
#  endif
#endif

  /* VG surface */
  rb_cCairo_VGSurface =
    rb_define_class_under (rb_mCairo, "VGSurface", rb_cCairo_Surface);

  /* GL surface */
  rb_cCairo_GLSurface =
    rb_define_class_under (rb_mCairo, "GLSurface", rb_cCairo_Surface);
  rb_cCairo_GLTextureSurface =
    rb_define_class_under (rb_mCairo, "GLTextureSurface", rb_cCairo_GLSurface);
#ifdef RB_CAIRO_HAS_GL_SURFACE
  rb_define_method (rb_cCairo_GLSurface, "initialize",
                    cr_gl_surface_initialize, 1);

  rb_define_method (rb_cCairo_GLSurface, "set_size",
                    cr_gl_surface_set_size, 2);
  rb_define_method (rb_cCairo_GLSurface, "width",
                    cr_gl_surface_get_width, 0);
  rb_define_method (rb_cCairo_GLSurface, "height",
                    cr_gl_surface_get_height, 0);
  rb_define_method (rb_cCairo_GLSurface, "swap_buffers",
                    cr_gl_surface_swap_buffers, 0);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_GLSurface);

  rb_define_method (rb_cCairo_GLTextureSurface, "initialize",
                    cr_gl_texture_surface_initialize, 1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_GLTextureSurface);
#endif

  /* DRM surface */
  rb_cCairo_DRMSurface =
    rb_define_class_under (rb_mCairo, "DRMSurface", rb_cCairo_Surface);

  /* tee surface */
  rb_cCairo_TeeSurface =
    rb_define_class_under (rb_mCairo, "TeeSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_TEE_SURFACE
  rb_define_method (rb_cCairo_TeeSurface, "initialize",
                    cr_tee_surface_initialize, 1);

  rb_define_method (rb_cCairo_TeeSurface, "add",
                    cr_tee_surface_add, 1);
  rb_define_method (rb_cCairo_TeeSurface, "<<",
                    cr_tee_surface_shift_operator, 1);
  rb_define_method (rb_cCairo_TeeSurface, "remove",
                    cr_tee_surface_remove, 1);
  rb_define_method (rb_cCairo_TeeSurface, "[]",
                    cr_tee_surface_array_reference, 1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_TeeSurface);
#endif

  /* XML surface */
  rb_cCairo_XMLSurface =
    rb_define_class_under (rb_mCairo, "XMLSurface", rb_cCairo_Surface);
#ifdef CAIRO_HAS_XML_SURFACE
  rb_define_method (rb_cCairo_XMLSurface, "initialize",
                    cr_xml_surface_initialize, -1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_XMLSurface);
#endif

  /* Skia surface */
  rb_cCairo_SkiaSurface =
    rb_define_class_under (rb_mCairo, "SkiaSurface", rb_cCairo_Surface);

  /* sub surface */
  rb_cCairo_SubSurface =
    rb_define_class_under (rb_mCairo, "SubSurface", rb_cCairo_Surface);

  /* Cogl surface */
  rb_cCairo_CoglSurface =
    rb_define_class_under (rb_mCairo, "CoglSurface", rb_cCairo_Surface);
}
