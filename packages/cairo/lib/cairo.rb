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
        ( x0, y0 ) = current_point
        cx1 = x0 + 2 * ( x1 - x0 ) / 3
        cy1 = y0 + 2 * ( y1 - y0 ) / 3
        cx2 = cx1 + ( x2 - x0 ) / 3
        cy2 = cy1 + ( y2 - y0 ) / 3
        curve_to(cx1, cy1, cx2, cy2, x2, y2)
    end
    def rel_quad_to(x1, y1, x2, y2)
        ( x0, y0 ) = current_point
        quad_to(x1 + x0, y1 + y0, x2 + x0, y2 + x0)
    end

    private :current_path_array
    def current_path(handler=nil)
        array = current_path_array
        if handler.nil?
            array.each {|event| yield event } if block_given?
        else
            array.each {|event| handler.send(*event) }
        end
        array
    end

    private :current_path_flat_array
    def current_path_flat(handler=nil)
        array = current_path_flat_array
        if handler.nil?
            array.each {|event| yield event } if block_given?
        else
            array.each {|event| handler.send(*event) }
        end
        array
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
    alias operator current_operator
    alias alpha= set_alpha
    alias alpha current_alpha
    alias tolerance= set_tolerance
    alias tolerance current_tolerance
    alias fill_rule= set_fill_rule
    alias fill_rule current_fill_rule
    alias line_width= set_line_width
    alias line_width current_line_width
    alias line_cap= set_line_cap
    alias line_cap current_line_cap
    alias line_join= set_line_join
    alias line_join current_line_join
    alias miter_limit= set_miter_limit
    alias miter_limit current_miter_limit
    alias matrix= set_matrix
    alias matrix current_matrix
    alias pattern current_pattern
    alias pattern= set_pattern
    alias set_transform set_matrix
    alias current_transform current_matrix
    alias transform= set_transform
    alias transform current_transform
    alias target_surface= set_target_surface
    alias target_surface current_target_surface
    alias font current_font
    alias font= set_font

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

class Pattern

    alias matrix  get_matrix
    alias matrix= set_matrix
    alias extend  get_extend
    alias extend= set_extend
    alias filter  get_filter
    alias filter= set_filter
    
    class << Pattern  # singleton overrides
        alias   :create_linear_internal :create_linear
        private :create_linear_internal

        def create_linear(x0,y0,x1,y1)
            if block_given?
                pat = create_linear_internal(x0,y0,x1,y1)
                yield pat
                return pat
            end
            create_linear_internal(x0,y0,x1,y1)
        end

        alias   :create_radial_internal :create_radial
        private :create_radial_internal

        def create_radial(cx0,cy0,r0,cx1,cy1,r1)
            if block_given?
                pat = create_radial_internal(cx0,cy0,r0,cx1,cy1,r1)
                yield pat
                return pat
            end
            create_radial_internal(cx0,cy0,r0,cx1,cy1,r1)
        end

    end



end
end
