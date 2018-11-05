module Cairo
  class Point
    def distance(other)
      Math.hypot(other.x - x, other.y - y)
    end
  end
end
