module Cairo
  class Context
    module Quad
      def quad_to(x1, y1, x2, y2)
        x0, y0 = current_point
        cx1 = x0 + 2 * (x1 - x0) / 3.0
        cy1 = y0 + 2 * (y1 - y0) / 3.0
        cx2 = cx1 + (x2 - x0) / 3.0
        cy2 = cy1 + (y2 - y0) / 3.0
        curve_to(cx1, cy1, cx2, cy2, x2, y2)
      end

      def rel_quad_to(x1, y1, x2, y2)
        x0, y0 = current_point
        quad_to(x1 + x0, y1 + y0, x2 + x0, y2 + x0)
      end
    end
  end
end
