require 'cairo'
require 'stringio'

class SurfaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_new
    output = StringIO.new
    surface = Cairo::PDFSurface.new(output, 10, 10)
    assert_no_match(/%%EOF\s*\z/m, output.string)
    surface.finish
    assert_match(/%%EOF\s*\z/m, output.string)
  end

  def test_new_with_block
    output = StringIO.new
    Cairo::PDFSurface.new(output, 10, 10) do |surface|
      assert_no_match(/%%EOF\s*\z/m, output.string)
    end
    assert_match(/%%EOF\s*\z/m, output.string)
  end

  def test_new_with_block_and_finish
    assert_nothing_raised do
      Cairo::PDFSurface.new(StringIO.new, 10, 10) do |surface|
        surface.finish
      end
    end
  end

  def test_fallback_resolution
    surface = Cairo::ImageSurface.new(100, 100)

    assert_equal([300.0, 300.0], surface.fallback_resolution)

    only_cairo_version(1, 7, 2)
    surface.set_fallback_resolution(95, 95)
    assert_equal([95.0, 95.0], surface.fallback_resolution)
  end
end
