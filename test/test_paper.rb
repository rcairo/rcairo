require 'cairo'

class PaperTest < Test::Unit::TestCase
  def test_parse_name
    assert_parse(:A4, "A4")
    assert_parse(:A4, "A4")
    assert_parse(:A4, :A4)
    assert_parse(:A4, :a4)

    assert_parse(:JAPANESE_POSTCARD, :japanese_postcard)
    assert_parse(:JAPANESE_POSTCARD, "japanese-postcard")
    assert_parse(:JAPANESE_POSTCARD, "Japanese postcard")

    exception = assert_raise(Cairo::Paper::UnknownPaperName) do
      Cairo::Paper.parse(:nonexistence)
    end
    assert_equal(:nonexistence, exception.name)
  end

  def test_parse_size
    assert_parse(paper(100, 200), "100x200")
    assert_parse(paper(100, 200), "100mmx200mm")
    assert_parse(paper(100.5, 200.9), "100.5mmx200.9")
    assert_parse(paper(100.5, 200.9), "100.5mmx200.9")
    assert_parse(paper(25.4, 215.9), "1inchx8.5inch")

    exception = assert_raise(Cairo::Paper::UnknownUnit) do
      Cairo::Paper.parse("100kmx100")
    end
    assert_equal("km", exception.unit)
  end

  private
  def paper(width, height)
    Cairo::Paper.new(width, height)
  end

  def assert_parse(expected, paper_description)
    expected = Cairo::Paper.const_get(expected) if expected.is_a?(Symbol)
    actual_paper = Cairo::Paper.parse(paper_description)
    assert_equal(expected.to_s, actual_paper.nil? ? nil : actual_paper.to_s)
  end
end
