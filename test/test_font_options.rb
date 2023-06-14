require 'cairo'

class FontOptionsTest < Test::Unit::TestCase
  include Helper

  def setup
    @options = Cairo::FontOptions.new
  end

  sub_test_case "#==" do
    test "not FontOptions" do
      assert do
        !(@options == nil)
      end
    end

    test "same object" do
      assert do
        @options == @options
      end
    end

    test "same content" do
      assert do
        @options == @options.dup
      end
    end
  end

  sub_test_case "#eql? and #hash" do
    test "not FontOptions" do
      object = Object.new
      options = @options
      object.singleton_class.__send__(:define_method, :hash) do
        options.hash
      end

      hash = {
        object => :value,
      }
      assert_nil(hash[@options])
    end

    test "same object" do
      hash = {
        @options => :value,
      }
      assert_equal(:value, hash[@options])
    end

    test "same content" do
      hash = {
        @options => :value,
      }
      assert_equal(:value, hash[@options.dup])
    end
  end

  test "variations" do
    only_cairo_version(1, 15, 12)
    assert_nil(@options.variations)
    @options.variations = "wdth=200"
    assert_equal("wdth=200", @options.variations)
  end

  test "color mode" do
    only_cairo_version(1, 17, 8)
    assert_equal(Cairo::ColorMode::DEFAULT, @options.color_mode)
    @options.color_mode = Cairo::ColorMode::COLOR
    assert_equal(Cairo::ColorMode::COLOR, @options.color_mode)
  end

  test "color palette" do
    only_cairo_version(1, 17, 8)
    assert_equal(Cairo::ColorPalette::DEFAULT, @options.color_palette)
    @options.set_custom_palette_color(1,
                                      1.0,
                                      0.2,
                                      0.0,
                                      0.8)
    @options.color_palette = 1
    assert_equal(1, @options.color_palette)
  end
end
