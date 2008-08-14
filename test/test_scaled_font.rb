require 'cairo'

class ScaledFontTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_scale_matrix
    only_cairo_version(1, 7, 2)

    surface = Cairo::ImageSurface.new(100, 100)
    context = Cairo::Context.new(surface)
    scaled_font = context.scaled_font

    assert_equal(Cairo::Matrix.new(10.0, 0.0, 0.0,
                                   10.0, 0.0, 0.0),
                 scaled_font.scale_matrix)
  end
end
