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

#ifndef RB_CAIRO_PRIVATE_H
#define RB_CAIRO_PRIVATE_H

#define CR_TRUE 1
#define CR_FALSE 0

#define CAIRO_INT_STATUS_UNSUPPORTED 100

#define CSTR2RVAL(str) rb_str_new2(str)
#define RVAL2CSTR(str) StringValueCStr(str)

#define CBOOL2RVAL(bool) (bool ? Qtrue : Qfalse)
#define RVAL2CBOOL(bool) RTEST(bool)

#ifndef RSTRING_LEN
#  define RSTRING_LEN(string) (RSTRING(string)->len)
#endif

#ifndef RARRAY_PTR
#  define RARRAY_PTR(array) (RARRAY(array)->ptr)
#endif

#ifndef RARRAY_LEN
#  define RARRAY_LEN(array) (RARRAY(array)->len)
#endif

#ifdef HAVE_RB_ERRINFO
#  define RB_ERRINFO (rb_errinfo())
#else
#  define RB_ERRINFO (ruby_errinfo)
#endif

/* from dl/dl.h (ruby 1.9) */
#if SIZEOF_LONG == SIZEOF_VOIDP
#  define PTR2NUM(x)   (ULONG2NUM((unsigned long)(x)))
#  define NUM2PTR(x)   ((void *)(NUM2ULONG(x)))
#else
#  define PTR2NUM(x)   (ULL2NUM((unsigned long long)(x)))
#  define NUM2PTR(x)   ((void *)(NUM2ULL(x)))
#endif

extern void Init_cairo_private (void);
extern void Init_cairo_io (void);
extern void Init_cairo_constants (void);

extern void Init_cairo_context (void);
extern void Init_cairo_rectangle (void);
extern void Init_cairo_path (void);
extern void Init_cairo_matrix (void);
extern void Init_cairo_region (void);
extern void Init_cairo_device (void);
extern void Init_cairo_surface (void);
extern void Init_cairo_quartz_surface (void);
extern void Init_cairo_exception (void);
extern void Init_cairo_font (void);
extern void Init_cairo_font_extents (void);
extern void Init_cairo_font_options (void);
extern void Init_cairo_scaled_font (void);
extern void Init_cairo_text_extents (void);
extern void Init_cairo_pattern (void);
extern void Init_cairo_glyph (void);
extern void Init_cairo_text_cluster (void);

#define RB_CAIRO__GLYPHS_TO_ARRAY(rb_array, glyphs, length)     \
do                                                              \
  {                                                             \
    Check_Type (rb_array, T_ARRAY);                             \
    length = (int) RARRAY_LEN (rb_array);                       \
    glyphs = ALLOCA_N (cairo_glyph_t, length);                  \
                                                                \
    if (!glyphs)                                                \
      rb_cairo_check_status (CAIRO_STATUS_NO_MEMORY);           \
                                                                \
    rb_cairo__glyphs_to_array (rb_array, glyphs, length);       \
  } while (0)

VALUE rb_cairo__float_array (double *values, unsigned count);
void rb_cairo__glyphs_to_array (VALUE rb_array, cairo_glyph_t *glyphs, int length);

VALUE rb_cairo__const_get (VALUE name, const char *prefix);
cairo_bool_t rb_cairo__is_kind_of (VALUE object, VALUE klass);

typedef struct rb_cairo__object_holder {
  VALUE object;
} rb_cairo__object_holder_t;

rb_cairo__object_holder_t *rb_cairo__object_holder_new (VALUE klass, VALUE object);
void rb_cairo__object_holder_free (VALUE klass, void *ptr);


void rb_cairo__initialize_gc_guard_holder_class (VALUE klass);
void rb_cairo__gc_guard_add (VALUE klass, VALUE object);
void rb_cairo__gc_guard_remove (VALUE klass, VALUE object);
VALUE rb_cairo__gc_guarded_objects (VALUE klass);

const char *rb_cairo__inspect (VALUE object);

#if CAIRO_CHECK_VERSION(1, 7, 2)
VALUE rb_cairo__glyphs_to_ruby_object (cairo_glyph_t *glyphs, int num_glyphs);
void rb_cairo__glyphs_from_ruby_object (VALUE rb_glyphs,
                                        cairo_glyph_t **glyphs, int *num_glyphs);
VALUE rb_cairo__text_clusters_to_ruby_object (cairo_text_cluster_t *clusters,
                                              int num_clusters);
void rb_cairo__text_clusters_from_ruby_object (VALUE rb_clusters,
                                               cairo_text_cluster_t **clusters,
                                               int *num_clusters);
#endif

cairo_status_t rb_cairo__exception_to_status (VALUE exception);

typedef VALUE (*cr_callback_func_t) (VALUE user_data);
VALUE rb_cairo__invoke_callback (cr_callback_func_t func, VALUE user_data);

extern VALUE rb_cairo__cFFIPointer;

VALUE rb_cairo__surface_yield_and_finish (VALUE self);

#endif
