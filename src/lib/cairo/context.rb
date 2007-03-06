require 'cairo/context/quad'
require 'cairo/context/rectangle'
require 'cairo/context/circle'
require 'cairo/context/path'

module Cairo
  class Context
    include Quad
    include Rectangle
    include Circle
    include Path
  end
end
