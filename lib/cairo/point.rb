module Cairo
  class Point
    def distance(other)
      Math.sqrt((other.x - x) ** 2 + (other.y - y) ** 2)
    end
  end
end
