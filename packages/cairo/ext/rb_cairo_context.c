/*
 * Ruby Cairo Binding
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo_context.h"

VALUE rb_cCairo_Context;

#define _SELF  (DATA_PTR(self))

cairo_t *
rb_v_to_cairo_t (VALUE value)
{
  cairo_t  *context;
  if (CLASS_OF (value) != rb_cCairo_Context)
    {
      rb_raise (rb_eTypeError, "not a cairo graphics context");
    }
  Data_Get_Struct (value, cairo_t, context);
  return context;
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

static inline void
check_context_status (cairo_t *context)
{
  cairo_status_t status;
  status = cairo_status (context);
  if (status)
    {
      raise_cairo_exception (status, cairo_status_string (context));
    }
}

void
rb_free_context (void *ptr)
{
  if (ptr)
    {
      cairo_destroy ((cairo_t *) ptr);
    }
}

static    VALUE
rb_cairo_new (VALUE klass)
{
  cairo_t  *cr;
  cr = cairo_create ();
  if (cr)
    {
      return Data_Wrap_Struct (rb_cCairo_Context, NULL, rb_free_context, cr);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate cairo context");
      return Qundef;
    }
}

VALUE
rb_cairo_new_from (cairo_t *cr)
{
  cairo_reference (cr);
  return Data_Wrap_Struct (rb_cCairo_Context, NULL, rb_free_context, cr);
}

static    VALUE
rb_cairo_save (VALUE self)
{
  cairo_save (_SELF);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_restore (VALUE self)
{
  cairo_restore (_SELF);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_copy (VALUE self,
               VALUE other)
{
  cairo_copy (_SELF, rb_v_to_cairo_t (other));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_target_surface (VALUE self,
                             VALUE surface)
{
  cairo_set_target_surface (_SELF, rb_v_to_cairo_surface_t (surface));
  check_context_status (_SELF);
  return self;
}

#if 0
NYI
rb_cairo_set_target_image (VALUE self,
#endif              

static    VALUE
rb_cairo_set_operator (VALUE self,
                       VALUE op_v)
{
  int       op;
  Check_Type (op_v, T_FIXNUM);
  op = FIX2INT (op_v);
  if (op < CAIRO_OPERATOR_CLEAR || op > CAIRO_OPERATOR_SATURATE)
    {
      rb_raise (rb_eArgError, "invalid composition operator");
    }
  cairo_set_operator (_SELF, (cairo_operator_t) op);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_rgb_color (VALUE self,
                        VALUE red,
                        VALUE green,
                        VALUE blue)
{
  cairo_set_rgb_color (_SELF,
                       NUM2DBL (red),
                       NUM2DBL (green),
                       NUM2DBL (blue));
  return self;
}

static    VALUE
rb_cairo_set_pattern (VALUE self,
                      VALUE pattern_v)
{
  cairo_pattern_t *pattern;
  pattern = rb_v_to_cairo_pattern_t (pattern_v);

  cairo_set_pattern (_SELF, pattern);
  check_context_status (_SELF);
  return self;
}


static    VALUE
rb_cairo_set_alpha (VALUE self,
                    VALUE alpha)
{
  cairo_set_alpha (_SELF, NUM2DBL (alpha));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_tolerance (VALUE self,
                        VALUE tolerance)
{
  cairo_set_tolerance (_SELF, NUM2DBL (tolerance));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_fill_rule (VALUE self,
                        VALUE rule_v)
{
  int       rule;
  Check_Type (rule_v, T_FIXNUM);
  rule = FIX2INT (rule_v);
  if (rule < CAIRO_FILL_RULE_WINDING || rule > CAIRO_FILL_RULE_EVEN_ODD)
    {
      rb_raise (rb_eArgError, "invalid fill rule");
    }
  cairo_set_fill_rule (_SELF, (cairo_fill_rule_t) rule);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_line_width (VALUE self,
                         VALUE width)
{
  cairo_set_line_width (_SELF, NUM2DBL (width));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_line_cap (VALUE self,
                       VALUE cap_v)
{
  int       cap;
  Check_Type (cap_v, T_FIXNUM);
  cap = FIX2INT (cap_v);
  if (cap < CAIRO_LINE_CAP_BUTT || cap > CAIRO_LINE_CAP_SQUARE)
    {
      rb_raise (rb_eArgError, "invalid line cap type");
    }
  cairo_set_line_cap (_SELF, (cairo_line_cap_t) cap);
  return self;
}

static    VALUE
rb_cairo_set_line_join (VALUE self,
                        VALUE join_v)
{
  int       join;
  Check_Type (join_v, T_FIXNUM);
  join = FIX2INT (join_v);
  if (join < CAIRO_LINE_JOIN_MITER || join > CAIRO_LINE_JOIN_BEVEL)
    {
      rb_raise (rb_eArgError, "invalid line join type");
    }
  cairo_set_line_join (_SELF, (cairo_line_join_t) join);
  return self;
}

static    VALUE
rb_cairo_set_dash (VALUE self,
                   VALUE dash_array,
                   VALUE offset)
{
  int       length;
  double   *values;

  if (!NIL_P (dash_array))
    {
      Check_Type (dash_array, T_ARRAY);
    }

  if (NIL_P (dash_array) || RARRAY (dash_array)->len == 0)
    {
      length = 0;
      values = NULL;
    }
  else
    {
      int       i;
      length = RARRAY (dash_array)->len;
      values = (double *) malloc (sizeof (double) * length);
      if (!values)
        {
          rb_raise (rb_eNoMemError, "out of memory");
        }
      for (i = 0; i < length; i++)
        {
          // TODO: handle memory leak if NUM2DBL throws an exception
          values[i] = NUM2DBL (RARRAY (dash_array)->ptr[i]);
        }
    }

  cairo_set_dash (_SELF, values, length, NUM2DBL (offset));
  free (values);

  return self;
}

static    VALUE
rb_cairo_set_miter_limit (VALUE self,
                          VALUE limit)
{
  cairo_set_miter_limit (_SELF, NUM2DBL (limit));
  return self;
}

static    VALUE
rb_cairo_translate (VALUE self,
                    VALUE tx,
                    VALUE ty)
{
  cairo_translate (_SELF, NUM2DBL (tx), NUM2DBL (ty));
  return self;
}

static    VALUE
rb_cairo_scale (VALUE self,
                VALUE sx,
                VALUE sy)
{
  cairo_scale (_SELF, NUM2DBL (sx), NUM2DBL (sy));
  return self;
}

static    VALUE
rb_cairo_rotate (VALUE self,
                 VALUE radians)
{
  cairo_rotate (_SELF, NUM2DBL (radians));
  return self;
}

static    VALUE
rb_cairo_concat_matrix (VALUE self,
                        VALUE xform)
{
  cairo_concat_matrix (_SELF, rb_v_to_cairo_matrix_t (xform));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_matrix (VALUE self,
                     VALUE xform)
{
  cairo_set_matrix (_SELF, rb_v_to_cairo_matrix_t (xform));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_default_matrix (VALUE self)
{
  cairo_default_matrix (_SELF);
  return self;
}

static    VALUE
rb_cairo_identity_matrix (VALUE self)
{
  cairo_identity_matrix (_SELF);
  return self;
}

static    VALUE
rb_cairo_transform_point (VALUE self,
                          VALUE x, VALUE y)
{
  double    pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_transform_point (_SELF, pair, pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_transform_distance (VALUE self,
                             VALUE dx, VALUE dy)
{
  double    pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_transform_distance (_SELF, pair,
                            pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_inverse_transform_point (VALUE self,
                                  VALUE x, VALUE y)
{
  double    pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_inverse_transform_point (_SELF,
                                 pair, pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_inverse_transform_distance (VALUE self,
                                     VALUE dx, VALUE dy)
{
  double    pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_inverse_transform_distance (_SELF,
                                    pair, pair + 1);
  return float_array (pair, 2);
}

/* Path creation functions */

static    VALUE
rb_cairo_new_path (VALUE self)
{
  cairo_new_path (_SELF);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_move_to (VALUE self,
                  VALUE x, VALUE y)
{
  cairo_move_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_line_to (VALUE self,
                  VALUE x, VALUE y)
{
  cairo_line_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_curve_to (VALUE self,
                   VALUE x1, VALUE y1,
                   VALUE x2, VALUE y2,
                   VALUE x3, VALUE y3)
{
  cairo_curve_to (_SELF, NUM2DBL (x1), NUM2DBL (y1),
                  NUM2DBL (x2), NUM2DBL (y2), NUM2DBL (x3), NUM2DBL (y3));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_arc (VALUE self,
              VALUE cx, VALUE cy,
              VALUE radius,
              VALUE angle1,
              VALUE angle2)
{
  cairo_arc (_SELF, NUM2DBL (cx), NUM2DBL (cy), NUM2DBL (radius),
             NUM2DBL (angle1), NUM2DBL (angle2));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_arc_negative (VALUE self,
                       VALUE cx, VALUE cy,
                       VALUE radius,
                       VALUE angle1,
                       VALUE angle2)
{
  cairo_arc_negative (_SELF, NUM2DBL (cx), NUM2DBL (cy), NUM2DBL (radius),
                      NUM2DBL (angle1), NUM2DBL (angle2));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_rel_move_to (VALUE self,
                      VALUE x, VALUE y)
{
  cairo_rel_move_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_rel_line_to (VALUE self,
                      VALUE x, VALUE y)
{
  cairo_rel_line_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_rel_curve_to (VALUE self,
                       VALUE x1, VALUE y1,
                       VALUE x2, VALUE y2,
                       VALUE x3, VALUE y3)
{
  cairo_rel_curve_to (_SELF, NUM2DBL (x1), NUM2DBL (y1),
                      NUM2DBL (x2), NUM2DBL (y2), NUM2DBL (x3), NUM2DBL (y3));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_rectangle (VALUE self,
                    VALUE x, VALUE y,
                    VALUE width, VALUE height)
{
  cairo_rectangle (_SELF, NUM2DBL (x), NUM2DBL (y),
                   NUM2DBL (width), NUM2DBL (height));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_close_path (VALUE self)
{
  cairo_close_path (_SELF);
  check_context_status (_SELF);
  return self;
}




static    VALUE
rb_cairo_stroke (VALUE self)
{
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  cairo_stroke (_SELF);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_fill (VALUE self)
{
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  cairo_fill (_SELF);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_copy_page (VALUE self)
{
  cairo_copy_page (_SELF);
  check_context_status (_SELF);
  return self;
}


static    VALUE
rb_cairo_show_page (VALUE self)
{
  cairo_show_page (_SELF);
  check_context_status (_SELF);
  return self;
}

/* Insideness testing */

static    VALUE
rb_cairo_in_fill (VALUE self,
                  VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  return cairo_in_fill (_SELF, NUM2DBL (x), NUM2DBL (y))
         ? Qtrue : Qfalse;
}

static    VALUE
rb_cairo_in_stroke (VALUE self,
                    VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  return cairo_in_stroke (_SELF, NUM2DBL (x), NUM2DBL (y))
         ? Qtrue : Qfalse;
}

/* Rectangular extents */

static    VALUE
rb_cairo_stroke_extents (VALUE self)
{
  double    extents[4];
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  cairo_stroke_extents (_SELF,
                        extents,     extents + 1,
                        extents + 2, extents + 3);
  return float_array (extents, 4);
}

static    VALUE
rb_cairo_fill_extents (VALUE self)
{
  double    extents[4];
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  cairo_fill_extents (_SELF,
                      extents,     extents + 1,
                      extents + 2, extents + 3);
  return float_array (extents, 4);
}

/* Clipping */

static    VALUE
rb_cairo_init_clip (VALUE self)
{
  cairo_init_clip (_SELF);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_clip (VALUE self)
{
  cairo_clip (_SELF);
  check_context_status (_SELF);
  return self;
}

/* Font/Text functions */

/* The "toy" text api */

static   VALUE
rb_cairo_select_font (VALUE self,
                      VALUE familiy,
                      VALUE slant_v,
                      VALUE weight_v)
{
  int slant  = NUM2INT (slant_v);
  int weight = NUM2INT (weight_v);

  if (slant < CAIRO_FONT_SLANT_NORMAL ||
      slant > CAIRO_FONT_SLANT_OBLIQUE)
    {
      rb_raise (rb_eArgError, "invalid font slant");
    }

  if (weight < CAIRO_FONT_WEIGHT_NORMAL ||
      weight > CAIRO_FONT_WEIGHT_BOLD)
    {
      rb_raise (rb_eArgError, "invalid font weight");
    }
 

  cairo_select_font (_SELF,
                     STR2CSTR (familiy),
                     slant,
                     weight);
  return self;
}

static   VALUE
rb_cairo_scale_font  (VALUE self,
                      VALUE scale)
{
  cairo_scale_font (_SELF,
                    NUM2DBL (scale));
  return self;
}

static   VALUE
rb_cairo_transform_font  (VALUE self,
                          VALUE matrix)
{
  cairo_transform_font (_SELF,
                        rb_v_to_cairo_matrix_t (matrix));
  return self;
}

static    VALUE
rb_cairo_show_text (VALUE self,
                    VALUE utf8)
{
  cairo_show_text (_SELF,
                   STR2CSTR (utf8));
  return self;
}

static    VALUE
rb_cairo_show_glyphs (VALUE self,
                      VALUE glyphs_v)
{
  int            i;
  int            count;
  cairo_glyph_t *glyphs;

  if (!rb_obj_is_kind_of (glyphs_v, rb_cArray))
     rb_raise (rb_eTypeError, "expected array");
    

  count  = RARRAY(glyphs_v)->len;
  glyphs = malloc (sizeof (cairo_glyph_t) * count);

  if (!glyphs)
     rb_raise (rb_eNoMemError, "unable to allocate memory for text extents");

  for (i=0; i< count; i++)
    {
      memcpy ( (char *) &glyphs[i],
               (char *) DATA_PTR (rb_ary_entry (glyphs_v, i)),
               sizeof (cairo_glyph_t));
    }

  cairo_show_glyphs (_SELF, glyphs, count);

  free (glyphs);
                     
  return self;
}

static    VALUE
rb_cairo_current_font (VALUE self)
{
  cairo_font_t *xform;
  xform = cairo_current_font (_SELF);
  if (xform)
    {
      if (cairo_status (_SELF))
        {
          rb_free_font (xform);
          raise_cairo_exception (cairo_status (_SELF),
                                 cairo_status_string (_SELF));
        }
      return Data_Wrap_Struct (rb_cCairo_Font, NULL, rb_free_font, xform);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to get current font");
      return Qundef;
    }
}

static    VALUE
rb_cairo_current_font_extents (VALUE self)
{
  return Qnil;
}

static    VALUE
rb_cairo_set_font (VALUE self,
                   VALUE xform)
{
  cairo_set_font (_SELF, value_to_font (xform));
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_text_extents (VALUE self,
                       VALUE utf8)
{
  cairo_text_extents_t *xform;

  xform = ALLOC (cairo_text_extents_t);
  if (xform)
    {
      cairo_text_extents (_SELF, STR2CSTR(utf8),xform);
      if (cairo_status (_SELF))
        {
          rb_free_font (xform);
          raise_cairo_exception (cairo_status (_SELF),
                                 cairo_status_string (_SELF));
        }
      return Data_Wrap_Struct (rb_cCairo_TextExtents, NULL, rb_free_text_extents, xform);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate memory for text extents");
      return Qundef;
    }
}

static    VALUE
rb_cairo_glyph_extents (VALUE self,
                        VALUE glyphs_v)
{
  int                   i;
  int                   count;
  cairo_glyph_t        *glyphs;
  cairo_text_extents_t *xform;

  if (!rb_obj_is_kind_of (glyphs_v, rb_cArray))
     rb_raise (rb_eTypeError, "expected array");
    

  count  = RARRAY(glyphs_v)->len;
  glyphs = malloc (sizeof (cairo_glyph_t) * count);

  if (!glyphs)
     rb_raise (rb_eNoMemError, "unable to allocate memory for text extents");

  for (i=0; i< count; i++)
    {
      memcpy ( (char *) &glyphs[i],
               (char *) DATA_PTR (rb_ary_entry (glyphs_v, i)),
               sizeof (cairo_glyph_t));
    }

  xform = ALLOC (cairo_text_extents_t);

  if (xform)
    {
      cairo_glyph_extents (_SELF, glyphs, count, xform);
      if (cairo_status (_SELF))
        {
          rb_free_font (xform);
          raise_cairo_exception (cairo_status (_SELF),
                                 cairo_status_string (_SELF));
        }
      free (glyphs);
      return Data_Wrap_Struct (rb_cCairo_TextExtents, NULL, rb_free_text_extents, xform);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to allocate memory for text extents");
      free (glyphs);
      return Qundef;
    }
}

static    VALUE
rb_cairo_text_path (VALUE self,
                    VALUE utf8)
{
  cairo_text_path (_SELF,
                   STR2CSTR (utf8));
  return self;
}

static    VALUE
rb_cairo_glyph_path (VALUE self,
                     VALUE glyphs_v)
{
  int            i;
  int            count;
  cairo_glyph_t *glyphs;

  if (!rb_obj_is_kind_of (glyphs_v, rb_cArray))
     rb_raise (rb_eTypeError, "expected array");
    

  count  = RARRAY(glyphs_v)->len;
  glyphs = malloc (sizeof (cairo_glyph_t) * count);

  if (!glyphs)
     rb_raise (rb_eNoMemError, "unable to allocate memory for text extents");

  for (i=0; i< count; i++)
    {
      memcpy ( (char *) &glyphs[i],
               (char *) DATA_PTR (rb_ary_entry (glyphs_v, i)),
               sizeof (cairo_glyph_t));
    }

  cairo_glyph_path (_SELF, glyphs, count);

  free (glyphs);
  return self;
}


/* Image functions */

static    VALUE
rb_cairo_show_surface (VALUE self,
                       VALUE surface,
                       VALUE width, VALUE height)
{
  cairo_show_surface (_SELF, rb_v_to_cairo_surface_t (surface),
                      NUM2INT (width), NUM2INT (height));
  check_context_status (_SELF);
  return self;
}

/* Query functions */

static    VALUE
rb_cairo_current_operator (VALUE self)
{
  cairo_operator_t op;
  op = cairo_current_operator (_SELF);
  return INT2FIX (op);
}

static    VALUE
rb_cairo_current_rgb_color (VALUE self)
{
  double    rgb[3];
  cairo_current_rgb_color (_SELF,
                           rgb, rgb + 1, rgb + 2);
  return float_array (rgb, 3);
}

static    VALUE
rb_cairo_current_pattern (VALUE self)
{
  return rb_cairo_pattern_wrap (cairo_current_pattern (_SELF));
}

static    VALUE
rb_cairo_current_alpha (VALUE self)
{
  double    alpha;
  alpha = cairo_current_alpha (_SELF);
  return rb_float_new (alpha);
}

static    VALUE
rb_cairo_current_tolerance (VALUE self)
{
  double    tolerance;
  tolerance = cairo_current_tolerance (_SELF);
  return rb_float_new (tolerance);
}

static    VALUE
rb_cairo_current_point (VALUE self)
{
  double    point[2];
  cairo_current_point (_SELF, point, point + 1);
  return float_array (point, 2);
}

static    VALUE
rb_cairo_current_fill_rule (VALUE self)
{
  cairo_fill_rule_t rule;
  rule = cairo_current_fill_rule (_SELF);
  return INT2FIX (rule);
}

static    VALUE
rb_cairo_current_line_width (VALUE self)
{
  double    line_width;
  line_width = cairo_current_line_width (_SELF);
  return rb_float_new (line_width);
}

static    VALUE
rb_cairo_current_line_cap (VALUE self)
{
  cairo_line_cap_t cap;
  cap = cairo_current_line_cap (_SELF);
  return INT2FIX (cap);
}

static    VALUE
rb_cairo_current_line_join (VALUE self)
{
  cairo_line_join_t join;
  join = cairo_current_line_join (_SELF);
  return INT2FIX (join);
}

static    VALUE
rb_cairo_current_miter_limit (VALUE self)
{
  double    miter_limit;
  miter_limit = cairo_current_miter_limit (_SELF);
  return rb_float_new (miter_limit);
}

static    VALUE
rb_cairo_current_matrix (VALUE self)
{
  cairo_matrix_t *matrix = cairo_matrix_create ();
  if (matrix)
    {
      cairo_current_matrix (_SELF, matrix);
      if (cairo_status (_SELF))
        {
          rb_free_matrix (matrix);
          raise_cairo_exception (cairo_status (_SELF),
                                 cairo_status_string (_SELF));
        }
      return rb_cairo_matrix_wrap (matrix);
    }
  else
    {
      rb_raise (rb_eNoMemError, "out of memory");
      return Qundef;
    }
}


static    VALUE
rb_cairo_current_target_surface (VALUE self)
{
  cairo_surface_t *surface;
  surface = cairo_current_target_surface (_SELF);
  if (surface)
    {
      cairo_surface_reference (surface);
      return Data_Wrap_Struct (rb_cCairo_Surface, NULL, rb_free_surface,
                               surface);
    }
  else
    {
      return Qnil;
    }
}

static    VALUE
symbol (const char *name,
        VALUE      *cache)
{
  if (NIL_P (*cache))
    {
      *cache = ID2SYM (rb_intern (name));
    }
  return *cache;
}

static void
push_move_to (void  *closure,
              double x, double y)
{
  static VALUE move_to = Qnil;
  VALUE     array = (VALUE) closure;
  rb_ary_push (array,
               rb_ary_new3 (3,
                            symbol ("move_to", &move_to),
                            rb_float_new (x), rb_float_new (y)));
}

static void
push_line_to (void   *closure,
              double   x, double y)
{
  static VALUE line_to = Qnil;
  VALUE     array = (VALUE) closure;
  rb_ary_push (array,
               rb_ary_new3 (3,
                            symbol ("line_to", &line_to),
                            rb_float_new (x), rb_float_new (y)));
}

static void
push_curve_to (void   *closure,
               double   x1, double y1,
               double   x2, double y2,
               double   x3, double y3)
{
  static VALUE curve_to = Qnil;
  VALUE     array = (VALUE) closure;
  rb_ary_push (array,
               rb_ary_new3 (7,
                            symbol ("curve_to", &curve_to),
                            rb_float_new (x1), rb_float_new (y1),
                            rb_float_new (x2), rb_float_new (y2),
                            rb_float_new (x3), rb_float_new (y3)));
}

static void
push_close_path (void *closure)
{
  static VALUE close_path = Qnil;
  VALUE     array = (VALUE) closure;
  rb_ary_push (array, rb_ary_new3 (1, symbol ("close_path", &close_path)));
}

static    VALUE
rb_cairo_current_path_array (VALUE self)
{
  VALUE     array;
  array = rb_ary_new ();

  cairo_current_path (_SELF,
                      &push_move_to,
                      &push_line_to,
                      &push_curve_to, &push_close_path, (void *) array);

  return array;
}

static    VALUE
rb_cairo_current_path_flat_array (VALUE self)
{
  VALUE     array;
  array = rb_ary_new ();

  cairo_current_path_flat (_SELF,
                           &push_move_to,
                           &push_line_to, &push_close_path, (void *) array);

  return array;
}

void
Init_cairo_context (void)
{
  rb_cCairo_Context =
    rb_define_class_under (rb_mCairo, "Context", rb_cObject);

  rb_define_singleton_method (rb_cCairo_Context, "new",
                              RUBY_METHOD_FUNC (rb_cairo_new), 0);

  rb_define_method (rb_cCairo_Context, "save",
                    RUBY_METHOD_FUNC (rb_cairo_save), 0);
  rb_define_method (rb_cCairo_Context, "restore",
                    RUBY_METHOD_FUNC (rb_cairo_restore), 0);
  rb_define_method (rb_cCairo_Context, "copy",
                    RUBY_METHOD_FUNC (rb_cairo_copy), 1);

  rb_define_method (rb_cCairo_Context, "set_target_surface",
                    RUBY_METHOD_FUNC (rb_cairo_set_target_surface), 1);
  rb_define_method (rb_cCairo_Context, "set_operator",
                    RUBY_METHOD_FUNC (rb_cairo_set_operator), 1);
  rb_define_method (rb_cCairo_Context, "set_rgb_color",
                    RUBY_METHOD_FUNC (rb_cairo_set_rgb_color), 3);
  rb_define_method (rb_cCairo_Context, "set_pattern",
                    RUBY_METHOD_FUNC (rb_cairo_set_pattern), 1);
  rb_define_method (rb_cCairo_Context, "set_alpha",
                    RUBY_METHOD_FUNC (rb_cairo_set_alpha), 1);
  rb_define_method (rb_cCairo_Context, "set_tolerance",
                    RUBY_METHOD_FUNC (rb_cairo_set_tolerance), 1);
  rb_define_method (rb_cCairo_Context, "set_fill_rule",
                    RUBY_METHOD_FUNC (rb_cairo_set_fill_rule), 1);
  rb_define_method (rb_cCairo_Context, "set_line_width",
                    RUBY_METHOD_FUNC (rb_cairo_set_line_width), 1);
  rb_define_method (rb_cCairo_Context, "set_line_cap",
                    RUBY_METHOD_FUNC (rb_cairo_set_line_cap), 1);
  rb_define_method (rb_cCairo_Context, "set_line_join",
                    RUBY_METHOD_FUNC (rb_cairo_set_line_join), 1);
  rb_define_method (rb_cCairo_Context, "set_dash",
                    RUBY_METHOD_FUNC (rb_cairo_set_dash), 2);
  rb_define_method (rb_cCairo_Context, "set_miter_limit",
                    RUBY_METHOD_FUNC (rb_cairo_set_miter_limit), 1);
  rb_define_method (rb_cCairo_Context, "translate",
                    RUBY_METHOD_FUNC (rb_cairo_translate), 2);
  rb_define_method (rb_cCairo_Context, "scale",
                    RUBY_METHOD_FUNC (rb_cairo_scale), 2);
  rb_define_method (rb_cCairo_Context, "rotate",
                    RUBY_METHOD_FUNC (rb_cairo_rotate), 1);
  rb_define_method (rb_cCairo_Context, "concat_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_concat_matrix), 1);
  rb_define_method (rb_cCairo_Context, "set_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_set_matrix), 1);
  rb_define_method (rb_cCairo_Context, "default_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_default_matrix), 1);
  rb_define_method (rb_cCairo_Context, "identity_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_identity_matrix), 1);
  rb_define_method (rb_cCairo_Context, "transform_point",
                    RUBY_METHOD_FUNC (rb_cairo_transform_point), 2);
  rb_define_method (rb_cCairo_Context, "transform_distance",
                    RUBY_METHOD_FUNC (rb_cairo_transform_distance), 2);
  rb_define_method (rb_cCairo_Context, "inverse_transform_point",
                    RUBY_METHOD_FUNC (rb_cairo_inverse_transform_point), 2);
  rb_define_method (rb_cCairo_Context, "inverse_transform_distance",
                    RUBY_METHOD_FUNC (rb_cairo_inverse_transform_distance),
                    2);

  /* path creation functions */
  
  rb_define_method (rb_cCairo_Context, "new_path",
                    RUBY_METHOD_FUNC (rb_cairo_new_path), 0);
  rb_define_method (rb_cCairo_Context, "move_to",
                    RUBY_METHOD_FUNC (rb_cairo_move_to), 2);
  rb_define_method (rb_cCairo_Context, "line_to",
                    RUBY_METHOD_FUNC (rb_cairo_line_to), 2);
  rb_define_method (rb_cCairo_Context, "curve_to",
                    RUBY_METHOD_FUNC (rb_cairo_curve_to), 6);
  rb_define_method (rb_cCairo_Context, "arc", RUBY_METHOD_FUNC (rb_cairo_arc),
                    5);
  rb_define_method (rb_cCairo_Context, "arc_negative",
                    RUBY_METHOD_FUNC (rb_cairo_arc_negative), 5);
  rb_define_method (rb_cCairo_Context, "rel_move_to",
                    RUBY_METHOD_FUNC (rb_cairo_rel_move_to), 2);
  rb_define_method (rb_cCairo_Context, "rel_line_to",
                    RUBY_METHOD_FUNC (rb_cairo_rel_line_to), 2);
  rb_define_method (rb_cCairo_Context, "rel_curve_to",
                    RUBY_METHOD_FUNC (rb_cairo_rel_curve_to), 6);
  rb_define_method (rb_cCairo_Context, "rectangle",
                    RUBY_METHOD_FUNC (rb_cairo_rectangle), 4);
  rb_define_method (rb_cCairo_Context, "close_path",
                    RUBY_METHOD_FUNC (rb_cairo_close_path), 0);


  
  rb_define_method (rb_cCairo_Context, "stroke",
                    RUBY_METHOD_FUNC (rb_cairo_stroke), 0);
  rb_define_method (rb_cCairo_Context, "fill",
                    RUBY_METHOD_FUNC (rb_cairo_fill), 0);


  rb_define_method (rb_cCairo_Context, "copy_page",
                    RUBY_METHOD_FUNC (rb_cairo_copy_page), 0);
  rb_define_method (rb_cCairo_Context, "show_page",
                    RUBY_METHOD_FUNC (rb_cairo_show_page), 0);
  rb_define_method (rb_cCairo_Context, "in_fill",
                    RUBY_METHOD_FUNC (rb_cairo_in_fill), 2);
  rb_define_method (rb_cCairo_Context, "in_stroke",
                    RUBY_METHOD_FUNC (rb_cairo_in_stroke), 2);
  rb_define_method (rb_cCairo_Context, "fill_extents",
                    RUBY_METHOD_FUNC (rb_cairo_fill_extents), 0);
  rb_define_method (rb_cCairo_Context, "stroke_extents",
                    RUBY_METHOD_FUNC (rb_cairo_stroke_extents), 0);

  rb_define_method (rb_cCairo_Context, "init_clip",
                    RUBY_METHOD_FUNC (rb_cairo_init_clip), 0);
  rb_define_method (rb_cCairo_Context, "clip",
                    RUBY_METHOD_FUNC (rb_cairo_clip), 0);

  rb_define_method (rb_cCairo_Context, "show_surface",
                    RUBY_METHOD_FUNC (rb_cairo_show_surface), 3);

  rb_define_method (rb_cCairo_Context, "current_operator",
                    RUBY_METHOD_FUNC (rb_cairo_current_operator), 0);
  rb_define_method (rb_cCairo_Context, "current_rgb_color",
                    RUBY_METHOD_FUNC (rb_cairo_current_rgb_color), 0);
  rb_define_method (rb_cCairo_Context, "current_pattern",
                    RUBY_METHOD_FUNC (rb_cairo_current_pattern), 0);
  rb_define_method (rb_cCairo_Context, "current_alpha",
                    RUBY_METHOD_FUNC (rb_cairo_current_alpha), 0);
  rb_define_method (rb_cCairo_Context, "current_tolerance",
                    RUBY_METHOD_FUNC (rb_cairo_current_tolerance), 0);
  rb_define_method (rb_cCairo_Context, "current_point",
                    RUBY_METHOD_FUNC (rb_cairo_current_point), 0);
  rb_define_method (rb_cCairo_Context, "current_fill_rule",
                    RUBY_METHOD_FUNC (rb_cairo_current_fill_rule), 0);
  rb_define_method (rb_cCairo_Context, "current_line_width",
                    RUBY_METHOD_FUNC (rb_cairo_current_line_width), 0);
  rb_define_method (rb_cCairo_Context, "current_line_cap",
                    RUBY_METHOD_FUNC (rb_cairo_current_line_cap), 0);
  rb_define_method (rb_cCairo_Context, "current_line_join",
                    RUBY_METHOD_FUNC (rb_cairo_current_line_join), 0);
  rb_define_method (rb_cCairo_Context, "current_miter_limit",
                    RUBY_METHOD_FUNC (rb_cairo_current_miter_limit), 0);
  rb_define_method (rb_cCairo_Context, "current_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_current_matrix), 0);


  rb_define_method (rb_cCairo_Context, "select_font",
                    RUBY_METHOD_FUNC (rb_cairo_select_font), 3);
  rb_define_method (rb_cCairo_Context, "scale_font",
                    RUBY_METHOD_FUNC (rb_cairo_scale_font), 1);
  rb_define_method (rb_cCairo_Context, "transform_font",
                    RUBY_METHOD_FUNC (rb_cairo_transform_font), 1);
  rb_define_method (rb_cCairo_Context, "show_text",
                    RUBY_METHOD_FUNC (rb_cairo_show_text), 1);
  rb_define_method (rb_cCairo_Context, "show_glyphs",
                    RUBY_METHOD_FUNC (rb_cairo_show_glyphs), 1);
  rb_define_method (rb_cCairo_Context, "current_font",
                    RUBY_METHOD_FUNC (rb_cairo_current_font), 0);
  rb_define_method (rb_cCairo_Context, "current_font_extents",
                    RUBY_METHOD_FUNC (rb_cairo_current_font_extents), 0);
  rb_define_method (rb_cCairo_Context, "set_font",
                    RUBY_METHOD_FUNC (rb_cairo_set_font), 1);
  rb_define_method (rb_cCairo_Context, "text_extents",
                    RUBY_METHOD_FUNC (rb_cairo_text_extents), 1);
  rb_define_method (rb_cCairo_Context, "glpyh_extents",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_extents), 1);
  rb_define_method (rb_cCairo_Context, "text_path",
                    RUBY_METHOD_FUNC (rb_cairo_text_path), 1);
  rb_define_method (rb_cCairo_Context, "glyph_path",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_path), 1);
  rb_define_method (rb_cCairo_Context, "current_target_surface",
                    RUBY_METHOD_FUNC (rb_cairo_current_target_surface), 0);
  rb_define_method (rb_cCairo_Context, "current_path_array",
                    RUBY_METHOD_FUNC (rb_cairo_current_path_array), 0);
  rb_define_method (rb_cCairo_Context, "current_path_flat_array",
                    RUBY_METHOD_FUNC (rb_cairo_current_path_flat_array), 0);
}


