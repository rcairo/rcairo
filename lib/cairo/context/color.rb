require 'cairo/color'

module Cairo
  class Context
    module Color
      def set_source_color(color)
        set_source_rgba(*Cairo::Color.parse(color).to_rgb.to_a)
      end
    end
  end
end
