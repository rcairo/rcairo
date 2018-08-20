require 'cairo'

class TextClusterTest < Test::Unit::TestCase
  include Helper

  def test_new
    only_cairo_version(1, 7, 2)

    cluster = Cairo::TextCluster.new(2, 3)
    assert_equal([2, 3], [cluster.num_bytes, cluster.num_glyphs])
    assert_equal("#<Cairo::TextCluster: num_bytes=2, num_glyphs=3>",
                 cluster.to_s)
  end

  def test_accessor
    only_cairo_version(1, 7, 2)

    cluster = Cairo::TextCluster.new(5, 7)
    assert_equal([5, 7], [cluster.num_bytes, cluster.num_glyphs])
    cluster.num_bytes = 1
    cluster.num_glyphs = 2
    assert_equal([1, 2], [cluster.num_bytes, cluster.num_glyphs])
  end

  def test_to_s
    only_cairo_version(1, 7, 2)

    cluster = Cairo::TextCluster.new(9, 1)
    assert_equal("#<Cairo::TextCluster: num_bytes=9, num_glyphs=1>",
                 cluster.to_s)
  end
end
