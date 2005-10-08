/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
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

VALUE rb_cCairo_Context;

#define _SELF  (RVAL2CRCONTEXT(self))

static VALUE
float_array (double *values, unsigned count)
{
  VALUE result;
  int i;

  result = rb_ary_new2 (count);
  for (i = 0; i < count; i++)
    {
      rb_ary_push (result, rb_float_new (values[i]));
    }
  return result;
}

static void
glyphs_to_array (VALUE rb_array, cairo_glyph_t **glyphs, int *length)
{
  int i;
  
  if (!rb_obj_is_kind_of (rb_array, rb_cArray))
     rb_raise (rb_eTypeError, "expected array");

  *length = RARRAY(rb_array)->len;
  *glyphs = ALLOCA_N (cairo_glyph_t, *length);

  if (!*glyphs)
    rb_cairo_raise_exception (CAIRO_STATUS_NO_MEMORY);

  for (i = 0; i < *length; i++)
    {
      memcpy ((char *) &(*glyphs)[i],
              (char *) RVAL2CRGLYPH (rb_ary_entry (rb_array, i)),
              sizeof (cairo_glyph_t));
    }
}

static inline void
cr_check_status (cairo_t *context)
{
  cairo_status_t status;
  status = cairo_status (context);
  if (status)
    {
      rb_cairo_raise_exception (status);
    }
}

/* Functions for manipulating state objects */
cairo_t *
rb_cairo_context_from_ruby_object (VALUE obj)
{
  cairo_t *context;
  if (!RTEST (rb_obj_is_kind_of (obj, rb_cCairo_Context)))
    {
      rb_raise (rb_eTypeError, "not a cairo graphics context");
    }
  Data_Get_Struct (obj, cairo_t, context);
  return context;
}

static void
cr_context_free (void *ptr)
{
  if (ptr)
    {
      cairo_destroy ((cairo_t *) ptr);
    }
}

VALUE
rb_cairo_context_to_ruby_object (cairo_t *cr)
{
  if (cr)
    {
      cairo_reference (cr);
      return Data_Wrap_Struct (rb_cCairo_Context, NULL, cr_context_free, cr);
    }
  else
    {
      return Qnil;
    }
}

static VALUE
cr_allocate (VALUE klass)
{
  return Data_Wrap_Struct (klass, NULL, cr_context_free, NULL);
}

static VALUE
cr_initialize (VALUE self, VALUE rb_target)
{
  cairo_t *cr;

  cr = cairo_create (RVAL2CRSURFACE (rb_target));
  cr_check_status (cr);
  DATA_PTR(self) = cr;
  return Qnil;
}

static VALUE
cr_restore (VALUE self)
{
  cairo_restore (_SELF);
  cr_check_status (_SELF);
  return Qnil;
}

static VALUE
cr_save (VALUE self)
{
  VALUE result = Qnil;
  cairo_save (_SELF);
  cr_check_status (_SELF);
  if (rb_block_given_p ())
    {
      result = rb_ensure (rb_yield, self, cr_restore, self);
    }
  return result;
}

/* Modify state */
static VALUE
cr_set_operator (VALUE self, VALUE rb_op)
{
  int op;
  Check_Type (rb_op, T_FIXNUM);
  op = FIX2INT (rb_op);
  if (op < CAIRO_OPERATOR_CLEAR || op > CAIRO_OPERATOR_SATURATE)
    {
      rb_raise (rb_eArgError, "invalid composition operator");
    }
  cairo_set_operator (_SELF, (cairo_operator_t) op);
  cr_check_status (_SELF);
  return self;
}


static VALUE
cr_set_source_rgb (int argc, VALUE *argv, VALUE self)
{
  VALUE red, green, blue;
  int n;

  n = rb_scan_args(argc, argv, "12", &red, &green, &blue);

  if (n == 1 && RTEST (rb_obj_is_kind_of (red, rb_cArray)))
    {
      VALUE ary = red;
      n = RARRAY (ary)->len;
      if (n >= 3)
        {
          red = rb_ary_entry (ary, 0);
          green = rb_ary_entry (ary, 1);
          blue = rb_ary_entry (ary, 2);
        }
    }

  if (n < 3)
    {
      rb_raise (rb_eArgError, "invalid RGB");
    }
      
  cairo_set_source_rgb (_SELF,
                        NUM2DBL (red),
                        NUM2DBL (green),
                        NUM2DBL (blue));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_source_rgba (int argc, VALUE *argv, VALUE self)
{
  VALUE red, green, blue, alpha;
  int n;

  n = rb_scan_args (argc, argv, "13", &red, &green, &blue, &alpha);

  if (n == 1 && RTEST (rb_obj_is_kind_of (red, rb_cArray)))
    {
      VALUE ary = red;
      n = RARRAY (ary)->len;
      if (n >= 4)
        {
          red = rb_ary_entry (ary, 0);
          green = rb_ary_entry (ary, 1);
          blue = rb_ary_entry (ary, 2);
          alpha = rb_ary_entry (ary, 3);
        }
    }

  if (n < 4)
    {
      return cr_set_source_rgb (argc, argv, self);
    }
  else
    {
      cairo_set_source_rgba (_SELF,
                             NUM2DBL (red),
                             NUM2DBL (green),
                             NUM2DBL (blue),
                             NUM2DBL (alpha));
      cr_check_status (_SELF);
      return self;
    }
}

static VALUE
cr_set_source_surface (VALUE self, VALUE surface, VALUE width, VALUE height)
{
  cairo_set_source_surface (_SELF,
                            RVAL2CRSURFACE (surface),
                            NUM2INT (width),
                            NUM2INT (height));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_source (VALUE self, VALUE pattern)
{
  cairo_set_source (_SELF, RVAL2CRPATTERN (pattern));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_source_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE arg1, arg2, arg3, arg4;
  int n;

  n = rb_scan_args (argc, argv, "13", &arg1, &arg2, &arg3, &arg4);

  if (n == 1 && RTEST (rb_obj_is_kind_of (arg1, rb_cArray)))
    {
      return cr_set_source_rgba (argc, argv, self);
    }
  else if (n == 1)
    {
      return cr_set_source (self, arg1);
    }
  else if (n == 3 && rb_obj_is_kind_of (self, rb_cCairo_Surface))
    {
      return cr_set_source_surface (self, arg1, arg2, arg3);
    }
  else if (n == 3 || n == 4)
    {
      return cr_set_source_rgba (argc, argv, self);
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect "
                "(red, green, blue), (red, green, blue, alpha), "
                "([red, green, blue]), ([red, green, blue, alpha]), "
                "(pattern) or (surface, x, y))");
    }
}

static VALUE
cr_set_tolerance (VALUE self, VALUE tolerance)
{
  cairo_set_tolerance (_SELF, NUM2DBL (tolerance));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_antialias(VALUE self, VALUE antialias)
{
  cairo_set_antialias(_SELF, NUM2INT(antialias));
  cr_check_status(_SELF);
  return self;
}

static VALUE
cr_set_fill_rule (VALUE self, VALUE rb_rule)
{
  cairo_fill_rule_t rule;
  Check_Type (rb_rule, T_FIXNUM);
  rule = FIX2INT (rb_rule);
  if (rule < CAIRO_FILL_RULE_WINDING || rule > CAIRO_FILL_RULE_EVEN_ODD)
    {
      rb_raise (rb_eArgError, "invalid fill rule");
    }
  cairo_set_fill_rule (_SELF, rule);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_line_width (VALUE self, VALUE width)
{
  cairo_set_line_width (_SELF, NUM2DBL (width));
  return self;
}

static VALUE
cr_set_line_cap (VALUE self, VALUE rb_cap)
{
  cairo_line_cap_t cap;
  Check_Type (rb_cap, T_FIXNUM);
  cap = FIX2INT (rb_cap);
  if (cap < CAIRO_LINE_CAP_BUTT || cap > CAIRO_LINE_CAP_SQUARE)
    {
      rb_raise (rb_eArgError, "invalid line cap type");
    }
  cairo_set_line_cap (_SELF, cap);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_line_join (VALUE self, VALUE rb_join)
{
  cairo_line_join_t join;
  Check_Type (rb_join, T_FIXNUM);
  join = FIX2INT (rb_join);
  if (join < CAIRO_LINE_JOIN_MITER || join > CAIRO_LINE_JOIN_BEVEL)
    {
      rb_raise (rb_eArgError, "invalid line join type");
    }
  cairo_set_line_join (_SELF, join);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_dash (VALUE self, VALUE dash_array, VALUE offset)
{
  if (!NIL_P (dash_array))
    {
      Check_Type (dash_array, T_ARRAY);
    }

  if (NIL_P (dash_array) || RARRAY (dash_array)->len == 0)
    {
      cairo_set_dash (_SELF, NULL, 0, NUM2DBL (offset));
    }
  else
    {
      int i, length;
      double *values;
      length = RARRAY (dash_array)->len;
      values = ALLOCA_N (double, length);
      if (!values)
        {
          rb_cairo_raise_exception (CAIRO_STATUS_NO_MEMORY);
        }
      for (i = 0; i < length; i++)
        {
          values[i] = NUM2DBL (RARRAY (dash_array)->ptr[i]);
        }
      cairo_set_dash (_SELF, values, length, NUM2DBL (offset));
    }
  
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_miter_limit (VALUE self, VALUE limit)
{
  cairo_set_miter_limit (_SELF, NUM2DBL (limit));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_translate (VALUE self, VALUE tx, VALUE ty)
{
  cairo_translate (_SELF, NUM2DBL (tx), NUM2DBL (ty));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_scale (VALUE self, VALUE sx, VALUE sy)
{
  cairo_scale (_SELF, NUM2DBL (sx), NUM2DBL (sy));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rotate (VALUE self, VALUE radians)
{
  cairo_rotate (_SELF, NUM2DBL (radians));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_transform (VALUE self, VALUE xform)
{
  cairo_transform (_SELF, RVAL2CRMATRIX (xform));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_matrix (VALUE self, VALUE xform)
{
  cairo_set_matrix (_SELF, RVAL2CRMATRIX (xform));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_identity_matrix (VALUE self)
{
  cairo_identity_matrix (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_user_to_device (VALUE self, VALUE x, VALUE y)
{
  double pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_user_to_device (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return float_array (pair, 2);
}

static VALUE
cr_user_to_device_distance (VALUE self, VALUE dx, VALUE dy)
{
  double pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_user_to_device_distance (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return float_array (pair, 2);
}

static VALUE
cr_device_to_user (VALUE self, VALUE x, VALUE y)
{
  double pair[2];
  pair[0] = NUM2DBL (x);
  pair[1] = NUM2DBL (y);
  cairo_device_to_user (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return float_array (pair, 2);
}

static VALUE
cr_device_to_user_distance (VALUE self, VALUE dx, VALUE dy)
{
  double pair[2];
  pair[0] = NUM2DBL (dx);
  pair[1] = NUM2DBL (dy);
  cairo_device_to_user_distance (_SELF, pair, pair + 1);
  cr_check_status (_SELF);
  return float_array (pair, 2);
}


/* Path creation functions */
static VALUE
cr_new_path (VALUE self)
{
  cairo_new_path (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_move_to (VALUE self, VALUE x, VALUE y)
{
  cairo_move_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_line_to (VALUE self, VALUE x, VALUE y)
{
  cairo_line_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_curve_to (VALUE self, VALUE x1, VALUE y1,
             VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  cairo_curve_to (_SELF, NUM2DBL (x1), NUM2DBL (y1),
                  NUM2DBL (x2), NUM2DBL (y2), NUM2DBL (x3), NUM2DBL (y3));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_arc (VALUE self, VALUE cx, VALUE cy, VALUE radius,
        VALUE angle1, VALUE angle2)
{
  cairo_arc (_SELF, NUM2DBL (cx), NUM2DBL (cy), NUM2DBL (radius),
             NUM2DBL (angle1), NUM2DBL (angle2));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_arc_negative (VALUE self, VALUE cx, VALUE cy, VALUE radius,
                 VALUE angle1, VALUE angle2)
{
  cairo_arc_negative (_SELF, NUM2DBL (cx), NUM2DBL (cy), NUM2DBL (radius),
                      NUM2DBL (angle1), NUM2DBL (angle2));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_move_to (VALUE self, VALUE x, VALUE y)
{
  cairo_rel_move_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_line_to (VALUE self, VALUE x, VALUE y)
{
  cairo_rel_line_to (_SELF, NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rel_curve_to (VALUE self, VALUE x1, VALUE y1,
                 VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  cairo_rel_curve_to (_SELF, NUM2DBL (x1), NUM2DBL (y1),
                      NUM2DBL (x2), NUM2DBL (y2), NUM2DBL (x3), NUM2DBL (y3));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_rectangle (VALUE self, VALUE x, VALUE y, VALUE width, VALUE height)
{
  cairo_rectangle (_SELF, NUM2DBL (x), NUM2DBL (y),
                   NUM2DBL (width), NUM2DBL (height));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_close_path (VALUE self)
{
  cairo_close_path (_SELF);
  cr_check_status (_SELF);
  return self;
}

/* Painting functions */
static VALUE
cr_paint (VALUE self)
{
  cairo_paint (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_paint_with_alpha (VALUE self, VALUE alpha)
{
  cairo_paint_with_alpha (_SELF, NUM2DBL (alpha));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_paint_generic(int argc, VALUE *argv, VALUE self)
{
  VALUE alpha;
  int n;

  n = rb_scan_args (argc, argv, "01", &alpha);

  if (n == 0 || (n == 1 && NIL_P(alpha)))
    {
      return cr_paint (self);
    }
  if (n == 1)
    {
      return cr_paint_with_alpha (self, alpha);
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect () or (alpha))");
    }
}

static VALUE
cr_mask(VALUE self, VALUE pattern)
{
  cairo_mask (_SELF, RVAL2CRPATTERN (pattern));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_mask_surface (VALUE self, VALUE surface, VALUE x, VALUE y)
{
  cairo_mask_surface (_SELF, RVAL2CRSURFACE (surface),
                      NUM2DBL (x), NUM2DBL (y));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_mask_generic (int argc, VALUE *argv, VALUE self)
{
  VALUE arg1, arg2, arg3;
  int n;

  n = rb_scan_args (argc, argv, "12", &arg1, &arg2, &arg3);

  if (n == 1)
    {
      return cr_mask (self, arg1);
    }
  else if (n == 3)
    {
      return cr_mask_surface (self, arg1, arg2, arg3);
    }
  else
    {
      rb_raise (rb_eArgError,
                "invalid argument (expect (pattern) or (surface, x, y))");
    }
}

static VALUE
cr_stroke (VALUE self)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_stroke (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_stroke_preserve (VALUE self)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_stroke_preserve (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_fill (VALUE self)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_fill (_SELF);
  cr_check_status (_SELF);
  return self;
}


static VALUE
cr_fill_preserve (VALUE self)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_fill_preserve (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_copy_page (VALUE self)
{
  cairo_copy_page (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_show_page (VALUE self)
{
  cairo_show_page (_SELF);
  cr_check_status (_SELF);
  return self;
}

/* Insideness testing */
static VALUE
cr_in_stroke (VALUE self, VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  return cairo_in_stroke (_SELF, NUM2DBL (x), NUM2DBL (y)) ? Qtrue : Qfalse;
}

static VALUE
cr_in_fill (VALUE self, VALUE x, VALUE y)
{
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  return cairo_in_fill (_SELF, NUM2DBL (x), NUM2DBL (y)) ? Qtrue : Qfalse;
}

/* Rectangular extents */
static VALUE
cr_stroke_extents (VALUE self)
{
  double extents[4];
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_stroke_extents (_SELF, extents, extents + 1, extents + 2, extents + 3);
  return float_array (extents, 4);
}

static VALUE
cr_fill_extents (VALUE self)
{
  double extents[4];
  if (rb_block_given_p ())
    {
      cr_new_path (self);
      rb_yield (self);
    }
  cairo_fill_extents (_SELF, extents, extents + 1, extents + 2, extents + 3);
  return float_array (extents, 4);
}

/* Clipping */
static VALUE
cr_reset_clip (VALUE self)
{
  cairo_reset_clip (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_clip (VALUE self)
{
  cairo_clip (_SELF);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_clip_preserve (VALUE self)
{
  cairo_clip_preserve (_SELF);
  cr_check_status (_SELF);
  return self;
}

/* Font/Text functions */
static   VALUE
cr_select_font_face (VALUE self, VALUE family, VALUE rb_slant, VALUE rb_weight)
{
  cairo_font_slant_t slant = NUM2INT (rb_slant);
  cairo_font_weight_t weight = NUM2INT (rb_weight);

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
 

  cairo_select_font_face (_SELF, STR2CSTR (family), slant, weight);
  cr_check_status (_SELF);
  return self;
}

static   VALUE
cr_set_font_size (VALUE self, VALUE scale)
{
  cairo_set_font_size (_SELF, NUM2DBL (scale));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_set_font_matrix (VALUE self, VALUE matrix)
{
  cairo_set_font_matrix (_SELF, RVAL2CRMATRIX (matrix));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_get_font_matrix (VALUE self)
{
  cairo_matrix_t matrix;
  cairo_get_font_matrix (_SELF, &matrix);
  cr_check_status (_SELF);
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_set_font_options (VALUE self, VALUE options)
{
  cairo_set_font_options (_SELF, RVAL2CRFONTOPTIONS (options));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_get_font_options (VALUE self)
{
  cairo_font_options_t *options = NULL;
  cairo_get_font_options (_SELF, options);
  cr_check_status (_SELF);
  return CRFONTOPTIONS2RVAL (options);
}

static VALUE
cr_show_text (VALUE self, VALUE utf8)
{
  cairo_show_text (_SELF, STR2CSTR (utf8));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_show_glyphs (VALUE self, VALUE rb_glyphs)
{
  int count;
  cairo_glyph_t *glyphs;

  if (!rb_obj_is_kind_of (rb_glyphs, rb_cArray))
     rb_raise (rb_eTypeError, "expected array");
    
  glyphs_to_array (rb_glyphs, &glyphs, &count);
  cairo_show_glyphs (_SELF, glyphs, count);
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_get_font_face (VALUE self)
{
  cairo_font_face_t *xform;
  
  xform = cairo_get_font_face (_SELF);
  cr_check_status (_SELF);
  return CRFONTFACE2RVAL (xform);
}

static VALUE
cr_font_extents (VALUE self)
{
  cairo_font_extents_t extents;
  cairo_font_extents (_SELF, &extents);
  cr_check_status (_SELF);
  return CRFONTEXTENTS2RVAL (&extents);
}

static VALUE
cr_set_font_face (VALUE self, VALUE xform)
{
  cairo_set_font_face (_SELF, RVAL2CRFONTFACE (xform));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_text_extents (VALUE self, VALUE utf8)
{
  cairo_text_extents_t extents;
  cairo_text_extents (_SELF, StringValuePtr (utf8), &extents);
  cr_check_status (_SELF);
  return CRTEXTEXTENTS2RVAL (&extents);
}

static VALUE
cr_glyph_extents (VALUE self, VALUE rb_glyphs)
{
  cairo_text_extents_t extents;
  cairo_glyph_t *glyphs;
  int length;

  glyphs_to_array (rb_glyphs, &glyphs, &length);
  cairo_glyph_extents (_SELF, glyphs, length, &extents);
  cr_check_status (_SELF);
  return CRTEXTEXTENTS2RVAL (&extents);
}

static VALUE
cr_text_path (VALUE self, VALUE utf8)
{
  cairo_text_path (_SELF, STR2CSTR (utf8));
  cr_check_status (_SELF);
  return self;
}

static VALUE
cr_glyph_path (VALUE self, VALUE rb_glyphs)
{
  int count;
  cairo_glyph_t *glyphs;

  glyphs_to_array (rb_glyphs, &glyphs, &count);
  cairo_glyph_path (_SELF, glyphs, count);
  cr_check_status (_SELF);
  
  return self;
}

/* Query functions */
static VALUE
cr_get_operator (VALUE self)
{
  return INT2FIX (cairo_get_operator (_SELF));
}

static VALUE
cr_get_source (VALUE self)
{
  return CRPATTERN2RVAL (cairo_get_source (_SELF));
}

static VALUE
cr_get_tolerance (VALUE self)
{
  return rb_float_new (cairo_get_tolerance (_SELF));
}

static VALUE
cr_get_antialias(VALUE self)
{
  return INT2NUM(cairo_get_antialias(_SELF));
}

static VALUE
cr_get_current_point (VALUE self)
{
  double point[2];
  cairo_get_current_point (_SELF, point, point + 1);
  return float_array (point, 2);
}

static VALUE
cr_get_fill_rule (VALUE self)
{
  return INT2FIX (cairo_get_fill_rule (_SELF));
}

static VALUE
cr_get_line_width (VALUE self)
{
  return rb_float_new (cairo_get_line_width (_SELF));
}

static VALUE
cr_get_line_cap (VALUE self)
{
  return INT2FIX (cairo_get_line_cap (_SELF));
}

static VALUE
cr_get_line_join (VALUE self)
{
  return INT2FIX (cairo_get_line_join (_SELF));
}

static VALUE
cr_get_miter_limit (VALUE self)
{
  return rb_float_new (cairo_get_miter_limit (_SELF));
}

static VALUE
cr_get_matrix (VALUE self)
{
  cairo_matrix_t matrix;
  cairo_get_matrix (_SELF, &matrix);
  cr_check_status (_SELF);
  return CRMATRIX2RVAL (&matrix);
}

static VALUE
cr_get_target (VALUE self)
{
  return CRSURFACE2RVAL (cairo_get_target (_SELF));
}

/* Paths */
static VALUE
cr_copy_path (VALUE self)
{
  VALUE path = CRPATH2RVAL (cairo_copy_path (_SELF));
  cr_check_status (_SELF);
  return path;
}

static VALUE
cr_copy_path_flat (VALUE self)
{
  VALUE path = CRPATH2RVAL (cairo_copy_path_flat (_SELF));
  cr_check_status (_SELF);
  return path;
}

static VALUE
cr_copy_append_path (VALUE self, VALUE path)
{
  cairo_append_path (_SELF, RVAL2CRPATH (path));
  cr_check_status (_SELF);
  return self;
}

void
Init_cairo_context (void)
{
  rb_cCairo_Context =
    rb_define_class_under (rb_mCairo, "Context", rb_cObject);

  rb_define_alloc_func (rb_cCairo_Context, cr_allocate);
  
  /* Functions for manipulating state objects */
  rb_define_method (rb_cCairo_Context, "initialize", cr_initialize, 1);

  rb_define_method (rb_cCairo_Context, "save", cr_save, 0);
  rb_define_method (rb_cCairo_Context, "restore", cr_restore, 0);

  /* Modify state */
  rb_define_method (rb_cCairo_Context, "set_operator", cr_set_operator, 1);
  rb_define_method (rb_cCairo_Context, "set_source", cr_set_source_generic, -1);
  rb_define_method (rb_cCairo_Context, "set_tolerance", cr_set_tolerance, 1);
  rb_define_method (rb_cCairo_Context, "set_antialias", cr_set_antialias, 1);
  rb_define_method (rb_cCairo_Context, "set_fill_rule", cr_set_fill_rule, 1);
  rb_define_method (rb_cCairo_Context, "set_line_width", cr_set_line_width, 1);
  rb_define_method (rb_cCairo_Context, "set_line_cap", cr_set_line_cap, 1);
  rb_define_method (rb_cCairo_Context, "set_line_join", cr_set_line_join, 1);
  rb_define_method (rb_cCairo_Context, "set_dash", cr_set_dash, 2);
  rb_define_method (rb_cCairo_Context, "set_miter_limit",
                    cr_set_miter_limit, 1);
  
  rb_define_method (rb_cCairo_Context, "translate", cr_translate, 2);
  rb_define_method (rb_cCairo_Context, "scale", cr_scale, 2);
  rb_define_method (rb_cCairo_Context, "rotate", cr_rotate, 1);
  rb_define_method (rb_cCairo_Context, "transform", cr_transform, 1);
  
  rb_define_method (rb_cCairo_Context, "set_matrix", cr_set_matrix, 1);
  rb_define_method (rb_cCairo_Context, "identity_matrix",
                    cr_identity_matrix, 1);
  rb_define_method (rb_cCairo_Context, "user_to_device", cr_user_to_device, 2);
  rb_define_method (rb_cCairo_Context, "user_to_device_distance",
                    cr_user_to_device_distance, 2);
  rb_define_method (rb_cCairo_Context, "device_to_user", cr_device_to_user, 2);
  rb_define_method (rb_cCairo_Context, "device_to_user_distance",
                    cr_device_to_user_distance, 2);

  /* Path creation functions */
  rb_define_method (rb_cCairo_Context, "new_path", cr_new_path, 0);
  rb_define_method (rb_cCairo_Context, "move_to", cr_move_to, 2);
  rb_define_method (rb_cCairo_Context, "line_to", cr_line_to, 2);
  rb_define_method (rb_cCairo_Context, "curve_to", cr_curve_to, 6);
  rb_define_method (rb_cCairo_Context, "arc", cr_arc, 5);
  rb_define_method (rb_cCairo_Context, "arc_negative", cr_arc_negative, 5);
  rb_define_method (rb_cCairo_Context, "rel_move_to", cr_rel_move_to, 2);
  rb_define_method (rb_cCairo_Context, "rel_line_to", cr_rel_line_to, 2);
  rb_define_method (rb_cCairo_Context, "rel_curve_to", cr_rel_curve_to, 6);
  rb_define_method (rb_cCairo_Context, "rectangle", cr_rectangle, 4);
  rb_define_method (rb_cCairo_Context, "close_path", cr_close_path, 0);

  /* Painting functions */
  rb_define_method (rb_cCairo_Context, "paint", cr_paint_generic, -1);
  rb_define_method (rb_cCairo_Context, "mask", cr_mask_generic, -1);
  rb_define_method (rb_cCairo_Context, "stroke", cr_stroke, 0);
  rb_define_method (rb_cCairo_Context, "stroke_preserve",
                    cr_stroke_preserve, 0);
  rb_define_method (rb_cCairo_Context, "fill", cr_fill, 0);
  rb_define_method (rb_cCairo_Context, "fill_preserve", cr_fill_preserve, 0);
  rb_define_method (rb_cCairo_Context, "copy_page", cr_copy_page, 0);
  rb_define_method (rb_cCairo_Context, "show_page", cr_show_page, 0);

  /* Insideness testing */
  rb_define_method (rb_cCairo_Context, "in_stroke?", cr_in_stroke, 2);
  rb_define_method (rb_cCairo_Context, "in_fill?", cr_in_fill, 2);
  
  /* Rectangular extents */
  rb_define_method (rb_cCairo_Context, "stroke_extents", cr_stroke_extents, 0);
  rb_define_method (rb_cCairo_Context, "fill_extents", cr_fill_extents, 0);
  
  /* Clipping */
  rb_define_method (rb_cCairo_Context, "reset_clip", cr_reset_clip, 0);
  rb_define_method (rb_cCairo_Context, "clip", cr_clip, 0);
  rb_define_method (rb_cCairo_Context, "clip_preserve", cr_clip_preserve, 0);

  /* Font/Text functions */
  rb_define_method (rb_cCairo_Context, "select_font_face",
                    cr_select_font_face, 3);
  rb_define_method (rb_cCairo_Context, "set_font_size", cr_set_font_size, 1);
  rb_define_method (rb_cCairo_Context, "set_font_matrix",
                    cr_set_font_matrix, 1);
  rb_define_method (rb_cCairo_Context, "font_matrix", cr_get_font_matrix, 0);
  rb_define_method (rb_cCairo_Context, "set_font_options",
                    cr_set_font_options, 1);
  rb_define_method (rb_cCairo_Context, "font_options", cr_get_font_options, 0);
  rb_define_method (rb_cCairo_Context, "show_text", cr_show_text, 1);
  rb_define_method (rb_cCairo_Context, "show_glyphs", cr_show_glyphs, 1);
  rb_define_method (rb_cCairo_Context, "font_face", cr_get_font_face, 0);
  rb_define_method (rb_cCairo_Context, "font_extents",
                    cr_font_extents, 0);
  rb_define_method (rb_cCairo_Context, "set_font_face", cr_set_font_face, 1);
  rb_define_method (rb_cCairo_Context, "text_extents", cr_text_extents, 1);
  rb_define_method (rb_cCairo_Context, "glyph_extents", cr_glyph_extents, 1);
  rb_define_method (rb_cCairo_Context, "text_path", cr_text_path, 1);
  rb_define_method (rb_cCairo_Context, "glyph_path", cr_glyph_path, 1);

  /* Query functions */
  rb_define_method (rb_cCairo_Context, "operator", cr_get_operator, 0);
  rb_define_method (rb_cCairo_Context, "source", cr_get_source, 0);
  rb_define_method (rb_cCairo_Context, "tolerance", cr_get_tolerance, 0);
  rb_define_method (rb_cCairo_Context, "antialias", cr_get_antialias, 0);
  rb_define_method (rb_cCairo_Context, "current_point",
                    cr_get_current_point, 0);
  rb_define_method (rb_cCairo_Context, "fill_rule", cr_get_fill_rule, 0);
  rb_define_method (rb_cCairo_Context, "line_width", cr_get_line_width, 0);
  rb_define_method (rb_cCairo_Context, "line_cap", cr_get_line_cap, 0);
  rb_define_method (rb_cCairo_Context, "line_join", cr_get_line_join, 0);
  rb_define_method (rb_cCairo_Context, "miter_limit", cr_get_miter_limit, 0);
  rb_define_method (rb_cCairo_Context, "matrix", cr_get_matrix, 0);
  rb_define_method (rb_cCairo_Context, "target", cr_get_target, 0);
  
  /* Paths */
  rb_define_method (rb_cCairo_Context, "copy_path", cr_copy_path, 0);
  rb_define_method (rb_cCairo_Context, "copy_path_flat", cr_copy_path_flat, 0);
  rb_define_method (rb_cCairo_Context, "append_path", cr_copy_append_path, 1);
}
