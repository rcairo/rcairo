module Cairo
  class Context
    module Circle
      def circle(center_x, center_y, radius)
        arc(center_x, center_y, radius, 0, 2 * Math::PI)
      end
    end
  end
end
