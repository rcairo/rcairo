/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-02-21 13:18:10 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"

#include "rubyio.h"

#if CAIRO_HAS_PS_SURFACE || CAIRO_HAS_PDF_SURFACE || CAIRO_HAS_SVG_SURFACE
#  define HAS_CREATE_CR_CLOSURE_SURFACE 1
#else
#  define HAS_CREATE_CR_CLOSURE_SURFACE 0
#endif


VALUE rb_cCairo_Surface;
VALUE rb_cCairo_ImageSurface;
VALUE rb_cCairo_PDFSurface = Qnil;
VALUE rb_cCairo_PSSurface = Qnil;
VALUE rb_cCairo_SVGSurface = Qnil;
VALUE rb_cCairo_Win32Surface = Qnil;
VALUE rb_cCairo_QuartzSurface = Qnil;

static ID cr_id_target;
static ID cr_id_read;
static ID cr_id_write;
static ID cr_id_inspect;
static cairo_user_data_key_t cr_closure_key;

#define _SELF  (RVAL2CRSURFACE(self))

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
    case CAIRO_SURFACE_TYPE_SVG:
      klass = rb_cCairo_SVGSurface;
      break;
    case CAIRO_SURFACE_TYPE_WIN32:
      klass = rb_cCairo_Win32Surface;
      break;
    default:
      rb_raise (rb_eArgError, "unknown source type: %d", type);
      break;
    }

  return klass;
}

static char *
inspect (VALUE object)
{
  VALUE inspected;
  inspected = rb_funcall (object, cr_id_inspect, 0);
  return StringValueCStr(inspected);
}

/* read/write callback */
typedef struct cr_io_callback_closure {
  VALUE target;
  VALUE error;
  unsigned char *data;
  unsigned int length;
} cr_io_callback_closure_t;

#if HAS_CREATE_CR_CLOSURE_SURFACE
static cr_io_callback_closure_t *
cr_closure_new (VALUE target)
{
  cr_io_callback_closure_t *closure;
  closure = ALLOC (cr_io_callback_closure_t);

  closure->target = target;
  closure->error = Qnil;

  return closure;
}

static void
cr_closure_destroy (cr_io_callback_closure_t *closure)
{
  free (closure);
}

static void
cr_closure_free (void *closure)
{
  cr_closure_destroy ((cr_io_callback_closure_t *) closure);
}
#endif

static VALUE
cr_surface_io_func_rescue (VALUE io_closure)
{
  cr_io_callback_closure_t *closure;
  closure = (cr_io_callback_closure_t *)io_closure;
  closure->error = RB_ERRINFO;
  return Qnil;
}

/* write callback */
static VALUE
cr_surface_write_func_invoke (VALUE write_closure)
{
  VALUE output, data;
  long written_bytes;
  cr_io_callback_closure_t *closure;
  unsigned int length;

  closure = (cr_io_callback_closure_t *)write_closure;
  
  output = closure->target;
  data = rb_str_new ((const char *)closure->data, closure->length);

  length = RSTRING_LEN (data);
  while (length != 0)
    {
      VALUE rb_written_bytes = rb_funcall (output, cr_id_write, 1, data);
      written_bytes = NUM2LONG (rb_written_bytes);
      data = rb_str_substr (data, written_bytes,
                            RSTRING_LEN (data) - written_bytes);
      length -= written_bytes;
    }
  
  return Qnil;
}

static cairo_status_t
cr_surface_write_func (void *write_closure,
                       const unsigned char *data, unsigned int length)
{
  cr_io_callback_closure_t *closure;

  closure = (cr_io_callback_closure_t *)write_closure;
  closure->data = (unsigned char *)data;
  closure->length = length;
  
  rb_rescue2 (cr_surface_write_func_invoke, (VALUE) closure,
              cr_surface_io_func_rescue, (VALUE) closure, rb_eException,
              (VALUE)0);
  
  if (NIL_P (closure->error))
    return CAIRO_STATUS_SUCCESS;
  else
    return CAIRO_STATUS_WRITE_ERROR;
}

/* read callback */
static VALUE
cr_surface_read_func_invoke (VALUE read_closure)
{
  VALUE input, result;
  cr_io_callback_closure_t *closure;
  unsigned int length, rest;

  closure = (cr_io_callback_closure_t *)read_closure;
  input = closure->target;
  length = closure->length;
  
  result = rb_str_new2 ("");

  for (rest = length; rest != 0; rest = length - RSTRING_LEN (result))
    {
      rb_str_concat (result, rb_funcall (input, cr_id_read, 1, INT2NUM (rest)));
    }

  memcpy ((void *)closure->data, (const void *)StringValuePtr (result), length);

  return Qnil;
}

static cairo_status_t
cr_surface_read_func (void *read_closure,
                      unsigned char *data, unsigned int length)
{
  cr_io_callback_closure_t *closure;

  closure = (cr_io_callback_closure_t *)read_closure;
  closure->data = data;
  closure->length = length;
  rb_rescue2 (cr_surface_read_func_invoke, (VALUE) closure,
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
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Surface))
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

static VALUE
cr_surface_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_surface_free, NULL);
}

/* Surface manipulation */
static void
yield_and_finish (VALUE self)
{
  cairo_surface_t *surface;
  cairo_status_t status;

  rb_yield (self);

  surface = _SELF;
  if (cairo_surface_status (surface))
    return;
  cairo_surface_finish (surface);
  status = cairo_surface_status (surface);
  if (status == CAIRO_STATUS_SUCCESS || status == CAIRO_STATUS_SURFACE_FINISHED)
    return;

  cr_surface_check_status (surface);
}

static VALUE
cr_surface_create_similar (VALUE self, VALUE content,
                           VALUE width, VALUE height)
{
  cairo_surface_t *surface;

  surface = cairo_surface_create_similar (RVAL2CRSURFACE (self),
                                          RVAL2CRCONTENT (content),
                                          NUM2INT (width), NUM2INT (height));
  cr_surface_check_status (surface);
  return CRSURFACE2RVAL (surface);
}

static VALUE
cr_surface_finish (VALUE self)
{
  cr_io_callback_closure_t *closure;
  closure = cairo_surface_get_user_data (_SELF, &cr_closure_key);
  
  cairo_surface_finish (_SELF);

  if (closure && !NIL_P (closure->error))
    rb_exc_raise (closure->error);
  
  cr_surface_check_status (_SELF);
  return self;
}

static VALUE
cr_surface_get_content (VALUE self)
{
  return INT2NUM (cairo_surface_get_content (_SELF));
}


#if CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_surface_write_to_png_stream (VALUE self, VALUE target)
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
  if (rb_respond_to (target, cr_id_write))
    return cr_surface_write_to_png_stream (self, target);
  else
    return cr_surface_write_to_png (self, target);
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
                inspect (args));
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

/* Image-surface functions */
#if CAIRO_HAS_PNG_FUNCTIONS
static cairo_surface_t *
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

  if (rb_respond_to (target, cr_id_read))
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
              inspect (rb_ary_new3 (4, arg1, arg2, arg3, arg4)));

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


/* Printing surfaces */
#define DEFINE_SURFACE(type)                                            \
static VALUE                                                            \
cr_ ## type ## _surface_initialize (VALUE self, VALUE target,           \
                                    VALUE rb_width_in_points,           \
                                    VALUE rb_height_in_points)          \
{                                                                       \
  cairo_surface_t *surface;                                             \
  double width_in_points, height_in_points;                             \
                                                                        \
  width_in_points = NUM2DBL (rb_width_in_points);                       \
  height_in_points = NUM2DBL (rb_height_in_points);                     \
                                                                        \
  if (rb_respond_to (target, cr_id_write))                              \
    {                                                                   \
      cr_io_callback_closure_t *closure;                                \
                                                                        \
      closure = cr_closure_new (target);                                \
      surface =                                                         \
        cairo_ ## type ## _surface_create_for_stream (                  \
          cr_surface_write_func,                                        \
          (void *) closure,                                             \
          width_in_points,                                              \
          height_in_points);                                            \
                                                                        \
      if (cairo_surface_status (surface))                               \
        {                                                               \
          cr_closure_destroy (closure);                                 \
        }                                                               \
      else                                                              \
        {                                                               \
          rb_ivar_set (self, cr_id_target, target);                     \
          cairo_surface_set_user_data (surface, &cr_closure_key,        \
                                       closure, cr_closure_free);       \
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


#if CAIRO_HAS_PS_SURFACE
/* PS-surface functions */
DEFINE_SURFACE(ps)

static VALUE
cr_ps_surface_set_size (VALUE self,
                        VALUE width_in_points,
                        VALUE height_in_points)
{
  cairo_ps_surface_set_size (_SELF,
                             NUM2DBL (width_in_points),
                             NUM2DBL (height_in_points));
  cr_surface_check_status (_SELF);
  return Qnil;
}

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
cr_ps_surface_set_eps (VALUE self, VALUE eps)
{
  cairo_ps_surface_set_eps (_SELF, RTEST (eps));
  cr_surface_check_status (_SELF);
  return Qnil;
}
#  endif
#endif

#if CAIRO_HAS_PDF_SURFACE
/* PDF-surface functions */
DEFINE_SURFACE(pdf)

static VALUE
cr_pdf_surface_set_size (VALUE self,
                         VALUE width_in_points,
                         VALUE height_in_points)
{
  cairo_pdf_surface_set_size (_SELF,
                              NUM2DBL (width_in_points),
                              NUM2DBL (height_in_points));
  cr_surface_check_status (_SELF);
  return Qnil;
}
#endif

#if CAIRO_HAS_SVG_SURFACE
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

#if CAIRO_HAS_WIN32_SURFACE
/* WIN32-surface functions */

/* from dl/dl.h (ruby 1.9) */
#if SIZEOF_LONG == SIZEOF_VOIDP
#  define PTR2NUM(x)   (ULONG2NUM((unsigned long)(x)))
#  define NUM2PTR(x)   ((void *)(NUM2ULONG(x)))
#else
#  define PTR2NUM(x)   (ULL2NUM((unsigned long long)(x)))
#  define NUM2PTR(x)   ((void *)(NUM2ULL(x)))
#endif

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
          hdc = arg1;
          width = arg2;
          height = arg3;
          HDC win32_hdc = NIL_P (hdc) ? NULL : NUM2PTR (hdc);
          surface = cairo_win32_surface_create_with_ddb (win32_hdc,
                                                         CAIRO_FORMAT_RGB24,
                                                         NUM2INT (width),
                                                         NUM2INT (height));
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

static VALUE
cr_win32_surface_get_image (VALUE self)
{
  cairo_surface_t *surface;

  surface = cairo_win32_surface_get_image (_SELF);
  if (!surface)
    return Qnil;
  rb_cairo_check_status (cairo_surface_status (surface));
  return CRSURFACE2RVAL (surface);
}
#endif

#if CAIRO_HAS_QUARTZ_SURFACE && defined(HAVE_RUBY_COCOA)
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
                      inspect (rb_ary_new3 (3, arg1, arg2, arg3)));
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


void
Init_cairo_surface (void)
{
  cr_id_target = rb_intern ("target");
  cr_id_read = rb_intern ("read");
  cr_id_write = rb_intern ("write");
  cr_id_inspect = rb_intern ("inspect");

  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);
  rb_define_alloc_func (rb_cCairo_Surface, cr_surface_allocate);
  
  rb_define_method (rb_cCairo_Surface, "create_similar",
                    cr_surface_create_similar, 3);
  rb_define_method (rb_cCairo_Surface, "finish", cr_surface_finish, 0);
  rb_define_method (rb_cCairo_Surface, "content", cr_surface_get_content, 0);

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
#if CAIRO_CHECK_VERSION(1, 5, 2)
  rb_define_method (rb_cCairo_Surface, "copy_page",
                    cr_surface_copy_page, 2);
  rb_define_method (rb_cCairo_Surface, "show_page",
                    cr_surface_show_page, 2);
#endif

#if CAIRO_HAS_PNG_FUNCTIONS
  rb_define_method (rb_cCairo_Surface, "write_to_png",
                    cr_surface_write_to_png_generic, 1);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_Surface);

  /* Image-surface */
  rb_cCairo_ImageSurface =
    rb_define_class_under (rb_mCairo, "ImageSurface", rb_cCairo_Surface);
  
#if CAIRO_HAS_PNG_FUNCTIONS
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

#define INIT_SURFACE(type, name)                                        \
  rb_cCairo_ ## name ## Surface =                                       \
    rb_define_class_under (rb_mCairo, # name "Surface",                 \
                           rb_cCairo_Surface);                          \
                                                                        \
  rb_define_method (rb_cCairo_ ## name ## Surface, "initialize",        \
                    cr_ ## type ## _surface_initialize, 3);

#if CAIRO_HAS_PS_SURFACE
  /* PS-surface */
  INIT_SURFACE(ps, PS)

  rb_define_method (rb_cCairo_PSSurface, "set_size", cr_ps_surface_set_size, 2);
  rb_define_method (rb_cCairo_PSSurface, "dsc_comment",
                    cr_ps_surface_dsc_comment, 1);
  rb_define_method (rb_cCairo_PSSurface, "dsc_begin_setup",
                    cr_ps_surface_dsc_begin_setup, 0);
  rb_define_method (rb_cCairo_PSSurface, "dsc_begin_page_setup",
                    cr_ps_surface_dsc_begin_page_setup, 0);

#if CAIRO_CHECK_VERSION(1, 5, 2)
  rb_define_method (rb_cCairo_PSSurface, "restrict_to_level",
                    cr_ps_surface_restrict_to_level, 1);
  rb_define_method (rb_cCairo_PSSurface, "set_eps",
                    cr_ps_surface_set_eps, 1);
#endif

  RB_CAIRO_DEF_SETTERS (rb_cCairo_PSSurface);
#endif

#if CAIRO_HAS_PDF_SURFACE
  /* PDF-surface */
  INIT_SURFACE(pdf, PDF)

  rb_define_method (rb_cCairo_PDFSurface, "set_size",
                    cr_pdf_surface_set_size, 2);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_PDFSurface);
#endif

#if CAIRO_HAS_SVG_SURFACE
  /* SVG-surface */
  INIT_SURFACE(svg, SVG)

  rb_define_method (rb_cCairo_SVGSurface, "restrict_to_version",
                    cr_svg_surface_restrict_to_version, 1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_SVGSurface);
#endif

#if CAIRO_HAS_WIN32_SURFACE
  /* Win32-surface */
  rb_cCairo_Win32Surface =
    rb_define_class_under (rb_mCairo, "Win32Surface", rb_cCairo_Surface);

  rb_define_method (rb_cCairo_Win32Surface, "initialize",
                    cr_win32_surface_initialize, -1);
  rb_define_method (rb_cCairo_Win32Surface, "hdc",
                    cr_win32_surface_get_hdc, 0);
  rb_define_method (rb_cCairo_Win32Surface, "image",
                    cr_win32_surface_get_image, 0);
#endif

#if CAIRO_HAS_QUARTZ_SURFACE
  /* Quartz-surface */

  rb_cCairo_QuartzSurface =
    rb_define_class_under (rb_mCairo, "QuartzSurface", rb_cCairo_Surface);

  rb_define_method (rb_cCairo_QuartzSurface, "initialize",
                    cr_quartz_surface_initialize, -1);
  rb_define_method (rb_cCairo_QuartzSurface, "cg_context",
                    cr_quartz_surface_get_cg_context, 0);
#endif
}
