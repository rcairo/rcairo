class RecordingSurfaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def setup
    only_surface("Recording")
  end

  def test_new
    surface = Cairo::RecordingSurface.new(10, 20, 300, 400)
    assert_equal([0.0, 0.0, 0.0, 0.0], surface.ink_extents)
    Cairo::Context.new(surface) do |context|
      context.move_to(15, 30)
      context.line_to(80, 100)
      context.stroke
    end
    # https://bugs.freedesktop.org/show_bug.cgi?id=24688
    # causes expected value change. It is introduced between
    # cairo 1.10.0 and 1.10.2.
    assert_equal([14.0, 29.0, 67.0, 72.0], surface.ink_extents)
  end
end
