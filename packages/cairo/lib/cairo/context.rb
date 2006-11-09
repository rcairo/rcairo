require 'cairo/context/quad'
require 'cairo/context/rectangle'
require 'cairo/context/circle'

module Cairo
  class Context
    include Quad
    include Rectangle
    include Circle
  end
end
