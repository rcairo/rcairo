#!/usr/bin/env ruby
#
# 2004 (c) Øyvind Kolås,  <pippin@freedesktop.org>

require 'canvas'

module FM

class Control < CANVAS::HPad
    def initialize
        super "x"=>10, "y"=> -20, "spacing" => 6
        self << CANVAS::Label.new(
            "label"=>"File Manager"
        )
       self << CANVAS::Button.new(
            "label"=>"@",
            "action" => proc {parent.reload}
        )
        self << CANVAS::Button.new(
            "label"=>"X",
            "action" => proc {parent.parent.delete parent}
        )
    end
end

class Folder < CANVAS::VPad
    def handle_entry entry
        puts "pretending to handle #{entry}"
    end
    def initialize
        super
        entries = Dir.new(Dir.pwd).entries.sort

        entries.each do |entry|
          self << CANVAS::Button.new(
            "label"=>entry,
            "action"=> proc {handle_entry entry}
          )
        end
    end
end

class FileManager < CANVAS::Pad
  def initialize 
    super
    self << CANVAS::MovePod.new
    self << Control.new

    @folder = Folder.new
    self << @folder
  end

  def reload
      self.delete @folder
      @folder = Folder.new
      self << @folder
  end
  
end

end

__END__
FM::FileManager.new
