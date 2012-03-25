class RecordingSurfaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def setup
    only_surface("Recording")
  end

  def test_new
    only_cairo_version(1, 12, 0)
    surface = Cairo::RecordingSurface.new(10, 20, 300, 400)
    assert_equal([0.0, 0.0, 0.0, 0.0], surface.ink_extents)
    Cairo::Context.new(surface) do |context|
      context.move_to(15, 30)
      context.line_to(80, 100)
      context.stroke
    end
    assert_equal([10.0, 20.0, 61.0, 61.0], surface.ink_extents)
  end
end
