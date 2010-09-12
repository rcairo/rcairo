/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-14 12:37:50 $
 *
 * Copyright 2006-2008 Kouhei Sutou <kou@cozmixng.org>
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"
#include "rb_cairo_private.h"

VALUE rb_cCairo_Matrix;

static ID cr_id_equal;

#define _SELF  (RVAL2CRMATRIX(self))

cairo_matrix_t *
rb_cairo_matrix_from_ruby_object (VALUE obj)
{
  cairo_matrix_t *matrix;
  if (!rb_cairo__is_kind_of (obj, rb_cCairo_Matrix))
    {
      rb_raise (rb_eTypeError, "not a cairo matrix");
    }
  Data_Get_Struct (obj, cairo_matrix_t, matrix);
  return matrix;
}

static void
cr_matrix_free (void *ptr)
{
  if (ptr)
    {
      xfree ((cairo_matrix_t *) ptr);
    }
}

VALUE
rb_cairo_matrix_to_ruby_object (cairo_matrix_t *matrix)
{
  if (matrix)
    {
      cairo_matrix_t *new_matrix = ALLOC (cairo_matrix_t);
      *new_matrix = *matrix;
      return Data_Wrap_Struct (rb_cCairo_Matrix, NULL,
                               cr_matrix_free, new_matrix);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_matrix_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_matrix_free, NULL);
}

static VALUE
cr_matrix_initialize (VALUE self,
                      VALUE xx, VALUE yx,
                      VALUE xy, VALUE yy,
                      VALUE x0, VALUE y0)
{
  cairo_matrix_t *matrix = ALLOC (cairo_matrix_t);

  cairo_matrix_init (matrix,
                     NUM2DBL (xx), NUM2DBL (yx),
                     NUM2DBL (xy), NUM2DBL (yy),
                     NUM2DBL (x0), NUM2DBL (y0));
  DATA_PTR (self) = matrix;
  return Qnil;
}

static VALUE
cr_matrix_init_identity (VALUE self)
{
  cairo_matrix_t matrix;
  cairo_matrix_init_identity (&matrix);
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_matrix_init_translate (VALUE self, VALUE tx, VALUE ty)
{
  cairo_matrix_t matrix;
  cairo_matrix_init_translate (&matrix, NUM2DBL (tx), NUM2DBL (ty));
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_matrix_init_scale (VALUE self, VALUE sx, VALUE sy)
{
  cairo_matrix_t matrix;
  cairo_matrix_init_scale (&matrix, NUM2DBL (sx), NUM2DBL (sy));
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_matrix_init_rotate (VALUE self, VALUE radius)
{
  cairo_matrix_t matrix;
  cairo_matrix_init_rotate (&matrix, NUM2DBL (radius));
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_matrix_identity (VALUE self)
{
  cairo_matrix_init_identity (_SELF);
  return self;
}

static VALUE
cr_matrix_translate (VALUE self, VALUE tx, VALUE ty)
{
  cairo_matrix_translate (_SELF, NUM2DBL (tx), NUM2DBL (ty));
  return self;
}

static VALUE
cr_matrix_scale (VALUE self, VALUE sx, VALUE sy)
{
  cairo_matrix_scale (_SELF, NUM2DBL (sx), NUM2DBL (sy));
  return self;
}

static VALUE
cr_matrix_rotate (VALUE self, VALUE radians)
{
  cairo_matrix_rotate (_SELF, NUM2DBL (radians));
  return self;
}

static VALUE
cr_matrix_invert (VALUE self)
{
  rb_cairo_check_status (cairo_matrix_invert (_SELF));
  return self;
}

static VALUE
cr_matrix_multiply (VALUE self, VALUE other)
{
  cairo_matrix_multiply (_SELF, _SELF, RVAL2CRMATRIX (other));
  return self;
}

static VALUE
cr_matrix_transform_distance (VALUE self, VALUE dx, VALUE dy)
{
  double pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_matrix_transform_distance (_SELF, pair, pair + 1);
  return rb_cairo__float_array (pair, 2);
}

static VALUE
cr_matrix_transform_point (VALUE self, VALUE x, VALUE y)
{
  double pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_matrix_transform_point (_SELF, pair, pair + 1);
  return rb_cairo__float_array (pair, 2);
}


/* Accessors */
static VALUE
cr_matrix_get_xx (VALUE self)
{
  return rb_float_new (_SELF->xx);
}

static VALUE
cr_matrix_set_xx (VALUE self, VALUE xx)
{
  _SELF->xx = NUM2DBL (xx);
  return Qnil;
}

static VALUE
cr_matrix_get_yx (VALUE self)
{
  return rb_float_new (_SELF->yx);
}

static VALUE
cr_matrix_set_yx (VALUE self, VALUE yx)
{
  _SELF->yx = NUM2DBL (yx);
  return Qnil;
}

static VALUE
cr_matrix_get_xy (VALUE self)
{
  return rb_float_new (_SELF->xy);
}

static VALUE
cr_matrix_set_xy (VALUE self, VALUE xy)
{
  _SELF->xy = NUM2DBL (xy);
  return Qnil;
}

static VALUE
cr_matrix_get_yy (VALUE self)
{
  return rb_float_new (_SELF->yy);
}

static VALUE
cr_matrix_set_yy (VALUE self, VALUE yy)
{
  _SELF->yy = NUM2DBL (yy);
  return Qnil;
}

static VALUE
cr_matrix_get_x0 (VALUE self)
{
  return rb_float_new (_SELF->x0);
}

static VALUE
cr_matrix_set_x0 (VALUE self, VALUE x0)
{
  _SELF->x0 = NUM2DBL (x0);
  return Qnil;
}

static VALUE
cr_matrix_get_y0 (VALUE self)
{
  return rb_float_new (_SELF->y0);
}

static VALUE
cr_matrix_set_y0 (VALUE self, VALUE y0)
{
  _SELF->y0 = NUM2DBL (y0);
  return Qnil;
}

/* Utilities */
static VALUE
cr_matrix_set (VALUE self,
               VALUE xx, VALUE yx,
               VALUE xy, VALUE yy,
               VALUE x0, VALUE y0)
{
  cairo_matrix_init (_SELF,
                     NUM2DBL (xx), NUM2DBL (yx),
                     NUM2DBL (xy), NUM2DBL (yy),
                     NUM2DBL (x0), NUM2DBL (y0));
  return self;
}

static VALUE
cr_matrix_to_a (VALUE self)
{
  cairo_matrix_t *matrix = _SELF;
  double affine[6];
  affine[0] = matrix->xx;
  affine[1] = matrix->yx;
  affine[2] = matrix->xy;
  affine[3] = matrix->yy;
  affine[4] = matrix->x0;
  affine[5] = matrix->y0;
  return rb_cairo__float_array (affine, 6);
}

static VALUE
cr_matrix_to_s(VALUE self)
{
  VALUE ret;

  ret = rb_str_new2 ("#<");
  rb_str_cat2 (ret, rb_class2name (CLASS_OF (self)));
  rb_str_cat2 (ret, ":");
  rb_str_concat (ret, rb_inspect (cr_matrix_to_a (self)));
  rb_str_cat2 (ret, ">");
  
  return ret;
}

static VALUE
cr_matrix_equal (VALUE self, VALUE other)
{
  if (!rb_cairo__is_kind_of (other, rb_cCairo_Matrix))
    return Qfalse;

  return rb_funcall (cr_matrix_to_a (self),
                     cr_id_equal, 1,
                     cr_matrix_to_a (other));
}

void
Init_cairo_matrix (void)
{
  cr_id_equal = rb_intern ("==");

  rb_cCairo_Matrix =
    rb_define_class_under (rb_mCairo, "Matrix", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Matrix, cr_matrix_allocate);

  rb_define_singleton_method (rb_cCairo_Matrix, "identity",
                              cr_matrix_init_identity, 0);
  rb_define_singleton_method (rb_cCairo_Matrix, "translate",
                              cr_matrix_init_translate, 2);
  rb_define_singleton_method (rb_cCairo_Matrix, "scale",
                              cr_matrix_init_scale, 2);
  rb_define_singleton_method (rb_cCairo_Matrix, "rotate",
                              cr_matrix_init_rotate, 1);
  
  rb_define_method (rb_cCairo_Matrix, "initialize", cr_matrix_initialize, 6);
  
  rb_define_method (rb_cCairo_Matrix, "identity!", cr_matrix_identity, 0);
  rb_define_method (rb_cCairo_Matrix, "translate!", cr_matrix_translate, 2);
  rb_define_method (rb_cCairo_Matrix, "scale!", cr_matrix_scale, 2);
  rb_define_method (rb_cCairo_Matrix, "rotate!", cr_matrix_rotate, 1);
  rb_define_method (rb_cCairo_Matrix, "invert!", cr_matrix_invert, 0);
  rb_define_method (rb_cCairo_Matrix, "multiply!", cr_matrix_multiply, 1);
  rb_define_method (rb_cCairo_Matrix, "transform_distance",
                    cr_matrix_transform_distance, 2);
  rb_define_method (rb_cCairo_Matrix, "transform_point",
                    cr_matrix_transform_point, 2);

  /* Accessors */
  rb_define_method (rb_cCairo_Matrix, "xx", cr_matrix_get_xx, 0);
  rb_define_method (rb_cCairo_Matrix, "set_xx", cr_matrix_set_xx, 1);
  rb_define_method (rb_cCairo_Matrix, "yx", cr_matrix_get_yx, 0);
  rb_define_method (rb_cCairo_Matrix, "set_yx", cr_matrix_set_yx, 1);
  rb_define_method (rb_cCairo_Matrix, "xy", cr_matrix_get_xy, 0);
  rb_define_method (rb_cCairo_Matrix, "set_xy", cr_matrix_set_xy, 1);
  rb_define_method (rb_cCairo_Matrix, "yy", cr_matrix_get_yy, 0);
  rb_define_method (rb_cCairo_Matrix, "set_yy", cr_matrix_set_yy, 1);
  rb_define_method (rb_cCairo_Matrix, "x0", cr_matrix_get_x0, 0);
  rb_define_method (rb_cCairo_Matrix, "set_x0", cr_matrix_set_x0, 1);
  rb_define_method (rb_cCairo_Matrix, "y0", cr_matrix_get_y0, 0);
  rb_define_method (rb_cCairo_Matrix, "set_y0", cr_matrix_set_y0, 1);

  /* Utilities */
  rb_define_method (rb_cCairo_Matrix, "set", cr_matrix_set, 6);
  rb_define_method (rb_cCairo_Matrix, "to_a", cr_matrix_to_a, 0);
  rb_define_method (rb_cCairo_Matrix, "to_s", cr_matrix_to_s, 0);
  rb_define_method (rb_cCairo_Matrix, "==", cr_matrix_equal, 1);


  RB_CAIRO_DEF_SETTERS (rb_cCairo_Matrix);
}
