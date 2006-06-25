#!/usr/bin/env ruby

$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

require 'cairo'

format = Cairo::FORMAT_ARGB32
width = 200
height = 200

surface = Cairo::ImageSurface.new(format, width, height)
cr = Cairo::Context.new(surface)

# fill background with white
cr.set_source_rgba(1.0, 1.0, 1.0, 0.8)
cr.paint

# create shape
cr.move_to(50, 50)
cr.curve_to(100, 25, 100, 75, 150, 50)
cr.line_to(150, 150)
cr.line_to(50, 150)
cr.close_path

cr.set_source_rgb(0.0, 0.0, 0.0)
cr.fill_preserve
cr.set_source_rgb(1.0, 0.0, 0.0)
cr.set_line_join(Cairo::LINE_JOIN_MITER)
cr.set_line_width(4)
cr.stroke

cr.target.write_to_png("test.png")

data = cr.target.data
stride = cr.target.stride

cr.target.finish

surface = Cairo::ImageSurface.new(data, Cairo::FORMAT_ARGB32,
                                  width, height, stride)
surface.write_to_png("test-renew.png")
