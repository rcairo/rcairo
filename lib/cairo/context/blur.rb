module Cairo
  class Context
    module Blur
      def pseudo_blur(radius=3, &block)
        raise ArgumentError, "should specify block" if block.nil?
        pattern = push_group(Cairo::CONTENT_COLOR_ALPHA, false, &block)

        save do
          set_source(pattern)
          paint(0.5)
        end

        1.step(radius, 1) do |i|
          opacity = 0.075 - 0.005 * i
          next if opacity <= 0
          5.downto(1) do |ratio|
            r = i / ratio.to_f
            r_13 = r / 3.0
            r_23 = 2 * r_13
            [
             [-r, 0],
             [-r_23, r_23],
             [-r_23, r_13],
             [0, r],
             [r_13, r_23],
             [r_23, r_23],
             [r, 0],
             [r_23, -r_13],
             [r_23, -r_23],
             [0, -r],
             [-r_13, -r_23],
             [-r_23, -r_23],
            ].each do |x, y|
              save do
                translate(x, y)
                set_source(pattern)
                paint(opacity)
              end
            end
          end
        end
      end
    end
  end
end
