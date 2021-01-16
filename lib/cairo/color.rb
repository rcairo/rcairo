require "colors"

module Cairo
  module Color
    module_function
    def parse(value, robust=false)
      return value.dup if value.is_a?(Base)
      case value
      when Array
        case value.first
        when :cmyk, :cmyka
          CMYK.new(*value[1..-1])
        when :hsv, :hsva
          HSV.new(*value[1..-1])
        else
          _, *value = value if [:rgb, :rgba].include?(value.first)
          RGB.new(*value)
        end
      when /\A\#/
        parse_hex_color(value)
      when String, Symbol
        name = Cairo.normalize_const_name(value)
        begin
          const_get(name).dup
        rescue NameError
          color = Colors[value]
          if color == value.to_s
            raise ArgumentError, "unknown color name: #{value}"
          end
          RGB.new(*color.to_rgba.components)
        end
      when Colors::AbstractColor
        RGB.new(*value.to_rgba.components)
      else
        if robust
          raise ArgumentError, "can't parse as color name: #{value.inspect}"
        end
        value
      end
    end

    HEX_RE = "(?i:[a-f\\d])"
    def parse_hex_color(value)
      case value
      when /\A\#((?:#{HEX_RE}){3,4})\z/
        RGB.new(*$1.scan(/./).collect {|part| part.hex / 15.0})
      when /\A\#((?:#{HEX_RE}{2,2}){3,4})\z/
        RGB.new(*$1.scan(/.{2,2}/).collect {|part| part.hex / 255.0})
      when /\A\#((?:#{HEX_RE}{4,4}){3,4})\z/
        RGB.new(*$1.scan(/.{4,4}/).collect {|part| part.hex / 65535.0})
      else
        message = "invalid hex color format: #{value} should be "
        message << "\#RGB, \#RGBA, \#RRGGBB, \#RRGGBBAA, \#RRRRGGGGBBBB "
        message << "or \#RRRRGGGGBBBBAAAA"
        raise ArgumentError, message
      end
    end

    class Base
      attr_accessor :alpha

      alias_method :a, :alpha
      alias_method :a=, :alpha=

      def initialize(a)
        assert_in_range(a, "alpha channel")
        @alpha = a
      end

      private
      def assert_in_range(value, description)
        unless (0.0..1.0).include?(value)
          raise ArgumentError,
                "#{description} value should be in [0.0, 1.0]: #{value.inspect}"
        end
      end
    end

    class RGB < Base
      attr_accessor :red, :green, :blue

      alias_method :r, :red
      alias_method :r=, :red=
      alias_method :g, :green
      alias_method :g=, :green=
      alias_method :b, :blue
      alias_method :b=, :blue=

      def initialize(r, g, b, a=1.0)
        super(a)
        assert_in_range(r, "red")
        assert_in_range(g, "green")
        assert_in_range(b, "blue")
        @red = r
        @green = g
        @blue = b
      end

      def hash
        to_s.hash
      end

      def eql?(other)
        self == other
      end

      def ==(other)
        other.is_a?(self.class) and other.to_s == to_s
      end

      def to_a
        [@red, @green, @blue, @alpha]
      end
      alias_method :to_ary, :to_a

      def to_s
        "#%02X%02X%02X%02X" % to_a.collect {|v| (v * 255).round(1)}
      end

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

      def to_hsv
        max = [@red, @blue, @green].max
        if max > 0
          min = [@red, @blue, @green].min
          max_min = max - min
          case max
          when @red
            numerator = @green - @blue
            angle = 0
          when @green
            numerator = @blue - @red
            angle = 120
          when @blue
            numerator = @red - @green
            angle = 240
          end
          h = max_min > 0 ? 60 * numerator / max_min + angle : 0.0
          s = max_min / max
        else
          h = 0.0
          s = 0.0
        end
        v = max
        HSV.new(h, s, v, @alpha)
      end
    end

    class CMYK < Base
      attr_accessor :cyan, :magenta, :yellow, :key_plate

      alias_method :c, :cyan
      alias_method :c=, :cyan=
      alias_method :m, :magenta
      alias_method :m=, :magenta=
      alias_method :y, :yellow
      alias_method :y=, :yellow=
      alias_method :k, :key_plate
      alias_method :k=, :key_plate=

      def initialize(c, m, y, k, a=1.0)
        super(a)
        assert_in_range(c, "cyan")
        assert_in_range(m, "magenta")
        assert_in_range(y, "yellow")
        assert_in_range(k, "key plate")
        @cyan = c
        @magenta = m
        @yellow = y
        @key_plate = k
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

      def to_hsv
        to_rgb.to_hsv
      end
    end

    class HSV < Base
      attr_accessor :hue, :saturation, :value

      alias_method :h, :hue
      alias_method :h=, :hue=
      alias_method :s, :saturation
      alias_method :s=, :saturation=
      alias_method :v, :value
      alias_method :v=, :value=

      def initialize(h, s, v, a=1.0)
        super(a)
        assert_in_range(s, "saturation")
        assert_in_range(v, "value")
        @hue = h.modulo(360.0)
        @saturation = s
        @value = v
      end

      def to_a
        [@hue, @saturation, @value, @alpha]
      end
      alias_method :to_ary, :to_a

      def to_rgb
        if s > 0
          h_60 = @hue / 60.0
          hi = h_60.floor.modulo(6)
          f = h_60 - hi
          p = @value * (1 - @saturation)
          q = @value * (1 - f * @saturation)
          t = @value * (1 - (1 - f) * @saturation)
          case hi
          when 0
            rgb = [@value, t, p]
          when 1
            rgb = [q, @value, p]
          when 2
            rgb = [p, @value, t]
          when 3
            rgb = [p, q, @value]
          when 4
            rgb = [t, p, @value]
          when 5
            rgb = [@value, p, q]
          end
          rgba = rgb + [@alpha]
          RGB.new(*rgba)
        else
          RGB.new(@value, @value, @value, @alpha)
        end
      end

      def to_cmyk
        to_rgb.to_cmyk
      end

      def to_hsv
        clone
      end
    end
  end
end
