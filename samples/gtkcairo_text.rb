#!/usr/bin/env ruby

$LOAD_PATH.unshift "../packages/gtkcairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/ext/"
$LOAD_PATH.unshift "../packages/cairo/lib/"

require 'gtk2'
require 'cairo'
require 'gtkcairo'

class Canvas < Gtk::CairoWidget
    attr_accessor :x, :y

    def initialize
        super

        @x = 10
        @y = 10
        
        add_events Gdk::Event::BUTTON_PRESS_MASK

        signal_connect('paint') { paint }
        signal_connect('button_press_event') {|w,e|
            press_event e.x, e.y, e.button
        }
    end
    def press_event x,y,b
        @x = x
        @y = y
        queue_draw
    end
    def paint
        cr = cairo

        cr.save
          cr.set_rgb_color 0,0,0
          cr.move_to @x, @y
          cr.line_to 20,20
          cr.stroke
          cr.move_to @x, @y
          
          cr.select_font "Sans", Cairo::FONT_WEIGHT_NORMAL, Cairo::FONT_SLANT_NORMAL
          cr.scale_font 10
          cr.show_text "foo"
        cr.restore
    end
end

Gtk.init

win = Gtk::Window.new
win.signal_connect('destroy') { Gtk.main_quit }
win.set_default_size(512,512)
canvas = Canvas.new
win.add(canvas)
canvas.show
win.show

Gtk.main
