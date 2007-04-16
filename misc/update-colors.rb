#!/usr/bin/env ruby

begin
  require 'scrapi'
rescue LoadError
  require 'rubygems'
  require 'scrapi'
end

row = Scraper.define do
  process "th > a:first-child", :name => :text
  process "td:nth-child(3)", :hex_triplet => :text
  process "td:nth-child(4)", :red => :text
  process "td:nth-child(5)", :green => :text
  process "td:nth-child(6)", :blue => :text
  result :name, :hex_triplet, :red, :green, :blue
end

scraper = Scraper.define do
  process "table > tr", "rows[]" => row
  result :rows
end

colors = scraper.scrape(URI("http://en.wikipedia.org/wiki/List_of_colors"))

def constanize_color_name(name)
  names = name.gsub(/&eacute;/, "e").upcase.split(/(?:\s*\(|\)\s*)/)
  names = names.collect {|name| name.gsub(/[ \-]/, "_")}
  if names[1] and ["WEB", "COLOR_WHEEL", "X11"].include?(names[1])
    real_names = [names.join("_")]
    if names == ["ORANGE", "COLOR_WHEEL"]
      real_names << names.first
    end
    names = real_names
  end
  names
end

top_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
colors_rb = File.join(top_dir, "src", "lib", "cairo", "colors.rb")
File.open(colors_rb, "w") do |rb|
  rb.puts <<-HEADER
require 'cairo/color'

module Cairo
  module Color
HEADER

  colors.each do |color|
    if color.name and color.hex_triplet and
        color.red and color.green and color.blue
      begin
        names = constanize_color_name(color.name)

        hexes = color.hex_triplet.scan(/[\da-f]{2,2}/i)
        red_hex, green_hex, blue_hex = hexes.collect {|hex| hex.hex}

        red = Integer(color.red)
        green = Integer(color.green)
        blue = Integer(color.blue)

        if [red_hex, green_hex, blue_hex] != [red, green, blue]
          warning_message = "Hex triplet(#{color.hex_triplet}) of "
          warning_message << "#{color.name} is difference from RGB"
          warning_message << "(#{red}, #{green}, #{blue}). "
          if ["Alice Blue", "Old Rose"].include?(color.name)
            warning_message << "Use hex triplet value."
            red, green, blue = red_hex, green_hex, blue_hex
          else
            warning_message << "Use RGB value."
          end
          puts warning_message
        end

        r, g, b = [red, green, blue].collect {|v| v / 255.0}

        rb.puts("    # #{color.name}: #{color.hex_triplet}")
        name, *alias_names = names
        rb.puts("    #{name} = RGB.new(#{r}, #{g}, #{b})")
        alias_names.each do |alias_name|
          rb.puts("    #{alias_name} = #{name}")
        end
      rescue ArgumentError
        next
      end
    end
  end

  rb.puts <<-FOOTER
  end
end
FOOTER
end
