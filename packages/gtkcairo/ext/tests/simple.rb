#!/usr/bin/env ruby
# vim: set ts=2 sw=2 et :

$LOAD_PATH << "../src"

require 'gtk2'

$LOAD_PATH << "../../src"
require 'cairo'

$LOAD_PATH << ".."
require 'gtkcairo'

class DemoWindow < Gtk::Window
	def initialize
    super

    @gc = Gtk::CairoWidget.new

    set_default_size(200, 200)
    signal_connect('destroy') { Gtk.main_quit }
    @gc.signal_connect('redraw') { redraw }

    vb = Gtk::VBox.new(FALSE, 5)
    vb.border_width = 10
    vb.pack_start(@gc, TRUE, TRUE, 0)
    vb.show_all
    add(vb)
  end
  def redraw
    cr = @gc.cairo
    cr.set_rgb_color(0, 0, 0)
    cr.rectangle(0, 0, 100, 100)
    cr.fill

    cr.set_rgb_color(1, 0, 0)
    cr.rectangle(10, 10, 50, 50)
    cr.fill
  end
end

Gtk.init
win = DemoWindow.new
win.show
Gtk.main
