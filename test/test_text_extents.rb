require 'cairo'

class TextExtentsTest < Test::Unit::TestCase
  include Helper

  def test_new
    extents = Cairo::TextExtents.new
    assert_equal([0.0, -1.0, 0.0, 1.0, 1.0, 0.0],
                 [extents.x_bearing, extents.y_bearing,
                  extents.width, extents.height,
                  extents.x_advance, extents.y_advance])
  end

  def test_accessor
    extents = Cairo::TextExtents.new
    extents.x_bearing = 0.1
    extents.y_bearing = 0.2
    extents.width = 0.3
    extents.height = 0.4
    extents.x_advance = 0.5
    extents.y_advance = 0.6
    assert_equal([0.1, 0.2, 0.3, 0.4, 0.5, 0.6],
                 [extents.x_bearing, extents.y_bearing,
                  extents.width, extents.height,
                  extents.x_advance, extents.y_advance])
  end

  def test_to_s
    extents = Cairo::TextExtents.new
    extents.x_bearing = 0.1
    extents.y_bearing = 0.2
    extents.width = 0.3
    extents.height = 0.4
    extents.x_advance = 0.5
    extents.y_advance = 0.6
    assert_equal("#<Cairo::TextExtents: x_bearing=0.1, y_bearing=0.2, " +
                 "width=0.3, height=0.4, x_advance=0.5, y_advance=0.6>",
                 extents.to_s)
  end
end
