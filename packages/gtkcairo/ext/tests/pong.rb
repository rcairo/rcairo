#!/usr/bin/env ruby
# vim: set ts=2 sw=2 et :

require 'gtk2'

$LOAD_PATH << "../../src"
require 'cairo'

$LOAD_PATH << ".."
require 'gtkcairo'

class CenteredRect
  attr_accessor :x, :y
  def initialize(x, y, width, height)
    @x, @y, @width, @height = x, y, width, height
  end
  def minx; @x - @width/2; end
  def maxx; @x + @width/2; end
  def miny; @y - @height/2; end
  def maxy; @y + @height/2; end
  def draw(cr)
    cr.rectangle(minx, miny, @width, @height)
    cr.fill
  end
end

class Ball < CenteredRect
  attr_accessor :dx, :dy
  def initialize
    super(180, 50, 4, 4)
    @dx = @dy = 5
  end
  def update
    @x += @dx; @y += @dy
  end
end

class Paddle < CenteredRect
  def initialize(field, x, y)
    @field = field
    super(x, y, 10, 60)
    @speed = 4
  end
  def update(ball, center)
    # is the ball coming towards us?
    if (ball.x < @x and ball.dx > 0) or
       (ball.x > @x and ball.dx < 0)
      # move to intercept it
      #@y += @speed*(ball.y <=> @y)
      @y = ball.y
    else
      # otherwise, head back towards the center
      if (center - @y).abs > @speed
        @y += @speed*(center <=> @y)
      else
        @y = center
      end
    end
  end
  def ballhittest(ball)
    if ball.y > miny and ball.y < maxy
      if ball.minx < @x and ball.maxx > minx # hit our left side
        ball.x -= (ball.maxx - minx)
        ball.dx = -ball.dx
      elsif ball.maxx > @x and ball.minx < maxx # hit our right side
        ball.x += (maxx - ball.minx)
        ball.dx = -ball.dx
      end
    end
  end
end

class Field
  Margin = 10
  Width = 250
  Height = 200

  attr_accessor :width, :height

  def initialize
    @width = Width
    @height = Height

    @p1 = Paddle.new(self, Margin, 50)
    @p2 = Paddle.new(self, Width-Margin, 80)
    @paddles = [@p1, @p2]
    @ball = Ball.new
  end

  def update
    @paddles.each {|p| p.update(@ball, Height/2)}
    @ball.update

    # ball bouncing
    if @ball.maxy > Height
      @ball.y = Height-(@ball.maxy-Height)
      @ball.dy = -@ball.dy
    elsif @ball.miny < 0
      @ball.y -= @ball.miny
      @ball.dy = -@ball.dy
    end

    if @ball.maxx > Width
      @ball.x = Width-(@ball.maxx-Width)
      @ball.dx = -@ball.dx
    elsif @ball.minx < 0
      @ball.x -= @ball.minx
      @ball.dx = -@ball.dx
    end

    @paddles.each { |p| p.ballhittest(@ball) }

    return TRUE
  end

  def draw(cr)
    cr.set_rgb_color(1,1,1)

    @p1.draw(cr)
    @p2.draw(cr)
    @ball.draw(cr)
  end
end

class PongWindow < Gtk::Window
  Speed = 30

	def initialize
    super

    #set_default_size(200, 200)
    self.title = 'Pong Demonstration'
    signal_connect('destroy') { Gtk.main_quit }

    @field = Field.new

    @gc = Gtk::CairoWidget.new
    @gc.modify_bg(Gtk::STATE_NORMAL, Gdk::Color.new(0,0,0))
    @gc.set_size_request(@field.width, @field.height)
    @gc.signal_connect('redraw') { redraw }

    Gtk::timeout_add(Speed) { @field.update; @gc.queue_draw }

    vb = Gtk::VBox.new(FALSE, 5)
    vb.border_width = 10
    vb.pack_start(@gc, TRUE, TRUE, 0)
    vb.show_all
    add(vb)
  end

  def redraw
    cr = @gc.cairo
    @field.draw(cr)
  end
end

Gtk.init
win = PongWindow.new
win.show
Gtk.main
