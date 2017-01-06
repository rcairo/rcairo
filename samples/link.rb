#!/usr/bin/env ruby

top = File.expand_path(File.join(File.dirname(__FILE__), ".."))
$LOAD_PATH.unshift File.join(top, "ext", "cairo")
$LOAD_PATH.unshift File.join(top, "lib")

require "cairo"

width = 200
height = 200

Cairo::PDFSurface.new("link.pdf", width, height) do |surface|
  Cairo::Context.new(surface) do |context|
    context.move_to(50, 50)
    context.tag(Cairo::Tag::LINK, "uri='http://rcairo.github.io/'") do
      context.show_text("rcairo site")
    end
  end
end
