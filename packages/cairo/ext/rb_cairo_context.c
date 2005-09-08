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
      rb_cairo_raise_exception (status);
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
rb_cairo_new (VALUE klass,
              VALUE target_v)
{
  cairo_surface_t *target;
  cairo_t         *cr;

  target = rb_v_to_cairo_surface_t (target_v);
  cr     = cairo_create (target);

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
rb_cairo_set_source_rgb (VALUE self,
                         VALUE red,
                         VALUE green,
                         VALUE blue)
{
  cairo_set_source_rgb (_SELF,
                        NUM2DBL (red),
                        NUM2DBL (green),
                        NUM2DBL (blue));
  return self;
}

static    VALUE
rb_cairo_set_source_rgba (VALUE self,
                          VALUE red_v,
                          VALUE green_v,
                          VALUE blue_v,
                          VALUE alpha_v)
{
  cairo_set_source_rgba (_SELF,
                         NUM2DBL (red_v),
                         NUM2DBL (green_v),
                         NUM2DBL (blue_v),
                         NUM2DBL (alpha_v));
  return self;
}

static    VALUE
rb_cairo_set_source_surface (VALUE self,
                             VALUE surface_v,
                             VALUE width_v,
                             VALUE height_v)
{
  cairo_surface_t *surface = rb_v_to_cairo_surface_t (surface_v);
  int              width  = NUM2INT (width_v);
  int              height = NUM2INT (height_v);
  cairo_set_source_surface (_SELF, surface, width, height);
  check_context_status (_SELF);
  return self;
}

static    VALUE
rb_cairo_set_source (VALUE self,
                     VALUE pattern_v)
{
  cairo_pattern_t *pattern;
  pattern = rb_v_to_cairo_pattern_t (pattern_v);

  cairo_set_source (_SELF, pattern);
  check_context_status (_SELF);
  return self;
}


static    VALUE
rb_cairo_get_source (VALUE self)
{
  cairo_pattern_t *pattern;
  pattern = cairo_get_source (_SELF);
  return rb_cairo_pattern_wrap  (pattern);
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
rb_cairo_transform (VALUE self,
                    VALUE xform)
{
  cairo_transform (_SELF, rb_v_to_cairo_matrix_t (xform));
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
rb_cairo_identity_matrix (VALUE self)
{
  cairo_identity_matrix (_SELF);
  return self;
}

static    VALUE
rb_cairo_user_to_device (VALUE self,
                         VALUE x, VALUE y)
{
  double    pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_user_to_device (_SELF, pair, pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_user_to_device_distance (VALUE self,
                                  VALUE dx, VALUE dy)
{
  double    pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_user_to_device_distance (_SELF, pair, pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_device_to_user (VALUE self,
                         VALUE x, VALUE y)
{
  double    pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_device_to_user (_SELF, pair, pair + 1);
  return float_array (pair, 2);
}

static    VALUE
rb_cairo_device_to_user_distance (VALUE self,
                                  VALUE dx, VALUE dy)
{
  double    pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_device_to_user_distance (_SELF, pair, pair + 1);
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
rb_cairo_stroke_preserve (VALUE self)
{
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  cairo_stroke_preserve (_SELF);
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
rb_cairo_fill_preserve (VALUE self)
{
  if (rb_block_given_p ())
    {
      cairo_new_path (_SELF);
      rb_yield (Qnil);
    }
  cairo_fill_preserve (_SELF);
  check_context_status (_SELF);
  return self;
}

static VALUE
rb_cairo_paint (VALUE self)
{
  cairo_paint (_SELF);
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
rb_cairo_reset_clip (VALUE self)
{
  cairo_reset_clip (_SELF);
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
rb_cairo_select_font_face (VALUE self,
                           VALUE family,
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
 

  cairo_select_font_face (_SELF,
                          STR2CSTR (family),
                          slant,
                          weight);
  return self;
}

static   VALUE
rb_cairo_set_font_size (VALUE self,
                        VALUE scale)
{
  cairo_set_font_size (_SELF,
                       NUM2DBL (scale));
  return self;
}

static   VALUE
rb_cairo_set_font_matrix (VALUE self,
                          VALUE matrix)
{
  cairo_set_font_matrix (_SELF,
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
rb_cairo_get_font_face (VALUE self)
{
  cairo_font_face_t *xform;
  xform = cairo_get_font_face (_SELF);
  if (xform)
    {
      if (cairo_status (_SELF))
        {
          rb_free_font_face (xform);
          rb_cairo_raise_exception (cairo_status (_SELF));
        }
      return Data_Wrap_Struct (rb_cCairo_FontFace, NULL, rb_free_font_face, xform);
    }
  else
    {
      rb_raise (rb_eNoMemError, "unable to get current font face");
      return Qundef;
    }
}

static    VALUE
rb_cairo_set_font_face (VALUE self,
                        VALUE xform)
{
  cairo_set_font_face (_SELF,
                       value_to_font_face (xform));
  check_context_status (_SELF);
  return self;
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


/* Query functions */

static    VALUE
rb_cairo_get_operator (VALUE self)
{
  cairo_operator_t op;
  op = cairo_get_operator (_SELF);
  return INT2FIX (op);
}


static    VALUE
rb_cairo_get_tolerance (VALUE self)
{
  double    tolerance;
  tolerance = cairo_get_tolerance (_SELF);
  return rb_float_new (tolerance);
}

static    VALUE
rb_cairo_get_current_point (VALUE self)
{
  double    point[2];
  cairo_get_current_point (_SELF, point, point + 1);
  return float_array (point, 2);
}

static    VALUE
rb_cairo_get_fill_rule (VALUE self)
{
  cairo_fill_rule_t rule;
  rule = cairo_get_fill_rule (_SELF);
  return INT2FIX (rule);
}

static    VALUE
rb_cairo_get_line_width (VALUE self)
{
  double    line_width;
  line_width = cairo_get_line_width (_SELF);
  return rb_float_new (line_width);
}

static    VALUE
rb_cairo_get_line_cap (VALUE self)
{
  cairo_line_cap_t cap;
  cap = cairo_get_line_cap (_SELF);
  return INT2FIX (cap);
}

static    VALUE
rb_cairo_get_line_join (VALUE self)
{
  cairo_line_join_t join;
  join = cairo_get_line_join (_SELF);
  return INT2FIX (join);
}

static    VALUE
rb_cairo_get_miter_limit (VALUE self)
{
  double    miter_limit;
  miter_limit = cairo_get_miter_limit (_SELF);
  return rb_float_new (miter_limit);
}

static    VALUE
rb_cairo_get_matrix (VALUE self)
{
  cairo_matrix_t *matrix = malloc (sizeof (cairo_matrix_t));
  if (matrix)
    {
      cairo_get_matrix (_SELF, matrix);
      if (cairo_status (_SELF))
        {
          rb_free_matrix (matrix);
          rb_cairo_raise_exception (cairo_status (_SELF));
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
rb_cairo_get_target (VALUE self)
{
  cairo_surface_t *surface;
  surface = cairo_get_target (_SELF);
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

void
Init_cairo_context (void)
{
  rb_cCairo_Context =
    rb_define_class_under (rb_mCairo, "Context", rb_cObject);

  rb_define_singleton_method (rb_cCairo_Context, "new",
                              RUBY_METHOD_FUNC (rb_cairo_new), 1);

  rb_define_method (rb_cCairo_Context, "save",
                    RUBY_METHOD_FUNC (rb_cairo_save), 0);
  rb_define_method (rb_cCairo_Context, "restore",
                    RUBY_METHOD_FUNC (rb_cairo_restore), 0);

  rb_define_method (rb_cCairo_Context, "set_operator",
                    RUBY_METHOD_FUNC (rb_cairo_set_operator), 1);
  rb_define_method (rb_cCairo_Context, "set_source_rgb",
                    RUBY_METHOD_FUNC (rb_cairo_set_source_rgb), 3);
  rb_define_method (rb_cCairo_Context, "set_source_rgba",
                    RUBY_METHOD_FUNC (rb_cairo_set_source_rgba), 4);
  rb_define_method (rb_cCairo_Context, "set_source",
                    RUBY_METHOD_FUNC (rb_cairo_set_source), 1);
  rb_define_method (rb_cCairo_Context, "set_source_surface",
                    RUBY_METHOD_FUNC (rb_cairo_set_source_surface), 3);
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
  rb_define_method (rb_cCairo_Context, "transform",
                    RUBY_METHOD_FUNC (rb_cairo_transform), 1);
  rb_define_method (rb_cCairo_Context, "set_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_set_matrix), 1);
  rb_define_method (rb_cCairo_Context, "identity_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_identity_matrix), 1);
  rb_define_method (rb_cCairo_Context, "user_to_device",
                    RUBY_METHOD_FUNC (rb_cairo_user_to_device), 2);
  rb_define_method (rb_cCairo_Context, "user_to_device_distance",
                    RUBY_METHOD_FUNC (rb_cairo_user_to_device_distance), 2);
  rb_define_method (rb_cCairo_Context, "device_to_user",
                    RUBY_METHOD_FUNC (rb_cairo_device_to_user), 2);
  rb_define_method (rb_cCairo_Context, "device_to_user_distance",
                    RUBY_METHOD_FUNC (rb_cairo_device_to_user_distance), 2);

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


  rb_define_method (rb_cCairo_Context, "paint",
                    RUBY_METHOD_FUNC (rb_cairo_paint), 0);
  
  rb_define_method (rb_cCairo_Context, "stroke",
                    RUBY_METHOD_FUNC (rb_cairo_stroke), 0);
  rb_define_method (rb_cCairo_Context, "fill",
                    RUBY_METHOD_FUNC (rb_cairo_fill), 0);

  rb_define_method (rb_cCairo_Context, "stroke_preserve",
                    RUBY_METHOD_FUNC (rb_cairo_stroke_preserve), 0);
  rb_define_method (rb_cCairo_Context, "fill_preserve",
                    RUBY_METHOD_FUNC (rb_cairo_fill_preserve), 0);

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

  rb_define_method (rb_cCairo_Context, "reset_clip",
                    RUBY_METHOD_FUNC (rb_cairo_reset_clip), 0);
  rb_define_method (rb_cCairo_Context, "clip",
                    RUBY_METHOD_FUNC (rb_cairo_clip), 0);


  rb_define_method (rb_cCairo_Context, "get_operator",
                    RUBY_METHOD_FUNC (rb_cairo_get_operator), 0);
  rb_define_method (rb_cCairo_Context, "get_source",
                    RUBY_METHOD_FUNC (rb_cairo_get_source), 0);
  rb_define_method (rb_cCairo_Context, "get_tolerance",
                    RUBY_METHOD_FUNC (rb_cairo_get_tolerance), 0);
  rb_define_method (rb_cCairo_Context, "get_current_point",
                    RUBY_METHOD_FUNC (rb_cairo_get_current_point), 0);
  rb_define_method (rb_cCairo_Context, "get_fill_rule",
                    RUBY_METHOD_FUNC (rb_cairo_get_fill_rule), 0);
  rb_define_method (rb_cCairo_Context, "get_line_width",
                    RUBY_METHOD_FUNC (rb_cairo_get_line_width), 0);
  rb_define_method (rb_cCairo_Context, "get_line_cap",
                    RUBY_METHOD_FUNC (rb_cairo_get_line_cap), 0);
  rb_define_method (rb_cCairo_Context, "get_line_join",
                    RUBY_METHOD_FUNC (rb_cairo_get_line_join), 0);
  rb_define_method (rb_cCairo_Context, "get_miter_limit",
                    RUBY_METHOD_FUNC (rb_cairo_get_miter_limit), 0);
  rb_define_method (rb_cCairo_Context, "get_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_get_matrix), 0);


  rb_define_method (rb_cCairo_Context, "get_font_face",
                    RUBY_METHOD_FUNC (rb_cairo_get_font_face), 0);
  rb_define_method (rb_cCairo_Context, "select_font_face",
                    RUBY_METHOD_FUNC (rb_cairo_select_font_face), 3);
  rb_define_method (rb_cCairo_Context, "set_font_face",
                    RUBY_METHOD_FUNC (rb_cairo_set_font_face), 1);
  rb_define_method (rb_cCairo_Context, "set_font_size",
                    RUBY_METHOD_FUNC (rb_cairo_set_font_size), 1);
  rb_define_method (rb_cCairo_Context, "set_font_matrix",
                    RUBY_METHOD_FUNC (rb_cairo_set_font_matrix), 1);
  rb_define_method (rb_cCairo_Context, "show_text",
                    RUBY_METHOD_FUNC (rb_cairo_show_text), 1);
  rb_define_method (rb_cCairo_Context, "show_glyphs",
                    RUBY_METHOD_FUNC (rb_cairo_show_glyphs), 1);
  rb_define_method (rb_cCairo_Context, "text_path",
                    RUBY_METHOD_FUNC (rb_cairo_text_path), 1);
  rb_define_method (rb_cCairo_Context, "glyph_path",
                    RUBY_METHOD_FUNC (rb_cairo_glyph_path), 1);
  rb_define_method (rb_cCairo_Context, "get_target",
                    RUBY_METHOD_FUNC (rb_cairo_get_target), 0);
}


