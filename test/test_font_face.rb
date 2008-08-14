require 'cairo'

class FontFaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_toy_font_face
    only_cairo_version(1, 7, 2)

    face = Cairo::ToyFontFace.new("sans")
    assert_equal(["sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("sans", :oblique)
    assert_equal(["sans", Cairo::FONT_SLANT_OBLIQUE, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("sans", nil, :bold)
    assert_equal(["sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("sans", :italic, :bold)
    assert_equal(["sans", Cairo::FONT_SLANT_ITALIC, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])
  end
end
