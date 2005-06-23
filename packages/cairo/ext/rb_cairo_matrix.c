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
      free (ptr);
    }
}


VALUE
rb_cairo_matrix_wrap (cairo_matrix_t *matrix)
{
  if (matrix)
    {
      return Data_Wrap_Struct (rb_cCairo_Matrix, NULL, rb_free_matrix, matrix);
    }
  else
    {
      rb_raise (rb_eArgError, "unable to wrap matrix");
      return Qundef;
    }
}  


static VALUE
float_array (double   *values,
             unsigned  count)
{
  VALUE     result;
  unsigned  i;

  result = rb_ary_new2 (count);
  for (i = 0; i < count; i++)
    {
      rb_ary_push (result, rb_float_new (values[i]));
    }
  return result;
}


/*
 * methods
 */



static    VALUE
rb_cairo_matrix_new (VALUE klass)
{
  cairo_matrix_t *matrix;
  
  matrix = malloc (sizeof (cairo_matrix_t));

  if (matrix)
    {
      cairo_matrix_init_identity (matrix);
      return rb_cairo_matrix_wrap (matrix);
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
  cairo_matrix_copy (_SELF,
                     rb_v_to_cairo_matrix_t (other));
  return self;
}

static    VALUE
rb_cairo_matrix_init_identity (VALUE self)
{
  cairo_matrix_init_identity (_SELF);
  return self;
}

static    VALUE
rb_cairo_matrix_set (VALUE self,
                     VALUE a,  VALUE b,
                     VALUE c,  VALUE d,
                     VALUE tx, VALUE ty)
{
  cairo_matrix_init (_SELF,
                     NUM2DBL (a), NUM2DBL (b),
                     NUM2DBL (c), NUM2DBL (d),
                     NUM2DBL (tx), NUM2DBL (ty));
  return self;
}

static    VALUE
rb_cairo_matrix_get (VALUE self)
{
  cairo_matrix_t *matrix = _SELF;
  double    affine[6];
  affine[0] = matrix->xx;
  affine[1] = matrix->yx;
  affine[2] = matrix->xy;
  affine[3] = matrix->yy;
  affine[4] = matrix->x0;
  affine[5] = matrix->y0;
  return float_array (affine, 6);
}

static    VALUE
rb_cairo_matrix_translate (VALUE self,
                           VALUE tx, VALUE ty)
{
  cairo_matrix_translate (_SELF,
                          NUM2DBL (tx), NUM2DBL (ty));
  return self;
}

static    VALUE
rb_cairo_matrix_scale (VALUE self,
                          VALUE sx, VALUE sy)
{
  cairo_matrix_scale (_SELF,
                      NUM2DBL (sx), NUM2DBL (sy));
  return self;
}

static    VALUE
rb_cairo_matrix_rotate (VALUE self,
                           VALUE radians)
{
  cairo_matrix_rotate (_SELF,
                       NUM2DBL (radians));
  return self;
}

static    VALUE
rb_cairo_matrix_invert (VALUE self)
{
  cairo_matrix_invert (_SELF);
  return self;
}

static    VALUE
rb_cairo_matrix_multiply (VALUE self,
                          VALUE a,
                          VALUE b)
{
  cairo_matrix_multiply (_SELF,
                         rb_v_to_cairo_matrix_t (a),
                         rb_v_to_cairo_matrix_t (b));
  return self;
}

static    VALUE
rb_cairo_matrix_transform_distance (VALUE self,
                                    VALUE dx, VALUE dy)
{
  double    pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_matrix_transform_distance (_SELF,
                                   pair, pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_matrix_transform_point (VALUE self,
                                 VALUE x, VALUE y)
{
  double    pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_matrix_transform_point (_SELF,
                                pair, pair + 1);
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
  rb_define_method (rb_cCairo_Matrix, "set",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_set), 6);
  rb_define_method (rb_cCairo_Matrix, "get",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_get), 0);
  rb_define_method (rb_cCairo_Matrix, "init_identity",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_init_identity), 1);
  rb_define_method (rb_cCairo_Matrix, "translate!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_translate), 2);
  rb_define_method (rb_cCairo_Matrix, "scale!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_scale), 2);
  rb_define_method (rb_cCairo_Matrix, "rotate!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_rotate), 2);
  rb_define_method (rb_cCairo_Matrix, "multiply!",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_multiply), 3);
  rb_define_method (rb_cCairo_Matrix, "transform_point",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_transform_point), 2);
  rb_define_method (rb_cCairo_Matrix, "matrix_distance",
                    RUBY_METHOD_FUNC (rb_cairo_matrix_transform_distance), 2);
}
