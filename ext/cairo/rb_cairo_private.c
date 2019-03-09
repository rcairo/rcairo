/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-17 07:21:42 $
 *
 * Copyright 2005-2019 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cairo__cFFIPointer;

static ID cr_id_normalize_const_name;
static ID cr_id_objects;
static ID cr_id_dup;
static ID cr_id_inspect;
static ID cr_id_exit_application;

VALUE
rb_cairo__float_array (double *values, unsigned count)
{
  VALUE result;
  unsigned i;

  result = rb_ary_new2 (count);
  for (i = 0; i < count; i++)
    {
      rb_ary_push (result, rb_float_new (values[i]));
    }
  return result;
}

void
rb_cairo__glyphs_to_array (VALUE rb_array, cairo_glyph_t *glyphs, int length)
{
  int i;

  for (i = 0; i < length; i++)
    {
      memcpy ((char *) &glyphs[i],
              (char *) RVAL2CRGLYPH (rb_ary_entry (rb_array, i)),
              sizeof (cairo_glyph_t));
    }
}

VALUE
rb_cairo__const_get (VALUE name, const char *prefix)
{
  VALUE rb_normalized_name;
  char *const_name, *normalized_name;
  size_t prefix_len, normalized_name_len;

  rb_normalized_name = rb_funcall (rb_mCairo,
                                   cr_id_normalize_const_name, 1, name);
  normalized_name = RVAL2CSTR (rb_normalized_name);

  prefix_len = strlen (prefix);
  normalized_name_len = strlen (normalized_name);

  const_name = ALLOCA_N (char, prefix_len + normalized_name_len + 1);
  strcpy (const_name, prefix);
  strcpy (const_name + prefix_len, normalized_name);

  return rb_const_get (rb_mCairo, rb_intern (const_name));
}

cairo_bool_t
rb_cairo__is_kind_of (VALUE object, VALUE klass)
{
  return RVAL2CBOOL (rb_obj_is_kind_of (object, klass));
}

rb_cairo__object_holder_t *
rb_cairo__object_holder_new (VALUE klass, VALUE object)
{
  rb_cairo__object_holder_t *holder;

  holder = ALLOC(rb_cairo__object_holder_t);
  rb_cairo__gc_guard_add (klass, object);
  holder->object = object;
  return holder;
}

void
rb_cairo__object_holder_free (VALUE klass, void *ptr)
{
  rb_cairo__object_holder_t *holder = ptr;

  if (!NIL_P (holder->object))
    rb_cairo__gc_guard_remove (klass, holder->object);

  xfree (holder);
}

void
rb_cairo__initialize_gc_guard_holder_class (VALUE klass)
{
  rb_ivar_set (klass, cr_id_objects, rb_hash_new ());
}

void
rb_cairo__gc_guard_add (VALUE klass, VALUE object)
{
  rb_hash_aset (rb_ivar_get (klass, cr_id_objects), object, Qnil);
}

void
rb_cairo__gc_guard_remove (VALUE klass, VALUE object)
{
  rb_hash_delete (rb_ivar_get (klass, cr_id_objects), object);
}

VALUE
rb_cairo__gc_guarded_objects (VALUE klass)
{
  return rb_funcall (rb_ivar_get (klass, cr_id_objects), cr_id_dup, 0);
}

const char *
rb_cairo__inspect (VALUE object)
{
  VALUE inspected;

  inspected = rb_funcall (object, cr_id_inspect, 0);
  return RSTRING_PTR (inspected);
}

#if CAIRO_CHECK_VERSION(1, 7, 2)
VALUE
rb_cairo__glyphs_to_ruby_object (cairo_glyph_t *glyphs, int num_glyphs)
{
  int i;
  VALUE rb_glyphs;

  rb_glyphs = rb_ary_new2 (num_glyphs);
  for (i = 0; i < num_glyphs; i++)
    {
      RARRAY_PTR (rb_glyphs)[i] = CRGLYPH2RVAL (glyphs + i);
    }

  return rb_glyphs;
}

void
rb_cairo__glyphs_from_ruby_object (VALUE rb_glyphs,
                                   cairo_glyph_t **glyphs, int *num_glyphs)
{
  int i, len;

  if (NIL_P (rb_glyphs))
    {
      *num_glyphs = -1;
      return;
    }

  len = (int) RARRAY_LEN (rb_glyphs);
  if (*num_glyphs < len)
    *glyphs = cairo_glyph_allocate (len);
  *num_glyphs = len;
  for (i = 0; i < len; i++)
    {
      cairo_glyph_t *glyph;

      glyph = *glyphs + i;
      *glyph = *(RVAL2CRGLYPH (RARRAY_PTR (rb_glyphs)[i]));
    }
}

VALUE
rb_cairo__text_clusters_to_ruby_object (cairo_text_cluster_t *clusters,
                                        int num_clusters)
{
  int i;
  VALUE rb_clusters;

  rb_clusters = rb_ary_new2 (num_clusters);
  for (i = 0; i < num_clusters; i++)
    {
      RARRAY_PTR (rb_clusters)[i] = CRTEXTCLUSTER2RVAL (clusters + i);
    }

  return rb_clusters;
}

void
rb_cairo__text_clusters_from_ruby_object (VALUE rb_clusters,
                                          cairo_text_cluster_t **clusters,
                                          int *num_clusters)
{
  int i, len;

  if (NIL_P (rb_clusters))
    {
      *num_clusters = -1;
      return;
    }

  len = (int) RARRAY_LEN (rb_clusters);
  if (*num_clusters < len)
    *clusters = cairo_text_cluster_allocate (len);
  *num_clusters = len;
  for (i = 0; i < len; i++)
    {
      cairo_text_cluster_t *cluster;

      cluster = *clusters + i;
      *cluster = *(RVAL2CRTEXTCLUSTER (RARRAY_PTR (rb_clusters)[i]));
    }
}
#endif

VALUE
rb_cairo__invoke_callback (cr_callback_func_t func, VALUE data)
{
  int state = 0;
  VALUE result, exception;

  result = rb_protect (func, data, &state);
  if (state)
    {
      exception = RB_ERRINFO;
      if (exception)
        rb_funcall (rb_mCairo, cr_id_exit_application, 2,
                    exception, INT2NUM (EXIT_FAILURE));
    }
  return result;
}

void
Init_cairo_private (void)
{
  cr_id_normalize_const_name = rb_intern ("normalize_const_name");
  cr_id_objects = rb_intern ("objects");
  cr_id_dup = rb_intern ("dup");
  cr_id_inspect = rb_intern ("inspect");
  cr_id_exit_application = rb_intern ("exit_application");

  if (rb_const_defined (rb_cObject, rb_intern ("FFI")))
    {
      rb_cairo__cFFIPointer =
        rb_const_get (rb_const_get (rb_cObject, rb_intern ("FFI")),
                      rb_intern ("Pointer"));
    }
  else
    {
      rb_cairo__cFFIPointer = Qnil;
    }
}
