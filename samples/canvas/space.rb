#!/usr/bin/env ruby

$LOAD_PATH.unshift "../../packages/gtkcairo/ext/"
$LOAD_PATH.unshift "../../packages/cairo/ext/"
$LOAD_PATH.unshift "../../packages/cairo/lib/"

require 'canvas'

module SPACE

# == "application menu"
#
# preliminary application menu, allowinging to construct
# the predefined Pad s from within your user interface

    class AppMenu < CANVAS::VPad


      def components
         list = Dir['*.rb']
         ["space.rb","canvas.rb","fdlogo.rb"].each {|item| list=list.delete_if {|itemb| itemb==item}}
          list
      end

      def initialize hash={"x"=>0, "y"=>0}
        super hash.update("spacing" => 4)
        @offset= hash["offset"] || 64
        @x_pos, @y_pos = @offset, @offset
      end

      # add a new window to the toplevel, implementing
      # a cascading behavior for new positions
      def add_pad pad
        toplevel << pad

        pad.x = @x_pos
        pad.y = @x_pos

        @x_pos += @offset
        @y_pos += @offset

        @x_pos = @offset if @x_pos + @offset > toplevel.width
        @y_pos = @offset if @y_pos + @offset > toplevel.height
      end

      def launch_component toplevel, component
          load component
          pad_creator = File.new(component).read.split("\n").last
          add_pad eval(pad_creator)
      end

      # add pad that might be created,
      # kind is the class to instantiate as a child of the toplevel
      # canvas

      def add_entry kind, label=kind.to_s
        self << CANVAS::Button.new(
              "label"=> label,
              "action" => proc {launch_component toplevel, label}
              )
      end
    end

  class Menu < AppMenu
    def initialize
      super
      puts components
     
      components.each {|component| add_entry component} 
    end
  end

  class Space < CANVAS::CanvasTopLevel
    def initialize
        
      super "width"  => 640,
            "height" => 480,
            "title"  => "ruby cairo space"

      self << Menu.new
      self << CANVAS::ResizePod.new
    end
  end

end


  CANVAS.init
  SPACE::Space.new
  CANVAS.main
