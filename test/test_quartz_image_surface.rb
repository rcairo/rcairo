class QuartzImageSurfaceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_surface("QuartzImage")
  end

  def test_quartz_image_surface
    Cairo::ImageSurface.create(100, 100) do |surface|
      Cairo::QuartzImageSurface.create(surface) do |quartz_surface|
        assert_kind_of(Cairo::QuartzImageSurface, quartz_surface)
      end
    end
  end
end
