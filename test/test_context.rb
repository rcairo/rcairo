class ContextTest < Test::Unit::TestCase
  include Helper

  def setup
    @output = StringIO.new
    @surface = Cairo::PDFSurface.new(@output, 10, 10)
  end

  def test_new_and_destroy
    context = Cairo::Context.new(@surface)
    @surface.destroy
    assert_not_equal("%%EOF\n", @output.string[-6..-1])
    assert {not context.destroyed?}
    context.destroy
    assert {context.destroyed?}
    assert_equal("%%EOF\n", @output.string[-6..-1])
  end

  def test_create_with_block
    Cairo::Context.create(@surface) do |context|
      @surface.destroy
      assert_not_equal("%%EOF\n", @output.string[-6..-1])
    end
    assert_equal("%%EOF\n", @output.string[-6..-1])
  end

  def test_create_with_block_and_destroy
    assert_nothing_raised do
      Cairo::Context.create(@surface) do |context|
        context.destroy
      end
    end
  end

  def test_font_face
    only_cairo_version(1, 7, 2)

    context = Cairo::Context.new(@surface)

    assert_kind_of(Cairo::FontFace, context.font_face)

    face = Cairo::ToyFontFace.new("serif")
    context.font_face = face
    assert_equal("serif", context.font_face.family)

    face = Cairo::ToyFontFace.new("sans")
    context.font_face = face
    assert_equal("sans", context.font_face.family)
  end

  def test_text_to_glyphs
    only_cairo_version(1, 7, 2)

    surface = Cairo::PDFSurface.new(StringIO.new, 10, 10)
    context = Cairo::Context.new(surface)
    scaled_font = Cairo::ScaledFont.new(context.font_face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)

    utf8 = "text"
    glyphs, clusters, backward = scaled_font.text_to_glyphs(0, 0, utf8)
    assert_nothing_raised do
      context.show_text_glyphs(utf8, glyphs, clusters, backward)
    end
  end

  def test_select_font_face
    only_cairo_version(1, 7, 2)

    context = Cairo::Context.new(@surface)

    face = context.font_face
    default_font_family = ""
    default_font_family = "Helvetica" if quartz?
    default_font_family = "Arial" if windows?
    assert_equal([default_font_family,
                  Cairo::FONT_SLANT_NORMAL,
                  Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    context.select_font_face
    face = context.font_face
    assert_equal([default_font_family,
                  Cairo::FONT_SLANT_NORMAL,
                  Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    context.select_font_face(:serif, :italic, :bold)
    face = context.font_face
    assert_equal(["serif", Cairo::FONT_SLANT_ITALIC, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])
  end

  def test_select_font_face_with_invalid_family_name
    context = Cairo::Context.new(@surface)

    exception = assert_raise(ArgumentError) do
      context.select_font_face([999])
    end
    assert_equal("family name should be nil, String or Symbol: [999]",
                 exception.message)
  end

  sub_test_case("#tag") do
    setup do
      only_cairo_version(1, 15, 4)
    end

    test("LINK") do
      Cairo::Context.create(@surface) do |context|
        context.tag(Cairo::Tag::LINK, "uri='http://localhost/'") do
          context.show_text("localhost")
        end
        @surface.finish
      end
      document = Poppler::Document.new(@output.string)
      uris = document[0].link_mapping.collect do |mapping|
        mapping.action.uri
      end
      assert_equal(["http://localhost/"],
                   uris)
    end
  end

  def test_raw_address
    context = Cairo::Context.new(@surface)
    assert do
      context.raw_address > 0
    end
  end
end
