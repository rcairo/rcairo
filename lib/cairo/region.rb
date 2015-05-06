module Cairo
  class Region
    def each_rectangle
      return to_enum(:each_rectangle) unless block_given?
      num_rectangles.times.each do |i|
        yield(self[i])
      end
    end

    def rectangles
      each_rectangle.to_a
    end
  end
end
