# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

require 'cairo.so' 

module Cairo

  module_function
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

    def dup
      copy = Context.new
      copy.copy(self)
      return copy
    end
    def clone
      copy = Context.new
      copy.copy(self)
      copy.freeze if self.frozen?
      return copy
    end

    def set_target_png(port, format, width, height)
      set_target_surface(Surface.new_png(port, format, width, height))
    end

    def set_target_ps(port, width_inches, height_inches, x_pixels_inch, y_pixels_inch)
      set_target_surface(Surface.new_ps(port, width_inches, height_inches, x_pixels_inch, y_pixels_inch))
    end

    def set_target_pdf(port, width_inches, height_inches, x_pixels_inch, y_pixels_inch)
      set_target_surface(Surface.new_pdf(port, width_inches, height_inches, x_pixels_inch, y_pixels_inch))
    end

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
      copy = Matrix.new
      copy.copy(self)
      return copy
    end
    def clone
      copy = Matrix.new
      copy.copy(self)
      copy.freeze if self.frozen?
      return copy
    end

    def transform(tx, ty) ; dup.transform!(tx, ty) ; end
    def scale(sx, sy) ; dup.scale!(sx, sy) ; end
    def rotate(radians) ; dup.rotate!(radians) ; end
    def invert() ; dup.invert! ; end

    def multiply!(other) ; set_product(self, other) ; end
    def multiply(other) ; Matrix.new.set_product(self, other) ; end

    def *(other) ; Matrix.new.set_product(self, other) ; end
  end
end
