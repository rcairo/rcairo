/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-09-26 14:13:58 $
 *
 * Copyright 2003-2019 Sutou Kouhei <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_FontFace;
VALUE rb_cCairo_FreeTypeFontFace = Qnil;
VALUE rb_cCairo_ToyFontFace = Qnil;
VALUE rb_cCairo_UserFontFace = Qnil;
VALUE rb_cCairo_UserFontFace_TextToGlyphsData = Qnil;

#ifdef CAIRO_HAS_FT_FONT
#  include <cairo-ft.h>

static cairo_user_data_key_t cr_freetype_face_key;
static FT_Library cr_freetype_library;
static int cr_freetype_n_faces = 0;
static cairo_bool_t cr_freetype_finishing = CR_FALSE;
#endif

#if CAIRO_CHECK_VERSION(1, 7, 6)
static cairo_user_data_key_t ruby_object_key;
static ID cr_id_call;
static ID cr_id_new;

static ID cr_id_init;
static ID cr_id_render_glyph;
static ID cr_id_text_to_glyphs;
static ID cr_id_unicode_to_glyph;

static ID cr_id_at_glyphs;
static ID cr_id_at_clusters;
static ID cr_id_at_cluster_flags;
static ID cr_id_at_need_glyphs;
static ID cr_id_at_need_clusters;
static ID cr_id_at_need_cluster_flags;
#endif

#define _SELF  (RVAL2CRFONTFACE(self))

static inline void
cr_font_face_check_status (cairo_font_face_t *face)
{
  rb_cairo_check_status (cairo_font_face_status (face));
}

cairo_font_face_t *
rb_cairo_font_face_from_ruby_object (VALUE obj)
{
  cairo_font_face_t *face;

  if (!rb_cairo__is_kind_of (obj, rb_cCairo_FontFace))
    {
      rb_raise (rb_eTypeError,
                "not a cairo font face: %s",
                rb_cairo__inspect (obj));
    }
  Data_Get_Struct (obj, cairo_font_face_t, face);
  if (!face)
    rb_cairo_check_status (CAIRO_STATUS_NULL_POINTER);
  cr_font_face_check_status (face);
  return face;
}

static void
cr_font_face_free (void *ptr)
{
  if (ptr)
    {
      cairo_font_face_t *face = ptr;
      cairo_font_face_destroy (face);
    }
}

VALUE
rb_cairo_font_face_to_ruby_object (cairo_font_face_t *face)
{
  if (face)
    {
      VALUE klass;

      switch (cairo_font_face_get_type (face))
        {
#ifdef CAIRO_HAS_FT_FONT
        case CAIRO_FONT_TYPE_FT:
          klass = rb_cCairo_FreeTypeFontFace;
          break;
#endif
#if CAIRO_CHECK_VERSION(1, 7, 6)
        case CAIRO_FONT_TYPE_TOY:
          klass = rb_cCairo_ToyFontFace;
          break;
        case CAIRO_FONT_TYPE_USER:
          klass = rb_cCairo_UserFontFace;
          break;
#endif
        default:
          klass = rb_cCairo_FontFace;
          break;
        }
      cairo_font_face_reference (face);
      return Data_Wrap_Struct (klass, NULL, cr_font_face_free, face);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_font_face_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_font_face_free, NULL);
}

static VALUE
cr_font_face_quartz_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_QUARTZ_FONT
  return Qtrue;
#else
  return Qfalse;
#endif
}

static VALUE
cr_font_face_freetype_supported_p (VALUE klass)
{
#ifdef CAIRO_HAS_FT_FONT
  return Qtrue;
#else
  return Qfalse;
#endif
}

#ifdef CAIRO_HAS_FT_FONT
static VALUE
cr_freetype_done_library (VALUE yielded_arg,
                          VALUE callback_arg,
                          int argc,
                          const VALUE *argv,
                          VALUE block_arg)
{
  cr_freetype_finishing = CR_TRUE;
  if (cr_freetype_n_faces == 0)
    FT_Done_FreeType (cr_freetype_library);
  return Qnil;
}

static void
cr_freetype_done_face (void *data)
{
  FT_Face face = data;

  FT_Done_Face (face);
  cr_freetype_n_faces--;
  if (cr_freetype_n_faces == 0 && cr_freetype_finishing)
    FT_Done_FreeType (cr_freetype_library);
}

static cairo_bool_t
cr_freetype_error_detail (FT_Error error,
                          const char **name,
                          const char **message)
{
#undef __FTERRORS_H__
#define FT_STRINGIFY(v) #v
#define FT_ERRORDEF(e, v, s)    {FT_STRINGIFY(e), v, s},
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       {NULL, 0, NULL}};
  size_t i = 0;
  static const struct {
    const char *name;
    FT_Error code;
    const char *message;
  } errors[] =
#include FT_ERRORS_H
  for (i = 0; i < (sizeof (errors) / sizeof (errors[0])); i++)
    {
      if (errors[i].code == error)
        {
          *name = errors[i].name;
          *message = errors[i].message;
          return CR_TRUE;
        }
    }

  return CR_FALSE;
}

static void
cr_freetype_error_check (FT_Error error,
                         const char *message,
                         VALUE related_object)
{
  const char *name = NULL;
  const char *system_message = NULL;
  const char *error_class_name;
  VALUE rb_eCairo_FreeTypeError;

  if (error == FT_Err_Ok)
    return;

  cr_freetype_error_detail (error, &name, &system_message);
#if CAIRO_CHECK_VERSION(1, 15, 4)
  error_class_name = "FreeTypeError";
#else
  error_class_name = "Error";
#endif
  rb_eCairo_FreeTypeError =
    rb_const_get (rb_mCairo, rb_intern (error_class_name));
  if (NIL_P (related_object))
    {
      rb_raise (rb_eCairo_FreeTypeError,
                "%s: %s[%d]: %s",
                message,
                name ? name : "unknown",
                error,
                system_message ? system_message : "unknown");
    }
  else
    {
      rb_raise (rb_eCairo_FreeTypeError,
                "%s: %s[%d]: %s: %+" PRIsVALUE,
                message,
                name ? name : "unknown",
                error,
                system_message ? system_message : "unknown",
                related_object);
    }
}

static VALUE
cr_freetype_font_face_initialize (VALUE self, VALUE path)
{
  FT_Face freetype_face;
  FT_Error error;
  cairo_font_face_t *face;
  cairo_status_t status;

  error = FT_New_Face (cr_freetype_library,
                       StringValueCStr(path),
                       0,
                       &freetype_face);
  cr_freetype_error_check (error, "failed to open FreeType font", path);
  cr_freetype_n_faces++;

  face = cairo_ft_font_face_create_for_ft_face (freetype_face, 0);
  cr_font_face_check_status (face);
  status =
    cairo_font_face_set_user_data (face,
                                   &cr_freetype_face_key,
                                   freetype_face,
                                   (cairo_destroy_func_t) cr_freetype_done_face);
  if (status != CAIRO_STATUS_SUCCESS) {
    cairo_font_face_destroy (face);
    FT_Done_Face (freetype_face);
    rb_cairo_check_status (status);
  }

  DATA_PTR (self) = face;

  return Qnil;
}
#endif

#if CAIRO_CHECK_VERSION(1, 7, 6)
static VALUE
cr_toy_font_face_initialize (int argc, VALUE *argv, VALUE self)
{
  cairo_font_face_t *face;
  VALUE rb_family, rb_slant, rb_weight;
  const char *family;
  cairo_font_slant_t slant;
  cairo_font_weight_t weight;

  rb_scan_args (argc, argv, "03", &rb_family, &rb_slant, &rb_weight);

  if (NIL_P (rb_family))
    {
      family = "";
    }
  else if (rb_cairo__is_kind_of (rb_family, rb_cString))
    {
      family = RSTRING_PTR (rb_family);
    }
  else if (rb_cairo__is_kind_of (rb_family, rb_cSymbol))
    {
      family = rb_id2name (SYM2ID (rb_family));
    }
  else
    {
      rb_raise (rb_eArgError,
                "family name should be nil, String or Symbol: %s",
                rb_cairo__inspect (rb_family));
    }

  if (NIL_P (rb_slant))
    slant = CAIRO_FONT_SLANT_NORMAL;
  else
    slant = RVAL2CRFONTSLANT (rb_slant);

  if (NIL_P (rb_weight))
    weight = CAIRO_FONT_WEIGHT_NORMAL;
  else
    weight = RVAL2CRFONTWEIGHT (rb_weight);

  face = cairo_toy_font_face_create (family, slant, weight);
  cr_font_face_check_status (face);
  DATA_PTR (self) = face;

  return Qnil;
}

static VALUE
cr_toy_font_face_get_family (VALUE self)
{
  return CSTR2RVAL (cairo_toy_font_face_get_family (_SELF));
}

static VALUE
cr_toy_font_face_get_slant (VALUE self)
{
  return INT2NUM (cairo_toy_font_face_get_slant (_SELF));
}

static VALUE
cr_toy_font_face_get_weight (VALUE self)
{
  return INT2NUM (cairo_toy_font_face_get_weight (_SELF));
}

typedef struct cr_user_font_face_invoke_data
{
  VALUE receiver;
  ID method;
  int argc;
  VALUE *argv;
  cairo_status_t *status;
  VALUE result;
  cr_callback_func_t after_hook;
  void *after_hook_data;
} cr_user_font_face_invoke_data_t;

static VALUE
cr_user_font_face_invoke_body (VALUE user_data)
{
  cr_user_font_face_invoke_data_t *data;
  VALUE result;

  data = (cr_user_font_face_invoke_data_t *)user_data;
  result = rb_funcall2 (data->receiver, data->method, data->argc, data->argv);
  data->result = result;
  if (data->after_hook)
    result = data->after_hook(user_data);
  return result;
}

static VALUE
cr_user_font_face_invoke_rescue (VALUE user_data, VALUE exception)
{
  cr_user_font_face_invoke_data_t *data;

  data = (cr_user_font_face_invoke_data_t *)user_data;
  *(data->status) = rb_cairo__exception_to_status (exception);

  if (*(data->status) == (cairo_status_t)-1)
    rb_exc_raise (exception);

  return Qnil;
}

static VALUE
cr_user_font_face_invoke_func (VALUE user_data)
{
  return rb_rescue2 (cr_user_font_face_invoke_body, user_data,
                     cr_user_font_face_invoke_rescue, user_data, rb_eException,
                     (VALUE)0);
}

static VALUE
cr_user_font_face_init_func_after (VALUE user_data)
{
  cr_user_font_face_invoke_data_t *data;
  cairo_font_extents_t *extents;

  data = (cr_user_font_face_invoke_data_t *)user_data;
  extents = data->after_hook_data;

  *extents = *(RVAL2CRFONTEXTENTS (data->argv[2]));

  return data->result;
}

static cairo_status_t
cr_user_font_face_init_func (cairo_scaled_font_t *scaled_font,
                             cairo_t *cr, cairo_font_extents_t *extents)
{
  cairo_status_t status = CAIRO_STATUS_SUCCESS;
  cairo_font_face_t *face;
  VALUE self;
  VALUE receiver = Qnil;
  ID id_method_name = cr_id_call;

  face = cairo_scaled_font_get_font_face (scaled_font);
  self = (VALUE)cairo_font_face_get_user_data (face, &ruby_object_key);
  receiver = rb_ivar_get (self, cr_id_init);
  if (NIL_P (receiver) && rb_obj_respond_to (self, cr_id_init, Qtrue))
    {
      receiver = self;
      id_method_name = cr_id_init;
    }

  if (!NIL_P (receiver))
    {
      cr_user_font_face_invoke_data_t data;
      VALUE argv[3];

      argv[0] = CRSCALEDFONT2RVAL (scaled_font);
      argv[1] = CRCONTEXT2RVAL (cr);
      argv[2] = CRFONTEXTENTS2RVAL (extents);

      data.receiver = receiver;
      data.method = id_method_name;
      data.argc = 3;
      data.argv = argv;
      data.status = &status;
      data.after_hook = cr_user_font_face_init_func_after;
      data.after_hook_data = extents;

      rb_cairo__invoke_callback (cr_user_font_face_invoke_func, (VALUE)&data);
    }

  return status;
}

static VALUE
cr_user_font_face_render_glyph_func_after (VALUE user_data)
{
  cr_user_font_face_invoke_data_t *data;
  cairo_text_extents_t *extents;

  data = (cr_user_font_face_invoke_data_t *)user_data;
  extents = data->after_hook_data;

  *extents = *(RVAL2CRTEXTEXTENTS (data->argv[3]));

  return data->result;
}

static cairo_status_t
cr_user_font_face_render_glyph_func (cairo_scaled_font_t *scaled_font,
                                     unsigned long glyph,
                                     cairo_t *cr,
                                     cairo_text_extents_t *extents)
{
  cairo_status_t status = CAIRO_STATUS_SUCCESS;
  cairo_font_face_t *face;
  VALUE self;
  VALUE receiver = Qnil;
  ID id_method_name = cr_id_call;

  face = cairo_scaled_font_get_font_face (scaled_font);
  self = (VALUE)cairo_font_face_get_user_data (face, &ruby_object_key);
  receiver = rb_ivar_get (self, cr_id_render_glyph);
  if (NIL_P (receiver) && rb_obj_respond_to (self, cr_id_render_glyph, Qtrue))
    {
      receiver = self;
      id_method_name = cr_id_render_glyph;
    }

  if (!NIL_P (receiver))
    {
      cr_user_font_face_invoke_data_t data;
      VALUE argv[4];

      argv[0] = CRSCALEDFONT2RVAL (scaled_font);
      argv[1] = ULONG2NUM (glyph);
      argv[2] = CRCONTEXT2RVAL (cr);
      argv[3] = CRTEXTEXTENTS2RVAL (extents);

      data.receiver = receiver;
      data.method = id_method_name;
      data.argc = 4;
      data.argv = argv;
      data.status = &status;
      data.after_hook = cr_user_font_face_render_glyph_func_after;
      data.after_hook_data = extents;

      rb_cairo__invoke_callback (cr_user_font_face_invoke_func, (VALUE)&data);
    }

  return status;
}

typedef struct _cr_text_to_glyphs_after_hook_data {
  VALUE text_to_glyphs_data;
  cairo_glyph_t **glyphs;
  int *num_glyphs;
  cairo_text_cluster_t **clusters;
  int *num_clusters;
  cairo_text_cluster_flags_t *cluster_flags;
} cr_text_to_glyphs_after_hook_data_t;

static VALUE
cr_user_font_face_text_to_glyphs_func_after (VALUE user_data)
{
  cr_user_font_face_invoke_data_t *data;
  cr_text_to_glyphs_after_hook_data_t *after_hook_data;
  VALUE text_to_glyphs_data;


  data = (cr_user_font_face_invoke_data_t *)user_data;
  after_hook_data = data->after_hook_data;
  text_to_glyphs_data = after_hook_data->text_to_glyphs_data;

  if (after_hook_data->glyphs)
    {
      VALUE rb_glyphs;

      rb_glyphs = rb_ivar_get (text_to_glyphs_data, cr_id_at_glyphs);
      rb_cairo__glyphs_from_ruby_object (rb_glyphs,
                                         after_hook_data->glyphs,
                                         after_hook_data->num_glyphs);
    }

  if (after_hook_data->clusters)
    {
      VALUE rb_clusters;

      rb_clusters = rb_ivar_get (text_to_glyphs_data, cr_id_at_clusters);
      rb_cairo__text_clusters_from_ruby_object (rb_clusters,
                                                after_hook_data->clusters,
                                                after_hook_data->num_clusters);
    }

  if (after_hook_data->cluster_flags)
    {
      VALUE rb_cluster_flags;

      rb_cluster_flags = rb_ivar_get (text_to_glyphs_data,
                                      cr_id_at_cluster_flags);
      *(after_hook_data->cluster_flags) =
        RVAL2CRTEXTCLUSTERFLAGS (rb_cluster_flags);
    }

  return data->result;
}

static cairo_status_t
cr_user_font_face_text_to_glyphs_func (cairo_scaled_font_t *scaled_font,
                                       const char *utf8, int utf8_len,
                                       cairo_glyph_t **glyphs, int *num_glyphs,
                                       cairo_text_cluster_t **clusters,
                                       int *num_clusters,
                                       cairo_text_cluster_flags_t *cluster_flags)
{
  cairo_status_t status = CAIRO_INT_STATUS_UNSUPPORTED;
  cairo_font_face_t *face;
  VALUE self;
  VALUE receiver = Qnil;
  ID id_method_name = cr_id_call;

  face = cairo_scaled_font_get_font_face (scaled_font);
  self = (VALUE)cairo_font_face_get_user_data (face, &ruby_object_key);
  receiver = rb_ivar_get (self, cr_id_text_to_glyphs);
  if (NIL_P (receiver) && rb_obj_respond_to (self, cr_id_text_to_glyphs, Qtrue))
    {
      receiver = self;
      id_method_name = cr_id_text_to_glyphs;
    }

  if (NIL_P (receiver))
    {
      if (num_glyphs)
        *num_glyphs = -1;
    }
  else
    {
      cr_user_font_face_invoke_data_t data;
      cr_text_to_glyphs_after_hook_data_t after_hook_data;
      VALUE text_to_glyphs_data;
      VALUE argv[3];

      argv[0] = CRSCALEDFONT2RVAL (scaled_font);
      argv[1] = rb_str_new (utf8, utf8_len);
      text_to_glyphs_data = rb_funcall (rb_cCairo_UserFontFace_TextToGlyphsData,
                                        cr_id_new,
                                        3,
                                        CBOOL2RVAL (glyphs != NULL),
                                        CBOOL2RVAL (clusters != NULL),
                                        CBOOL2RVAL (cluster_flags != NULL));
      argv[2] = text_to_glyphs_data;

      data.receiver = receiver;
      data.method = id_method_name;
      data.argc = 3;
      data.argv = argv;
      data.status = &status;
      data.after_hook = cr_user_font_face_text_to_glyphs_func_after;
      data.after_hook_data = &after_hook_data;

      after_hook_data.text_to_glyphs_data = text_to_glyphs_data;
      after_hook_data.glyphs = glyphs;
      after_hook_data.num_glyphs = num_glyphs;
      after_hook_data.clusters = clusters;
      after_hook_data.num_clusters = num_clusters;
      after_hook_data.cluster_flags = cluster_flags;

      rb_cairo__invoke_callback (cr_user_font_face_invoke_func, (VALUE)&data);
    }

  return status;
}

static VALUE
cr_user_font_face_unicode_to_glyph_func_after (VALUE user_data)
{
  cr_user_font_face_invoke_data_t *data;
  unsigned long *glyph_index;

  data = (cr_user_font_face_invoke_data_t *)user_data;
  glyph_index = data->after_hook_data;

  *glyph_index = NUM2ULONG (data->result);

  return data->result;
}

static cairo_status_t
cr_user_font_face_unicode_to_glyph_func (cairo_scaled_font_t *scaled_font,
                                         unsigned long unicode,
                                         unsigned long *glyph_index)
{
  cairo_status_t status = CAIRO_STATUS_SUCCESS;
  cairo_font_face_t *face;
  VALUE self;
  VALUE receiver = Qnil;
  ID id_method_name = cr_id_call;

  face = cairo_scaled_font_get_font_face (scaled_font);
  self = (VALUE)cairo_font_face_get_user_data (face, &ruby_object_key);
  receiver = rb_ivar_get (self, cr_id_unicode_to_glyph);
  if (NIL_P (receiver) &&
      rb_obj_respond_to (self, cr_id_unicode_to_glyph, Qtrue))
    {
      receiver = self;
      id_method_name = cr_id_unicode_to_glyph;
    }

  if (NIL_P (receiver))
    {
      *glyph_index = unicode;
    }
  else
    {
      cr_user_font_face_invoke_data_t data;
      VALUE argv[2];

      argv[0] = CRSCALEDFONT2RVAL (scaled_font);
      argv[1] = ULONG2NUM (unicode);

      data.receiver = receiver;
      data.method = id_method_name;
      data.argc = 2;
      data.argv = argv;
      data.status = &status;
      data.after_hook = cr_user_font_face_unicode_to_glyph_func_after;
      data.after_hook_data = glyph_index;

      rb_cairo__invoke_callback (cr_user_font_face_invoke_func, (VALUE)&data);
    }

  return status;
}


static VALUE
cr_user_font_face_initialize (VALUE self)
{
  cairo_font_face_t *face;

  face = cairo_user_font_face_create ();
  cr_font_face_check_status (face);

  cairo_font_face_set_user_data (face, &ruby_object_key, (void *)self, NULL);

  cairo_user_font_face_set_init_func
    (face, cr_user_font_face_init_func);
  cairo_user_font_face_set_render_glyph_func
    (face, cr_user_font_face_render_glyph_func);
  cairo_user_font_face_set_text_to_glyphs_func
    (face, cr_user_font_face_text_to_glyphs_func);
  cairo_user_font_face_set_unicode_to_glyph_func
    (face, cr_user_font_face_unicode_to_glyph_func);

  rb_ivar_set (self, cr_id_init, Qnil);
  rb_ivar_set (self, cr_id_render_glyph, Qnil);
  rb_ivar_set (self, cr_id_text_to_glyphs, Qnil);
  rb_ivar_set (self, cr_id_unicode_to_glyph, Qnil);

  DATA_PTR (self) = face;

  return Qnil;
}

static VALUE
cr_user_font_face_on_init (VALUE self)
{
  rb_ivar_set (self, cr_id_init, rb_block_proc ());
  return self;
}

static VALUE
cr_user_font_face_on_render_glyph (VALUE self)
{
  rb_ivar_set (self, cr_id_render_glyph, rb_block_proc ());
  return self;
}

static VALUE
cr_user_font_face_on_text_to_glyphs (VALUE self)
{
  rb_ivar_set (self, cr_id_text_to_glyphs, rb_block_proc ());
  return self;
}

static VALUE
cr_user_font_face_on_unicode_to_glyph (VALUE self)
{
  rb_ivar_set (self, cr_id_unicode_to_glyph, rb_block_proc ());
  return self;
}


static VALUE
cr_text_to_glyphs_data_initialize (VALUE self,
                                   VALUE need_glyphs, VALUE need_clusters,
                                   VALUE need_cluster_flags)
{
  rb_ivar_set (self, cr_id_at_glyphs, Qnil);
  rb_ivar_set (self, cr_id_at_clusters, Qnil);
  rb_ivar_set (self, cr_id_at_cluster_flags, INT2NUM (0));
  rb_ivar_set (self, cr_id_at_need_glyphs, need_glyphs);
  rb_ivar_set (self, cr_id_at_need_clusters, need_clusters);
  rb_ivar_set (self, cr_id_at_need_cluster_flags, need_cluster_flags);

  return Qnil;
}

static VALUE
cr_text_to_glyphs_data_get_cluster_flags (VALUE self)
{
  return rb_ivar_get (self, cr_id_at_cluster_flags);
}

static VALUE
cr_text_to_glyphs_data_set_cluster_flags (VALUE self, VALUE cluster_flags)
{
  rb_ivar_set (self, cr_id_at_cluster_flags,
               INT2NUM (RVAL2CRTEXTCLUSTERFLAGS (cluster_flags)));
  return Qnil;
}

static VALUE
cr_text_to_glyphs_data_need_glyphs (VALUE self)
{
  return rb_ivar_get (self, cr_id_at_need_glyphs);
}

static VALUE
cr_text_to_glyphs_data_need_clusters (VALUE self)
{
  return rb_ivar_get (self, cr_id_at_need_clusters);
}

static VALUE
cr_text_to_glyphs_data_need_cluster_flags (VALUE self)
{
  return rb_ivar_get (self, cr_id_at_need_cluster_flags);
}
#endif

void
Init_cairo_font (void)
{
#if CAIRO_CHECK_VERSION(1, 7, 6)
  cr_id_call = rb_intern ("call");
  cr_id_new = rb_intern ("new");

  cr_id_init = rb_intern ("init");
  cr_id_render_glyph = rb_intern ("render_glyph");
  cr_id_text_to_glyphs = rb_intern ("text_to_glyphs");
  cr_id_unicode_to_glyph = rb_intern ("unicode_to_glyph");

  cr_id_at_glyphs = rb_intern ("@glyphs");
  cr_id_at_clusters = rb_intern ("@clusters");
  cr_id_at_cluster_flags = rb_intern ("@cluster_flags");
  cr_id_at_need_glyphs = rb_intern ("@need_glyphs");
  cr_id_at_need_clusters = rb_intern ("@need_clusters");
  cr_id_at_need_cluster_flags = rb_intern ("@need_cluster_flags");
#endif

  rb_cCairo_FontFace =
    rb_define_class_under (rb_mCairo, "FontFace", rb_cObject);
  rb_define_alloc_func (rb_cCairo_FontFace, cr_font_face_allocate);

  rb_define_singleton_method (rb_cCairo_FontFace, "quartz_supported?",
                              cr_font_face_quartz_supported_p, 0);
  rb_define_singleton_method (rb_cCairo_FontFace, "freetype_supported?",
                              cr_font_face_freetype_supported_p, 0);

#ifdef CAIRO_HAS_FT_FONT
  rb_cCairo_FreeTypeFontFace =
    rb_define_class_under (rb_mCairo, "FreeTypeFontFace", rb_cCairo_FontFace);

  {
    FT_Error error;

    error = FT_Init_FreeType (&cr_freetype_library);
    cr_freetype_error_check (error, "failed to initialize FreeType", Qnil);

    rb_define_finalizer (rb_cCairo_FreeTypeFontFace,
                         rb_proc_new (cr_freetype_done_library, Qnil));
  }

  rb_define_method (rb_cCairo_FreeTypeFontFace, "initialize",
                    cr_freetype_font_face_initialize, 1);
#endif

#if CAIRO_CHECK_VERSION(1, 7, 6)
  rb_cCairo_ToyFontFace =
    rb_define_class_under (rb_mCairo, "ToyFontFace", rb_cCairo_FontFace);

  rb_define_method (rb_cCairo_ToyFontFace, "initialize",
                    cr_toy_font_face_initialize, -1);

  rb_define_method (rb_cCairo_ToyFontFace, "family",
                    cr_toy_font_face_get_family, 0);
  rb_define_method (rb_cCairo_ToyFontFace, "slant",
                    cr_toy_font_face_get_slant, 0);
  rb_define_method (rb_cCairo_ToyFontFace, "weight",
                    cr_toy_font_face_get_weight, 0);


  rb_cCairo_UserFontFace =
    rb_define_class_under (rb_mCairo, "UserFontFace", rb_cCairo_FontFace);

  rb_define_method (rb_cCairo_UserFontFace, "initialize",
                    cr_user_font_face_initialize, 0);

  rb_define_method (rb_cCairo_UserFontFace, "on_init",
                    cr_user_font_face_on_init, 0);
  rb_define_method (rb_cCairo_UserFontFace, "on_render_glyph",
                    cr_user_font_face_on_render_glyph, 0);
  rb_define_method (rb_cCairo_UserFontFace, "on_text_to_glyphs",
                    cr_user_font_face_on_text_to_glyphs, 0);
  rb_define_method (rb_cCairo_UserFontFace, "on_unicode_to_glyph",
                    cr_user_font_face_on_unicode_to_glyph, 0);


  rb_cCairo_UserFontFace_TextToGlyphsData =
    rb_define_class_under (rb_cCairo_UserFontFace,
                           "TextToGlyphsData", rb_cObject);
  rb_attr (rb_cCairo_UserFontFace_TextToGlyphsData, rb_intern ("glyphs"),
           CR_TRUE, CR_TRUE, CR_TRUE);
  rb_attr (rb_cCairo_UserFontFace_TextToGlyphsData, rb_intern ("clusters"),
           CR_TRUE, CR_TRUE, CR_TRUE);

  rb_define_method (rb_cCairo_UserFontFace_TextToGlyphsData,
                    "initialize", cr_text_to_glyphs_data_initialize, 3);

  rb_define_method (rb_cCairo_UserFontFace_TextToGlyphsData,
                    "cluster_flags",
                    cr_text_to_glyphs_data_get_cluster_flags, 0);
  rb_define_method (rb_cCairo_UserFontFace_TextToGlyphsData,
                    "cluster_flags=",
                    cr_text_to_glyphs_data_set_cluster_flags, 1);
  rb_define_method (rb_cCairo_UserFontFace_TextToGlyphsData,
                    "need_glyphs?", cr_text_to_glyphs_data_need_glyphs, 0);
  rb_define_method (rb_cCairo_UserFontFace_TextToGlyphsData,
                    "need_clusters?", cr_text_to_glyphs_data_need_clusters, 0);
  rb_define_method (rb_cCairo_UserFontFace_TextToGlyphsData,
                    "need_cluster_flags?",
                    cr_text_to_glyphs_data_need_cluster_flags, 0);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_UserFontFace_TextToGlyphsData);
#endif
}
