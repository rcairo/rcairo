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
    def add_color_stop(*args)
      if args.size == 1 and args.first.is_a?(Color)
        add_color_stop_rgba(*args.first.to_rgb.to_a)
      else
        add_color_stop_rgba(*args)
      end
    end

    if method_defined?(:get_color_stop_rgba)
      def get_color_stop(index)
        Color::RGB.new(*get_color_stop_rgba(index))
      end
    end
  end
end
