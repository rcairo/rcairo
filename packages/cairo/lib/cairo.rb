# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

module Cairo
  def self.__add_one_arg_setter(klass)
    names = klass.instance_methods(false)
    names.each do |name|
      if /^set_(.*)/ =~ name and
          not names.include? "#{$1}=" and
          klass.instance_method(name).arity == 1
        klass.module_eval("def #{$1}=(val); set_#{$1}(val); val; end")
      end
    end
  end
end

require 'cairo.so'

module Cairo
  class << self
    undef __add_one_arg_setter
  end

  module_function
  def bindings_version
    major, minor, micro, tag = BINDINGS_VERSION
    version = [major, minor, micro].join('.')
    version << "-#{tag}" if tag
    version
  end

  class Surface
    def dup
      raise NotImplementedError
    end
    def clone
      raise NotImplementedError
    end
  end

  class SVGSurface
    class << self
      def versions_as_string
        versions.collect do |version|
          version_to_string(version)
        end
      end
    end
  end

  class Matrix
    def dup
      Matrix.new(*to_a)
    end

    def clone
      copy = dup
      copy.freeze if self.frozen?
      copy
    end

    def translate(tx, ty); dup.translate!(tx, ty); end
    def scale(sx, sy); dup.scale!(sx, sy); end
    def rotate(radians); dup.rotate!(radians); end
    def invert; dup.invert!; end
    def multiply(other); dup.multiply!(other); end
    alias * multiply
  end
end

require 'cairo/context'
