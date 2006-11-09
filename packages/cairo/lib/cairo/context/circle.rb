module Cairo
  class Context
    module Circle
      def circle(x, y, radius)
        arc(x, y, radius, 0, 2 * Math::PI)
      end
    end
  end
end
