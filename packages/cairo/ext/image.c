/* ruby-cairo - Ruby bindings for Cairo.
 * Copyright (C) 2003 Evan Martin <martine@danga.com>
 *           (C) 2004 Øyvind Kolås <pippin@freedesktop.org>
 *
 */

#include "rbcairo.h"

VALUE cCairoImage;
VALUE eCairoImageFormat;

static void
rcairo_image_free (RCairoImage *img)
{
  free(img->data); free(img);
}

RCairoImage*
rcairo_image_get_image (VALUE vimage)
{
  RCairoImage *img;
  Data_Get_Struct(vimage, RCairoImage, img);
  return img;
}

static VALUE
rcairo_image_new (VALUE class,
                  VALUE vformat,
                  VALUE vwidth, VALUE vheight,
                  VALUE vstride)
{
  int format = FIX2INT(vformat);
  int bpp = 0;
  int datasize;
  RCairoImage *img;
  
  /* XXX only supports one format. */
  format = CAIRO_FORMAT_ARGB32;
  switch (format) {
    case CAIRO_FORMAT_ARGB32:
      bpp = 32;
      break;
    default:
      rb_raise(eCairoImageFormat, "unimplemented image format %d\n", format);
      return Qnil;
  }
  img = malloc(sizeof(RCairoImage));
  img->format = format;
  img->width  = FIX2INT(vwidth);
  img->height = FIX2INT(vheight);
  img->stride = FIX2INT(vstride);
  datasize = img->stride * img->height * bpp/8;
  img->data = malloc(datasize);
  memset(img->data, 0, datasize);
  return Data_Wrap_Struct(cCairoImage, NULL, rcairo_image_free, img);
}

static VALUE
rcairo_image_each_pixel (VALUE self)
{
  RCairoImage *img = rcairo_image_get_image(self);
  unsigned int *data;
  int x, y;

  /* XXX assumes 32bpp format and stride == width. */
  data = (unsigned int*)img->data;
  for (y = 0; y < img->height; y++) {
    for (x = 0; x < img->width; x++) {
      rb_yield(rb_ary_new3(4, INT2FIX(x), INT2FIX(y), UINT2NUM(*data)));
      data++;
    }
  }
  return Qnil;
}

void
rcairo_image_init (void)
{
  cCairoImage = rb_define_class_under(mCairo, "Image", rb_cObject);
  rb_define_singleton_method(cCairoImage, "new", rcairo_image_new, 4);
  rb_define_method(cCairoImage, "each_pixel", rcairo_image_each_pixel, 0);

  eCairoImageFormat = rb_define_class_under(mCairo, "ImageFormat", rb_eException);
}

