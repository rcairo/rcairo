/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *           (C) 2004 Øyvind Kolås <pippin@freedesktop.org>
 *
 */

#include "rbcairo.h"

static VALUE
rcairo_set_target_surface (VALUE self,
                           VALUE surface)
{
  cairo_set_target_surface (rcairo_get_cairo(self),
                            rsurface_get_surface(surface));
  return Qnil;
}

static VALUE
rcairo_set_operator (VALUE self,
                     VALUE op)
{
  cairo_set_operator (rcairo_get_cairo(self),
                      NUM2INT(op));
  return Qnil;
}
static VALUE
rcairo_set_rgb_color (VALUE self,
                      VALUE red,
                      VALUE green,
                      VALUE blue)
{
  cairo_set_rgb_color (rcairo_get_cairo(self),
                       NUM2DBL(red),
                       NUM2DBL(green),
                       NUM2DBL(blue));
  return Qnil;
}

static VALUE
rcairo_set_alpha (VALUE self,
                  VALUE alpha)
{
  cairo_set_alpha (rcairo_get_cairo(self),
                   NUM2DBL(alpha));
  return Qnil;
}

static VALUE
rcairo_set_tolerance (VALUE self,
                      VALUE tolerance)
{
  cairo_set_tolerance (rcairo_get_cairo(self),
                       NUM2DBL(tolerance));
  return Qnil;
}

static VALUE
rcairo_set_fill_rule (VALUE self,
                      VALUE fill_rule)
{
  cairo_set_fill_rule (rcairo_get_cairo(self),
                       NUM2INT(fill_rule));
  return Qnil;
}

static VALUE
rcairo_set_line_width (VALUE self,
                       VALUE width)
{
  cairo_set_line_width (rcairo_get_cairo(self),
                        NUM2DBL(width));
  return Qnil;
}

static VALUE
rcairo_set_line_cap (VALUE self,
                     VALUE line_cap)
{
  cairo_set_line_cap (rcairo_get_cairo(self),
                      NUM2INT(line_cap));
  return Qnil;
}

static VALUE
rcairo_set_line_join (VALUE self,
                      VALUE line_join)
{
  cairo_set_line_join (rcairo_get_cairo(self),
                       NUM2INT(line_join));
  return Qnil;
}

static VALUE
rcairo_set_miter_limit (VALUE self,
                        VALUE limit)
{
  cairo_set_miter_limit(rcairo_get_cairo(self), NUM2DBL(limit));
  return Qnil;
}

static VALUE
rcairo_set_matrix (VALUE self,
                   VALUE matrix)
{
  cairo_set_matrix (rcairo_get_cairo(self),
                    rmatrix_get_matrix(matrix));
  return Qnil;
}

static VALUE
rcairo_current_operator (VALUE self)
{
  return INT2FIX(cairo_current_operator(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_alpha (VALUE self)
{
  return rb_float_new(cairo_current_alpha(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_tolerance (VALUE self)
{
  return rb_float_new(cairo_current_tolerance(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_fill_rule (VALUE self)
{
  return INT2FIX(cairo_current_fill_rule(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_line_width (VALUE self)
{
  return rb_float_new(cairo_current_line_width(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_line_cap (VALUE self)
{
  return INT2FIX(cairo_current_line_cap(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_line_join (VALUE self)
{
  return INT2FIX(cairo_current_line_join(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_miter_limit (VALUE self)
{
  return rb_float_new(cairo_current_miter_limit(rcairo_get_cairo(self)));
}

static VALUE
rcairo_current_target_surface (VALUE self)
{
  return rsurface_new_from(cairo_current_target_surface(rcairo_get_cairo(self)));
}

static VALUE
rcairo_status (VALUE self)
{
  return INT2FIX(cairo_status(rcairo_get_cairo(self)));
}

static VALUE
rcairo_status_string (VALUE self)
{
  return rb_str_new2(cairo_status_string(rcairo_get_cairo(self)));
}

static VALUE
rcairo_save (VALUE self)
{
  cairo_save(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_restore (VALUE self)
{
  cairo_restore(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_translate (VALUE self,
                  VALUE tx, VALUE ty)
{
  cairo_translate (rcairo_get_cairo(self),
                   NUM2DBL(tx), NUM2DBL(ty));
  return Qnil;
}

static VALUE
rcairo_scale (VALUE self,
              VALUE sx, VALUE sy)
{
  cairo_scale (rcairo_get_cairo(self),
               NUM2DBL(sx), NUM2DBL(sy));
  return Qnil;
}

static VALUE
rcairo_rotate (VALUE self,
               VALUE angle)
{
  cairo_rotate (rcairo_get_cairo(self),
                NUM2DBL(angle));
  return Qnil;
}

static VALUE
rcairo_concat_matrix (VALUE self,
                      VALUE matrix)
{
  cairo_concat_matrix (rcairo_get_cairo(self),
                       rmatrix_get_matrix(matrix));
  return Qnil;
}

static VALUE
rcairo_default_matrix (VALUE self)
{
  cairo_default_matrix (rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_identity_matrix (VALUE self)
{
  cairo_identity_matrix (rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_new_path (VALUE self)
{
  cairo_new_path (rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_move_to (VALUE self,
                VALUE x, VALUE y)
{
  cairo_move_to(rcairo_get_cairo(self),
                NUM2DBL(x), NUM2DBL(y));
  return Qnil;
}

static VALUE
rcairo_line_to (VALUE self,
                VALUE x, VALUE y)
{
  cairo_line_to (rcairo_get_cairo(self),
                 NUM2DBL(x), NUM2DBL(y));
  return Qnil;
}

static VALUE
rcairo_curve_to (VALUE self,
                 VALUE x1, VALUE y1,
                 VALUE x2, VALUE y2,
                 VALUE x3, VALUE y3)
{
  cairo_curve_to (rcairo_get_cairo(self),
                  NUM2DBL(x1), NUM2DBL(y1),
                  NUM2DBL(x2), NUM2DBL(y2),
                  NUM2DBL(x3), NUM2DBL(y3));
  return Qnil;
}

static VALUE
rcairo_arc (VALUE self,
            VALUE xc, VALUE yc,
            VALUE radius,
            VALUE angle1, VALUE angle2)
{
  cairo_arc (rcairo_get_cairo(self),
             NUM2DBL(xc), NUM2DBL(yc),
             NUM2DBL(radius),
             NUM2DBL(angle1), NUM2DBL(angle2));
  return Qnil;
}
static VALUE
rcairo_arc_negative (VALUE self,
                     VALUE xc, VALUE yc,
                     VALUE radius,
                     VALUE angle1, VALUE angle2)
{
  cairo_arc_negative (rcairo_get_cairo(self),
                      NUM2DBL(xc), NUM2DBL(yc),
                      NUM2DBL(radius),
                      NUM2DBL(angle1), NUM2DBL(angle2));
  return Qnil;
}

static VALUE
rcairo_rel_move_to (VALUE self,
                    VALUE dx, VALUE dy)
{
  cairo_rel_move_to (rcairo_get_cairo(self),
                     NUM2DBL(dx), NUM2DBL(dy));
  return Qnil;
}
static VALUE
rcairo_rel_line_to (VALUE self,
                    VALUE dx, VALUE dy)
{
  cairo_rel_line_to(rcairo_get_cairo(self), NUM2DBL(dx), NUM2DBL(dy));
  return Qnil;
}

static VALUE
rcairo_rel_curve_to (VALUE self,
                     VALUE dx1, VALUE dy1,
                     VALUE dx2, VALUE dy2,
                     VALUE dx3, VALUE dy3)
{
  cairo_rel_curve_to (rcairo_get_cairo(self),
                      NUM2DBL(dx1), NUM2DBL(dy1),
                      NUM2DBL(dx2), NUM2DBL(dy2),
                      NUM2DBL(dx3), NUM2DBL(dy3));
  return Qnil;
}

static VALUE
rcairo_rectangle (VALUE self,
                  VALUE x, VALUE y,
                  VALUE width, VALUE height)
{
  cairo_rectangle (rcairo_get_cairo(self),
                   NUM2DBL(x), NUM2DBL(y),
                   NUM2DBL(width), NUM2DBL(height));
  return Qnil;
}

static VALUE
rcairo_close_path (VALUE self)
{
  cairo_close_path(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_copy_page (VALUE self)
{
  cairo_copy_page(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_show_page (VALUE self)
{
  cairo_show_page(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_init_clip (VALUE self)
{
  cairo_init_clip(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_clip(VALUE self)
{
  cairo_clip(rcairo_get_cairo(self));
  return Qnil;
}

static VALUE
rcairo_select_font (VALUE self,
                    VALUE family,
                    VALUE slant,
                    VALUE weight)
{
  cairo_select_font (rcairo_get_cairo(self),
                     STR2CSTR(family),
                     NUM2INT(slant),
                     NUM2INT(weight));
  return Qnil;
}

static VALUE
rcairo_scale_font (VALUE self,
                   VALUE scale)
{
  cairo_scale_font (rcairo_get_cairo(self),
                    NUM2DBL(scale));
  return Qnil;
}

static VALUE
rcairo_transform_font (VALUE self,
                       VALUE matrix)
{
  cairo_transform_font (rcairo_get_cairo(self),
                        rmatrix_get_matrix(matrix));
  return Qnil;
}

static VALUE
rcairo_show_text (VALUE self,
                  VALUE utf8)
{
  cairo_show_text (rcairo_get_cairo(self),
                   STR2CSTR(utf8));
  return Qnil;
}

static VALUE
rcairo_text_path (VALUE self,
                  VALUE utf8)
{
  cairo_text_path (rcairo_get_cairo(self), STR2CSTR(utf8));
  return Qnil;
}

static VALUE
rcairo_show_surface (VALUE self,
                     VALUE surface,
                     VALUE width, VALUE height)
{
  cairo_show_surface (rcairo_get_cairo(self),
                      rsurface_get_surface(surface),
                      FIX2INT(width), FIX2INT(height));
  return Qnil;
}
static VALUE
rcairo_current_matrix (VALUE self,
                       VALUE matrix)
{
  cairo_current_matrix (rcairo_get_cairo(self),
                        rmatrix_get_matrix(matrix));
  return Qnil;
}

VALUE gen_Cairo (void)
{
  VALUE cCairo = rb_define_class_under(mCairo, "Cairo", rb_cObject);

  rb_define_method(cCairo, "save",
                           rcairo_save, 0);

  rb_define_method(cCairo, "restore",
                           rcairo_restore, 0);

  rb_define_method(cCairo, "translate",
                           rcairo_translate, 2);

  rb_define_method(cCairo, "scale",
                           rcairo_scale, 2);

  rb_define_method(cCairo, "rotate",
                           rcairo_rotate, 1);

  rb_define_method(cCairo, "concat_matrix",
                           rcairo_concat_matrix, 1);

  rb_define_method(cCairo, "default_matrix",
                           rcairo_default_matrix, 0);

  rb_define_method(cCairo, "identity_matrix",
                           rcairo_identity_matrix, 0);

  rb_define_method(cCairo, "new_path",
                           rcairo_new_path, 0);

  rb_define_method(cCairo, "move_to",
                           rcairo_move_to, 2);

  rb_define_method(cCairo, "line_to",
                           rcairo_line_to, 2);
  
  rb_define_method(cCairo, "curve_to",
                           rcairo_curve_to, 6);

  rb_define_method(cCairo, "arc",
                           rcairo_arc, 5);

  rb_define_method(cCairo, "arc_negative",
                           rcairo_arc_negative, 5);

  rb_define_method(cCairo, "rel_move_to",
                           rcairo_rel_move_to, 2);

  rb_define_method(cCairo, "rel_line_to",
                           rcairo_rel_line_to, 2);

  rb_define_method(cCairo, "rel_curve_to",
                           rcairo_rel_curve_to, 6);

  rb_define_method(cCairo, "rectangle",
                           rcairo_rectangle, 4);

  rb_define_method(cCairo, "close_path",
                           rcairo_close_path, 0);

  rb_define_method(cCairo, "copy_page",
                           rcairo_copy_page, 0);

  rb_define_method(cCairo, "show_page",
                           rcairo_show_page, 0);

  rb_define_method(cCairo, "init_clip",
                           rcairo_init_clip, 0);
  
  rb_define_method(cCairo, "clip",
                           rcairo_clip, 0);

  rb_define_method(cCairo, "select_font",
                           rcairo_select_font, 3);
  
  rb_define_method(cCairo, "scale_font",
                           rcairo_scale_font, 1);
  
  rb_define_method(cCairo, "transform_font",
                           rcairo_transform_font, 1);
  
  rb_define_method(cCairo, "show_text",
                           rcairo_show_text, 1);
  
  rb_define_method(cCairo, "text_path",
                           rcairo_text_path, 1);

  rb_define_method(cCairo, "show_surface",
                           rcairo_show_surface, 3);

  rb_define_method(cCairo, "current_matrix",
                           rcairo_current_matrix, 1);

  rb_define_method(cCairo, "set_target_surface",
                           rcairo_set_target_surface, 1);

  rb_define_method(cCairo, "target_surface=",
                           rcairo_set_target_surface, 1);

  rb_define_method(cCairo, "set_operator",
                           rcairo_set_operator, 1);

  rb_define_method(cCairo, "operator=",
                           rcairo_set_operator, 1);

  rb_define_method(cCairo, "set_rgb_color",
                           rcairo_set_rgb_color, 3);

  rb_define_method(cCairo, "set_alpha",
                           rcairo_set_alpha, 1);

  rb_define_method(cCairo, "alpha=",
                           rcairo_set_alpha, 1);

  rb_define_method(cCairo, "set_tolerance",
                           rcairo_set_tolerance, 1);

  rb_define_method(cCairo, "tolerance=",
                           rcairo_set_tolerance, 1);

  rb_define_method(cCairo, "set_fill_rule",
                           rcairo_set_fill_rule, 1);

  rb_define_method(cCairo, "fill_rule=",
                           rcairo_set_fill_rule, 1);

  rb_define_method(cCairo, "set_line_width",
                           rcairo_set_line_width, 1);

  rb_define_method(cCairo, "line_width=",
                           rcairo_set_line_width, 1);

  rb_define_method(cCairo, "set_line_cap",
                           rcairo_set_line_cap, 1);

  rb_define_method(cCairo, "line_cap=",
                           rcairo_set_line_cap, 1);

  rb_define_method(cCairo, "set_line_join",
                           rcairo_set_line_join, 1);

  rb_define_method(cCairo, "line_join=",
                           rcairo_set_line_join, 1);

  rb_define_method(cCairo, "set_miter_limit",
                           rcairo_set_miter_limit, 1);

  rb_define_method(cCairo, "miter_limit=",
                           rcairo_set_miter_limit, 1);

  rb_define_method(cCairo, "set_matrix",
                           rcairo_set_matrix, 1);

  rb_define_method(cCairo, "matrix=",
                           rcairo_set_matrix, 1);

  rb_define_method(cCairo, "operator",
                           rcairo_current_operator, 0);

  rb_define_method(cCairo, "alpha",
                           rcairo_current_alpha, 0);

  rb_define_method(cCairo, "tolerance",
                           rcairo_current_tolerance, 0);

  rb_define_method(cCairo, "fill_rule",
                           rcairo_current_fill_rule, 0);

  rb_define_method(cCairo, "line_width",
                           rcairo_current_line_width, 0);

  rb_define_method(cCairo, "line_cap",
                           rcairo_current_line_cap, 0);

  rb_define_method(cCairo, "line_join",
                           rcairo_current_line_join, 0);

  rb_define_method(cCairo, "miter_limit",
                           rcairo_current_miter_limit, 0);

  rb_define_method(cCairo, "target_surface",
                           rcairo_current_target_surface, 0);

  rb_define_method(cCairo, "status",
                           rcairo_status, 0);

  rb_define_method(cCairo, "status_string",
                           rcairo_status_string, 0);

  return cCairo;
}
