class PDFSurfaceTest < Test::Unit::TestCase
  include CairoTestUtils

  def test_new_with_nil_target
    surface = Cairo::PDFSurface.new(nil, 10, 20)
    surface.finish
  end

  sub_test_case "#add_outline" do
    def test_sub_outline
      only_cairo_version(1, 15, 4)
      surface = Cairo::PDFSurface.new(nil, 10, 20)
      context = Cairo::Context.new(surface)
      context.tag(Cairo::Tag::DEST, "name='destination'") do
        context.show_text("Destination")
      end
      id = surface.add_outline(Cairo::PDFOutline::ROOT,
                               "top-level",
                               "destination",
                               Cairo::PDFOutlineFlags::BOOKMARK_FLAG_OPEN)
      sub_id = surface.add_outline(sub_id,
                                   "sub",
                                   "destination",
                                   Cairo::PDFOutlineFlags::BOOKMARK_FLAG_OPEN)
      assert_equal(2, sub_id)
    end
  end
end
