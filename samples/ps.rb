#!/usr/bin/env ruby
# vim: set ts=2 sw=2 et :

$LOAD_PATH.unshift "../packages/cairo/lib/"
$LOAD_PATH.unshift "../packages/cairo/ext/"

require 'cairo'

cr = Cairo::Context.new

# tweak these:
SIZE = 4
DPI = 200
FILENAME = 'test.ps'

# derived constants:
PIXELS = SIZE * DPI
MARGIN = PIXELS/40

File.open(FILENAME, "w") { |f|
  cr.set_target_ps(f, SIZE, SIZE, DPI, DPI)
  cr.set_rgb_color(0,0,0)
  cr.line_cap = Cairo::LINE_CAP_ROUND
  cr.line_width = PIXELS/40
  cr.stroke {
    cr.move_to(MARGIN, MARGIN)
    cr.line_to(PIXELS-MARGIN, PIXELS-MARGIN)
  }
  cr.show_page
}
puts "wrote #{SIZE}x#{SIZE}in, #{DPI}dpi image to #{FILENAME}."

