#!/usr/bin/env ruby

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
$LOAD_PATH.unshift File.join(top, "ext", "cairo")
$LOAD_PATH.unshift File.join(top, "lib")

require 'cairo'
require 'pango'

def render_background(cr)
  cr.set_source_color(:white)
  cr.paint
end

def make_layout(cr, text)
  layout = cr.create_pango_layout
  layout.text = text
  layout.font_description = Pango::FontDescription.new("Serif 36")
  cr.update_pango_layout(layout)
  layout
end

def render(surface)
  text = "It was a dream... Oh Just a dream..."

  cr = Cairo::Context.new(surface)

  render_background(cr)

  cr.set_source_color(:red)
  cr.move_to(25, 350)
  cr.line_to(150, 375)
  cr.curve_to(275, 400, 450, 350, 450, 200)
  cr.curve_to(450, 0, 300, 150, 50, 50)
  cr.stroke_preserve
  path = cr.copy_path_flat

  cr.line_width = 1
  cr.new_path
  layout = make_layout(cr, text)
  cr.pango_layout_line_path(layout.get_line(0))
  cr.map_path_onto(path)

  cr.set_source_rgba(0.3, 0.3, 1.0, 0.3)
  cr.fill_preserve
  cr.set_source_rgba(0.1, 0.1, 0.1)
  cr.stroke

  cr.show_page
end

def output
  Cairo::ImageSurface.new(500, 500) do |surface|
    render(surface)
    surface.write_to_png("text-on-path.png")
  end
end

output
