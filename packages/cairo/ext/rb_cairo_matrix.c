/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo_matrix.h"

#define _SELF  (DATA_PTR(self))

VALUE rb_cCairo_Matrix;

cairo_matrix_t *
rb_v_to_cairo_matrix_t (VALUE value)
{
  cairo_matrix_t *xform;
  if (CLASS_OF (value) != rb_cCairo_Matrix)
    {
      rb_raise (rb_eTypeError, "not a cairo matrix");
    }
  Data_Get_Struct (value, cairo_matrix_t, xform);
  return xform;
}

void
rb_free_matrix (void *ptr)
{
  if (ptr)
    {
      cairo_matrix_destroy ((cairo_matrix_t *) ptr);
    }
}


/*
 * methods
 */

static    VALUE
rb_cairo_matrix_new (VALUE klass)
{
  cairo_matrix_t *xform;
  xform = cairo_matrix_create ();
  if (xform)
    {
      return Data_Wrap_Struct (rb_cCairo_Matrix, NULL, rb_free_matrix, xform);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate matrix");
      return Qundef;
    }
}

static    VALUE
rb_cairo_matrix_copy (VALUE self, VALUE other)
{
  cairo_status_t status;
  status =
    cairo_matrix_copy (_SELF,
                       rb_v_to_cairo_matrix_t (other));
  if (status)
    {
      raise_cairo_exception (status, "error copying matrix");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_set_identity (VALUE self)
{
  cairo_status_t status;
  status = cairo_matrix_set_identity (_SELF);
  if (status)
    {
      raise_cairo_exception (status, "error resetting matrix");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_set_affine (VALUE self,
                            VALUE a,  VALUE b,
                            VALUE c,  VALUE d,
                            VALUE tx, VALUE ty)
{
  cairo_status_t status;
  status = cairo_matrix_set_affine (_SELF,
                                    NUM2DBL (a), NUM2DBL (b),
                                    NUM2DBL (c), NUM2DBL (d),
                                    NUM2DBL (tx), NUM2DBL (ty));
  if (status)
    {
      raise_cairo_exception (status, "error setting matrix components");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_get_affine (VALUE self)
{
  cairo_status_t status;
  double    affine[6];
  status = cairo_matrix_get_affine (_SELF,
                                    affine, affine + 1,
                                    affine + 2, affine + 3,
                                    affine + 4, affine + 5);
  if (status)
    {
      raise_cairo_exception (status, "error getting matrix components");
    }
  return float_array (affine, 6);
}

static    VALUE
rb_cairo_matrix_translate (VALUE self,
                           VALUE tx, VALUE ty)
{
  cairo_status_t status;
  status = cairo_matrix_translate (_SELF,
                                   NUM2DBL (tx), NUM2DBL (ty));
  if (status)
    {
      raise_cairo_exception (status, "error translating matrix");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_scale (VALUE self,
                          VALUE sx, VALUE sy)
{
  cairo_status_t status;
  status = cairo_matrix_scale (_SELF,
                               NUM2DBL (sx), NUM2DBL (sy));
  if (status)
    {
      raise_cairo_exception (status, "error scaling matrix");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_rotate (VALUE self,
                           VALUE radians)
{
  cairo_status_t status;
  status = cairo_matrix_rotate (_SELF,
                                NUM2DBL (radians));
  if (status)
    {
      raise_cairo_exception (status, "error rotating matrix");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_invert (VALUE self)
{
  cairo_status_t status;
  status = cairo_matrix_invert (_SELF);
  if (status)
    {
      raise_cairo_exception (status, "error inverting matrix");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_set_product (VALUE self,
                                VALUE a,
                                VALUE b)
{
  cairo_status_t status;
  status = cairo_matrix_multiply (_SELF,
                                  rb_v_to_cairo_matrix_t (a), rb_v_to_cairo_matrix_t (b));
  if (status)
    {
      raise_cairo_exception (status, "error multiplying matrices");
    }
  return self;
}

static    VALUE
rb_cairo_matrix_transform_distance (VALUE self,
                                       VALUE dx, VALUE dy)
{
  cairo_status_t status;
  double    pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  status = cairo_matrix_transform_distance (_SELF,
                                            pair, pair + 1);
  if (status)
    {
      raise_cairo_exception (status, "error transforming distance");
    }
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_matrix_transform_point (VALUE self,
                                    VALUE x, VALUE y)
{
  cairo_status_t status;
  double    pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  status = cairo_matrix_transform_point (_SELF,
                                         pair, pair + 1);
  if (status)
    {
      raise_cairo_exception (status, "error transforming point");
    }
  return float_array (pair, 2);
}


void
Init_cairo_matrix (void)
{
  rb_cCairo_Matrix =
    rb_define_class_under (rb_mCairo, "Matrix", rb_cObject);
  rb_define_singleton_method (rb_cCairo_Matrix, "new",
                              RUBY_METHOD_FUNC (rb_cairo_matrix_new), 0);
  rb_define_method (rb_cCairo_Matrix, "copy",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_copy), 1);
  rb_define_method (rb_cCairo_Matrix, "set_identity",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_set_identity), 6);
  rb_define_method (rb_cCairo_Matrix, "set_affine",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_set_affine), 6);
  rb_define_method (rb_cCairo_Matrix, "translate!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_translate), 2);
  rb_define_method (rb_cCairo_Matrix, "scale!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_scale), 2);
  rb_define_method (rb_cCairo_Matrix, "rotate!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_rotate), 2);
  rb_define_method (rb_cCairo_Matrix, "set_product",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_set_product), 3);
  rb_define_method (rb_cCairo_Matrix, "matrix_distance",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_translate), 2);
  rb_define_method (rb_cCairo_Matrix, "matrix_point",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_translate), 2);
  rb_define_method (rb_cCairo_Matrix, "get_affine",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_get_affine), 0);
}
