class SVGSurfaceTest < Test::Unit::TestCase
  include Helper

  def test_new_with_nil_target
    surface = Cairo::SVGSurface.new(nil, 10, 20)
    surface.finish
  end

  def test_unit
    only_cairo_version(1, 15, 10)
    output = StringIO.new
    surface = Cairo::SVGSurface.new(output, 10, 20)
    assert_equal(Cairo::SVGUnit::PT, surface.document_unit)
    surface.document_unit = Cairo::SVGUnit::CM
    assert_equal(Cairo::SVGUnit::CM, surface.document_unit)
  end
end
