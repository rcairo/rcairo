#!/usr/bin/env ruby

$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

require 'optparse'
require 'ostruct'

require 'cairo'
require 'pango'

def parse(args=ARGV)
  options = OpenStruct.new
  options.width = 595.275590551181.round
  options.height = 841.889763779528.round
  options.font_description = "Monospace 12"

  opts = OptionParser.new do |opts|
    opts.on("--width=WIDTH", "paper width") do |width|
      options.width = width.to_i
    end

    opts.on("--height=HEIGHT", "paper width") do |width|
      options.width = width.to_i
    end

    opts.on("--font-description=DESCRIPTION",
            "font description (e.g. 'Monospace 14')") do |desc|
      options.font_description = desc
    end
  end

  opts.parse!(args)

  options
end

def render(text, width, height, font_description, output, surface_class)
  margin_left = (width * 0.05).ceil
  margin_right = (width * 0.05).ceil
  margin_top = (height * 0.05).ceil
  margin_bottom = (height * 0.05).ceil
  body_width = width - margin_left - margin_right
  body_height = height - margin_top - margin_bottom

  surface = surface_class.new(output, width, height)
  cr = Cairo::Context.new(surface)

  cr.set_source_rgba(1.0, 1.0, 1.0)
  cr.paint

  cr.set_source_rgba(0, 0, 0, 1)
  layout = cr.create_pango_layout
  layout.text = text
  layout.width = body_width * Pango::SCALE
  layout.font_description = Pango::FontDescription.new(font_description)
  cr.update_pango_layout(layout)

  x = margin_left
  y = margin_top
  rest_height = body_height
  layout.lines.each do |line|
    ink_rect, logical_rect = line.pixel_extents
    line_height = logical_rect.height
    if rest_height < line_height
      cr.show_page
      rest_height = body_height
      y = margin_top
    end
    cr.move_to(x + logical_rect.x, y - logical_rect.y)
    cr.show_pango_layout_line(line)
    rest_height -= line_height
    y += line_height
  end

  cr.show_page

  cr.target.finish
  cr
end

def output(text, width, height, font_description, surface_class_name, suffix)
  if Cairo.const_defined?(surface_class_name)
    surface_class = Cairo.const_get(surface_class_name)
    render(text, width, height, font_description,
           "text2.#{suffix}", surface_class)
  else
    puts("#{surface_class_name} isn't supported.")
  end
end

options = parse
width = options.width
height = options.height
font_description = options.font_description
text = ARGF.read
output(text, width, height, font_description, "PSSurface", "ps")
output(text, width, height, font_description, "PDFSurface", "pdf")
output(text, width, height, font_description, "SVGSurface", "svg")
