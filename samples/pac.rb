=begin
  pac.rb - rcairo sample script.

  Original: pac.rb in http://www.artima.com/rubycs/articles/pdf_writer3.html
=end

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
base = File.join(top, "packages", "cairo")
$LOAD_PATH.unshift File.join(base, "ext")
$LOAD_PATH.unshift File.join(base, "lib")

require "cairo"

WIDTH = 841.889763779528
HEIGHT = 595.275590551181

def pac(surface)
  white = [1, 1, 1]
  black = [0, 0, 0]
  magenta = [1, 0, 1]
  cyan = [0, 1, 1]
  yellow = [1, 1, 0]
  blue = [0, 0, 1]
  
  cr = Cairo::Context.new(surface)

  cr.set_source_rgb(*black)
  cr.rectangle(0, 0, WIDTH, HEIGHT).fill

  # Wall
  cr.set_source_rgb(*magenta)
  cr.rounded_rectangle(20, 80, 750, 20, 10)
  cr.fill
  cr.set_source_rgb(*cyan)
  cr.rounded_rectangle(20, 80, 750, 20, 10)
  cr.stroke
  
  cr.set_source_rgb(*magenta)
  cr.rounded_rectangle(20, 380, 750, 20, 10)
  cr.fill
  cr.set_source_rgb(*cyan)
  cr.rounded_rectangle(20, 380, 750, 20, 10)
  cr.stroke
  
  # Body
  cr.set_source_rgb(*yellow)
  cr.fill do
    cr.arc(150, 250, 100, 30 * (Math::PI / 180), 330 * (Math::PI / 180))
    cr.line_to(150, 250)
  end

  # Dot
  cr.set_source_rgb(*yellow)
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

  cr.set_source_rgb(*blue)
  cr.fill_preserve
  cr.set_source_rgb(*cyan)
  cr.stroke

  # Ghost Eyes
  cr.set_source_rgb(*white)
  cr.rectangle(525, 200, 25, 25).fill
  cr.rectangle(575, 200, 25, 25).fill
  
  cr.set_source_rgb(*black)
  cr.rectangle(525, 215, 10, 10).fill
  cr.rectangle(575, 215, 10, 10).fill
  
  cr.show_page
end

surface = Cairo::ImageSurface.new(WIDTH, HEIGHT)
cr = pac(surface)
cr.target.write_to_png("pac.png")

def scalable_surface_output(surface_class_name, suffix)
  if Cairo.const_defined?(surface_class_name)
    surface_class = Cairo.const_get(surface_class_name)
    surface = surface_class.new("pac.#{suffix}", WIDTH, HEIGHT)
    cr = pac(surface)
    cr.target.finish
  else
    puts("#{surface_class_name} isn't supported.")
  end
end

scalable_surface_output("PSSurface", "ps")
scalable_surface_output("PDFSurface", "pdf")
scalable_surface_output("SVGSurface", "svg")
