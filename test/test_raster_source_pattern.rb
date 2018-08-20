require "cairo"
require "tempfile"

class RasterSourcePatternTest < Test::Unit::TestCase
  include Helper

  def setup
    only_pattern("RasterSource")
  end

  def test_acquire_and_release
    Cairo::ImageSurface.create(100, 100) do |surface|
      Cairo::Context.create(surface) do |context|
        context.set_source(1, 1, 1)
        context.paint

        called = []
        red_pattern = Cairo::RasterSourcePattern.new(100, 100)
        red_pattern.acquire do |pattern, target, extents|
          called << :acquire
          red_image = target.create_similar_image(extents.width, extents.height)
          red_image.set_device_offset(extents.x, extents.y)
          Cairo::Context.create(red_image) do |red_image_context|
            red_image_context.set_source(1, 0, 0)
            red_image_context.paint
          end
          red_image
        end
        red_pattern.release do |pattern, surface|
          called << :release
          surface.finish
        end
        context.set_source(red_pattern)
        context.rectangle(40, 40, 20, 20)
        context.fill
        assert_equal([:acquire, :release], called)
      end
      show_result(surface)
    end
  end

  class SnapshotTest < self
    def setup
      super
      only_surface("Recording")
    end

    def test_success
      Cairo::RecordingSurface.create(0, 0, 100, 100) do |surface|
        Cairo::Context.create(surface) do |context|
          called = []
          raster_source = Cairo::RasterSourcePattern.new(100, 100)
          raster_source.snapshot do |pattern|
            called << :snapshot
          end
          context.set_source(raster_source)
          context.rectangle(40, 40, 20, 20)
          context.fill
          assert_equal([:snapshot], called)
        end
        show_result(surface)
      end
    end

    def test_error
      Cairo::RecordingSurface.create(0, 0, 100, 100) do |surface|
        Cairo::Context.create(surface) do |context|
          called = []
          raster_source = Cairo::RasterSourcePattern.new(100, 100)
          raster_source.snapshot do |pattern|
            called << :snapshot
            raise NoMemoryError
          end
          context.set_source(raster_source)
          context.rectangle(40, 40, 20, 20)
          assert_raise(NoMemoryError) do
            context.fill
          end
          assert_equal([:snapshot], called)
        end
        show_result(surface)
      end
    end
  end

  class CopyTest < self
    def setup
      super
      only_surface("Script")
    end

    def test_success
      output = StringIO.new
      device = Cairo::ScriptDevice.new(output)
      Cairo::ScriptSurface.create(device, 100, 200) do |surface|
        Cairo::Context.create(surface) do |context|
          called = []

          raster_source = Cairo::RasterSourcePattern.new(100, 100)
          raster_source.acquire do |pattern, target, extents|
            called << :acquire
            red_image = target.create_similar_image(extents.width,
                                                    extents.height)
            red_image.set_device_offset(extents.x, extents.y)
            Cairo::Context.create(red_image) do |red_image_context|
              red_image_context.set_source(1, 0, 0)
              red_image_context.paint
            end
            red_image
          end
          raster_source.release do |pattern, surface|
            called << :release
            surface.finish
          end
          raster_source.copy do |pattern|
            called << :copy
          end

          context.set_source(raster_source)
          context.rectangle(40, 40, 20, 20)
          context.fill

          assert_equal([:copy, :acquire, :release], called)
        end
        show_result(surface)
      end
    end

    def test_error
      output = StringIO.new
      device = Cairo::ScriptDevice.new(output)
      Cairo::ScriptSurface.create(device, 100, 200) do |surface|
        Cairo::Context.create(surface) do |context|
          called = []

          raster_source = Cairo::RasterSourcePattern.new(100, 100)
          raster_source.copy do |pattern|
            called << :copy
            raise NoMemoryError
          end

          context.set_source(raster_source)
          context.rectangle(40, 40, 20, 20)
          assert_raise(NoMemoryError) do
            context.fill
          end

          assert_equal([:copy], called)
        end
        show_result(surface)
      end
    end
  end

  private
  def show_result(image_surface)
    return if ENV["RCAIRO_TEST_SHOW_RESULT"] != "yes"
    result = Tempfile.new("result")
    image_surface.write_to_png(result.path)
    system("display", result.path)
  end
end
