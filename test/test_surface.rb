require 'cairo'
require 'stringio'

class SurfaceTest < Test::Unit::TestCase
  include Helper

  def test_new
    output = StringIO.new
    surface = Cairo::PDFSurface.new(output, 10, 10)
    assert_not_equal("%%EOF\n", output.string[-6..-1])
    surface.finish
    assert_equal("%%EOF\n", output.string[-6..-1])
  end

  def test_create_with_block
    output = StringIO.new
    Cairo::PDFSurface.create(output, 10, 10) do |surface|
      assert_not_equal("%%EOF\n", output.string[-6..-1])
    end
    assert_equal("%%EOF\n", output.string[-6..-1])
  end

  def test_create_with_block_and_finish
    assert_nothing_raised do
      Cairo::PDFSurface.create(StringIO.new, 10, 10) do |surface|
        surface.finish
      end
    end
  end

  def test_device_scale
    only_cairo_version(1, 14, 0)
    surface = Cairo::ImageSurface.new(100, 100)

    assert_equal([1.0, 1.0], surface.device_scale)

    surface.set_device_scale(3.0, 4.0)
    assert_equal([3.0, 4.0], surface.device_scale)
  end

  def test_fallback_resolution
    only_cairo_version(1, 7, 2)

    surface = Cairo::ImageSurface.new(100, 100)

    assert_equal([300.0, 300.0], surface.fallback_resolution)

    surface.set_fallback_resolution(95, 95)
    assert_equal([95.0, 95.0], surface.fallback_resolution)
  end

  def test_mime_data
    only_cairo_version(1, 10, 0)

    output = StringIO.new
    surface = Cairo::PDFSurface.new(output, 100, 100)
    surface.set_mime_data(Cairo::MimeType::URI, "http://cairo.rubyforge.org/")
    assert_equal("http://cairo.rubyforge.org/",
                 surface.get_mime_data(Cairo::MimeType::URI))
  end
end
