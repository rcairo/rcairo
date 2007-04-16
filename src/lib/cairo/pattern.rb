require 'cairo/color'

module Cairo
  class SolidPattern
    if method_defined?(:rgba)
      def color
        Color::RGB.new(*rgba)
      end
    end
  end

  class GradientPattern
    def add_color_stop(offset, *args)
      if args.size == 1
        color = Color.parse(args.first)
        args = color.to_rgb.to_a
      end
      add_color_stop_rgba(offset, *args)
    end

    if method_defined?(:get_color_stop_rgba)
      def get_color_stop(index)
        Color::RGB.new(*get_color_stop_rgba(index))
      end
    end
  end
end
