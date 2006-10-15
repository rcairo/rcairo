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

  class Context
    def quad_to(x1, y1, x2, y2)
      x0, y0 = current_point
      cx1 = x0 + 2 * (x1 - x0) / 3.0
      cy1 = y0 + 2 * (y1 - y0) / 3.0
      cx2 = cx1 + (x2 - x0) / 3.0
      cy2 = cy1 + (y2 - y0) / 3.0
      curve_to(cx1, cy1, cx2, cy2, x2, y2)
    end

    def rel_quad_to(x1, y1, x2, y2)
      x0, y0 = current_point
      quad_to(x1 + x0, y1 + y0, x2 + x0, y2 + x0)
    end

    def rounded_rectangle(x, y, width, height, x_radius, y_radius=nil)
      x1 = x
      x2 = x1 + width
      y1 = y
      y2 = y1 + height

      y_radius ||= x_radius

      x_radius = [x_radius, width / 2.0].min
      y_radius = [y_radius, height / 2.0].min

      xr1 = x_radius
      xr2 = x_radius / 2.0
      yr1 = y_radius
      yr2 = y_radius / 2.0

      move_to(x1 + xr1, y1)
      line_to(x2 - xr1, y1)
      curve_to(x2 - xr2, y1, x2, y1 + yr2, x2, y1 + yr1)
      line_to(x2, y2 - yr1)
      curve_to(x2, y2 - yr2, x2 - xr2, y2, x2 - xr1, y2)
      line_to(x1 + xr1, y2)
      curve_to(x1 + xr2, y2, x1, y2 - yr2, x1, y2 - yr1)
      line_to(x1, y1 + yr1)
      curve_to(x1, y1 + yr2, x1 + xr2, y1, x1 + xr1, y1)
      close_path
    end

    def circle(x, y, radius)
      arc(x, y, radius, 0, 2 * Math::PI)
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
