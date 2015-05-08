/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005-2010 Kouhei Sutou <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
*/

#ifndef RB_CAIRO_IO_H
#define RB_CAIRO_IO_H

#include <rb_cairo.h>

typedef struct rb_cairo__io_callback_closure {
  VALUE target;
  VALUE error;
  unsigned char *data;
  unsigned int length;
} rb_cairo__io_callback_closure_t;

typedef struct rb_cairo__io_invoke_data {
  cr_callback_func_t func;
  VALUE data;
} rb_cairo__io_invoke_data_t;

RB_CAIRO_VAR ID rb_cairo__io_id_read;
RB_CAIRO_VAR ID rb_cairo__io_id_write;
RB_CAIRO_VAR ID rb_cairo__io_id_output;
RB_CAIRO_VAR ID rb_cairo__io_id_to_io;
RB_CAIRO_VAR ID rb_cairo__io_id_to_path;

rb_cairo__io_callback_closure_t *
               rb_cairo__io_closure_new     (VALUE                target);
void           rb_cairo__io_closure_destroy (rb_cairo__io_callback_closure_t *closure);
void           rb_cairo__io_closure_free    (void                *closure);
cairo_status_t rb_cairo__io_write_func      (void                *write_closure,
                                             const unsigned char *data,
                                             unsigned int         length);
cairo_status_t rb_cairo__io_read_func       (void                *read_closure,
                                             unsigned char       *data,
                                             unsigned int         length);


#endif
