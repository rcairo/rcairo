#!/usr/bin/env ruby
# vim: set ts=2 sw=2 et :

module TANGRAM

require 'canvas'

class RotationLine < CANVAS::Line
  # calculate angle betwen two coordinate pairs
  def angle x0, y0, x1, y1
    Math::atan2((y1-y0), (x1-x0))
  end
  def init
    @active_tan = @parent.active_tan
    @original_rotation  = @active_tan.rotation
    @start_rotation     = angle(@active_tan.x, @active_tan.y, self.x1,self.y1)
    @prev_x = self.x1
    @prev_y = self.y1
  end
  def motion x,y,event

    delta_x, delta_y = x-@prev_x,  y-@prev_y

    if @active_tan.flipped
          @active_tan.rotation = @original_rotation - (angle(@active_tan.x, @active_tan.y,x,y) - @start_rotation)
    else
          @active_tan.rotation = @original_rotation + (angle(@active_tan.x, @active_tan.y,x,y) - @start_rotation)
    end
 
    self.x1, self.y1= x,y
    @parent.queue_draw
  end
  def release x,y,button
    mouse_release
    @parent.delete self
    @parent.queue_draw
  end
end

class Tan < CANVAS::Item
  attr_accessor :edge_length, :rotation, :flipped, :active
  def initialize hash
    super hash
    @edge_length = hash["edge_length"] || 100
    @rotation    = hash["rotation"]    || 0.0

    @flipped  = false
    @active   = false
    @in_drag  = false
  end

  def flip!
    self.flipped = !self.flipped
  end
  
  def pre_shape cr
    cr.translate(@x, @y)
    cr.scale(1, -1) if @flipped
    cr.rotate(@rotation)
    cr.translate(-@x,-@y)
  end

  def post_shape cr
    # FIXME: need to figure out how to access the matrix functions in cairo
    cr.translate(@x, @y)
    cr.rotate(-@rotation)
    cr.scale(1, -1) if @flipped
    cr.translate(-@x, -@y)
  end
  
  def make_shape cr
    cr.arc  @x, @y, 40, 0, 3.14*2
  end
 
  def fill_color cr
      cr.rgb_color = [0.45, 0.45, 1.0] if @active
      cr.rgb_color = [0.35, 0.35, 0.65] unless @active
  end
  
  def paint
    cr = cairo
    cr.save()
      pre_shape cr
      make_shape cr
      post_shape cr
      cr.save()
        fill_color cr
        cr.fill()
      cr.restore()
      
      cr.rgb_color= [0.6,0.8,8]
      cr.line_width=2
      cr.stroke()
    cr.restore()
  end

  def bounding_box
    return @x-@edge_length, @y-@edge_length, @edge_length*2, @edge_length*2
  end
  def hit x,y
    return false if !bound_test x,y
    cr = cairo
    cr.save
      pre_shape cr
      make_shape cr
      post_shape cr
      ret = cr.in_fill?(x, y)
    cr.restore
    ret
  end

  def enter
    #puts "entered tan #{self}"
  end

  def leave
    #puts "left tan #{self}"
  end
  
  def press x,y,button
    #puts  "tan hit #{self}"
    @parent.active_tan=self

    if button==1
      @in_drag = true
      @drag_x = x
      @drag_y = y
      mouse_grab
    elsif button==2
      self.flip!
    elsif button==3
      rot_line    = RotationLine.new "line_width" => 4.0
      rot_line.x0 = @x
      rot_line.y0 = @y
      rot_line.x1 = x
      rot_line.y1 = y

      @parent[:rot_line]=rot_line

      rot_line.init  # must be called after adding to the canvas

      rot_line.mouse_grab
      queue_draw
    end
 
    
 end

  def motion x,y,event
    if @in_drag
      delta_x, delta_y = x-@drag_x,  y-@drag_y

      self.x += delta_x
      self.y += delta_y 

      @drag_x, @drag_y = x, y
      @parent.queue_draw

      #puts "#{self}: #{@x},#{@y} : #{@rotation}"
    else
    end
  end

  def release x,y,button
    @in_drag = false
    mouse_release
  end
end

class Square < Tan
  def initialize
    super "edge_length"=>75 
  end
  def make_shape cr
    cr.rectangle @x-@edge_length/2, @y-@edge_length/2, @edge_length, @edge_length
  end
end

class Triangle < Tan
  def make_shape cr
    cr.move_to(@x, @y)
    cr.rel_move_to(-@edge_length*0.33, -@edge_length*0.33)
    cr.rel_line_to(@edge_length, 0)
    cr.rel_line_to(-@edge_length, @edge_length)
    cr.close_path()
  end
end

class TriangleSmall < Triangle
  def initialize
    super "edge_length"=>75 
  end
end

class TriangleMedium < Triangle
  def initialize
    super "edge_length"=>150/Math::sqrt(2.0)
  end
end

class TriangleBig < Triangle
  def initialize
    super "edge_length"=>150
  end
end



class Parallelogram < Tan
  def initialize
    super "edge_length"=>75 
  end
  def make_shape cr
    cr.move_to(@x, @y)
    cr.rel_move_to(0, -@edge_length/2)
    cr.rel_line_to(@edge_length, 0)
    cr.rel_line_to(-@edge_length, @edge_length)
    cr.rel_line_to(-@edge_length, 0)
    cr.close_path()
  end
end

class Control < CANVAS::HPad
  def initialize tangram_pad, hash
    super hash.update("spacing" => 4.0)
    self << CANVAS::Button.new(
     "label" => "X",
    "action" => proc {parent.parent.delete parent}
    )
 
    self << CANVAS::Button.new(
     "label" => "reset",
    "action" => proc {tangram_pad.square_position}
    )

    help = CANVAS::Label.new(
       "size"  => 14,
       "label" => "Left click to move\n, right click to rotate,\n middle click to flip");

       #self << help
  end
end

class Pad < CANVAS::Pad
  attr_reader :active_tan
  def initialize
    super
    @active_tan  = nil
    @in_rotation = false

    add_tans
    self << CANVAS::MovePod.new("x"=> -20, "y"=> -20)
    self << Control.new(self,
        "x"=> 5,
        "y"=> -40)
  end

  def active_tan= tan
      @active_tan.active = false if @active_tan
      @active_tan = tan

      send_to_front @active_tan
      
      @active_tan.active = true
      queue_draw
  end

  def square_position
    @bigtri_A.x=39
    @bigtri_A.y=105
    @bigtri_A.rotation=-3.9316
    @bigtri_B.x=110
    @bigtri_B.y=175
    @bigtri_B.rotation=0.76823
    @smalltri_A.x=108
    @smalltri_A.y=72
    @smalltri_A.rotation    = 3.9147314
    @smalltri_B.x=196
    @smalltri_B.y=154
    @smalltri_B.rotation    = -0.8199
    @medtri.x=175
    @medtri.y=38
    @medtri.rotation        = 1.5766
    @parallelogram.x=82.0
    @parallelogram.y=29.0
    @parallelogram.rotation = 3.14/4
    @square.x=160
    @square.y=104
    @square.rotation=0.768733
  end
 

  def start_position
    @bigtri_A.x=75
    @bigtri_A.y=75
    @bigtri_A.rotation=0.0
    @bigtri_B.x=241
    @bigtri_B.y=75
    @bigtri_B.rotation=0.0
    @smalltri_A.x=269
    @smalltri_A.y=142
    @smalltri_A.rotation    = 3.14/4
    @smalltri_B.x=308
    @smalltri_B.y=103
    @smalltri_B.rotation    = -3.14/4
    @medtri.x=126
    @medtri.y=120
    @medtri.rotation        = 3.14
    @parallelogram.x=425
    @parallelogram.y=138
    @parallelogram.rotation = 3.14/4
    @square.x=405
    @square.y=61
    @square.rotation=0
  end
 
  def add_tans
    self << @bigtri_A      = TriangleBig.new
    self << @bigtri_B      = TriangleBig.new
    self << @smalltri_A    = TriangleSmall.new
    self << @smalltri_B    = TriangleSmall.new
    self << @medtri        = TriangleMedium.new
    self << @parallelogram = Parallelogram.new
    self << @square        = Square.new

    start_position
    square_position
  end

  def paint
    cr = cairo
    cr.save
      cr.rectangle @x, @y,
                   150 * Math.sqrt(2.0),
                   150 * Math.sqrt(2.0)
      cr.rgb_color = 0,0,0
      cr.alpha = 0.2
      cr.fill
    cr.restore
    
    super
  end
end

end

__END__
TANGRAM::Pad.new
