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

static VALUE rb_eCairo_InvalidPopGroupError;
static VALUE rb_eCairo_InvalidRestoreError;
static VALUE rb_eCairo_NoCurrentPointError;
static VALUE rb_eCairo_InvalidMatrixError;
static VALUE rb_eCairo_NoTargetSurfaceError;
static VALUE rb_eCairo_NullPointerError;

void
rb_cairo_raise_exception (cairo_status_t  status,
                          const char     *string)
{
  switch (status)
    {
    case CAIRO_STATUS_NO_MEMORY:
      rb_raise (rb_eNoMemError, string);
      break;
    case CAIRO_STATUS_INVALID_RESTORE:
      rb_raise (rb_eCairo_InvalidRestoreError, string);
      break;
    case CAIRO_STATUS_INVALID_POP_GROUP:
      rb_raise (rb_eCairo_InvalidPopGroupError, string);
      break;
    case CAIRO_STATUS_NO_CURRENT_POINT:
      rb_raise (rb_eCairo_NoCurrentPointError, string);
      break;
    case CAIRO_STATUS_INVALID_MATRIX:
      rb_raise (rb_eCairo_InvalidMatrixError, string);
      break;
    case CAIRO_STATUS_NO_TARGET_SURFACE:
      rb_raise (rb_eCairo_NoTargetSurfaceError, string);
      break;
    case CAIRO_STATUS_NULL_POINTER:
      rb_raise (rb_eCairo_NullPointerError, string);
      break;
    }
}

void
Init_cairo_exception ()
{
  rb_eCairo_InvalidRestoreError =
    rb_define_class_under (rb_mCairo, "InvalidRestoreError",
                           rb_eRuntimeError);
  rb_eCairo_InvalidPopGroupError =
    rb_define_class_under (rb_mCairo, "InvalidPopGroupError",
                           rb_eRuntimeError);
  rb_eCairo_NoCurrentPointError =
    rb_define_class_under (rb_mCairo, "NoCurrentPointError",
                           rb_eRuntimeError);
  rb_eCairo_InvalidMatrixError =
    rb_define_class_under (rb_mCairo, "InvalidMatrixError", rb_eArgError);
  rb_eCairo_NoTargetSurfaceError =
    rb_define_class_under (rb_mCairo, "NoTargetSurfaceError",
                           rb_eRuntimeError);
  rb_eCairo_NullPointerError =
    rb_define_class_under (rb_mCairo, "NullPointerError", rb_eTypeError);
}
