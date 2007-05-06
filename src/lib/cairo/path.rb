require 'forwardable'

module Cairo
  class Path
    extend Forwardable
    methods = %w(new_path new_sub_path move_to line_to curve_to
                 arc arc_negative rel_move_to rel_line_to rel_curve_to
                 rectangle rounded_rectangle circle)
    def_delegators :@context, *methods

    def close
      @context.close_path
    end
  end
end
