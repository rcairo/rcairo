#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

$:.push File.join(File.dirname($0), "cairo")

require 'cairo'
include Cairo

def draw_quad(ctx, x0, y0, x1, y1, x2, y2)
    ctx.new_path
    ctx.move_to(x0, y0)
    ctx.line_to(x1, y1)
    ctx.line_to(x2, y2)

    ctx.set_rgb_color(1.0, 0.0, 0.0)
    ctx.save
    ctx.alpha = 0.2
    ctx.fill
    ctx.restore
    ctx.line_width = 1
    ctx.stroke

    ctx.new_path
    ctx.move_to(x0, y0)
    ctx.quad_to(x1, y1, x2, y2)
    
    ctx.set_rgb_color(0.0, 0.0, 0.0)
    ctx.line_width = 3
    ctx.stroke
end

File.open("test-1.png", "wb") {|stream|
    ctx = Context.new
    ctx.set_target_png(stream, FORMAT_ARGB32, 200, 200);

    ctx.new_path
    ctx.rectangle(0, 0, 200, 200)

    ctx.set_rgb_color(1.0, 1.0, 1.0)
    ctx.fill

    draw_quad(ctx, 20, 20, 110, 25, 180, 180)

    ctx.show_page
}

