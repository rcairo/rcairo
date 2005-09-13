/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
 */


#include "rb_cairo.h"

VALUE rb_cCairo_Matrix;

#define _SELF  (RVAL2CRMATRIX(self))

cairo_matrix_t *
rb_cairo_matrix_from_ruby_object (VALUE obj)
{
  cairo_matrix_t *xform;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_Matrix)))
    {
      rb_raise (rb_eTypeError, "not a cairo matrix");
    }
  Data_Get_Struct (obj, cairo_matrix_t, xform);
  return xform;
}

VALUE
rb_cairo_matrix_to_ruby_object (cairo_matrix_t *matrix)
{
  if (matrix)
    {
      cairo_matrix_t *new_matrix = ALLOC (cairo_matrix_t);
      *new_matrix = *matrix;
      return Data_Wrap_Struct (rb_cCairo_Matrix, NULL, -1, new_matrix);
    }
  else
    {
      return Qnil;
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
cr_matrix_new (VALUE klass)
{
  cairo_matrix_t matrix;
  VALUE rb_matrix;
  
  cairo_matrix_init_identity (&matrix);
  rb_matrix = CRMATRIX2RVAL (&matrix);
  rb_obj_call_init (rb_matrix, 0, NULL);
  return rb_matrix;
}

static    VALUE
cr_matrix_copy (VALUE self, VALUE other)
{
  cairo_matrix_t *matrix = RVAL2CRMATRIX (other);
  
  cairo_matrix_init (_SELF,
                     matrix->xx, matrix->yx,
                     matrix->xy, matrix->yy,
                     matrix->x0, matrix->y0);
  return self;
}

static    VALUE
cr_matrix_init_identity (VALUE self)
{
  cairo_matrix_init_identity (_SELF);
  return self;
}

static    VALUE
cr_matrix_set (VALUE self,
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
cr_matrix_get (VALUE self)
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
cr_matrix_translate (VALUE self,
                     VALUE tx, VALUE ty)
{
  cairo_matrix_translate (_SELF,
                          NUM2DBL (tx), NUM2DBL (ty));
  return self;
}

static    VALUE
cr_matrix_scale (VALUE self,
                 VALUE sx, VALUE sy)
{
  cairo_matrix_scale (_SELF,
                      NUM2DBL (sx), NUM2DBL (sy));
  return self;
}

static    VALUE
cr_matrix_rotate (VALUE self,
                  VALUE radians)
{
  cairo_matrix_rotate (_SELF,
                       NUM2DBL (radians));
  return self;
}

static    VALUE
cr_matrix_invert (VALUE self)
{
  cairo_status_t status;
  status = cairo_matrix_invert (_SELF);
  if (status)
    {
      rb_cairo_raise_exception (status);
    }
      
  return self;
}

static    VALUE
cr_matrix_multiply (VALUE self,
                    VALUE a,
                    VALUE b)
{
  cairo_matrix_multiply (_SELF,
                         RVAL2CRMATRIX (a),
                         RVAL2CRMATRIX (b));
  return self;
}

static    VALUE
cr_matrix_transform_distance (VALUE self,
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
cr_matrix_transform_point (VALUE self,
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
                              cr_matrix_new, 0);
  rb_define_method (rb_cCairo_Matrix, "copy",
                    cr_matrix_copy, 1);
  rb_define_method (rb_cCairo_Matrix, "set",
                    cr_matrix_set, 6);
  rb_define_method (rb_cCairo_Matrix, "to_a",
                    cr_matrix_get, 0);
  rb_define_method (rb_cCairo_Matrix, "init_identity",
                    cr_matrix_init_identity, 1);
  rb_define_method (rb_cCairo_Matrix, "translate!",
                    cr_matrix_translate, 2);
  rb_define_method (rb_cCairo_Matrix, "scale!",
                    cr_matrix_scale, 2);
  rb_define_method (rb_cCairo_Matrix, "rotate!",
                    cr_matrix_rotate, 2);
  rb_define_method (rb_cCairo_Matrix, "invert!",
                    cr_matrix_invert, 0);
  rb_define_method (rb_cCairo_Matrix, "multiply!",
                    cr_matrix_multiply, 3);
  rb_define_method (rb_cCairo_Matrix, "transform_point",
                    cr_matrix_transform_point, 2);
  rb_define_method (rb_cCairo_Matrix, "matrix_distance",
                    cr_matrix_transform_distance, 2);
}
