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
          paper ||= parse_size(paper_description.gsub(/#.*\z/, ''))
          return paper.dup if paper
        when Array
          return new(*paper_description)
        end

        raise UnrecognizedPaperDescription.new(paper_description) if robust
        nil
      end

      @@unit_resolvers = []
      def register_unit_resolver(name, *aliases, &resolver)
        ([name] + aliases).each do |unit|
          @@unit_resolvers << [unit, resolver]
        end
      end

      def resolve_unit(size, target_unit)
        @@unit_resolvers.each do |unit, resolver|
          return resolver.call(size) if target_unit == unit
        end
        raise UnknownUnit.new(target_unit)
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
        return nil if /\A#{size_re}#{unit_re}?x#{size_re}#{unit_re}?\z/ !~ size

        width = $1
        width_fractional = $2
        width_unit = $3
        height = $4
        height_fractional = $5
        height_unit = $6
        width = width_fractional ? Float(width) : Integer(width)
        height = height_fractional ?  Float(height) : Integer(height)
        new(resolve_unit(width, width_unit),
            resolve_unit(height, height_unit))
      end
    end

    register_unit_resolver(nil) {|size| size}
    register_unit_resolver("pt") {|size| size}
    register_unit_resolver("in", "inch") {|size| size * 72}
    register_unit_resolver("mm") {|size| size / 25.4 * 72}
    register_unit_resolver("cm") {|size| size / 2.54 * 72}
    register_unit_resolver("m") {|size| size / 0.0254 * 72}

    attr_reader :width, :height, :unit
    attr_accessor :name
    def initialize(width, height, unit=nil, name=nil)
      @unit = unit
      self.width = width
      self.height = height
      @name = name
    end

    def width=(width)
      @width = self.class.resolve_unit(width, @unit)
      width
    end

    def height=(height)
      @height = self.class.resolve_unit(height, @unit)
      height
    end

    def unit=(unit)
      original_unit = @unit
      @unit = unit
      if original_unit != @unit
        self.width = width
        self.height = height
      end
      unit
    end

    def size
      [@width, @height]
    end

    def ==(other)
      other.is_a?(self.class) and
        [@width, @height, @name] == [other.width, other.height, other.name]
    end

    def to_s
      string = "#{@width}#{@unit}x#{@height}#{@unit}"
      string << "\##{@name}" if @name
      string
    end
  end
end
