require 'cairo'

class FontFaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_toy_font_face
    only_cairo_version(1, 7, 2)

    face = Cairo::ToyFontFace.new("sans")
    assert_equal(["sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("sans", :oblique)
    assert_equal(["sans", Cairo::FONT_SLANT_OBLIQUE, Cairo::FONT_WEIGHT_NORMAL],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("sans", nil, :bold)
    assert_equal(["sans", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])

    face = Cairo::ToyFontFace.new("sans", :italic, :bold)
    assert_equal(["sans", Cairo::FONT_SLANT_ITALIC, Cairo::FONT_WEIGHT_BOLD],
                 [face.family, face.slant, face.weight])
  end

  def test_user_font_face_empty
    only_cairo_version(1, 7, 2)

    face = Cairo::UserFontFace.new
    scaled_font = Cairo::ScaledFont.new(face,
                                        Cairo::Matrix.identity,
                                        Cairo::Matrix.identity,
                                        Cairo::FontOptions.new)
    assert_equal([[], [], false],
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
      data.backward = true
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
                  [[Cairo::ScaledFont, ?t, Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, ?e, Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, ?x, Cairo::Context, Cairo::TextExtents]],
                  [[Cairo::ScaledFont, "text",
                    Cairo::UserFontFace::TextToGlyphsData]],
                  [[Cairo::ScaledFont, ?t],
                   [Cairo::ScaledFont, ?e],
                   [Cairo::ScaledFont, ?x],
                   [Cairo::ScaledFont, ?t]],
                  [[], [], true]],
                 [classify_cairo_object(init_args),
                  classify_cairo_object(render_glyph_args),
                  classify_cairo_object(text_to_glyphs_args),
                  classify_cairo_object(unicode_to_glyph_args),
                  result])
  end

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
      data.backward = true
    end

    def unicode_to_glyph(*args)
      @unicode_to_glyph_args << args
      scaled_font, unicode = args
      unicode
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
                  [[Cairo::ScaledFont, ?t, Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, ?e, Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, ?x, Cairo::Context, Cairo::TextExtents]],
                  [[Cairo::ScaledFont, "text",
                    Cairo::UserFontFace::TextToGlyphsData]],
                  [[Cairo::ScaledFont, ?t],
                   [Cairo::ScaledFont, ?e],
                   [Cairo::ScaledFont, ?x],
                   [Cairo::ScaledFont, ?t]],
                  [[], [], true]],
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
      data.backward = true
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
                  [[Cairo::ScaledFont, ?t, Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, ?e, Cairo::Context, Cairo::TextExtents],
                   [Cairo::ScaledFont, ?x, Cairo::Context, Cairo::TextExtents]],
                  [[Cairo::ScaledFont, "text",
                    Cairo::UserFontFace::TextToGlyphsData]],
                  [[Cairo::ScaledFont, ?t],
                   [Cairo::ScaledFont, ?e],
                   [Cairo::ScaledFont, ?x],
                   [Cairo::ScaledFont, ?t]],
                  [],
                  [],
                  [],
                  [],
                  [[], [], true]],
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

  def classify_cairo_object(object)
    if object.is_a?(Array)
      object.collect {|obj| classify_cairo_object(obj)}
    elsif /\ACairo::/ =~ object.class.name
      object.class
    else
      object
    end
  end
end
