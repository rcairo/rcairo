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

        signal_connect('button_press_event') do
           |widget,button_event|
           @x = button_event.x
           @y = button_event.y
           queue_draw
        end

        add_events Gdk::Event::BUTTON1_MOTION_MASK
        signal_connect('motion_notify_event') do
           |widget,motion_event|
           @x = motion_event.x
           @y = motion_event.y
           queue_draw
        end
    end
    def paint
        cr = cairo

        cr.save
          cr.rgb_color = 1,0,0
          cr.move_to 20,20
          cr.line_to @x, @y
          cr.rel_line_to 120,0
          cr.stroke

          cr.rgb_color = 0,0,1

          cr.alpha = 1
          cr.move_to @x, @y-4
          cr.select_font "Sans", Cairo::FONT_WEIGHT_NORMAL, Cairo::FONT_SLANT_NORMAL
          cr.scale_font 15
          cr.show_text "Ruby Cairo Foo"

          12.times do
              |i|
              cr.alpha = 0.2
              cr.stroke {
                  radius=@x/(i+1)
                  cr.arc @x, @y, radius, 0, 2*3.1415
              }
          end

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
