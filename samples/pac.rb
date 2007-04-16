=begin
  pac.rb - rcairo sample script.

  Original: pac.rb in http://www.artima.com/rubycs/articles/pdf_writer3.html
=end

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
src = File.join(top, "src")
$LOAD_PATH.unshift src
$LOAD_PATH.unshift File.join(src, "lib")

require "cairo"

WIDTH = 841.889763779528
HEIGHT = 595.275590551181

def pac(surface)
  cr = Cairo::Context.new(surface)

  cr.set_source_color(:black)
  cr.rectangle(0, 0, WIDTH, HEIGHT).fill

  # Wall
  cr.set_source_color(:magenta)
  cr.rounded_rectangle(20, 80, 750, 20, 10)
  cr.fill
  cr.set_source_color(:cyan)
  cr.rounded_rectangle(20, 80, 750, 20, 10)
  cr.stroke

  cr.set_source_color(:magenta)
  cr.rounded_rectangle(20, 380, 750, 20, 10)
  cr.fill
  cr.set_source_color(:cyan)
  cr.rounded_rectangle(20, 380, 750, 20, 10)
  cr.stroke

  # Body
  cr.set_source_color(:yellow)
  cr.fill do
    cr.arc(150, 250, 100, 30 * (Math::PI / 180), 330 * (Math::PI / 180))
    cr.line_to(150, 250)
  end

  # Dot
  cr.set_source_color(:yellow)
  cr.circle(250, 250, 20).fill
  cr.circle(300, 250, 10).fill
  cr.circle(350, 250, 10).fill
  cr.circle(400, 250, 10).fill
  cr.circle(450, 250, 10).fill

  # Ghost
  cr.move_to(500, 350)
  cr.line_to(500, 175)
  cr.curve_to(550, 125, 600, 125, 650, 175)
  cr.line_to(650, 350)
  cr.line_to(625, 325)
  cr.line_to(600, 350)
  cr.line_to(575, 325)
  cr.line_to(550, 350)
  cr.line_to(525, 325)
  cr.line_to(500, 350)

  cr.set_source_color(:blue)
  cr.fill_preserve
  cr.set_source_color(:cyan)
  cr.stroke

  # Ghost Eyes
  cr.set_source_color(:white)
  cr.rectangle(525, 200, 25, 25).fill
  cr.rectangle(575, 200, 25, 25).fill

  cr.set_source_color(:black)
  cr.rectangle(525, 215, 10, 10).fill
  cr.rectangle(575, 215, 10, 10).fill

  cr.show_page
end

Cairo::ImageSurface.new(WIDTH, HEIGHT) do |surface|
  cr = pac(surface)
  cr.target.write_to_png("pac.png")
end

def scalable_surface_output(surface_class_name, suffix)
  if Cairo.const_defined?(surface_class_name)
    surface_class = Cairo.const_get(surface_class_name)
    surface_class.new("pac.#{suffix}", WIDTH, HEIGHT) do |surface|
      pac(surface)
    end
  else
    puts("#{surface_class_name} isn't supported.")
  end
end

scalable_surface_output("PSSurface", "ps")
scalable_surface_output("PDFSurface", "pdf")
scalable_surface_output("SVGSurface", "svg")
