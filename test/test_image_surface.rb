require 'cairo'

class ImageSurfaceTest < Test::Unit::TestCase
  include Helper

  def test_cloned_data
    width = 10
    height = 10
    original_surface = Cairo::ImageSurface.new(:a1, width, height)

    original_data = original_surface.data
    cloned_data = original_data.clone

    cloned_surface = Cairo::ImageSurface.new(cloned_data,
                                             :a1, width, height,
                                             original_surface.stride)

    Cairo::Context.create(cloned_surface) do |context|
      context.set_source_rgb(255, 255, 255)
      context.scale(width, height)
      context.move_to(0, 0)
      context.line_to(1, 1)
      context.stroke
    end

    assert_not_equal(original_data, cloned_data)
  end
end
