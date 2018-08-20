require 'cairo'

class TextToGlyphsDataTest < Test::Unit::TestCase
  include Helper

  def test_new
    only_cairo_version(1, 7, 6)

    data = Cairo::UserFontFace::TextToGlyphsData.new(false, false, false)
    assert_equal([false, false, false],
                 [data.need_glyphs?, data.need_clusters?,
                  data.need_cluster_flags?])

    data = Cairo::UserFontFace::TextToGlyphsData.new(true, false, false)
    assert_equal([true, false, false],
                 [data.need_glyphs?, data.need_clusters?,
                  data.need_cluster_flags?])

    data = Cairo::UserFontFace::TextToGlyphsData.new(false, true, false)
    assert_equal([false, true, false],
                 [data.need_glyphs?, data.need_clusters?,
                  data.need_cluster_flags?])

    data = Cairo::UserFontFace::TextToGlyphsData.new(false, false, true)
    assert_equal([false, false, true],
                 [data.need_glyphs?, data.need_clusters?,
                  data.need_cluster_flags?])
  end

  def test_accessor
    only_cairo_version(1, 7, 6)

    data = Cairo::UserFontFace::TextToGlyphsData.new(true, true, true)
    assert_equal([nil, nil, 0],
                 [data.glyphs, data.clusters, data.cluster_flags])

    glyph = Cairo::Glyph.new(0, 5, 10)
    data.glyphs = [glyph]
    assert_equal([[glyph], nil, 0],
                 [data.glyphs, data.clusters, data.cluster_flags])

    cluster = Cairo::TextCluster.new(0, 1)
    data.clusters = [cluster]
    assert_equal([[glyph], [cluster], 0],
                 [data.glyphs, data.clusters, data.cluster_flags])

    data.cluster_flags = :backward
    assert_equal([[glyph], [cluster], Cairo::TextClusterFlag::BACKWARD],
                 [data.glyphs, data.clusters, data.cluster_flags])
  end
end
