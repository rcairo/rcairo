#!/usr/bin/env ruby
#
# 2004 (c) Øyvind Kolås,  <pippin@freedesktop.org>

require 'canvas'

class Fu
  attr_accessor :camera, :lookat, :fov
  attr_accessor :x, :y, :width, :height

  @camera = [0,0,-2]
  @lookat = [0,0,0]
  @fov    = [3.414/2]

  def initialize(camera=[0,0,-2],
                 lookat=[0,0,0],
                 fov=3.1415)
     @camera,@lookat,@fov = camera, lookat, fov

     @x = 0
     @y = 0
     @width = 100
     @height = 100
  end

  def x x,y,z
      @x + @width * 0.5 * (x+1)
  end
  def y x,y,z
      @y + @width * 0.5 * (y+1)
  end
end

class Pad3d < CANVAS::RectPad
  attr_accessor :cr
  def save cr
    cr.save
  end

  def restore cr
    cr.restore
  end

  def move_to(cr, x, y, z)
    cr.move_to(@fu.x(x,y,z),
               @fu.y(x,y,z))
    @ctx_x = x
    @ctx_y = y
    @ctx_z = z
  end

  def rel_move_to(cr, x, y, z)
    cr.move_to(@fu.x(x+@ctx_x,
                     y+@ctx_y,
                     z+@ctx_z),
               @fu.y(x+@ctx_x,
                     y+@ctx_y,
                     z+@ctx_z))
    @ctx_x = x
    @ctx_y = y
    @ctx_z = z
  end

  def line_to(cr, x, y, z)
    cr.line_to(@fu.x(x,y,z),
               @fu.y(x,y,z))
    @ctx_x = x
    @ctx_y = y
    @ctx_z = z
  end

  def rel_line_to(cr, rel_x, rel_y, rel_z)
    cr.line_to(@fu.x(@ctx_x+rel_x,
                     @ctx_y+rel_y,
                     @ctx_z+rel_z),
               @fu.y(@ctx_x+rel_x,
                     @ctx_y+rel_y,
                     @ctx_z+rel_z))
    @ctx_x = @ctx_x + rel_x
    @ctx_y = @ctx_y + rel_y
    @ctx_z = @ctx_z + rel_z
  end


  def curve_to(cr, x0, y0, z0,
                   x1, y1, z1,
                   x2, y2, z2)

    cr.curve_to(@fu.x(x0,y0,z0),
                @fu.y(x0,y0,z0),
                @fu.x(x1,y1,z1),
                @fu.y(x1,y1,z1),
                @fu.x(x2,y2,z2),
                @fu.y(x2,y2,z2))
  end

  def rel_curve_to(cr,
                   x0, y0, z0,
                   x1, y1, z1,
                   x2, y2, z2)

    cr.curve_to(@fu.x(@ctx_x + x0,
                      @ctx_y + y0,
                      @ctx_z + z0),
                @fu.y(@ctx_x + x0,
                      @ctx_y + y0,
                      @ctx_z + z0),
                @fu.x(@ctx_x + x1,
                      @ctx_y + y1,
                      @ctx_z + z1),
                @fu.y(@ctx_x + x1,
                      @ctx_y + y1,
                      @ctx_z + z1),
                @fu.x(@ctx_x + x2,
                      @ctx_y + y2,
                      @ctx_z + z2),
                @fu.y(@ctx_x + x2,
                      @ctx_y + y2,
                      @ctx_z + z2))

    @ctx_x = @ctx_x + x2
    @ctx_y = @ctx_y + y2
    @ctx_z = @ctx_z + z2
 
  end



  def arc(cr, x,y,z, radius, start_angle, span)
    cr.arc(@fu.x(x,y,z),
           @fu.y(x,y,z),
           radius,
           start_angle,
           span)
  end

  def draw_axis
      arc(@cr, 0, 0, 0, 8, 0, 3.14*2)
      @cr.fill
      move_to @cr, -1, 0, 0
      rel_line_to @cr, 2, 0, 0
      move_to @cr, 0, -1, 0
      rel_line_to @cr,0, 2, 0
      move_to @cr, 0, 0, -1
      rel_line_to @cr,0, 0, 2
      @cr.stroke
  end
   
  def paint_3d
      @fu.x=@x
      @fu.y=@y
      @fu.width=@width
      @fu.height=@height
      draw_axis
  end
 

  def initialize hash={"width" => 100,
                       "height"=> 100}
    super hash
    
    @fu = Fu.new
   
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
    @cr=cairo

    @cr.save
      @cr.move_to @x, @y
      @cr.rel_line_to @width, @height
      @cr.stroke
      paint_3d
    @cr.restore
  end
end

__END__
Pad3d.new
