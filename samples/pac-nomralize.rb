=begin
  pac-normalize.rb - rcairo sample script with #scale and #translate.

  Original: pac.rb in http://www.artima.com/rubycs/articles/pdf_writer3.html
=end

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
$LOAD_PATH.unshift File.join(top, "ext", "cairo")
$LOAD_PATH.unshift File.join(top, "lib")

require "cairo"

def pac(surface, width, height)
  cr = Cairo::Context.new(surface)

  # NOTE: You may need to set line width when use Cairo::Context#scale
  cr.set_line_width(cr.line_width / [width, height].max)

  cr.scale(width, height)

  cr.save do
    cr.set_source_color(:black)
    cr.rectangle(0, 0, 1, 1)
    cr.fill
  end

  # Wall
  wall_width = 0.89
  wall_height = 0.03
  wall_space = 0.5
  wall_x = 0.02
  wall1_y = 1 - 0.86
  wall2_y = wall1_y + wall_space
  wall_radius = 0.01

  cr.set_source_color(:magenta)
  cr.rounded_rectangle(wall_x, wall1_y, wall_width, wall_height, wall_radius)
  cr.fill
  cr.set_source_color(:cyan)
  cr.rounded_rectangle(wall_x, wall1_y, wall_width, wall_height, wall_radius)
  cr.stroke

  cr.set_source_color(:magenta)
  cr.rounded_rectangle(wall_x, wall2_y, wall_width, wall_height, wall_radius)
  cr.fill
  cr.set_source_color(:cyan)
  cr.rounded_rectangle(wall_x, wall2_y, wall_width, wall_height, wall_radius)
  cr.stroke

  # Body
  body_x = 0.17
  body_y = 1 - 0.58
  body_width = 0.23
  body_height = 0.33

  cr.save do
    cr.translate(body_x, body_y)
    cr.set_source_color(:yellow)
    cr.scale(body_width, body_height)
    cr.arc(0, 0, 0.5, 30 * (Math::PI / 180), 330 * (Math::PI / 180))
    cr.line_to(0, 0)
    cr.close_path
    cr.fill
  end

  # Dot
  dot_width = 0.02
  dot_height = 0.03
  small_dot_width = 0.01
  small_dot_height = 0.015
  dot_x = 0.29
  dot_y = 1 - 0.58
  dot_step = 0.05

  cr.save do
    cr.set_source_color(:yellow)
    cr.save do
      cr.translate(dot_x, dot_y)
      cr.scale(dot_width, dot_height)
      cr.circle(0, 0, 1).fill
    end

    4.times do |i|
      cr.save do
        cr.translate(dot_x + dot_step * (i + 1), dot_y)
        cr.scale(small_dot_width, small_dot_height)
        cr.circle(0, 0, 1).fill
      end
    end
   end

  # Ghost
  ghost_x = 0.59
  ghost_x_step = 0.03
  ghost_y = 1 - 0.42
  ghost_y_step = 0.04
  ghost_width = 0.18
  ghost_height = 0.29
  ghost_radius= 0.08
  cr.move_to(ghost_x, ghost_y)
  cr.line_to(ghost_x, ghost_y - ghost_height)
  cr.curve_to(ghost_x + ghost_width / 3.0,
              ghost_y - ghost_height - ghost_radius,
              ghost_x + ghost_width * (2.0 / 3.0),
              ghost_y - ghost_height - ghost_radius,
              ghost_x + ghost_width,
              ghost_y - ghost_height)
  cr.line_to(ghost_x + ghost_width, ghost_y)
  i = 0
  (ghost_x + ghost_width).step(ghost_x, -ghost_x_step) do |x|
    cr.line_to(x, ghost_y + -ghost_y_step * (i % 2))
    i += 1
  end
  cr.close_path

  cr.set_source_color(:blue)
  cr.fill_preserve
  cr.set_source_color(:cyan)
  cr.stroke

  # Ghost Eyes
  eye_x = 0.62
  eye_y = 1 - 0.63
  eye_space = 0.06
  white_eye_width = 0.03
  white_eye_height = 0.04
  black_eye_width = 0.01
  black_eye_height = 0.02

  cr.set_source_color(:white)
  cr.rectangle(eye_x, eye_y - white_eye_height,
               white_eye_width, white_eye_height)
  cr.fill
  cr.rectangle(eye_x + eye_space, eye_y - white_eye_height,
               white_eye_width, white_eye_height)
  cr.fill

  cr.set_source_color(:black)
  cr.rectangle(eye_x, eye_y - black_eye_height,
               black_eye_width, black_eye_height)
  cr.fill
  cr.rectangle(eye_x + eye_space, eye_y - black_eye_height,
               black_eye_width, black_eye_height)
  cr.fill

  cr.show_page
end

paper = Cairo::Paper.parse(:a4_landscape)

size_in_points = paper.size("pt")
Cairo::ImageSurface.new(*size_in_points) do |surface|
  cr = pac(surface, *size_in_points)
  cr.target.write_to_png("pac-normalize.png")
end

scalable_surface_output = Proc.new do |surface_class_name, suffix|
  if Cairo.const_defined?(surface_class_name)
    surface_class = Cairo.const_get(surface_class_name)
    surface_class.new("pac-normalize.#{suffix}", paper) do |surface|
      pac(surface, *size_in_points)
    end
  else
    puts("#{surface_class_name} isn't supported.")
  end
end

scalable_surface_output.call("PSSurface", "ps")
scalable_surface_output.call("PDFSurface", "pdf")
scalable_surface_output.call("SVGSurface", "svg")
