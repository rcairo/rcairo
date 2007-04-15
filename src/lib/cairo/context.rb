require 'cairo/context/quad'
require 'cairo/context/rectangle'
require 'cairo/context/circle'
require 'cairo/context/path'
require 'cairo/context/blur'

module Cairo
  class Context
    include Quad
    include Rectangle
    include Circle
    include Path
    include Blur
  end
end
