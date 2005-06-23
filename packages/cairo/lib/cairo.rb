# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

require 'cairo.so' 

module Cairo

class Context
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

    def rgb_color=(*args)
        args = args[0] if args[0].is_a? Array
        self.set_rgb_color(*args)
    end

    alias save_internal save
    private :save_internal
    def save
        if block_given?
            save_internal
            begin
                yield
            ensure
                restore
            end
        else
            save_internal
        end
    end

    alias operator= set_operator
    alias operator get_operator
    alias tolerance= set_tolerance
    alias tolerance get_tolerance
    alias fill_rule= set_fill_rule
    alias fill_rule get_fill_rule
    alias line_width= set_line_width
    alias line_width get_line_width
    alias line_cap= set_line_cap
    alias line_cap get_line_cap
    alias line_join= set_line_join
    alias line_join get_line_join
    alias miter_limit= set_miter_limit
    alias miter_limit get_miter_limit
    alias matrix= set_matrix
    alias matrix get_matrix
    alias source get_source
    alias source= set_source
    alias set_transform set_matrix
    alias get_transform get_matrix
    alias transform= set_transform
    alias transform get_transform
    alias target get_target
    alias font_face get_font_face
    alias font_face= set_font_face

    alias in_fill? in_fill
    alias in_stroke? in_stroke
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
