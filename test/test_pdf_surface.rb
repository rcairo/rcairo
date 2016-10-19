class PDFSurfaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_new_with_nil_target
    surface = Cairo::PDFSurface.new(nil, 10, 20)
    surface.finish
  end
end
