require 'cairo'

class ConstantsTest < Test::Unit::TestCase
  def test_lcd_filter
    constant_name = "LCDFilter"
    unless Cairo.satisfied_version?(1, 7, 2)
      assert_false(Cairo.const_defined?(constant_name))
      return
    end

    assert_true(Cairo.const_defined?(constant_name))
    assert_equal((0..4).to_a,
                 [Cairo::LCDFilter::DEFAULT,
                  Cairo::LCDFilter::NONE,
                  Cairo::LCDFilter::INTRA_PIXEL,
                  Cairo::LCDFilter::FIR3,
                  Cairo::LCDFilter::FIR5])
  end
end
