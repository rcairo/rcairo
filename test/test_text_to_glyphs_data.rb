require 'cairo'

class TextToGlyphsDataTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_new
    only_cairo_version(1, 7, 2)

    data = Cairo::UserFontFace::TextToGlyphsData.new(false, false, false)
    assert_equal([false, false, false],
                 [data.need_glyphs?, data.need_clusters?, data.need_backward?])

    data = Cairo::UserFontFace::TextToGlyphsData.new(true, false, false)
    assert_equal([true, false, false],
                 [data.need_glyphs?, data.need_clusters?, data.need_backward?])

    data = Cairo::UserFontFace::TextToGlyphsData.new(false, true, false)
    assert_equal([false, true, false],
                 [data.need_glyphs?, data.need_clusters?, data.need_backward?])

    data = Cairo::UserFontFace::TextToGlyphsData.new(false, false, true)
    assert_equal([false, false, true],
                 [data.need_glyphs?, data.need_clusters?, data.need_backward?])
  end

  def test_accessor
    only_cairo_version(1, 7, 2)

    data = Cairo::UserFontFace::TextToGlyphsData.new(true, true, true)
    assert_equal([nil, nil, false],
                 [data.glyphs, data.clusters, data.backward?])

    glyph = Cairo::Glyph.new(0, 5, 10)
    data.glyphs = [glyph]
    assert_equal([[glyph], nil, false],
                 [data.glyphs, data.clusters, data.backward?])

    cluster = Cairo::TextCluster.new(0, 1)
    data.clusters = [cluster]
    assert_equal([[glyph], [cluster], false],
                 [data.glyphs, data.clusters, data.backward?])

    data.backward = true
    assert_equal([[glyph], [cluster], true],
                 [data.glyphs, data.clusters, data.backward?])
  end
end
