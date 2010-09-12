/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2010 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_Region = Qnil;

#if CAIRO_CHECK_VERSION(1, 10, 0)

#define _SELF  (RVAL2CRREGION(self))

static inline void
cr_region_check_status (cairo_region_t *region)
{
  rb_cairo_check_status (cairo_region_status (region));
}

cairo_region_t *
rb_cairo_region_from_ruby_object (VALUE obj)
{
  cairo_region_t *region;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Region))
    {
      rb_raise (rb_eTypeError, "not a cairo region");
    }
  Data_Get_Struct (obj, cairo_region_t, region);
  return region;
}

static void
cr_region_free (void *ptr)
{
  if (ptr)
    {
      cairo_region_destroy ((cairo_region_t *) ptr);
    }
}

VALUE
rb_cairo_region_to_ruby_object (cairo_region_t *region)
{
  if (region)
    {
      cairo_region_reference (region);
      return Data_Wrap_Struct (rb_cCairo_Region, NULL, cr_region_free, region);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_region_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_region_free, NULL);
}

static VALUE
cr_region_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_region_t *region;

  if (argc == 0)
    {
      region = cairo_region_create ();
    }
  else
    {
      int i;
      cairo_rectangle_int_t *rectangles;

      rectangles = ALLOCA_N (cairo_rectangle_int_t, argc);
      for (i = 0; i < argc; i++)
        {
          VALUE rb_rectangle;

          rb_rectangle = rb_check_array_type (argv[i]);
          if (RARRAY_LEN (rb_rectangle) != 4)
            rb_raise (rb_eArgError,
                      "invalid argument (expect "
                      "() or ([x, y, width, height], ...): %s",
                      rb_cairo__inspect (rb_ary_new4 (argc, argv)));
          rectangles[i].x = NUM2INT (RARRAY_PTR (rb_rectangle)[0]);
          rectangles[i].y = NUM2INT (RARRAY_PTR (rb_rectangle)[1]);
          rectangles[i].width = NUM2INT (RARRAY_PTR (rb_rectangle)[2]);
          rectangles[i].height = NUM2INT (RARRAY_PTR (rb_rectangle)[3]);
        }
      region = cairo_region_create_rectangles (rectangles, argc);
    }
  cr_region_check_status (region);
  DATA_PTR (self) = region;
  return Qnil;
}

static VALUE
cr_region_dup (VALUE self)
{
  cairo_region_t *copied_region;
  VALUE rb_copied_region;

  copied_region = cairo_region_copy (_SELF);
  cr_region_check_status (copied_region);
  rb_copied_region = CRREGION2RVAL (copied_region);
  cairo_region_destroy (copied_region);
  return rb_copied_region;
}

static VALUE
cr_region_equal (VALUE self, VALUE other)
{
  cairo_region_t *region, *other_region;

  if (!rb_cairo__is_kind_of (other, rb_cCairo_Region))
    return Qfalse;

  region = _SELF;
  other_region = RVAL2CRREGION (other);
  return CBOOL2RVAL (cairo_region_equal (region, other_region));
}

static VALUE
cr_region_get_extents (VALUE self)
{
  cairo_region_t *region;
  cairo_rectangle_int_t extents;

  region = _SELF;
  cairo_region_get_extents (region, &extents);
  cr_region_check_status (region);
  return rb_ary_new3 (4,
                      INT2NUM (extents.x), INT2NUM (extents.y),
                      INT2NUM (extents.width), INT2NUM (extents.height));
}

static VALUE
cr_region_num_rectangles (VALUE self)
{
  cairo_region_t *region;
  int num_rectangles;

  region = _SELF;
  num_rectangles = cairo_region_num_rectangles (region);
  cr_region_check_status (region);
  return INT2NUM (num_rectangles);
}

static VALUE
cr_region_get_rectangle (VALUE self, VALUE index)
{
  cairo_region_t *region;
  cairo_rectangle_int_t extents;

  region = _SELF;
  cairo_region_get_rectangle (region, NUM2INT (index), &extents);
  cr_region_check_status (region);
  return rb_ary_new3 (4,
                      INT2NUM (extents.x), INT2NUM (extents.y),
                      INT2NUM (extents.width), INT2NUM (extents.height));
}

static VALUE
cr_region_is_empty (VALUE self)
{
  return CBOOL2RVAL (cairo_region_is_empty (_SELF));
}

static VALUE
cr_region_containts_rectangle (int argc, VALUE *argv, VALUE self)
{
  cairo_region_t *region;
  cairo_rectangle_int_t rectangle;
  cairo_region_overlap_t overlap;
  VALUE arg1, arg2, arg3, arg4;
  const char *error_message =
    "invalid argument (expect "
    "(x, y, width, height) or ([x, y, width, height])): %s";

  rb_scan_args (argc, argv, "13", &arg1, &arg2, &arg3, &arg4);

  region = _SELF;
  if (argc == 1)
    {
      VALUE rb_rectangle;

      rb_rectangle = rb_check_array_type (arg1);
      if (RARRAY_LEN (rb_rectangle) != 4)
        rb_raise (rb_eArgError, error_message,
                  rb_cairo__inspect (rb_ary_new4 (argc, argv)));
      rectangle.x = NUM2INT (RARRAY_PTR (rb_rectangle)[0]);
      rectangle.y = NUM2INT (RARRAY_PTR (rb_rectangle)[1]);
      rectangle.width = NUM2INT (RARRAY_PTR (rb_rectangle)[2]);
      rectangle.height = NUM2INT (RARRAY_PTR (rb_rectangle)[3]);
    }
  else if (argc == 4)
    {
      rectangle.x = NUM2INT (arg1);
      rectangle.y = NUM2INT (arg2);
      rectangle.width = NUM2INT (arg3);
      rectangle.height = NUM2INT (arg4);
    }
  else
    {
      rb_raise (rb_eArgError, error_message,
                rb_cairo__inspect (rb_ary_new4 (argc, argv)));
    }

  overlap = cairo_region_contains_rectangle (region, &rectangle);
  cr_region_check_status (region);
  return INT2NUM (overlap);
}

static VALUE
cr_region_containts_point (int argc, VALUE *argv, VALUE self)
{
  cairo_region_t *region;
  int x, y;
  VALUE arg1, arg2;
  const char *error_message =
    "invalid argument (expect "
    "(x, y) or ([x, y])): %s";

  rb_scan_args (argc, argv, "11", &arg1, &arg2);

  region = _SELF;
  if (argc == 1)
    {
      VALUE point;

      point = rb_check_array_type (arg1);
      if (RARRAY_LEN (point) != 4)
        rb_raise (rb_eArgError, error_message,
                  rb_cairo__inspect (rb_ary_new4 (argc, argv)));
      x = NUM2INT (RARRAY_PTR (point)[0]);
      y = NUM2INT (RARRAY_PTR (point)[1]);
    }
  else
    {
      x = NUM2INT (arg1);
      y = NUM2INT (arg2);
    }
  return CBOOL2RVAL (cairo_region_contains_point (region, x, y));
}

static VALUE
cr_region_translate (int argc, VALUE *argv, VALUE self)
{
  cairo_region_t *region;
  int x, y;
  VALUE arg1, arg2;
  const char *error_message =
    "invalid argument (expect "
    "(x, y) or ([x, y])): %s";

  rb_scan_args (argc, argv, "11", &arg1, &arg2);

  region = _SELF;
  if (argc == 1)
    {
      VALUE point;

      point = rb_check_array_type (arg1);
      if (RARRAY_LEN (point) != 4)
        rb_raise (rb_eArgError, error_message,
                  rb_cairo__inspect (rb_ary_new4 (argc, argv)));
      x = NUM2INT (RARRAY_PTR (point)[0]);
      y = NUM2INT (RARRAY_PTR (point)[1]);
    }
  else
    {
      x = NUM2INT (arg1);
      y = NUM2INT (arg2);
    }

  cairo_region_translate (region, x, y);
  cr_region_check_status (region);
  return Qnil;
}

#define DEFINE_OPERATOR(type)                                           \
static VALUE                                                            \
cr_region_ ## type (int argc, VALUE *argv, VALUE self)                  \
{                                                                       \
  cairo_status_t status;                                                \
  cairo_region_t *region, *other = NULL;                                \
  cairo_rectangle_int_t rectangle;                                      \
  VALUE arg1, arg2, arg3, arg4;                                         \
  const char *error_message =                                           \
    "invalid argument (expect "                                         \
    "(region), (x, y, width, height) or ([x, y, width, height])): %s";  \
                                                                        \
  rb_scan_args (argc, argv, "13", &arg1, &arg2, &arg3, &arg4);          \
                                                                        \
  region = _SELF;                                                       \
  if (argc == 1)                                                        \
    {                                                                   \
      if (rb_cairo__is_kind_of (arg1, rb_cCairo_Region))                \
        {                                                               \
          other = RVAL2CRREGION (arg1);                                 \
        }                                                               \
      else                                                              \
        {                                                               \
          VALUE rb_rectangle;                                           \
                                                                        \
          rb_rectangle = rb_check_array_type (arg1);                    \
          if (RARRAY_LEN (rb_rectangle) != 4)                           \
            rb_raise (rb_eArgError, error_message,                      \
                      rb_cairo__inspect (rb_ary_new4 (argc, argv)));    \
          rectangle.x = NUM2INT (RARRAY_PTR (rb_rectangle)[0]);         \
          rectangle.y = NUM2INT (RARRAY_PTR (rb_rectangle)[1]);         \
          rectangle.width = NUM2INT (RARRAY_PTR (rb_rectangle)[2]);     \
          rectangle.height = NUM2INT (RARRAY_PTR (rb_rectangle)[3]);    \
        }                                                               \
    }                                                                   \
  else if (argc == 4)                                                   \
    {                                                                   \
      rectangle.x = NUM2INT (arg1);                                     \
      rectangle.y = NUM2INT (arg2);                                     \
      rectangle.width = NUM2INT (arg3);                                 \
      rectangle.height = NUM2INT (arg4);                                \
    }                                                                   \
  else                                                                  \
    {                                                                   \
      rb_raise (rb_eArgError, error_message,                            \
                rb_cairo__inspect (rb_ary_new4 (argc, argv)));          \
    }                                                                   \
                                                                        \
  if (other)                                                            \
    status = cairo_region_ ## type (region, other);                     \
  else                                                                  \
    status = cairo_region_ ## type ## _rectangle (region, &rectangle);  \
  rb_cairo_check_status (status);                                       \
  cr_region_check_status (region);                                      \
  return Qnil;                                                          \
}

DEFINE_OPERATOR(subtract)
DEFINE_OPERATOR(intersect)
DEFINE_OPERATOR(union)
DEFINE_OPERATOR(xor)
#endif

void
Init_cairo_region (void)
{
#if CAIRO_CHECK_VERSION(1, 10, 0)
  rb_cCairo_Region =
    rb_define_class_under (rb_mCairo, "Region", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Region, cr_region_allocate);

  rb_define_method (rb_cCairo_Region, "initialize", cr_region_initialize, -1);

  rb_define_method (rb_cCairo_Region, "dup", cr_region_dup, 0);
  rb_define_method (rb_cCairo_Region, "==", cr_region_equal, 1);

  rb_define_method (rb_cCairo_Region, "extents", cr_region_get_extents, 0);
  rb_define_method (rb_cCairo_Region, "num_rectangles",
                    cr_region_num_rectangles, 0);
  rb_define_method (rb_cCairo_Region, "[]",
                    cr_region_get_rectangle, 1);
  rb_define_method (rb_cCairo_Region, "empty?", cr_region_is_empty, 0);
  rb_define_method (rb_cCairo_Region, "contains_rectangle",
                    cr_region_containts_rectangle, -1);
  rb_define_method (rb_cCairo_Region, "contains_point?",
                    cr_region_containts_point, -1);

  rb_define_method (rb_cCairo_Region, "translate!", cr_region_translate, -1);
  rb_define_method (rb_cCairo_Region, "subtract!", cr_region_subtract, -1);
  rb_define_method (rb_cCairo_Region, "intersect!", cr_region_intersect, -1);
  rb_define_method (rb_cCairo_Region, "union!", cr_region_union, -1);
  rb_define_method (rb_cCairo_Region, "xor!", cr_region_xor, -1);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_Region);
#endif
}
