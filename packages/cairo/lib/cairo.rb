# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

require 'cairo.so' 

module Cairo

  BINDINGS_VERSION = [1, 0, 0, "beta"]

  module_function
  def bindings_version
    major, minor, micro, tag = BINDINGS_VERSION
    version = [major, minor, micro].join('.')
    version << "-#{tag}" if tag
    version
  end
  
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

  class Context
    Cairo.__add_one_arg_setter(self)

    def quad_to(x1, y1, x2, y2)
      ( x0, y0 ) = get_point
      cx1 = x0 + 2 * ( x1 - x0 ) / 3
      cy1 = y0 + 2 * ( y1 - y0 ) / 3
      cx2 = cx1 + ( x2 - x0 ) / 3
      cy2 = cy1 + ( y2 - y0 ) / 3
      curve_to(cx1, cy1, cx2, cy2, x2, y2)
    end
    
    def rel_quad_to(x1, y1, x2, y2)
      ( x0, y0 ) = get_point
      quad_to(x1 + x0, y1 + y0, x2 + x0, y2 + x0)
    end

    def rounded_rectangle(x, y, width, height, x_radius, y_radius=nil)
      x1 = x
      x2 = x1 + width
      y1 = y
      y2 = y1 + height

      y_radius ||= x_radius

      x_radius = [x_radius, width / 2].min
      y_radius = [y_radius, height / 2].min
      
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

  class Glyph
    Cairo.__add_one_arg_setter(self)
  end

  class Surface
    def dup
      raise NotImplementedError
    end
    def clone
      raise NotImplementedError
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

    def transform(tx, ty); dup.transform!(tx, ty); end
    def scale(sx, sy); dup.scale!(sx, sy); end
    def rotate(radians); dup.rotate!(radians); end
    def invert; dup.invert!; end
    def multiply(other); dup.multiply!(other); end
    alias * multiply
  end

  class FontOptions
    Cairo.__add_one_arg_setter(self)
  end

  class Pattern
    Cairo.__add_one_arg_setter(self)
  end

  class SurfacePattern
    Cairo.__add_one_arg_setter(self)
  end
end
