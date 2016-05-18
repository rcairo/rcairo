require 'cairo'

class FontFaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_toy_font_face_new
    only_cairo_version(1, 7, 2)

    face = Cairo::ToyFontFace.new
    default_font_family = ""
    default_font_family = "Helvetica" if quartz?
    default_font_family = "Arial" if win32?
    assert_equal([default_font_family,
                  Cairo::FONT_SLANT_NORMAL,
                  Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("serif")
    assert_equal(["serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new(:serif)
    assert_equal(["serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("serif", :oblique)
    assert_equal(["serif", Cairo::FONT_SLANT_OBLIQUE, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("serif", nil, :bold)
    assert_equal(["serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("serif", :italic, :bold)
    assert_equal(["serif", Cairo::FONT_SLANT_ITALIC, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])
  end

  def test_toy_font_face_new_with_invalid_family_name
    only_cairo_version(1, 7, 2)

    exception = assert_raise(ArgumentError) do
      Cairo::ToyFontFace.new(999)
    end
    assert_equal("family name should be nil, String or Symbol: 999",
                 exception.message)
  end

  def test_user_font_face_empty
    only_cairo_version(1, 7, 2)

    face = Cairo::UserFontFace.new
    scaled_font = Cairo::ScaledFont.new(face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)
    assert_equal([[], [], 0],
                 scaled_font.text_to_glyphs(0, 0, "text"))
  end

  def test_user_font_face_callback
    only_cairo_version(1, 7, 2)

    face = Cairo::UserFontFace.new

    init_args = []
    face.on_init do |*args|
      init_args << args
    end

    render_glyph_args = []
    face.on_render_glyph do |*args|
      render_glyph_args << args
    end

    text_to_glyphs_args = []
    face.on_text_to_glyphs do |*args|
      text_to_glyphs_args << args
      scaled_font, utf8, data = args
      data.cluster_flags = :backward
    end

    unicode_to_glyph_args = []
    face.on_unicode_to_glyph do |*args|
      unicode_to_glyph_args << args
      scaled_font, unicode = args
      unicode
    end

    scaled_font = Cairo::ScaledFont.new(face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)
    result = scaled_font.text_to_glyphs(0, 0, "text")
    assert_equal([[[Cairo::ScaledFont, Cairo::Context, Cairo::FontExtents]],
                  [[Cairo::ScaledFont, codepoint("t"),
                    Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, codepoint("e"),
                    Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, codepoint("x"),
                    Cairo::Context, Cairo::TextExtents]],
                  [[Cairo::ScaledFont, "text",
                    Cairo::UserFontFace::TextToGlyphsData]],
                  [[Cairo::ScaledFont, codepoint("t")],
                   [Cairo::ScaledFont, codepoint("e")],
                   [Cairo::ScaledFont, codepoint("x")],
                   [Cairo::ScaledFont, codepoint("t")]],
                  [[], [], Cairo::TextClusterFlag::BACKWARD]],
                 [classify_cairo_object(init_args),
                  classify_cairo_object(render_glyph_args),
                  classify_cairo_object(text_to_glyphs_args),
                  classify_cairo_object(unicode_to_glyph_args),
                  result])
  end

  if Cairo.satisfied_version?(1, 7, 2)
    class CustomUserFontFace < Cairo::UserFontFace
      attr_reader :init_args, :render_glyph_args
      attr_reader :text_to_glyphs_args, :unicode_to_glyph_args
      def initialize
        super
        @init_args = []
        @render_glyph_args = []
        @text_to_glyphs_args = []
        @unicode_to_glyph_args = []
      end

      def init(*args)
        @init_args << args
      end

      def render_glyph(*args)
        @render_glyph_args << args
      end

      def text_to_glyphs(*args)
        @text_to_glyphs_args << args
        scaled_font, utf8, data = args
        data.cluster_flags = :backward
      end

      def unicode_to_glyph(*args)
        @unicode_to_glyph_args << args
        scaled_font, unicode = args
        unicode
      end
    end
  end

  def test_user_font_face_class
    only_cairo_version(1, 7, 2)

    face = CustomUserFontFace.new

    scaled_font = Cairo::ScaledFont.new(face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)
    result = scaled_font.text_to_glyphs(0, 0, "text")
    assert_equal([[[Cairo::ScaledFont, Cairo::Context, Cairo::FontExtents]],
                  [[Cairo::ScaledFont, codepoint("t"),
                    Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, codepoint("e"),
                    Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, codepoint("x"),
                    Cairo::Context, Cairo::TextExtents]],
                  [[Cairo::ScaledFont, "text",
                    Cairo::UserFontFace::TextToGlyphsData]],
                  [[Cairo::ScaledFont, codepoint("t")],
                   [Cairo::ScaledFont, codepoint("e")],
                   [Cairo::ScaledFont, codepoint("x")],
                   [Cairo::ScaledFont, codepoint("t")]],
                  [[], [], Cairo::TextClusterFlag::BACKWARD]],
                 [classify_cairo_object(face.init_args),
                  classify_cairo_object(face.render_glyph_args),
                  classify_cairo_object(face.text_to_glyphs_args),
                  classify_cairo_object(face.unicode_to_glyph_args),
                  result])
  end

  def test_user_font_face_class_and_callback
    only_cairo_version(1, 7, 2)

    face = CustomUserFontFace.new

    init_args = []
    face.on_init do |*args|
      init_args << args
    end

    render_glyph_args = []
    face.on_render_glyph do |*args|
      render_glyph_args << args
    end

    text_to_glyphs_args = []
    face.on_text_to_glyphs do |*args|
      text_to_glyphs_args << args
      scaled_font, utf8, data = args
      data.cluster_flags = :backward
    end

    unicode_to_glyph_args = []
    face.on_unicode_to_glyph do |*args|
      unicode_to_glyph_args << args
      scaled_font, unicode = args
      unicode
    end

    scaled_font = Cairo::ScaledFont.new(face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)
    result = scaled_font.text_to_glyphs(0, 0, "text")
    assert_equal([[[Cairo::ScaledFont, Cairo::Context, Cairo::FontExtents]],
                  [[Cairo::ScaledFont, codepoint("t"),
                    Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, codepoint("e"),
                    Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, codepoint("x"),
                    Cairo::Context, Cairo::TextExtents]],
                  [[Cairo::ScaledFont, "text",
                    Cairo::UserFontFace::TextToGlyphsData]],
                  [[Cairo::ScaledFont, codepoint("t")],
                   [Cairo::ScaledFont, codepoint("e")],
                   [Cairo::ScaledFont, codepoint("x")],
                   [Cairo::ScaledFont, codepoint("t")]],
                  [],
                  [],
                  [],
                  [],
                  [[], [], Cairo::TextClusterFlag::BACKWARD]],
                 [classify_cairo_object(init_args),
                  classify_cairo_object(render_glyph_args),
                  classify_cairo_object(text_to_glyphs_args),
                  classify_cairo_object(unicode_to_glyph_args),
                  classify_cairo_object(face.init_args),
                  classify_cairo_object(face.render_glyph_args),
                  classify_cairo_object(face.text_to_glyphs_args),
                  classify_cairo_object(face.unicode_to_glyph_args),
                  result])
  end

  def test_create_for_ft_face_valid
    font_face = Cairo::FontFace.create_for_ft_face('test/data/SourceSansPro-Regular.otf')
    assert_equal(classify_cairo_object(font_face), Cairo::FontFace)
  end

  def test_create_for_ft_face_error
    assert_raise do
      Cairo::FontFace.create_for_ft_face('test/data/SourceSansPro-Corrupted.otf')
    end

    assert_raise do
      Cairo::FontFace.create_for_ft_face('test/data/InvalidFile.otf')
    end
  end

  def classify_cairo_object(object)
    if object.is_a?(Array)
      object.collect {|obj| classify_cairo_object(obj)}
    elsif /\ACairo::/ =~ object.class.name
      object.class
    else
      object
    end
  end

  def codepoint(character)
    character.unpack("U")[0]
  end
end
