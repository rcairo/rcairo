require 'cairo'
require 'stringio'

class ScriptDeviceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_device("Script")
  end

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

  def test_write_comment
    output = StringIO.new
    Cairo::ScriptDevice.new(output) do |device|
      device.write_comment("Hello!")
    end
    assert_equal("%!CairoScript\n" +
                 "% Hello!\n",
                 output.string)
  end

  def test_mode
    output = StringIO.new
    Cairo::ScriptDevice.new(output) do |device|
      assert_equal(Cairo::ScriptMode::ASCII, device.mode)
      device.mode = Cairo::ScriptMode::BINARY
      assert_equal(Cairo::ScriptMode::BINARY, device.mode)
    end
  end
end
