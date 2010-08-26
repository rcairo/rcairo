module Cairo
  class Paper
    class ParseError < ArgumentError
    end

    class UnknownPaperName < ParseError
      attr_reader :name
      def initialize(name)
        @name = name
        super("unknown paper name: #{name}")
      end
    end

    class UnknownUnit < ParseError
      attr_reader :unit
      def initialize(unit)
        @unit = unit
        super("unknown unit: #{unit}")
      end
    end

    class UnrecognizedPaperDescription < ParseError
      attr_reader :description
      def initialize(description)
        @description = description
        super("unrecognized paper description: #{description.inspect}")
      end
    end

    class << self
      def parse(paper_description, robust=false)
        case paper_description
        when Paper
          return paper_description.dup
        when Symbol
          paper = resolve_constant(paper_description)
          return paper.dup if paper
          raise UnknownPaperName.new(paper_description)
        when String
          paper = resolve_constant(paper_description)
          paper ||= parse_size(paper_description)
          return paper.dup if paper
        when Array
          return new(*paper_description)
        end

        raise UnrecognizedPaperDescription.new(paper_description) if robust
        nil
      end

      @@default_unit = nil
      def default_unit
        @@default_unit
      end

      def default_unit=(unit)
        @@default_unit = unit
      end

      @@unit_resolvers = {}
      def register_unit_resolver(from_units, to_units, &resolver)
        from_units = [from_units] unless from_units.is_a?(Array)
        to_units = [to_units] unless to_units.is_a?(Array)
        from_units.each do |from_unit|
          @@unit_resolvers[from_unit] ||= []
          to_units.each do |unit|
            @@unit_resolvers[from_unit] << [unit, resolver]
          end
        end
      end

      def resolve_unit(size, from_unit, to_unit)
        from_unit ||= default_unit
        return size if from_unit == to_unit
        from_units = @@unit_resolvers[from_unit] || []
        raise UnknownUnit.new(from_unit) if from_units.empty?
        from_units.each do |unit, resolver|
          return resolver.call(size) if to_unit == unit
        end
        raise UnknownUnit.new(to_unit)
      end

      private
      def resolve_constant(name)
        name = name.to_s.upcase.gsub(/\s+|-/, '_')
        if /\A[A-Z]/ =~ name and const_defined?(name)
          const_get(name)
        else
          nil
        end
      end

      def parse_size(size)
        size_re = /(\d+(\.\d*)?)/
        unit_re = /([a-zA-Z]+?)/
        if /\A#{size_re}#{unit_re}?x#{size_re}#{unit_re}?(?:#(.*))?\z/ !~ size
          return nil
        end

        width = $1
        width_fractional = $2
        width_unit = $3
        height = $4
        height_fractional = $5
        height_unit = $6
        name = $7
        width = width_fractional ? Float(width) : Integer(width)
        height = height_fractional ?  Float(height) : Integer(height)
        new(resolve_unit(width, width_unit, "pt"),
            resolve_unit(height, height_unit, "pt"),
            nil, name)
      end
    end

    self.default_unit = "pt"
    register_unit_resolver("pt", ["in", "inch"]) {|size| size / 72.0}
    register_unit_resolver(["in", "inch"], "pt") {|size| size * 72}
    register_unit_resolver("pt", "mm") {|size| size * 25.4 / 72.0}
    register_unit_resolver("mm", "pt") {|size| size / 25.4 * 72}
    register_unit_resolver("pt", "cm") {|size| size * 2.54 / 72.0}
    register_unit_resolver("cm", "pt") {|size| size / 2.54 * 72}
    register_unit_resolver("pt", "m") {|size| size * 0.0254 / 72.0}
    register_unit_resolver("m", "pt") {|size| size / 0.0254 * 72}

    attr_reader :unit
    attr_writer :width, :height
    attr_accessor :name
    def initialize(width, height, unit=nil, name=nil)
      @width = width
      @height = height
      @unit = unit
      @name = name
    end

    def unit=(unit)
      if @unit != unit
        @width = self.class.resolve_unit(width, @unit, unit)
        @height = self.class.resolve_unit(height, @unit, unit)
      end
      @unit = unit
    end

    def width(unit=nil)
      return @width if unit.nil?
      self.class.resolve_unit(@width, @unit, unit)
    end

    def height(unit=nil)
      return @height if unit.nil?
      self.class.resolve_unit(@height, @unit, unit)
    end

    def size(unit=nil)
      [width(unit), height(unit)]
    end

    def ==(other)
      other.is_a?(self.class) and @name == other.name and
        width_in_delta?(other.width(@unit)) and
        height_in_delta?(other.height(@unit))
    end

    def to_s
      string = "#{@width}#{@unit}x#{@height}#{@unit}"
      string << "\##{@name}" if @name
      string
    end

    private
    def width_in_delta?(value, delta=nil)
      in_delta?(@width, delta, value)
    end

    def height_in_delta?(value, delta=nil)
      in_delta?(@height, delta, value)
    end

    def in_delta?(value, delta, other)
      delta ||= 0.001
      value - delta < other and other < value + delta
    end
  end
end
