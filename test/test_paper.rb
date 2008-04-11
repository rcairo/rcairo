require 'cairo'

class PaperTest < Test::Unit::TestCase
  def test_parse_paper
    a4 = Cairo::Paper::A4
    assert_parse(a4, a4)
  end

  def test_parse_name
    assert_parse(:A4, "A4")
    assert_parse(:A4_LANDSCAPE, "A4 landscape")
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
    assert_parse(paper(283.46456664, 566.929134), "100mmx200mm")
    assert_parse(paper(284.88188952, 200.9), "100.5mmx200.9")
    assert_parse(paper(72, 612.0), "1inx8.5inch")
    assert_parse(paper(28.346456664, 24094.488168), "1cmx8.5m")
    assert_parse(paper(100, 200), [100, 200])

    exception = assert_raise(Cairo::Paper::UnknownUnit) do
      Cairo::Paper.parse("100kmx100")
    end
    assert_equal("km", exception.unit)
  end

  def test_parse_size_with_name
    assert_parse(paper(28.346456664, 24094.488168, nil, "Name"),
                 "1cmx8.5m#Name")
  end

  def test_unrecognized_input
    assert_nothing_raised do
      Cairo::Paper.parse({})
    end

    exception = assert_raise(Cairo::Paper::UnrecognizedPaperDescription) do
      Cairo::Paper.parse({}, true)
    end
    assert_equal({}, exception.description)
  end

  def test_unit
    paper = parse("1cmx8.5m")
    assert_nil(paper.unit)
    assert_in_delta(28.346456664, 0.01, paper.width)
    assert_in_delta(24094.488168, 0.01, paper.height)

    paper.unit = "inch"
    assert_equal("inch", paper.unit)
    assert_in_delta(0.393700787, 0.01, paper.width)
    assert_in_delta(334.645669, 0.01, paper.height)
  end

  private
  def paper(width, height, *rest)
    Cairo::Paper.new(width, height, *rest)
  end

  def parse(paper_description)
    Cairo::Paper.parse(paper_description)
  end

  def assert_parse(expected, paper_description, message=nil)
    expected = Cairo::Paper.const_get(expected) if expected.is_a?(Symbol)
    actual_paper = parse(paper_description)
    assert_equal(expected, actual_paper, message)
  end
end
