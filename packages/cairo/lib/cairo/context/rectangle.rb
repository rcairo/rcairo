module Cairo
  class Context
    module Rectangle
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
    end
  end
end
