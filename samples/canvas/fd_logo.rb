#!/usr/bin/env ruby
#
# 2004 (c) Øyvind Kolås,  <pippin@freedesktop.org>

require 'canvas'

require 'fdlogo'
class FdLogoPad < CANVAS::RectPad
  def initialize hash={"width" => 100,
                       "height"=> 100}
    super hash
    @width  = hash["width"]  || 100
    @height = hash["height"] || 100

    self << CANVAS::MovePod.new
    self << CANVAS::ResizePod.new

    self << CANVAS::Button.new(
        "label" => "X",
       "action" => proc {parent.delete self}
    )
  end

  def paint
    super
    cr=cairo

    cr.save
      cr.translate @x, @y
      cr.fd_logo @width, @height
    cr.restore
  end
end

__END__
FdLogoPad.new
