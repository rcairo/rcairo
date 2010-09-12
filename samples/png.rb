#!/usr/bin/env ruby

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
$LOAD_PATH.unshift File.join(top, "ext", "cairo")
$LOAD_PATH.unshift File.join(top, "lib")

require 'cairo'

width = 200
height = 200

data = nil
stride = nil

Cairo::ImageSurface.new(width, height) do |surface|
  cr = Cairo::Context.new(surface)

  # fill background with white
  cr.set_source_color("#fffc")
  cr.paint

  # create shape
  cr.move_to(50, 50)
  cr.curve_to(100, 25, 100, 75, 150, 50)
  cr.line_to(150, 150)
  cr.line_to(50, 150)
  cr.close_path

  cr.set_source_color(:black)
  cr.fill_preserve
  cr.set_source_color(:red)
  cr.set_line_join(Cairo::LINE_JOIN_MITER)
  cr.set_line_width(4)
  cr.stroke

  cr.target.write_to_png("test.png")

  data = cr.target.data
  stride = cr.target.stride
end

Cairo::ImageSurface.new(data, :argb32, width, height, stride) do |surface|
  surface.write_to_png("test-renew.png")
end
