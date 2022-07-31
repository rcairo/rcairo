require 'cairo'

class FontFaceTest < Test::Unit::TestCase
  include Helper

  sub_test_case("FreeTypeFontFace") do
    setup do
      omit("Need FreeType support") unless Cairo::FontFace.freetype_supported?
    end

    sub_test_case("initialize") do
      test("valid") do
        assert_nothing_raised do
          Cairo::FreeTypeFontFace.new(fixture_path("a.otf"))
        end
      end

      sub_test_case("invalid") do
        setup do
          if Cairo.const_defined?(:FreeTypeError)
            @error_class = Cairo::FreeTypeError
          else
            @error_class = Cairo::Error
          end
        end

        test("broken") do
          path = __FILE__
          message = "failed to open FreeType font: "
          message << "FT_Err_Unknown_File_Format[2]: "
          message << "unknown file format: "
          message << path.inspect
          assert_raise(@error_class.new(message)) do
            Cairo::FreeTypeFontFace.new(path)
          end
        end

        test("nonexistent") do
          path = fixture_path("nonexistent.otf")
          message = "failed to open FreeType font: "
          message << "FT_Err_Cannot_Open_Resource[1]: "
          message << "cannot open resource: "
          message << path.inspect
          assert_raise(@error_class.new(message)) do
            Cairo::FreeTypeFontFace.new(path)
          end
        end
      end
    end
  end

  def test_toy_font_face_new
    only_cairo_version(1, 7, 2)

    face = Cairo::ToyFontFace.new
    default_font_family = ""
    default_font_family = "Helvetica" if quartz?
    default_font_family = "Arial" if windows?
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

    render_color_glyph_args = []
    if face.respond_to?(:on_render_color_glyph)
      face.on_render_color_glyph do |*args|
        render_color_glyph_args << args
      end
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
    result = scaled_font.text_to_glyphs(0, 0, "abc")
    expected = {
      init_args: [
        [Cairo::ScaledFont, Cairo::Context, Cairo::FontExtents],
      ],
      render_glyph_args: [
        [Cairo::ScaledFont, codepoint("a"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("b"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("c"), Cairo::Context, Cairo::TextExtents],
      ],
      render_color_glyph_args: [],
      text_to_glyphs_args: [
        [Cairo::ScaledFont, "abc", Cairo::UserFontFace::TextToGlyphsData],
      ],
      unicode_to_glyph_args: [
        [Cairo::ScaledFont, codepoint("a")],
        [Cairo::ScaledFont, codepoint("b")],
        [Cairo::ScaledFont, codepoint("c")],
      ],
      result: [[], [], Cairo::TextClusterFlag::BACKWARD],
    }
    actual = {
      init_args: classify_cairo_object(init_args),
      render_glyph_args: classify_cairo_object(render_glyph_args),
      render_color_glyph_args: classify_cairo_object(render_color_glyph_args),
      text_to_glyphs_args: classify_cairo_object(text_to_glyphs_args),
      unicode_to_glyph_args: classify_cairo_object(unicode_to_glyph_args),
      result: result,
    }
    if Cairo.satisfied_version?(1, 17, 6)
      expected[:render_glyph_args],
        expected[:render_color_glyph_args] =
          expected[:render_color_glyph_args],
            expected[:render_glyph_args]
    end
    assert_equal(expected, actual)
  end

  if Cairo.satisfied_version?(1, 7, 2)
    class CustomUserFontFace < Cairo::UserFontFace
      attr_reader :init_args
      attr_reader :render_glyph_args
      attr_reader :render_color_glyph_args
      attr_reader :text_to_glyphs_args
      attr_reader :unicode_to_glyph_args
      def initialize
        super
        @init_args = []
        @render_glyph_args = []
        @render_color_glyph_args = []
        @text_to_glyphs_args = []
        @unicode_to_glyph_args = []
      end

      def init(*args)
        @init_args << args
      end

      def render_glyph(*args)
        @render_glyph_args << args
      end

      def render_color_glyph(*args)
        @render_color_glyph_args << args
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
    result = scaled_font.text_to_glyphs(0, 0, "abc")
    expected = {
      init_args: [
        [Cairo::ScaledFont, Cairo::Context, Cairo::FontExtents]
      ],
      text_to_glyphs_args: [
        [Cairo::ScaledFont, "abc", Cairo::UserFontFace::TextToGlyphsData],
      ],
      unicode_to_glyph_args: [
        [Cairo::ScaledFont, codepoint("a")],
        [Cairo::ScaledFont, codepoint("b")],
        [Cairo::ScaledFont, codepoint("c")],
      ],
      result: [
        [],
        [],
        Cairo::TextClusterFlag::BACKWARD,
      ],
    }
    actual = {
      init_args: classify_cairo_object(face.init_args),
      text_to_glyphs_args:
        classify_cairo_object(face.text_to_glyphs_args),
      unicode_to_glyph_args:
        classify_cairo_object(face.unicode_to_glyph_args),
      result: result,
    }
    if Cairo.satisfied_version?(1, 17, 6)
      expected[:render_color_glyph_args] = [
        [Cairo::ScaledFont, codepoint("a"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("b"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("c"), Cairo::Context, Cairo::TextExtents],
      ]
      actual[:render_color_glyph_args] =
        classify_cairo_object(face.render_color_glyph_args)
      expected[:render_glyph_args] = []
      actual[:render_glyph_args] =
        classify_cairo_object(face.render_glyph_args)
    else
      expected[:render_glyph_args] = [
        [Cairo::ScaledFont, codepoint("a"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("b"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("c"), Cairo::Context, Cairo::TextExtents],
      ]
      actual[:render_glyph_args] =
        classify_cairo_object(face.render_glyph_args)
    end
    assert_equal(expected, actual)
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

    render_color_glyph_args = []
    if face.respond_to?(:on_render_color_glyph)
      face.on_render_color_glyph do |*args|
        render_color_glyph_args << args
      end
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
    result = scaled_font.text_to_glyphs(0, 0, "abc")
    expected = {
      callback_init_args: [
        [
          Cairo::ScaledFont, Cairo::Context, Cairo::FontExtents,
        ],
      ],
      callback_render_glyph_args: [
        [Cairo::ScaledFont, codepoint("a"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("b"), Cairo::Context, Cairo::TextExtents],
        [Cairo::ScaledFont, codepoint("c"), Cairo::Context, Cairo::TextExtents],
      ],
      callback_render_color_glyph_args: [],
      callback_text_to_glyphs_args: [
        [Cairo::ScaledFont, "abc", Cairo::UserFontFace::TextToGlyphsData],
      ],
      callback_unicode_to_glyph_args: [
        [Cairo::ScaledFont, codepoint("a")],
        [Cairo::ScaledFont, codepoint("b")],
        [Cairo::ScaledFont, codepoint("c")],
      ],
      object_init_args: [],
      object_render_glyph_args: [],
      object_render_color_glyph_args: [],
      object_text_to_glyphs_args: [],
      object_unicode_to_glyph_args: [],
      result: [[], [], Cairo::TextClusterFlag::BACKWARD],
    }
    actual = {
      callback_init_args: classify_cairo_object(init_args),
      callback_render_glyph_args:
        classify_cairo_object(render_glyph_args),
      callback_render_color_glyph_args:
        classify_cairo_object(render_color_glyph_args),
      callback_text_to_glyphs_args:
        classify_cairo_object(text_to_glyphs_args),
      callback_unicode_to_glyph_args:
        classify_cairo_object(unicode_to_glyph_args),
      object_init_args:
        classify_cairo_object(face.init_args),
      object_render_glyph_args:
        classify_cairo_object(face.render_glyph_args),
      object_render_color_glyph_args:
        classify_cairo_object(face.render_color_glyph_args),
      object_text_to_glyphs_args:
        classify_cairo_object(face.text_to_glyphs_args),
      object_unicode_to_glyph_args:
        classify_cairo_object(face.unicode_to_glyph_args),
      result: result,
    }
    if Cairo.satisfied_version?(1, 17, 6)
      expected[:callback_render_glyph_args],
        expected[:callback_render_color_glyph_args] =
          expected[:callback_render_color_glyph_args],
            expected[:callback_render_glyph_args]
    end
    assert_equal(expected, actual)
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
