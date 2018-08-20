class XMLSurfaceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_surface("XML")
  end

  def test_new
    only_cairo_version(1, 12, 0)
    output = StringIO.new
    device = Cairo::XMLDevice.new(output)
    surface = Cairo::XMLSurface.new(device, 100, 200)
    Cairo::Context.create(surface) do |context|
      context.move_to(15, 30)
      context.line_to(80, 100)
      context.stroke
    end
    assert_equal(<<-EOX, output.string)
<stroke>
  <operator>OVER</operator>
  <line-width>2</line-width>
  <miter-limit>10</miter-limit>
  <line-cap>LINE_CAP_BUTT</line-cap>
  <line-join>LINE_JOIN_MITER</line-join>
  <source-pattern>
    <solid>0 0 0 1</solid>
  </source-pattern>
  <path> 15 30 m 80 100 l</path>
  <tolerance>0.1</tolerance>
  <antialias>DEFAULT</antialias>
</stroke>
EOX
  end
end
