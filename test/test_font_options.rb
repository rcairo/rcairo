require 'cairo'

class FontOptionsTest < Test::Unit::TestCase
  include CairoTestUtils

  def setup
    @options = Cairo::FontOptions.new
  end

  def test_lcd_filter
    only_cairo_version(1, 7, 2)

    assert_equal(Cairo::LCDFilter::DEFAULT, @options.lcd_filter)
    @options.lcd_filter = :fir3
    assert_equal(Cairo::LCDFilter::FIR3, @options.lcd_filter)

    assert_invalid_lcd_filter(Cairo::LCDFilter::DEFAULT - 1)
    assert_invalid_lcd_filter(Cairo::LCDFilter::FIR5 + 1)
  end

  def assert_invalid_lcd_filter(value)
    options = Cairo::FontOptions.new
    exception = assert_raise(ArgumentError) do
      options.lcd_filter = value
    end
    min = Cairo::LCDFilter::DEFAULT
    max = Cairo::LCDFilter::FIR5
    assert_equal("invalid lcd_filter: #{value} " +
                 "(expect #{min} <= lcd_filter <= #{max})",
                 exception.message)
  end
end
