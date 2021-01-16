/* -*- c-file-style: "gnu"; indent-tabs-mode: nil -*- */
/*
 * Ruby Cairo Binding
 *
 * Copyright 2005-2021 Sutou Kouhei <kou@cozmixng.org>
 *
 * This file is made available under the same terms as Ruby
 *
 */

#include "rb_cairo.h"
#include "rb_cairo_private.h"
#include "rb_cairo_io.h"

ID rb_cairo__io_id_read;
ID rb_cairo__io_id_write;
ID rb_cairo__io_id_output;
ID rb_cairo__io_id_to_io;
ID rb_cairo__io_id_to_path;

/* read/write callback */
rb_cairo__io_callback_closure_t *
rb_cairo__io_closure_new (VALUE target)
{
  rb_cairo__io_callback_closure_t *closure;
  closure = ALLOC (rb_cairo__io_callback_closure_t);

  closure->target = target;
  closure->error = Qnil;

  return closure;
}

void
rb_cairo__io_closure_destroy (rb_cairo__io_callback_closure_t *closure)
{
  xfree (closure);
}

void
rb_cairo__io_closure_free (void *closure)
{
  rb_cairo__io_closure_destroy ((rb_cairo__io_callback_closure_t *) closure);
}

static VALUE
rb_cairo__io_func_rescue (VALUE io_closure, VALUE error)
{
  rb_cairo__io_callback_closure_t *closure;
  closure = (rb_cairo__io_callback_closure_t *)io_closure;
  closure->error = error;
  return Qnil;
}

static VALUE
rb_cairo__io_func_invoke (VALUE user_data)
{
  rb_cairo__io_invoke_data_t *data;

  data = (rb_cairo__io_invoke_data_t *)user_data;
  return rb_rescue2 (data->func, data->data,
                     rb_cairo__io_func_rescue, data->data, rb_eException,
                     (VALUE)0);
}

/* write callback */
static VALUE
rb_cairo__io_write_func_invoke (VALUE write_closure)
{
  VALUE output, data;
  long written_bytes;
  rb_cairo__io_callback_closure_t *closure;
  long length;

  closure = (rb_cairo__io_callback_closure_t *)write_closure;

  output = closure->target;
  data = rb_str_new ((const char *)closure->data, closure->length);

  length = RSTRING_LEN (data);
  while (length != 0)
    {
      VALUE rb_written_bytes = rb_funcall (output,
                                           rb_cairo__io_id_write, 1, data);
      written_bytes = NUM2LONG (rb_written_bytes);
      data = rb_str_substr (data, written_bytes,
                            RSTRING_LEN (data) - written_bytes);
      length -= written_bytes;
    }

  return Qnil;
}

cairo_status_t
rb_cairo__io_write_func (void *write_closure,
                         const unsigned char *data, unsigned int length)
{
  rb_cairo__io_callback_closure_t *closure;
  rb_cairo__io_invoke_data_t invoke_data;

  closure = (rb_cairo__io_callback_closure_t *)write_closure;
  closure->data = (unsigned char *)data;
  closure->length = length;

  invoke_data.func = rb_cairo__io_write_func_invoke;
  invoke_data.data = (VALUE)closure;
  rb_cairo__invoke_callback (rb_cairo__io_func_invoke, (VALUE)&invoke_data);

  if (NIL_P (closure->error))
    return CAIRO_STATUS_SUCCESS;
  else
    return CAIRO_STATUS_WRITE_ERROR;
}

/* read callback */
static VALUE
rb_cairo__io_read_func_invoke (VALUE read_closure)
{
  VALUE input, result;
  rb_cairo__io_callback_closure_t *closure;
  long length, rest;

  closure = (rb_cairo__io_callback_closure_t *)read_closure;
  input = closure->target;
  length = closure->length;

  result = rb_str_new2 ("");

  for (rest = length; rest != 0; rest = length - RSTRING_LEN (result))
    {
      rb_str_concat (result,
                     rb_funcall (input,
                                 rb_cairo__io_id_read, 1, LONG2NUM (rest)));
    }

  memcpy ((void *)closure->data, (const void *) StringValuePtr (result), length);

  return Qnil;
}

cairo_status_t
rb_cairo__io_read_func (void *read_closure,
                        unsigned char *data, unsigned int length)
{
  rb_cairo__io_callback_closure_t *closure;
  rb_cairo__io_invoke_data_t invoke_data;

  closure = (rb_cairo__io_callback_closure_t *)read_closure;
  closure->data = data;
  closure->length = length;

  invoke_data.func = rb_cairo__io_read_func_invoke;
  invoke_data.data = (VALUE)closure;
  rb_cairo__invoke_callback (rb_cairo__io_func_invoke, (VALUE)&invoke_data);

  if (NIL_P (closure->error))
    return CAIRO_STATUS_SUCCESS;
  else
    return CAIRO_STATUS_READ_ERROR;
}

void
Init_cairo_io (void)
{
  rb_cairo__io_id_read = rb_intern ("read");
  rb_cairo__io_id_write = rb_intern ("write");
  rb_cairo__io_id_output = rb_intern ("output");
  rb_cairo__io_id_to_io = rb_intern ("to_io");
  rb_cairo__io_id_to_path = rb_intern ("to_path");
}
