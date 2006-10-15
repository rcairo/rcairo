/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2006-10-15 07:12:33 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rubyio.h"

#if CAIRO_HAS_PS_SURFACE || CAIRO_HAS_PDF_SURFACE || CAIRO_HAS_SVG_SURFACE
#  define HAS_CREATE_CR_CLOSURE_SURFACE 1
#else
#  define HAS_CREATE_CR_CLOSURE_SURFACE 0
#endif


VALUE rb_cCairo_Surface;
VALUE rb_cCairo_ImageSurface;
VALUE rb_cCairo_PDFSurface;
VALUE rb_cCairo_PSSurface;
VALUE rb_cCairo_SVGSurface;

static ID cr_id_read;
static ID cr_id_write;
static ID cr_id_holder;
static ID cr_id_closed;
static ID cr_id_closure;
static cairo_user_data_key_t cr_klass_key;
static cairo_user_data_key_t cr_closure_key;

#define _SELF  (RVAL2CRSURFACE(self))

#define CR_TRUE 1
#define CR_FALSE 0

static inline void
cr_surface_check_status (cairo_surface_t *surface)
{
  rb_cairo_check_status (cairo_surface_status (surface));
}

static void
cr_surface_set_klass (cairo_surface_t *surface, VALUE klass)
{
  cairo_status_t status;
  status = cairo_surface_set_user_data (surface, &cr_klass_key,
                                        (void *)klass, NULL);
  rb_cairo_check_status (status);
}

static VALUE
cr_surface_get_klass (cairo_surface_t *surface)
{
  VALUE klass;
  void *data = cairo_surface_get_user_data (surface, &cr_klass_key);

  if (data)
    klass = (VALUE) data;
  else
    {
      switch (cairo_surface_get_type (surface))
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
        default:
          klass = rb_cCairo_Surface;
          break;
        }
    }

  return klass;
}

/* read/write callback */
typedef struct cr_io_callback_closure {
  VALUE target;
  VALUE error;
  VALUE klass;
  unsigned char *data;
  unsigned int length;
  cairo_bool_t is_file;
} cr_io_callback_closure_t;

#if HAS_CREATE_CR_CLOSURE_SURFACE
static VALUE
cr_closure_target_push (VALUE klass, VALUE obj)
{
  VALUE holder, key, objs;
  
  holder = rb_ivar_get (klass, cr_id_holder);
  key = rb_obj_id (obj);
  objs = rb_hash_aref (holder, key);

  if (NIL_P (objs))
    {
      objs = rb_ary_new ();
      rb_hash_aset (holder, key, objs);
    }

  rb_ary_push(objs, obj);

  return Qnil;
}

static VALUE
cr_closure_target_pop(VALUE klass, VALUE obj)
{
  VALUE holder, key, objs;
  VALUE result = Qnil;

  holder = rb_ivar_get (klass, cr_id_holder);
  key = rb_obj_id (obj);
  objs = rb_hash_aref (holder, key);

  if (!NIL_P (objs))
    {
      result = rb_ary_pop (objs);
      if (RARRAY (objs)->len == 0)
        {
          rb_hash_delete (holder, key);
        }
    }

  return result;
}

static cr_io_callback_closure_t *
cr_closure_new (VALUE target, cairo_bool_t is_file)
{
  cr_io_callback_closure_t *closure;
  closure = ALLOC (cr_io_callback_closure_t);

  closure->target = target;
  closure->error = Qnil;
  closure->is_file = is_file;
  
  return closure;
}

static void
cr_closure_destroy (cr_io_callback_closure_t *closure)
{
  if (closure->is_file)
    cr_closure_target_pop (closure->klass, closure->target);

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
  closure->error = ruby_errinfo;
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

  for (rest = length; rest != 0; rest = length - RSTRING (result)->len)
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
cr_surface_create_similar (VALUE self, VALUE content,
                           VALUE width, VALUE height)
{
  cairo_surface_t *surface;

  surface = cairo_surface_create_similar (RVAL2CRSURFACE (self),
                                          RVAL2CRCONTENT (content),
                                          NUM2INT (width), NUM2INT (height));
  cr_surface_check_status (surface);
  cr_surface_set_klass (surface, rb_obj_class (self));
  return CRSURFACE2RVAL (surface);
}

static VALUE
cr_surface_finish (VALUE self)
{
  cr_io_callback_closure_t *closure;
  closure = cairo_surface_get_user_data (_SELF, &cr_closure_key);
  
  cairo_surface_finish (_SELF);

  if (closure && closure->is_file)
    {
      VALUE file;
      file = closure->target;
      if (!RTEST (rb_funcall (file, cr_id_closed, 0)))
        rb_io_close (file);
    }
  
  if (closure && !NIL_P (closure->error))
    rb_exc_raise (closure->error);
  
  cr_surface_check_status (_SELF);
  return self;
}

static VALUE
cr_surface_get_type (VALUE self)
{
  return INT2NUM (cairo_surface_get_type (_SELF));
}

static VALUE
cr_surface_get_content (VALUE self)
{
  return INT2NUM (cairo_surface_get_content (_SELF));
}


#if CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_image_surface_write_to_png_stream (VALUE self, VALUE target)
{
  cairo_status_t status;
  cr_io_callback_closure_t closure;

  closure.target = target;
  closure.error = Qnil;
  closure.is_file = CR_FALSE;

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


/* Image-surface functions */
#if CAIRO_HAS_PNG_FUNCTIONS
static VALUE
cr_image_surface_create_from_png_stream (VALUE target)
{
  cr_io_callback_closure_t closure;
  cairo_surface_t *surface;

  closure.target = target;
  closure.error = Qnil;
  closure.is_file = CR_FALSE;
  
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
cr_image_surface_create_from_png_generic (VALUE klass, VALUE target)
{
  VALUE rb_surface;
  cairo_surface_t *surface;
  if (rb_respond_to (target, cr_id_read))
    surface = (cairo_surface_t *)cr_image_surface_create_from_png_stream (target);
  else
    surface = (cairo_surface_t *)cr_image_surface_create_from_png (target);

  cr_surface_check_status (surface);
  cr_surface_set_klass (surface, klass);
  rb_surface = cr_surface_allocate (klass);
  DATA_PTR (rb_surface) = surface;
  return rb_surface;
}
#endif


static cairo_surface_t *
cr_image_surface_create (VALUE self, VALUE format, VALUE width, VALUE height)
{
  return cairo_image_surface_create (RVAL2CRFORMAT (format),
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
#define DEFINE_SURFACE(type)                                              \
static VALUE                                                              \
cr_ ## type ## _surface_initialize (VALUE self, VALUE target,             \
                                    VALUE rb_width_in_points,             \
                                    VALUE rb_height_in_points)            \
{                                                                         \
  cr_io_callback_closure_t *closure;                                      \
  cairo_surface_t *surface;                                               \
  double width_in_points, height_in_points;                               \
                                                                          \
  if (rb_respond_to (target, cr_id_write))                                \
    {                                                                     \
      closure = cr_closure_new (target, CR_FALSE);                        \
    }                                                                     \
  else                                                                    \
    {                                                                     \
      VALUE file;                                                         \
      file = rb_file_open (StringValuePtr (target), "wb");                \
      closure = cr_closure_new (file, CR_TRUE);                           \
      closure->klass = rb_obj_class (self);                               \
      cr_closure_target_push (closure->klass, closure->target);           \
    }                                                                     \
                                                                          \
  width_in_points = NUM2DBL (rb_width_in_points);                         \
  height_in_points = NUM2DBL (rb_height_in_points);                       \
  surface =                                                               \
    cairo_ ## type ## _surface_create_for_stream (cr_surface_write_func,  \
                                                  (void *) closure,       \
                                                  width_in_points,        \
                                                  height_in_points);      \
                                                                          \
  if (cairo_surface_status (surface))                                     \
    cr_closure_destroy (closure);                                         \
  else                                                                    \
    cairo_surface_set_user_data (surface, &cr_closure_key,                \
                                 closure, cr_closure_free);               \
                                                                          \
  cr_surface_check_status (surface);                                      \
  DATA_PTR (self) = surface;                                              \
  return Qnil;                                                            \
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

static VALUE
cr_svg_get_versions (VALUE self)
{
  VALUE rb_versions;
  int i, num_versions;
  cairo_svg_version_t const *versions;

  cairo_svg_get_versions (&versions, &num_versions);

  rb_versions = rb_ary_new2 (num_versions);

  for (i = 0; i < num_versions; i++)
    {
      rb_ary_push (rb_versions, INT2NUM (versions[i]));
    }

  return rb_versions;
}

static VALUE
cr_svg_version_to_string (VALUE self, VALUE version)
{
  const char *ver_str;
  ver_str = cairo_svg_version_to_string (RVAL2CRSVGVERSION(version));
  return rb_str_new2 (ver_str);
}
#endif


void
Init_cairo_surface (void)
{
  cr_id_read = rb_intern ("read");
  cr_id_write = rb_intern ("write");
  cr_id_closed = rb_intern ("closed?");
  cr_id_closure = rb_intern ("closure");
  cr_id_holder = rb_intern ("holder");
  
  rb_cCairo_Surface =
    rb_define_class_under (rb_mCairo, "Surface", rb_cObject);
  rb_define_alloc_func (rb_cCairo_Surface, cr_surface_allocate);
  
  rb_define_method (rb_cCairo_Surface, "create_similar",
                    cr_surface_create_similar, 3);
  rb_define_method (rb_cCairo_Surface, "finish", cr_surface_finish, 0);
  rb_define_method (rb_cCairo_Surface, "type", cr_surface_get_type, 0);
  rb_define_method (rb_cCairo_Surface, "content", cr_surface_get_content, 0);

  rb_define_method (rb_cCairo_Surface, "font_options",
                    cr_surface_get_font_options, 0);
  rb_define_method (rb_cCairo_Surface, "flush", cr_surface_flush, 0);
  rb_define_method (rb_cCairo_Surface, "mark_dirty", cr_surface_mark_dirty, 0);
  rb_define_method (rb_cCairo_Surface, "set_device_offset",
                    cr_surface_set_device_offset, 2);
  rb_define_method (rb_cCairo_Surface, "device_offset",
                    cr_surface_get_device_offset, 0);
  rb_define_method (rb_cCairo_Surface, "set_fallback_resolution",
                    cr_surface_set_fallback_resolution, 2);

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

#if CAIRO_HAS_PNG_FUNCTIONS
  rb_define_method (rb_cCairo_ImageSurface, "write_to_png",
                    cr_image_surface_write_to_png_generic, 1);
#endif


#define INIT_SURFACE(type, name)                                        \
  rb_cCairo_ ## name ## Surface =                                       \
    rb_define_class_under (rb_mCairo, # name "Surface",                 \
                           rb_cCairo_Surface);                          \
                                                                        \
  rb_ivar_set (rb_cCairo_ ## name ## Surface,                           \
               cr_id_holder, rb_hash_new ());                           \
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

  RB_CAIRO_DEF_SETTERS (rb_cCairo_PSSurface);
#else
  rb_cCairo_PSSurface = Qnil;
#endif

#if CAIRO_HAS_PDF_SURFACE
  /* PDF-surface */
  INIT_SURFACE(pdf, PDF)

  rb_define_method (rb_cCairo_PDFSurface, "set_size",
                    cr_pdf_surface_set_size, 2);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_PDFSurface);
#else
  rb_cCairo_PDFSurface = Qnil;
#endif

#if CAIRO_HAS_SVG_SURFACE
  /* SVG-surface */
  INIT_SURFACE(svg, SVG)

  rb_define_const (rb_cCairo_SVGSurface, "VERSION_1_1",
                   rb_const_get (rb_mCairo, rb_intern ("SVG_VERSION_1_1")));
  rb_define_const (rb_cCairo_SVGSurface, "VERSION_1_2",
                   rb_const_get (rb_mCairo, rb_intern ("SVG_VERSION_1_2")));

  rb_define_singleton_method (rb_cCairo_SVGSurface, "versions",
                              cr_svg_get_versions, 0);
  rb_define_singleton_method (rb_cCairo_SVGSurface, "version_to_string",
                              cr_svg_version_to_string, 1);

  rb_define_method (rb_cCairo_SVGSurface, "restrict_to_version",
                    cr_svg_surface_restrict_to_version, 1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_SVGSurface);
#else
  rb_cCairo_SVGSurface = Qnil;
#endif
}
