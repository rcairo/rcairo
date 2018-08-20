class QuartzImageSurfaceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_surface("QuartzImage")
  end

  def test_quartz_image_surface
    surface = Cairo::ImageSurface.new(100, 100)
    quartz_surface = Cairo::QuartzImageSurface.new(surface)
    assert_kind_of(Cairo::QuartzImageSurface, quartz_surface)
  end
end
