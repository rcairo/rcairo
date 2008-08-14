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

  def test_font_face
    context = Cairo::Context.new(@surface)

    assert_kind_of(Cairo::FontFace, context.font_face)

    face = Cairo::ToyFontFace.new("serif")
    context.font_face = face
    assert_equal("serif", context.font_face.family)

    face = Cairo::ToyFontFace.new("sans")
    context.font_face = face
    assert_equal("sans", context.font_face.family)
  end
end
