#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

$:.push File.join(File.dirname($0), "cairo")

require 'cairo'
include Cairo

def normalize cr,width,height
    cr.scale width, height
end

File.open("gradients.png", "wb") {|stream|
    cr = Context.new
    cr.set_target_png(stream, FORMAT_ARGB32, 200, 200);

    normalize cr, 200, 200
    pat = Pattern.create_linear(0,0,0,1)
    pat.add_color_stop(1,0,0,0,1)
    pat.add_color_stop(0,1,1,1,1)
   
    cr.set_pattern(pat)         # or cr.pattern=pat
    cr.rectangle(0, 0, 1, 1)
    cr.fill

    # draw a sphere, using more syntactic sugar:
    cr.pattern = Pattern.create_radial(0.45, 0.4, 0.1,
                                       0.40, 0.4, 0.5) do
        |pat|
        pat.add_color_stop(0,1,1,1,1)
        pat.add_color_stop(1,0,0,0,1)
    end
    cr.fill {
        cr.arc 0.5, 0.5, 0.3, 0, 2*3.1415
    }
    cr.show_page
}

