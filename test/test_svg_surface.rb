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
    if Cairo.satisfied_version?(1, 17, 6)
      assert_equal(Cairo::SVGUnit::USER, surface.document_unit)
    else
      assert_equal(Cairo::SVGUnit::PT, surface.document_unit)
    end
    surface.document_unit = Cairo::SVGUnit::CM
    assert_equal(Cairo::SVGUnit::CM, surface.document_unit)
  end
end
