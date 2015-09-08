/* -*- mode: objc; c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2008-2015 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2014 Patrick Hanevold <patrick.hanevold@gmail.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"

#if CAIRO_CHECK_VERSION(1, 5, 12)
#  define RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE_TYPE
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
#  define RB_CAIRO_HAS_QUARTZ_SURFACE
#  ifdef CAIRO_HAS_QUARTZ_IMAGE_SURFACE
#    include <cairo-quartz-image.h>
#    define RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE
#  endif
#endif

#define _SELF  (RVAL2CRSURFACE(self))

#ifdef RB_CAIRO_HAS_QUARTZ_SURFACE
/* Quartz-surface functions */
#include <objc/objc-runtime.h>

#  ifdef HAVE_RUBY_COCOA
BOOL rbobj_to_nsobj (VALUE obj, id* nsobj);
VALUE ocid_to_rbobj (VALUE context_obj, id ocid);
#  endif

static VALUE
cr_quartz_surface_initialize (int argc, VALUE *argv, VALUE self)
{
  id objc_object = nil;
  CGContextRef context;
  unsigned int width, height;
  cairo_surface_t *surface = NULL;
  cairo_format_t format = CAIRO_FORMAT_ARGB32;
  VALUE arg1, arg2, arg3, rb_width, rb_height;
#  ifdef HAVE_RUBY_COCOA
  static VALUE rb_cOSXCGContextRef = Qnil;
#  endif

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
#  ifdef HAVE_RUBY_COCOA
          if (NIL_P (rb_cOSXCGContextRef))
            rb_cOSXCGContextRef =
              rb_const_get (rb_const_get (rb_cObject, rb_intern ("OSX")),
                            rb_intern ("CGContextRef"));
#  endif

#  ifdef HAVE_RUBY_COCOA
          if (RTEST (rb_obj_is_kind_of (arg1, rb_cOSXCGContextRef)))
            {
              rbobj_to_nsobj (arg1, &objc_object);
            }
          else
#  endif
            {
              if (!NIL_P (rb_cairo__cFFIPointer) &&
                  RTEST (rb_obj_is_kind_of (arg1, rb_cairo__cFFIPointer)))
                {
                  VALUE rb_objc_pointer;
                  rb_objc_pointer = rb_funcall (arg1,
                                                rb_intern ("address"),
                                                0);
                  objc_object = (id) NUM2ULONG (rb_objc_pointer);
                }
              else
                {
                  rb_raise (rb_eArgError,
                            "invalid argument (expect "
                            "(width, height), "
                            "(format, width, height), "
                            "(cg_context, width, height) or "
                            "(ffi_pointer, width, height)): %s",
                            rb_cairo__inspect (rb_ary_new3 (3, arg1, arg2, arg3)));
                }
            }
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

  rb_cairo_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    rb_cairo__surface_yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_quartz_surface_get_cg_context (VALUE self)
{
#  ifdef HAVE_RUBY_COCOA
  CGContextRef context;
  id objc_object;

  context = cairo_quartz_surface_get_cg_context (_SELF);
  objc_object = (id)context;
  return ocid_to_rbobj (Qnil, objc_object);
#  else
  rb_raise (rb_eNotImpError,
            "%s#cg_context requires RubyCocoa",
            rb_obj_classname(self));
  return Qnil;
#  endif
}
#endif

#ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE

/* Quartz image surface functions */
static VALUE
cr_quartz_image_surface_initialize (VALUE self, VALUE image_surface)
{
  cairo_surface_t *surface;

  surface = cairo_quartz_image_surface_create (RVAL2CRSURFACE (image_surface));
  rb_cairo_surface_check_status (surface);
  DATA_PTR (self) = surface;
  if (rb_block_given_p ())
    rb_cairo__surface_yield_and_finish (self);
  return Qnil;
}

static VALUE
cr_quartz_image_surface_get_image (VALUE self)
{
  cairo_surface_t *surface;

  surface = cairo_quartz_image_surface_get_image (_SELF);
  if (!surface)
    return Qnil;
  rb_cairo_surface_check_status (surface);
  return CRSURFACE2RVAL (surface);
}
#endif

void
Init_cairo_quartz_surface (void)
{
  /* Quartz surface */
#ifdef RB_CAIRO_HAS_QUARTZ_SURFACE
  rb_define_method (rb_cCairo_QuartzSurface, "initialize",
                    cr_quartz_surface_initialize, -1);
  rb_define_method (rb_cCairo_QuartzSurface, "cg_context",
                    cr_quartz_surface_get_cg_context, 0);
#endif

  /* Quartz image surface */
#ifdef RB_CAIRO_HAS_QUARTZ_IMAGE_SURFACE
  rb_define_method (rb_cCairo_QuartzImageSurface, "initialize",
                    cr_quartz_image_surface_initialize, 1);
  rb_define_method (rb_cCairo_QuartzImageSurface, "image",
                    cr_quartz_image_surface_get_image, 0);
#endif
}
