/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-16 08:16:40 $
 *
 * Copyright 2008 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_TextCluster = Qnil;

#if CAIRO_CHECK_VERSION(1, 7, 2)
#define _SELF(self)  (RVAL2CRTEXTCLUSTER(self))

cairo_text_cluster_t *
rb_cairo_text_cluster_from_ruby_object (VALUE obj)
{
  cairo_text_cluster_t *cluster;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_TextCluster))
    {
      rb_raise (rb_eTypeError,
                "not a cairo cluster: %s", rb_cairo__inspect (obj));
    }
  Data_Get_Struct (obj, cairo_text_cluster_t, cluster);
  return cluster;
}

static void
cr_text_cluster_free (void *ptr)
{
  if (ptr)
    {
      xfree (ptr);
    }
}

VALUE
rb_cairo_text_cluster_to_ruby_object (cairo_text_cluster_t *cluster)
{
  if (cluster)
    {
      cairo_text_cluster_t *new_cluster;

      new_cluster = ALLOC (cairo_text_cluster_t);
      *new_cluster = *cluster;
      return Data_Wrap_Struct (rb_cCairo_TextCluster, NULL,
                               cr_text_cluster_free, new_cluster);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_text_cluster_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_text_cluster_free, NULL);
}

static VALUE
cr_text_cluster_initialize (VALUE self, VALUE num_bytes, VALUE num_glyphs)
{
  cairo_text_cluster_t *cluster;

  cluster = ALLOC (cairo_text_cluster_t);
  cluster->num_bytes = NUM2INT (num_bytes);
  cluster->num_glyphs = NUM2INT (num_glyphs);

  DATA_PTR (self) = cluster;
  return Qnil;
}

static VALUE
cr_text_cluster_num_bytes (VALUE self)
{
  return INT2NUM (_SELF(self)->num_bytes);
}

static VALUE
cr_text_cluster_num_glyphs (VALUE self)
{
  return INT2NUM (_SELF(self)->num_glyphs);
}

static VALUE
cr_text_cluster_set_num_bytes (VALUE self, VALUE num_bytes)
{
  _SELF(self)->num_bytes = NUM2INT (num_bytes);
  return self;
}

static VALUE
cr_text_cluster_set_num_glyphs (VALUE self, VALUE num_glyphs)
{
  _SELF(self)->num_glyphs = NUM2INT (num_glyphs);
  return self;
}

static VALUE
cr_text_cluster_to_s (VALUE self)
{
  VALUE ret;

  ret = rb_str_new2 ("#<");
  rb_str_cat2 (ret, rb_class2name (CLASS_OF (self)));
  rb_str_cat2 (ret, ": ");
  rb_str_cat2 (ret, "num_bytes=");
  rb_str_concat (ret, rb_inspect (cr_text_cluster_num_bytes (self)));
  rb_str_cat2 (ret, ", ");
  rb_str_cat2 (ret, "num_glyphs=");
  rb_str_concat (ret, rb_inspect (cr_text_cluster_num_glyphs (self)));
  rb_str_cat2 (ret, ">");

  return ret;
}
#endif

void
Init_cairo_text_cluster (void)
{
#if CAIRO_CHECK_VERSION(1, 7, 2)
  rb_cCairo_TextCluster = rb_define_class_under (rb_mCairo, "TextCluster", rb_cObject);

  rb_define_alloc_func (rb_cCairo_TextCluster, cr_text_cluster_allocate);

  rb_define_method (rb_cCairo_TextCluster, "initialize",
                    cr_text_cluster_initialize, 2);

  rb_define_method (rb_cCairo_TextCluster, "num_bytes",
                    cr_text_cluster_num_bytes, 0);
  rb_define_method (rb_cCairo_TextCluster, "num_glyphs",
                    cr_text_cluster_num_glyphs, 0);
  rb_define_method (rb_cCairo_TextCluster, "set_num_bytes",
                    cr_text_cluster_set_num_bytes, 1);
  rb_define_method (rb_cCairo_TextCluster, "set_num_glyphs",
                    cr_text_cluster_set_num_glyphs, 1);

  rb_define_method (rb_cCairo_TextCluster, "to_s", cr_text_cluster_to_s, 0);

  RB_CAIRO_DEF_SETTERS (rb_cCairo_TextCluster);
#endif
}
