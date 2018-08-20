class PDFSurfaceTest < Test::Unit::TestCase
  include Helper

  def create_pdf
    pdf = StringIO.new
    surface = Cairo::PDFSurface.new(pdf, 10, 20)
    yield(surface)
    surface.finish
    Poppler::Document.new(pdf.string)
  end

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
                               "dest='destination'",
                               Cairo::PDFOutlineFlags::OPEN)
      sub_id = surface.add_outline(sub_id,
                                   "sub",
                                   "dest='destination'",
                                   Cairo::PDFOutlineFlags::OPEN)
      assert_equal(2, sub_id)
    end
  end

  sub_test_case "#set_metadata" do
    test "title" do
      only_cairo_version(1, 15, 4)
      pdf = create_pdf do |surface|
        surface.set_metadata(Cairo::PDFMetadata::TITLE, "Hello")
      end
      assert_equal("Hello", pdf.title)
    end

    test "author" do
      only_cairo_version(1, 15, 4)
      pdf = create_pdf do |surface|
        surface.set_metadata(Cairo::PDFMetadata::AUTHOR, "Alice")
      end
      assert_equal("Alice", pdf.author)
    end

    test "subject" do
      only_cairo_version(1, 15, 4)
      pdf = create_pdf do |surface|
        surface.set_metadata(Cairo::PDFMetadata::SUBJECT, "This is world.")
      end
      assert_equal("This is world.", pdf.subject)
    end

    test "keywords" do
      only_cairo_version(1, 15, 4)
      pdf = create_pdf do |surface|
        surface.set_metadata(Cairo::PDFMetadata::KEYWORDS, "hello, alice")
      end
      assert_equal("hello, alice", pdf.keywords)
    end

    test "creator" do
      only_cairo_version(1, 15, 4)
      pdf = create_pdf do |surface|
        surface.set_metadata(Cairo::PDFMetadata::CREATOR, "cairo")
      end
      assert_equal("cairo", pdf.creator)
    end

    sub_test_case "create date" do
      test "string" do
        only_cairo_version(1, 15, 4)
        pdf = create_pdf do |surface|
          surface.set_metadata(Cairo::PDFMetadata::CREATE_DATE,
                               "2017-01-04T02:17:01+09:00")
        end
        assert_equal(Time.parse("2017-01-04T02:17:01+09:00"),
                     Time.at(pdf.creation_date))
      end

      test "time" do
        only_cairo_version(1, 15, 4)
        pdf = create_pdf do |surface|
          surface.set_metadata(Cairo::PDFMetadata::CREATE_DATE,
                               Time.parse("2017-01-04T02:17:01+09:00"))
        end
        assert_equal(Time.parse("2017-01-04T02:17:01+09:00"),
                     Time.at(pdf.creation_date))
      end
    end

    sub_test_case "modified date" do
      test "string" do
        only_cairo_version(1, 15, 4)
        pdf = create_pdf do |surface|
          surface.set_metadata(Cairo::PDFMetadata::MOD_DATE,
                               "2017-01-04T02:17:01+09:00")
        end
        assert_equal(Time.parse("2017-01-04T02:17:01+09:00"),
                     Time.at(pdf.mod_date))
      end

      test "time" do
        only_cairo_version(1, 15, 4)
        pdf = create_pdf do |surface|
          surface.set_metadata(Cairo::PDFMetadata::MOD_DATE,
                               Time.parse("2017-01-04T02:17:01+09:00"))
        end
        assert_equal(Time.parse("2017-01-04T02:17:01+09:00"),
                     Time.at(pdf.mod_date))
      end
    end
  end

  test "#page_label=" do
    only_cairo_version(1, 15, 4)
    pdf = create_pdf do |surface|
      surface.page_label = "Hello"
    end
    assert_equal("Hello", pdf[0].label)
  end

  test "#set_thumbnail_size" do
    only_cairo_version(1, 15, 4)
    pdf = create_pdf do |surface|
      surface.set_thumbnail_size(5, 10)
    end
    thumbnail_size = pdf[0].thumbnail_size
    # TODO: Workaround for poppler gem 3.2.1
    thumbnail_size.shift if thumbnail_size.size == 3
    assert_equal([5, 10], thumbnail_size)
  end
end
