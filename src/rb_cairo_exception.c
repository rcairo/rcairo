/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * $Author: kou $
 * $Date: 2008-08-16 12:52:16 $
 *
 * Copyright 2005 Øyvind Kolås <pippin@freedesktop.org>
 * Copyright 2004-2005 MenTaLguY <mental@rydia.com>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#include "rb_cairo.h"
#include "rb_cairo_private.h"

static VALUE rb_eCairo_InvalidRestoreError;
static VALUE rb_eCairo_InvalidPopGroupError;
static VALUE rb_eCairo_NoCurrentPointError;
static VALUE rb_eCairo_InvalidMatrixError;
static VALUE rb_eCairo_InvalidStatusError;
static VALUE rb_eCairo_NullPointerError;
static VALUE rb_eCairo_InvalidStringError;
static VALUE rb_eCairo_InvalidPathDataError;
static VALUE rb_eCairo_ReadError;
static VALUE rb_eCairo_WriteError;
static VALUE rb_eCairo_SurfaceFinishedError;
static VALUE rb_eCairo_SurfaceTypeMismatchError;
static VALUE rb_eCairo_PatternTypeMismatchError;
static VALUE rb_eCairo_InvalidContentError;
static VALUE rb_eCairo_InvalidFormatError;
static VALUE rb_eCairo_InvalidVisualError;
static VALUE rb_eCairo_FileNotFoundError;
static VALUE rb_eCairo_InvalidDashError;
static VALUE rb_eCairo_InvalidDscCommentError;
#if CAIRO_CHECK_VERSION(1, 3, 0)
static VALUE rb_eCairo_InvalidIndexError;
static VALUE rb_eCairo_ClipNotRepresentableError;
#endif
#if CAIRO_CHECK_VERSION(1, 5, 6)
static VALUE rb_eCairo_TempFileError;
static VALUE rb_eCairo_InvalidStrideError;
#endif
#if CAIRO_CHECK_VERSION(1, 7, 2)
static VALUE rb_eCairo_FontTypeMismatch;
static VALUE rb_eCairo_UserFontImmutable;
static VALUE rb_eCairo_UserFontError;
static VALUE rb_eCairo_NegativeCount;
static VALUE rb_eCairo_InvalidClusters;
static VALUE rb_eCairo_InvalidSlant;
static VALUE rb_eCairo_InvalidWeight;
#endif

void
rb_cairo_check_status (cairo_status_t status)
{
  const char *string = cairo_status_to_string (status);
  
  switch (status)
    {
    case CAIRO_STATUS_SUCCESS:
      break;
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
    case CAIRO_STATUS_INVALID_STATUS:
      rb_raise (rb_eCairo_InvalidStatusError, string);
      break;
    case CAIRO_STATUS_NULL_POINTER:
      rb_raise (rb_eCairo_NullPointerError, string);
      break;
    case CAIRO_STATUS_INVALID_STRING:
      rb_raise (rb_eCairo_InvalidStringError, string);
      break;
    case CAIRO_STATUS_INVALID_PATH_DATA:
      rb_raise (rb_eCairo_InvalidPathDataError, string);
      break;
    case CAIRO_STATUS_READ_ERROR:
      rb_raise (rb_eCairo_ReadError, string);
      break;
    case CAIRO_STATUS_WRITE_ERROR:
      rb_raise (rb_eCairo_WriteError, string);
      break;
    case CAIRO_STATUS_SURFACE_FINISHED:
      rb_raise (rb_eCairo_SurfaceFinishedError, string);
      break;
    case CAIRO_STATUS_SURFACE_TYPE_MISMATCH:
      rb_raise (rb_eCairo_SurfaceTypeMismatchError, string);
      break;
    case CAIRO_STATUS_PATTERN_TYPE_MISMATCH:
      rb_raise (rb_eCairo_PatternTypeMismatchError, string);
      break;
    case CAIRO_STATUS_INVALID_CONTENT:
      rb_raise (rb_eCairo_InvalidContentError, string);
      break;
    case CAIRO_STATUS_INVALID_FORMAT:
      rb_raise (rb_eCairo_InvalidFormatError, string);
      break;
    case CAIRO_STATUS_INVALID_VISUAL:
      rb_raise (rb_eCairo_InvalidVisualError, string);
      break;
    case CAIRO_STATUS_FILE_NOT_FOUND:
      rb_raise (rb_eCairo_FileNotFoundError, string);
      break;
    case CAIRO_STATUS_INVALID_DASH:
      rb_raise (rb_eCairo_InvalidDashError, string);
      break;
    case CAIRO_STATUS_INVALID_DSC_COMMENT:
      rb_raise (rb_eCairo_InvalidDscCommentError, string);
      break;
#if CAIRO_CHECK_VERSION(1, 3, 0)
    case CAIRO_STATUS_INVALID_INDEX:
      rb_raise (rb_eCairo_InvalidIndexError, string);
      break;
    case CAIRO_STATUS_CLIP_NOT_REPRESENTABLE:
      rb_raise (rb_eCairo_ClipNotRepresentableError, string);
      break;
#endif
#if CAIRO_CHECK_VERSION(1, 5, 6)
    case CAIRO_STATUS_TEMP_FILE_ERROR:
      rb_raise (rb_eCairo_TempFileError, string);
      break;
    case CAIRO_STATUS_INVALID_STRIDE:
      rb_raise (rb_eCairo_InvalidStringError, string);
      break;
#endif
#if CAIRO_CHECK_VERSION(1, 7, 2)
    case CAIRO_STATUS_FONT_TYPE_MISMATCH:
      rb_raise (rb_eCairo_FontTypeMismatch, string);
      break;
    case CAIRO_STATUS_USER_FONT_IMMUTABLE:
      rb_raise (rb_eCairo_UserFontImmutable, string);
      break;
    case CAIRO_STATUS_USER_FONT_ERROR:
      rb_raise (rb_eCairo_UserFontError, string);
      break;
    case CAIRO_STATUS_NEGATIVE_COUNT:
      rb_raise (rb_eCairo_NegativeCount, string);
      break;
    case CAIRO_STATUS_INVALID_CLUSTERS:
      rb_raise (rb_eCairo_InvalidClusters, string);
      break;
    case CAIRO_STATUS_INVALID_SLANT:
      rb_raise (rb_eCairo_InvalidSlant, string);
      break;
    case CAIRO_STATUS_INVALID_WEIGHT:
      rb_raise (rb_eCairo_InvalidWeight, string);
      break;
#endif
    }
}

cairo_status_t
rb_cairo__exception_to_status (VALUE exception)
{
  if (NIL_P (exception))
    return CAIRO_STATUS_SUCCESS;
  else if (rb_cairo__is_kind_of (exception, rb_eNoMemError))
    return CAIRO_STATUS_NO_MEMORY;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidRestoreError))
    return CAIRO_STATUS_INVALID_RESTORE;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidPopGroupError))
    return CAIRO_STATUS_INVALID_POP_GROUP;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_NoCurrentPointError))
    return CAIRO_STATUS_NO_CURRENT_POINT;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidMatrixError))
    return CAIRO_STATUS_INVALID_MATRIX;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidStatusError))
    return CAIRO_STATUS_INVALID_STATUS;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_NullPointerError))
    return CAIRO_STATUS_NULL_POINTER;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidStringError))
    return CAIRO_STATUS_INVALID_STRING;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidPathDataError))
    return CAIRO_STATUS_INVALID_PATH_DATA;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_ReadError))
    return CAIRO_STATUS_READ_ERROR;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_WriteError))
    return CAIRO_STATUS_WRITE_ERROR;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_SurfaceFinishedError))
    return CAIRO_STATUS_SURFACE_FINISHED;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_SurfaceTypeMismatchError))
    return CAIRO_STATUS_SURFACE_TYPE_MISMATCH;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_PatternTypeMismatchError))
    return CAIRO_STATUS_PATTERN_TYPE_MISMATCH;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidContentError))
    return CAIRO_STATUS_INVALID_CONTENT;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidFormatError))
    return CAIRO_STATUS_INVALID_FORMAT;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidVisualError))
    return CAIRO_STATUS_INVALID_VISUAL;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_FileNotFoundError))
    return CAIRO_STATUS_FILE_NOT_FOUND;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidDashError))
    return CAIRO_STATUS_INVALID_DASH;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidDscCommentError))
    return CAIRO_STATUS_INVALID_DSC_COMMENT;
#if CAIRO_CHECK_VERSION(1, 3, 0)
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidIndexError))
    return CAIRO_STATUS_INVALID_INDEX;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_ClipNotRepresentableError))
    return CAIRO_STATUS_CLIP_NOT_REPRESENTABLE;
#endif
#if CAIRO_CHECK_VERSION(1, 5, 6)
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_TempFileError))
    return CAIRO_STATUS_TEMP_FILE_ERROR;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidStringError))
    return CAIRO_STATUS_INVALID_STRIDE;
#endif
#if CAIRO_CHECK_VERSION(1, 7, 2)
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_FontTypeMismatch))
    return CAIRO_STATUS_FONT_TYPE_MISMATCH;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_UserFontImmutable))
    return CAIRO_STATUS_USER_FONT_IMMUTABLE;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_UserFontError))
    return CAIRO_STATUS_USER_FONT_ERROR;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_NegativeCount))
    return CAIRO_STATUS_NEGATIVE_COUNT;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidClusters))
    return CAIRO_STATUS_INVALID_CLUSTERS;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidSlant))
    return CAIRO_STATUS_INVALID_SLANT;
  else if (rb_cairo__is_kind_of (exception, rb_eCairo_InvalidWeight))
    return CAIRO_STATUS_INVALID_WEIGHT;
#endif

  return -1;
}

void
Init_cairo_exception ()
{
  VALUE rb_eCairo_Error;
  rb_eCairo_Error =
    rb_define_class_under (rb_mCairo, "Error", rb_eStandardError);
  rb_eCairo_InvalidRestoreError =
    rb_define_class_under (rb_mCairo, "InvalidRestoreError",
                           rb_eCairo_Error);
  rb_eCairo_InvalidPopGroupError =
    rb_define_class_under (rb_mCairo, "InvalidPopGroupError",
                           rb_eCairo_Error);
  rb_eCairo_NoCurrentPointError =
    rb_define_class_under (rb_mCairo, "NoCurrentPointError",
                           rb_eCairo_Error);
  rb_eCairo_InvalidMatrixError =
    rb_define_class_under (rb_mCairo, "InvalidMatrixError",
                           rb_eArgError);
  rb_eCairo_InvalidStatusError =
    rb_define_class_under (rb_mCairo, "InvalidStatusError",
                           rb_eArgError);
  rb_eCairo_NullPointerError =
    rb_define_class_under (rb_mCairo, "NullPointerError",
                           rb_eTypeError);
  rb_eCairo_InvalidStringError =
    rb_define_class_under (rb_mCairo, "InvalidStringError",
                           rb_eArgError);
  rb_eCairo_InvalidPathDataError =
    rb_define_class_under (rb_mCairo, "InvalidPathDataError",
                           rb_eArgError);
  rb_eCairo_ReadError =
    rb_define_class_under (rb_mCairo, "ReadError",
                           rb_eIOError);
  rb_eCairo_WriteError =
    rb_define_class_under (rb_mCairo, "WriteError",
                           rb_eIOError);
  rb_eCairo_SurfaceFinishedError =
    rb_define_class_under (rb_mCairo, "SurfaceFinishedError",
                           rb_eCairo_Error);
  rb_eCairo_SurfaceTypeMismatchError =
    rb_define_class_under (rb_mCairo, "SurfaceTypeMismatchError",
                           rb_eTypeError);
  rb_eCairo_PatternTypeMismatchError =
    rb_define_class_under (rb_mCairo, "PatternTypeMismatchError",
                           rb_eTypeError);
  rb_eCairo_InvalidContentError =
    rb_define_class_under (rb_mCairo, "InvalidContentError",
                           rb_eArgError);
  rb_eCairo_InvalidFormatError =
    rb_define_class_under (rb_mCairo, "InvalidFormatError",
                           rb_eArgError);
  rb_eCairo_InvalidVisualError =
    rb_define_class_under (rb_mCairo, "InvalidVisualError",
                           rb_eArgError);
  rb_eCairo_FileNotFoundError =
    rb_define_class_under (rb_mCairo, "FileNotFound",
                           rb_eCairo_Error);
  rb_eCairo_InvalidDashError =
    rb_define_class_under (rb_mCairo, "InvalidDashError",
                           rb_eArgError);
  rb_eCairo_InvalidDscCommentError =
    rb_define_class_under (rb_mCairo, "InvalidDscCommentError",
                           rb_eArgError);
#if CAIRO_CHECK_VERSION(1, 3, 0)
  rb_eCairo_InvalidIndexError =
    rb_define_class_under (rb_mCairo, "InvalidIndexError",
                           rb_eArgError);
  rb_eCairo_ClipNotRepresentableError =
    rb_define_class_under (rb_mCairo, "ClipNotRepresentableError",
                           rb_eCairo_Error);
#endif

#if CAIRO_CHECK_VERSION(1, 5, 6)
  rb_eCairo_TempFileError =
    rb_define_class_under (rb_mCairo, "TempFileError",
                           rb_eCairo_Error);

  rb_eCairo_InvalidStrideError =
    rb_define_class_under (rb_mCairo, "InvalidStrideError",
                           rb_eArgError);
#endif

#if CAIRO_CHECK_VERSION(1, 7, 2)
  rb_eCairo_FontTypeMismatch =
    rb_define_class_under (rb_mCairo, "FontTypeMismatch",
                           rb_eCairo_Error);

  rb_eCairo_UserFontImmutable =
    rb_define_class_under (rb_mCairo, "UserFontImmutable",
                           rb_eCairo_Error);

  rb_eCairo_UserFontError =
    rb_define_class_under (rb_mCairo, "UserFontError",
                           rb_eCairo_Error);

  rb_eCairo_NegativeCount =
    rb_define_class_under (rb_mCairo, "NegativeCount",
                           rb_eCairo_Error);

  rb_eCairo_InvalidClusters =
    rb_define_class_under (rb_mCairo, "InvalidClusters",
                           rb_eArgError);

  rb_eCairo_InvalidSlant =
    rb_define_class_under (rb_mCairo, "InvalidSlant",
                           rb_eCairo_Error);

  rb_eCairo_InvalidWeight =
    rb_define_class_under (rb_mCairo, "InvalidWeight",
                           rb_eArgError);
#endif
}
