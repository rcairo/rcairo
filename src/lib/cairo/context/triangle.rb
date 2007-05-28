module Cairo
  class Context
    module Triangle
      def triangle(x1, y1, x2, y2, x3, y3)
        move_to(x1, y1)
        line_to(x2, y2)
        line_to(x3, y3)
        close_path
      end
    end
  end
end
