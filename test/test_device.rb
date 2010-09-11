require 'cairo'
require 'stringio'

class DeviceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_new
    output = StringIO.new
    device = Cairo::ScriptDevice.new(output)
    assert_equal("%!CairoScript\n", output.string)
    device.finish
    assert_equal("%!CairoScript\n", output.string)
  end

  def test_new_with_block
    output = StringIO.new
    string = nil
    Cairo::ScriptDevice.new(output) do |device|
      string = output.string
    end
    assert_equal("%!CairoScript\n", string)
  end
end
