module Cairo
  module Color
    class Base
    end

    class RGB < Base
      def initialize(r, g, b, a=1.0)
        @red = r
        @green = g
        @blue = b
        @alpha = a
      end

      def to_a
        [@red, @green, @blue, @alpha]
      end
      alias_method :to_ary, :to_a

      def to_rgb
        clone
      end

      def to_cmyk
        cmy = [1.0 - @red, 1.0 - @green, 1.0 - @blue]
        key_plate = cmy.min
        if key_plate < 1.0
          one_k = 1.0 - key_plate
          cmyk = cmy.collect {|value| (value - key_plate) / one_k} + [key_plate]
        else
          cmyk = [0, 0, 0, key_plate]
        end
        cmyka = cmyk + [@alpha]
        CMYK.new(*cmyka)
      end
    end

    class CMYK < Base
      def initialize(c, m, y, k, a=1.0)
        @cyan = c
        @magenta = m
        @yellow = y
        @key_plate = k
        @alpha = a
      end

      def to_a
        [@cyan, @magenta, @yellow, @key_plate, @alpha]
      end
      alias_method :to_ary, :to_a

      def to_rgb
        one_k = 1.0 - @key_plate
        rgba = [
                (1.0 - @cyan) * one_k,
                (1.0 - @magenta) * one_k,
                (1.0 - @yellow) * one_k,
                @alpha,
               ]
        RGB.new(*rgba)
      end

      def to_cmyk
        clone
      end
    end
  end
end
