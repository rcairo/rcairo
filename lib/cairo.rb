require "time"

module Cairo
  class << self
    def __add_one_arg_setter(klass)
      names = klass.instance_methods(false)
      names.each do |name|
        if /^set_(.*)/ =~ name and
            not names.include? "#{$1}=" and
            klass.instance_method(name).arity == 1
          klass.module_eval("def #{$1}=(val); set_#{$1}(val); val; end")
        end
      end
    end

    def normalize_const_name(name)
      name.to_s.upcase.gsub(/[\s\-_.]+/, "_")
    end
  end
end

require "cairo/color"
require "cairo/paper"
require "cairo.so"
require "cairo/constants"

module Cairo
  class << self
    undef __add_one_arg_setter

    def bindings_version
      major, minor, micro, tag = BINDINGS_VERSION
      version = [major, minor, micro].join(".")
      version << "-#{tag}" if tag
      version
    end

    def exit_application(exception, status)
      puts("#{exception.class}: #{exception}")
      puts(exception.backtrace)
      exit(status)
    end
  end

  class Surface
    def dup
      raise NotImplementedError
    end
    def clone
      raise NotImplementedError
    end
  end

  if const_defined?("PSLevel")
    module PSLevel
      class << self
        def names
          list.collect {|version| name(version)}
        end
      end
    end
  end

  if const_defined?("SVGVersion")
    module SVGVersion
      class << self
        def names
          list.collect {|version| name(version)}
        end
      end
    end
  end

  if const_defined?("SVGSurface")
    class SVGSurface
      class << self
        def versions_as_string
          SVGVersion.names
        end

        def versions
          SVGVersion.list
        end

        def version_to_string(version)
          SVGVersion.name(version)
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
    alias_method :*, :multiply
  end

  class FontOptions
    def merge(other)
      dup.merge!(other)
    end
  end
end

require "cairo/point"
require "cairo/colors"
require "cairo/papers"
require "cairo/context"
require "cairo/device"
require "cairo/surface"
require "cairo/pattern"
require "cairo/path"
require "cairo/region"

module Cairo
  if const_defined?(:Win32Surface)
    WIN32Surface = Win32Surface # For backward compatibility
  end
end
