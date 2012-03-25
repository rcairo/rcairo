require "cairo"
require "tempfile"

class RasterPatternSourceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_acquire_and_release
    Cairo::ImageSurface.new(100, 100) do |surface|
      Cairo::Context.new(surface) do |context|
        context.set_source(1, 1, 1)
        context.paint

        called = []
        red_pattern = Cairo::RasterSourcePattern.new(100, 100)
        red_pattern.acquire do |pattern, target, extents|
          called << :acquire
          red_image = target.create_similar_image(extents.width, extents.height);
          red_image.set_device_offset(extents.x, extents.y)
          Cairo::Context.new(red_image) do |red_image_context|
            red_image_context.set_source(1, 0, 0)
            red_image_context.paint
          end
          red_image
        end
        red_pattern.release do |pattern, surface|
          called << :release
          surface.finish
        end
        context.set_source(red_pattern)
        context.rectangle(40, 40, 20, 20)
        context.fill
        assert_equal([:acquire, :release], called)
      end
      show_result(surface)
    end
  end

  private
  def show_result(image_surface)
    return if ENV["RCAIRO_TEST_SHOW_RESULT"] != "yes"
    result = Tempfile.new("result")
    image_surface.write_to_png(result.path)
    system("display", result.path)
  end
end
