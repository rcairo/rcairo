module Cairo
  class Paper
    class ParseError < StandardError
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

    class << self
      def parse(paper_description)
        case paper_description
        when Symbol
          paper = resolve_constant(paper_description)
          raise UnknownPaperName.new(paper_description) if paper.nil?
          paper
        when String
          paper = resolve_constant(paper_description)
          paper ||= parse_size(paper_description.gsub(/#.*\z/, ''))
        end
      end

      @@unit_resolvers = []
      def register_unit_resolver(name, resolver=Proc.new)
        @@unit_resolvers << [name, resolver]
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

      def resolve_unit(size, target_unit)
        @@unit_resolvers.each do |unit, resolver|
          return resolver.call(size) if target_unit == unit
        end
        raise UnknownUnit.new(target_unit)
      end
    end

    register_unit_resolver(nil) {|size| size}
    register_unit_resolver("mm") {|size| size}
    register_unit_resolver("inch") {|size| size * 25.4}

    attr_accessor :width, :height, :name
    def initialize(width, height, name=nil)
      @width = width
      @height = height
      @name = name
    end

    def size
      [@width, @height]
    end

    def ==(other)
      other.is_a?(self.class) and
        [@width, @height, @name] == [other.width, other.height, other.name]
    end

    def to_s
      string = "#{@width}x#{@height}"
      string << "\##{@name}" if @name
      string
    end
  end
end
