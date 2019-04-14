#!/usr/bin/env ruby

require "open-uri"

require "nokogiri"

class Color < Struct.new(:name,
                         :red,
                         :green,
                         :blue,
                         :hex_triplet)
  def valid?
    name and hex_triplet and red and green and blue
  end

  def hex_rgb
    hex_triplet.scan(/[\da-f]{2,2}/i).collect do |hex|
      hex.hex
    end
  end

  def red=(red)
    super(Integer(red, 10))
  end

  def green=(green)
    super(Integer(green, 10))
  end

  def blue=(blue)
    super(Integer(blue, 10))
  end
end

def collect_popular_colors
  colors = []
  names = {}
  open("https://en.wikipedia.org/wiki/List_of_colors_(compact)") do |source|
    document = Nokogiri::HTML(source)
    document.css("div").each do |div|
      elements = div.elements
      next unless elements.collect(&:name) == ["p", "p"]

      color = Color.new

      name = elements[1].text
      case name
      when "Carmine (M&P)"
        color.name = "Rich Carmine"
      when "Khaki (HTML/CSS) (Khaki)"
        color.name = "Khaki"
      when "Khaki (X11) (Light khaki)"
        color.name = "Khaki (X11)"
      when "Lavender (floral)"
        color.name = "Lavender"
      else
        color.name = name
      end
      if names.key?(color.name.downcase)
        puts("#{color.name} is duplicated")
        next
      end

      title = elements[0]["title"].unicode_normalize(:nfkc)
      /RGB \((?<red>\d+)\s+(?<green>\d+)\s+(?<blue>\d+)\)/ =~ title
      color.red = red
      color.green = green
      color.blue = blue
      style = elements[0]["style"]
      /HEX \#(?<hex_triplet>[a-zA-Z\d]+)/ =~ title
      color.hex_triplet = hex_triplet
      color.hex_triplet ||= "C04000" if color.name == "Mahogany"

      unless color.valid?
        puts("Invalid color: #{color.inspect}")
        next
      end

      colors << color
      names[color.name.downcase] = true
    end
  end
  colors
end

def collect_x11_colors
  colors = []
  open("https://en.wikipedia.org/wiki/X11_color_names") do |source|
    document = Nokogiri::HTML(source)
    document.css("table").each do |table|
      caption = (table.css("caption").text || "").strip
      next unless caption == "X11 color names"

      table.css("tr")[1..-1].each do |tr|
        color = Color.new
        th = tr.css("th").first
        color.name = th.text.strip
        tds = tr.css("td")
        color.hex_triplet = tds[0].text.strip.gsub(/\A\#/, "")
        color.red = tds[1]["title"].split("/")[0]
        color.green = tds[2]["title"].split("/")[0]
        color.blue = tds[3]["title"].split("/")[0]
        unless color.valid?
          puts("Invalid X11 color: #{color.inspect}")
          next
        end
        colors << color
      end
    end
  end
  colors
end

def constanize_color_name(name)
  case name
  when "Tenné (tawny)"
    "TAWNY"
  else
    normalized_chars = name.chars.collect do |char|
      char.unicode_normalize(:nfkd)[0]
    end
    name = normalized_chars.join("")
    name = name.gsub(/&eacute;/, "e")
    name = name.gsub(/['().’]/, "")
    name = name.gsub(/\s+\#(\d+)/, "\\1")
    name = name.gsub(/[ \-\/]/, "_")
    name.upcase
  end
end

colors = collect_popular_colors
x11_colors = collect_x11_colors

top_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
colors_rb = File.join(top_dir, "lib", "cairo", "colors.rb")
test_colors_rb = File.join(top_dir, "test", "test_colors.rb")
File.open(colors_rb, "w") do |rb|
  File.open(test_colors_rb, "w") do |test_rb|
    rb.puts(<<-HEADER)
require "cairo/color"

module Cairo
  module Color
    HEADER
    test_rb.puts(<<-HEADER)
class ColorsTest < Test::Unit::TestCase
    HEADER

    [
      [colors, nil],
      [x11_colors, "X11"]
    ].each do |colors, mod|
      indent = "  " * 2
      test_indent = "  "
      if mod
        rb.puts
        rb.puts("#{indent}module #{mod}")
        indent << "  "
        test_rb.puts
        test_rb.puts("#{test_indent}class #{mod}Test < self")
        test_indent << "  "
      end

      first_color = true
      colors.each do |color|
        name = constanize_color_name(color.name)

        red_hex, green_hex, blue_hex = color.hex_rgb
        red = color.red
        green = color.green
        blue = color.blue
        if [red_hex, green_hex, blue_hex] != [red, green, blue]
          warning_message = "Hex triplet(#{color.hex_triplet}) of "
          warning_message << "#{color.name} is difference from RGB"
          warning_message << "(#{red}, #{green}, #{blue}). "
          warning_message << "Use RGB value."
          puts(warning_message)
        end

        r, g, b = [red, green, blue].collect {|v| v / 255.0}

        rb.puts("#{indent}\# #{color.name}: \##{color.hex_triplet}: " +
                "(#{red}, #{green}, #{blue})")
        rb.puts("#{indent}#{name} = RGB.new(#{r}, #{g}, #{b})")
        test_rb.puts unless first_color
        test_rb.puts("#{test_indent}\# #{color.name}: \##{color.hex_triplet}: " +
                     "(#{red}, #{green}, #{blue})")
        test_rb.puts("#{test_indent}test(#{color.name.dump}) do")
        full_name = "Cairo::Color"
        full_name += "::#{mod}" if mod
        full_name += "::#{name}"
        test_rb.puts("#{test_indent}  assert_equal(\"\\\#%02X%02X%02XFF\" % " +
                     "[#{red}, #{green}, #{blue}],")
        test_rb.puts("#{test_indent}               #{full_name}.to_s)")
        test_rb.puts("#{test_indent}end")
        first_color = false
      end

      if mod
        indent = indent[0..-3]
        rb.puts("#{indent}end")
        rb.puts("#{indent}include #{mod}")
        test_indent = test_indent[0..-3]
        test_rb.puts("#{test_indent}end")
      end
    end

    rb.puts(<<-FOOTER)
  end
end
    FOOTER
    test_rb.puts(<<-FOOTER)
end
    FOOTER
  end
end
