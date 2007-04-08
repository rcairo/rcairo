#!/usr/bin/env ruby

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
src = File.join(top, "src")
$LOAD_PATH.unshift src
$LOAD_PATH.unshift File.join(src, "lib")

require 'cairo'
require 'stringio'

def render(output, surface_class)
  surface_class.new(output, 200, 200) do |surface|
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

    cr.show_page
    surface.finish
  end
end

def output(surface_class_name, suffix)
  if Cairo.const_defined?(surface_class_name)
    surface_class = Cairo.const_get(surface_class_name)
    render("test.#{suffix}", surface_class)

    output = StringIO.new
    render(output, surface_class)
    output.rewind
    File.open("test2.#{suffix}", "wb") do |f|
      f.print(output.read)
    end
  else
    puts("#{surface_class_name} isn't supported.")
  end
end

output("PSSurface", "ps")
output("PDFSurface", "pdf")
output("SVGSurface", "svg")
