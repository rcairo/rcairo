class RegionTest < Test::Unit::TestCase
  include Helper

  def setup
    only_cairo_version(1, 10, 0)
  end

  def test_new_empty
    region = Cairo::Region.new
    assert_predicate(region, :empty?)
  end

  def test_new_rectangle
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_not_predicate(region, :empty?)
  end

  def test_num_rectangles
    region = Cairo::Region.new
    assert_equal(0, region.num_rectangles)
  end

  def test_get_rectangle
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_equal([0, 0, 10, 10], region[0])
  end

  def test_each_rectangle
    region = Cairo::Region.new
    region.union!([0, 0, 10, 10])
    region.union!([20, 20, 40, 40])
    rectangles = []
    region.each_rectangle do |rectangle|
      rectangles << rectangle
    end
    assert_equal([
                   [0, 0, 10, 10],
                   [20, 20, 40, 40],
                 ],
                 rectangles)
  end

  def test_rectangles
    region = Cairo::Region.new
    region.union!([0, 0, 10, 10])
    region.union!([20, 20, 40, 40])
    assert_equal([
                   [0, 0, 10, 10],
                   [20, 20, 40, 40],
                 ],
                 region.rectangles)
  end

  def test_dup
    region = Cairo::Region.new([0, 0, 10, 10])
    region.dup.subtract!([5, 5, 5, 5])
    assert_equal([0, 0, 10, 10], region.extents)
  end

  def test_equal
    assert_equal(Cairo::Region.new([0, 0, 10, 10]),
                 Cairo::Region.new([0, 0, 10, 10]))
    assert_not_equal(Cairo::Region.new([0, 0, 10, 10]),
                     Cairo::Region.new([0, 0, 100, 100]))
  end

  def test_extents
    region = Cairo::Region.new
    assert_equal([0, 0, 0, 0], region.extents)
    region.union!([0, 0, 10, 10])
    assert_equal([0, 0, 10, 10], region.extents)
  end

  def test_contains_rectangle
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_equal(Cairo::RegionOverlap::IN,
                 region.contains_rectangle([2, 2, 2, 2]))
    assert_equal(Cairo::RegionOverlap::OUT,
                 region.contains_rectangle([10, 10, 1, 1]))
    assert_equal(Cairo::RegionOverlap::PART,
                 region.contains_rectangle([2, 2, 10, 10]))
  end

  def test_contains_point
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_equal(true, region.contains_point?(5, 5))
    assert_equal(false, region.contains_point?(10, 10))
  end

  def test_translate
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_equal(true, region.contains_point?(5, 5))
    region.translate!(6, 6)
    assert_equal(false, region.contains_point?(5, 5))
  end

  def test_subtract
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_equal(true, region.contains_point?(5, 5))
    region.subtract!([5, 5, 2, 2])
    assert_equal(false, region.contains_point?(5, 5))
  end

  def test_intersect
    region = Cairo::Region.new([0, 0, 10, 10])
    assert_equal(true, region.contains_point?(5, 5))
    assert_equal(true, region.contains_point?(7, 7))
    region.intersect!([5, 5, 2, 2])
    assert_equal(true, region.contains_point?(5, 5))
    assert_equal(false, region.contains_point?(7, 7))
  end

  def test_union
    region = Cairo::Region.new([0, 0, 4, 4])
    assert_equal(false, region.contains_point?(5, 5))
    region.union!([5, 5, 5, 5])
    assert_equal(true, region.contains_point?(5, 5))
  end

  def test_xor
    region = Cairo::Region.new([0, 0, 5, 5])
    assert_equal(true, region.contains_point?(4, 4))
    assert_equal(false, region.contains_point?(7, 7))
    region.xor!([3, 3, 5, 5])
    assert_equal(false, region.contains_point?(4, 4))
    assert_equal(true, region.contains_point?(7, 7))
  end
end
