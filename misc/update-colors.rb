#!/usr/bin/env ruby

begin
  require 'scrapi'
rescue LoadError
  require 'rubygems'
  require 'scrapi'
end

def collect_popular_colors(src=nil)
  src ||= URI("http://en.wikipedia.org/wiki/List_of_colors")

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

  scraper.scrape(src)
end

def collect_x11_colors(src=nil)
  src ||= URI("http://en.wikipedia.org/wiki/X11_color_names")

  row = Scraper.define do
    process "th", :name => :text
    process "td:nth-child(2)", :hex_triplet => "@bgcolor"
    process "td:nth-child(6)", :red => :text
    process "td:nth-child(7)", :green => :text
    process "td:nth-child(8)", :blue => :text
    result :name, :hex_triplet, :red, :green, :blue
  end

  scraper = Scraper.define do
    process "table > tr", "rows[]" => row
    result :rows
  end

  x11_colors = scraper.scrape(src)
  x11_colors.collect do |color|
    if color.name
      color.name = color.name.gsub(/([a-z]|[A-Z]+)([A-Z])/, "\\1 \\2")
    end
    color
  end
end

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

colors = collect_popular_colors
x11_colors = collect_x11_colors

top_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
colors_rb = File.join(top_dir, "src", "lib", "cairo", "colors.rb")
File.open(colors_rb, "w") do |rb|
  rb.puts <<-HEADER
require 'cairo/color'

module Cairo
  module Color
HEADER

  [
   [colors, nil],
   [x11_colors, "X11"]
  ].each do |colors, mod|
    indent = "  " * 2
    if mod
      rb.puts("#{indent}module #{mod}")
      indent << "  "
    end
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

          rb.puts("#{indent}# #{color.name}: #{color.hex_triplet}")
          name, *alias_names = names
          rb.puts("#{indent}#{name} = RGB.new(#{r}, #{g}, #{b})")
          alias_names.each do |alias_name|
              rb.puts("#{indent}#{alias_name} = #{name}")
            end
        rescue ArgumentError
          next
        end
      end
    end

    if mod
      indent = indent[0..-3]
      rb.puts("#{indent}end")
      rb.puts("#{indent}include #{mod}")
      rb.puts
    end
  end

  rb.puts <<-FOOTER
  end
end
FOOTER
end
