require 'cairo'
require 'stringio'

class ContextTest < Test::Unit::TestCase
  def setup
    @output = StringIO.new
    @surface = Cairo::PDFSurface.new(@output, 10, 10)
  end

  def test_new_and_destroy
    context = Cairo::Context.new(@surface)
    @surface.destroy
    assert_no_match(/%%EOF\s*\z/m, @output.string)
    context.destroy
    assert_match(/%%EOF\s*\z/m, @output.string)
  end

  def test_new_with_block
    Cairo::Context.new(@surface) do |context|
      @surface.destroy
      assert_no_match(/%%EOF\s*\z/m, @output.string)
    end
    assert_match(/%%EOF\s*\z/m, @output.string)
  end

  def test_new_with_block_and_destroy
    assert_nothing_raised do
      Cairo::Context.new(@surface) do |context|
        context.destroy
      end
    end
  end
end
