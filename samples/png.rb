#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

$:.push File.join(File.dirname($0), "cairo")

require 'cairo'
include Cairo

File.open("test-0.png", "wb") {|stream|
    cr = Context.new
    cr.set_target_png(stream, FORMAT_ARGB32, 200, 200);

    cr.new_path
    cr.rectangle(0, 0, 200, 200)

    cr.set_rgb_color(1.0, 1.0, 1.0)
    cr.fill

    cr.new_path
    cr.move_to(50, 50)
    cr.curve_to(100, 25, 100, 75, 150, 50)
    cr.line_to(150, 150)
    cr.line_to(50, 150)
    cr.close_path

    cr.save # fill will consume the path
    cr.set_rgb_color(0.0, 0.0, 0.0)
    cr.fill
    cr.restore

    cr.set_rgb_color(1.0, 0.0, 0.0)
    cr.line_join = LINE_JOIN_MITER
    cr.line_width = 4
    cr.stroke

    cr.show_page
}


puts "foo"
