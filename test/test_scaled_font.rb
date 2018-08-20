require 'cairo'
require 'stringio'

class ScaledFontTest < Test::Unit::TestCase
  include Helper

  def test_scale_matrix
    only_cairo_version(1, 7, 2)

    surface = Cairo::ImageSurface.new(100, 100)
    context = Cairo::Context.new(surface)
    scaled_font = context.scaled_font

    assert_equal(Cairo::Matrix.new(10.0, 0.0, 0.0,
                                   10.0, 0.0, 0.0),
                 scaled_font.scale_matrix)
  end

  def test_text_to_glyphs
    only_cairo_version(1, 7, 6)

    surface = Cairo::PDFSurface.new(StringIO.new, 10, 10)
    context = Cairo::Context.new(surface)
    scaled_font = Cairo::ScaledFont.new(context.font_face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)
    expected_glyphs = []
    expected_clusters = []
    expected_cluster_flags = 0
    assert_equal([expected_glyphs, expected_clusters, expected_cluster_flags],
                 scaled_font.text_to_glyphs(0, 0, "text"))
  end
end
