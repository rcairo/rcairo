# Extends the Cairo module with a fd_logo  method that draw the freedesktop logo
#
# Copyright © 2003 Keith Packard (.c  version)
#             2004 Øyvind Kolås  (.rb version)

require 'cairo'

module Fdlogo
    def draw_boundary cr
        cr.move_to  63, 36
        cr.curve_to 63, 43,
                    58, 47,
                    51, 47
        cr.line_to  13, 47
        cr.curve_to  6, 47,
                     1, 43,
                     1, 36
        cr.line_to   1, 12
        cr.curve_to  1,  5,
                     6,  1,
                    13,  1
        cr.line_to  51,  1
        cr.curve_to 58,  1,
                    63,  5,
                    63, 12
        cr.close_path
    end
    def draw_outline cr
        cr.rgb_color  = 0.73, 0.73, 0.73
        cr.line_width = 2.0
        draw_boundary cr
        cr.stroke
    end
    def draw_background cr
        cr.save
          cr.rgb_color  =  0.231, 0.502, 0.682
          cr.translate     3.5, 3.5
          cr.scale         0.887, 0.848
          draw_boundary cr
          cr.fill
        cr.restore
    end
    def draw_window cr
       cr.move_to  -6, -7.125
       cr.line_to   6, -7.125
       cr.curve_to  8, -7.125,
                    9, -6.125,
                    9, -4.125
       cr.line_to   9,  4.125
       cr.curve_to  9,  6.125,
                    8,  7.125,
                    6,  7.125
       cr.line_to  -6,  7.125
       cr.curve_to -8,  7.125,
                   -9,  6.125,
                   -9,  4.125
       cr.line_to  -9, -4.125
       cr.curve_to -9, -6.125,
                   -8, -7.125,
                   -6, -7.125
       cr.close_path
    end
    def draw_window_at cr, x, y, scale
        cr.save
          cr.translate x,y
          cr.scale scale, scale
          draw_window cr
          cr.save
            cr.rgb_color = 1,1,1
            cr.fill
          cr.restore
          cr.rgb_color = 0.231, 0.502, 0.682
          cr.scale 1.0/scale, 1.0/scale
          cr.stroke
        cr.restore
    end
    def draw_windows cr
        cr.save
          cr.move_to 18.00, 16.125
          cr.line_to 48.25, 20.375
          cr.line_to 30.25, 35.825
          cr.close_path
          cr.rgb_color = 1,1,1
          cr.alpha = 0.5
          cr.stroke
        cr.restore
        draw_window_at cr, 18.00, 16.125, 1
        draw_window_at cr, 48.25, 20.375, 0.8
        draw_window_at cr, 30.25, 35.825, 0.5
    end

    FDLOGO_ROT_X_FACTOR = 1.086
    FDLOGO_ROT_Y_FACTOR = 1.213
    FDLOGO_WIDTH  = (64 * FDLOGO_ROT_X_FACTOR)
    FDLOGO_HEIGHT = (48 * FDLOGO_ROT_Y_FACTOR)
    
    def draw cr, width, height
        cr.save
          x_scale = width  / FDLOGO_WIDTH
          y_scale = height / FDLOGO_HEIGHT
          scale   = x_scale < y_scale ? x_scale : y_scale
          x_off   = (width  - (scale * FDLOGO_WIDTH)) /2
          y_off   = (height - (scale * FDLOGO_HEIGHT))/2
          cr.translate x_off, y_off
          cr.scale scale, scale

          cr.translate -2.5, 14.75
          cr.rotate -0.274990703529840

          draw_outline cr
          draw_background cr
          draw_windows cr
        cr.restore
    end
end

include Fdlogo

module Cairo
    class Cairo
        # draw the freedesktop logo in specified dimensions
        #
        def fd_logo width, height
            Fdlogo.draw self, width, height
            self
        end
    end
end
        
