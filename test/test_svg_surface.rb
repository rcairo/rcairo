class SVGSurfaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_new_with_nil_target
    surface = Cairo::SVGSurface.new(nil, 10, 20)
    surface.finish
  end
end
