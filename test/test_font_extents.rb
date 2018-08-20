require 'cairo'

class FontExtentsTest < Test::Unit::TestCase
  include Helper

  def test_new
    extents = Cairo::FontExtents.new
    assert_equal([1.0, 0.0, 1.0, 1.0, 0.0],
                 [extents.ascent, extents.descent, extents.height,
                  extents.max_x_advance, extents.max_y_advance])
  end

  def test_accessor
    extents = Cairo::FontExtents.new
    extents.ascent = 0.1
    extents.descent = 0.2
    extents.height = 0.3
    extents.max_x_advance = 0.4
    extents.max_y_advance = 0.5
    assert_equal([0.1, 0.2, 0.3, 0.4, 0.5],
                 [extents.ascent, extents.descent, extents.height,
                  extents.max_x_advance, extents.max_y_advance])
  end

  def test_to_s
    extents = Cairo::FontExtents.new
    extents.ascent = 0.1
    extents.descent = 0.2
    extents.height = 0.3
    extents.max_x_advance = 0.4
    extents.max_y_advance = 0.5
    assert_equal("#<Cairo::FontExtents: ascent=0.1, descent=0.2, " +
                 "height=0.3, max_x_advance=0.4, max_y_advance=0.5>",
                 extents.to_s)
  end
end
