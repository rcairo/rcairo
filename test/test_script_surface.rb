class ScriptSurfaceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_surface("Script")
  end

  def test_device
    device = Cairo::ScriptDevice.new(StringIO.new)
    surface = Cairo::ScriptSurface.new(device, 100, 100)
    assert_equal(Cairo::ScriptDevice, surface.device.class)
  end
end
