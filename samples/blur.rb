#!/usr/bin/env ruby

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
$LOAD_PATH.unshift File.join(top, "ext", "cairo")
$LOAD_PATH.unshift File.join(top, "lib")

require 'cairo'

margin = 10
rectangle_width = 300
rectangle_height = 100

width = rectangle_width + 2 * margin
height = (rectangle_height + 2 * margin) * 3

surface = Cairo::ImageSurface.new(width, height)
context = Cairo::Context.new(surface)

context.set_source_color(:white)
context.paint

module Cairo
  module Color
    GRAY30 = Cairo::Color::RGB.new(0.3, 0.3, 0.3)
  end
end

context.set_source_color(:gray30)
context.rectangle(margin, margin, rectangle_width, rectangle_height)
context.fill

context.pseudo_blur do
  context.set_source_color(:gray30)
  context.rectangle(margin, rectangle_height + 2 * margin + margin / 2,
                    rectangle_width, rectangle_height)
  context.fill
end

context.pseudo_blur(5) do
  context.set_source_color(:gray30)
  context.rectangle(margin, (rectangle_height + 2 * margin) * 2 + margin / 2,
                    rectangle_width, rectangle_height)
  context.fill
end

surface.write_to_png("blur.png")
