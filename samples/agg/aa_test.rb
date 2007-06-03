#!/usr/bin/env ruby

# ported from examples/aa_test.cpp in AGG source tree.

top = File.expand_path(File.join(File.dirname(__FILE__), "..", ".."))
src = File.join(top, "src")
$LOAD_PATH.unshift src
$LOAD_PATH.unshift File.join(src, "lib")

require 'gtk2'

window = Gtk::Window.new
window.set_default_size(480, 350)

area = Gtk::DrawingArea.new

def stroke_line(context, x1, y1, x2, y2, line_width, dash_length)
  context.save do
    yield if block_given?
    context.move_to(x1, y1)
    context.line_to(x2, y2)
    context.set_dash(dash_length) if dash_length > 0
    context.line_width = line_width
    context.line_cap = :round
    context.stroke
  end
end

def fill_triangle(context, x1, y1, x2, y2, x3, y3)
  context.save do
    yield if block_given?
    context.triangle(x1, y1, x2, y2, x3, y3)
    context.fill
  end
end

def set_gradient(context, x1, y1, x2, y2, color_stops)
  pattern = Cairo::LinearPattern.new(x1, y1, x2, y2)
  color_stops.each do |offset, color|
    pattern.add_color_stop(offset, color)
  end
  context.set_source(pattern)
end

def stroke_gradient_line(context, x1, y1, x2, y2,
                         line_width, dash_length, color_stops)
  stroke_line(context, x1, y1, x2, y2, line_width, dash_length) do
    set_gradient(context, x1, y1, x2, y2, color_stops)
  end
end

def fill_gradient_triangle(context, x1, y1, x2, y2, x3, y3, color_stops)
  fill_triangle(context, x1, y1, x2, y2, x3, y3) do
    set_gradient(context,
                 x1, y1,
                 x3 - (x3 - x2) / 2.0,
                 y3 - (y3 - y2) / 2.0,
                 color_stops)
  end
end

def draw_background_circle(context, w, h)
  context.set_source_color([1.0, 1.0, 1.0, 0.2])

  cx = w / 2.0
  cy = h / 2.0
  radius = [cx, cy].min
  1.upto(180) do |i|
    n = 2 * Math::PI * i / 180.0
    stroke_line(context,
                cx + radius * Math.sin(n),
                cy + radius * Math.cos(n),
                cx, cy,
                1.0, i < 90 ? i : 0)
  end
end

def draw_upper_small_circles(context, i)
  context.circle(18 + i * 4 + 0.5,
                 33 + 0.5,
                 i / 20.0)
  context.fill

  context.circle(18 + i * 4 + (i - 1) / 10.0 + 0.5,
                 27 + (i - 1) / 10.0 + 0.5,
                 0.5)
  context.fill
end

def draw_upper_circles(context, i)
  context.set_source_color(:white)
  context.circle(20 + i * (i + 1) + 0.5,
                 20.5,
                 i / 2.0)
  context.fill

  draw_upper_small_circles(context, i)
end

def draw_upper_gradient_lines(context, i)
  stroke_gradient_line(context,
                       20 + i * (i + 1),
                       40.5,
                       20 + i * (i + 1) + (i - 1) * 4,
                       100.5,
                       i,
                       0,
                       [[0, :white],
                        [1, [i % 2, (i % 3) * 0.5, (i % 5) * 0.25]]])
end

def draw_middle_small_circles(context, i)
  stroke_gradient_line(context,
                       17.5 + i * 4,
                       107,
                       17.5 + i * 4 + i / 6.66666667,
                       107,
                       1,
                       0,
                       [[0, :red],
                        [1, :blue]])

  stroke_gradient_line(context,
                       18 + i * 4,
                       112.5,
                       18 + i * 4,
                       112.5 + i / 6.66666667,
                       1,
                       0,
                       [[0, :red],
                        [1, :blue]])
end

def draw_middle_gradient_lines(context, i)
  stroke_gradient_line(context,
                       21.5,
                       120 + (i - 1) * 3.1,
                       52.5,
                       120 + (i - 1) * 3.1,
                       1,
                       0,
                       [[0, :red],
                        [1, :white]])

  stroke_gradient_line(context,
                       52.5,
                       118 + i * 3,
                       83.5,
                       118 + i * 3,
                       2 - (i - 1) / 10.0,
                       0,
                       [[0, :green],
                        [1, :white]])

  stroke_gradient_line(context,
                       83.5,
                       119 + i * 3,
                       114.5,
                       119 + i * 3,
                       2 - (i - 1) / 10.0,
                       3.0,
                       [[0, :blue],
                        [1, :white]])
end

def draw_middle_white_lines(context, i)
  context.set_source_color(:white)
  stroke_line(context,
              125.5, 119.5 + (i + 2) * (i / 2.0),
              135.5, 119.5 + (i + 2) * (i / 2.0),
              i, 0)
end

def draw_lower_short_lines(context, i)
  context.set_source_color(:white)

  stroke_line(context,
              17.5 + i * 4, 192,
              18.5 + i * 4, 192,
              i / 10.0, 0)

  stroke_line(context,
              17.5 + i * 4 + (i - 1) / 10.0, 186,
              18.5 + i * 4 + (i - 1) / 10.0, 186,
              1.0, 0)
end

def draw_right_triangles(context, i, w, h)
  x1 = w - 150
  x2 = w - 20
  y_upper = h - 20 - i * (i + 2)
  y_middle = h - 20 - i * (i + 1.5)
  y_lower = h - 20 - i * (i + 1)
  context.save do
    pattern = Cairo::LinearPattern.new(x1, y_middle, x2, y_middle)
    pattern.add_color_stop(0, :white)
    pattern.add_color_stop(1, [i % 2, (i % 3) * 0.5, (i % 5) * 0.25])
    context.set_source(pattern)
    context.move_to(x1, y_middle)
    context.line_to(x2, y_lower)
    context.line_to(x2, y_upper)
    context.fill
  end
end

def draw_sample_shapes(context, w, h)
  context.set_source_color(:black)
  context.paint

  draw_background_circle(context, w, h)

  1.upto(20) do |i|
    draw_upper_circles(context, i)
    draw_upper_gradient_lines(context, i)
    draw_middle_small_circles(context, i)
    draw_middle_gradient_lines(context, i)
    draw_middle_white_lines(context, i) if i <= 10
    draw_lower_short_lines(context, i)
  end

  1.upto(13) do |i|
    draw_right_triangles(context, i, w, h)
  end
end

def draw_random_shapes(context, w, h)
  srand(123)

  context.set_source_color(:black)
  context.paint

  n_circles = 20000
  start = Time.now
  n_circles.times do |i|
    context.circle(rand(w), rand(h), rand(20.0) + 1.0)
    context.set_source_color([rand, rand, rand, 0.5 + rand / 2])
    context.fill
  end
  circle_draw_time = Time.now - start

  n_lines = 2000
  start = Time.now
  n_lines.times do |i|
    x1 = rand(w)
    y1 = rand(h)
    stroke_gradient_line(context,
                         x1, y1,
                         x1 + rand(w * 0.5) - w * 0.25,
                         y1 + rand(h * 0.5) - h * 0.25,
                         10.0, 0,
                         [[0, [rand, rand, rand, 0.5 + rand / 2]],
                          [1, [rand, rand, rand, rand]]])
  end
  line_draw_time = Time.now - start

  n_triangles = 2000
  start = Time.now
  n_triangles.times do |i|
    x1 = rand(w)
    y1 = rand(h)
    fill_gradient_triangle(context,
                           x1, y1,
                           x1 + rand(w * 0.4) - w * 0.2,
                           y1 + rand(h * 0.4) - h * 0.2,
                           x1 + rand(w * 0.4) - w * 0.2,
                           y1 + rand(h * 0.4) - h * 0.2,
                           [[0, [rand, rand, rand, 0.5 + rand / 2]],
                            [0.5, [rand, rand, rand, rand]],
                            [1, [rand, rand, rand, rand]]])
  end
  triangle_draw_time = Time.now - start

  puts "Points=%.2fK/sec, Lines=%.2fK/sec, Triangles=%.2fK/sec" %
    [n_circles.to_f / circle_draw_time,
     n_lines.to_f / line_draw_time,
     n_triangles.to_f / triangle_draw_time]
end

random_mode = false

area.add_events(Gdk::Event::BUTTON_PRESS_MASK)
area.signal_connect("button-press-event") do |widget, event|
  random_mode = !random_mode
  widget.queue_draw
  false
end

area.signal_connect("expose-event") do |widget, event|
  context = widget.window.create_cairo_context
  x, y, w, h = widget.allocation.to_a
  if random_mode
    draw_random_shapes(context, w, h)
  else
    draw_sample_shapes(context, w, h)
  end
  true
end

window.add(area)

window.show_all

Gtk.main

