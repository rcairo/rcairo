require 'cairo'

class ColorTest < Test::Unit::TestCase
  def test_rgb_to_hsv
    color = rgb(0.3, 0.5, 0.75)
    assert_equal(color, color.to_hsv.to_rgb)
  end

  private
  def rgb(r, g, b)
    Cairo::Color::RGB.new(r, g, b)
  end

  def hsv(h, s, v)
    Cairo::Color::HSV.new(h, s, v)
  end
end
