class XMLDeviceTest < Test::Unit::TestCase
  include Helper

  def setup
    only_device("XML")
  end

  def test_new
    output = StringIO.new
    device = Cairo::XMLDevice.new(output)
    assert_equal("", output.string)
  end

  def test_new_with_block
    output = StringIO.new
    string = nil
    Cairo::XMLDevice.new(output) do |device|
      string = output.string
    end
    assert_equal("", string)
  end
end
