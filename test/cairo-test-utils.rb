require 'cairo'
require 'stringio'

module CairoTestUtils
  private
  def only_cairo_version(major, minor, micro=nil)
    unless Cairo.satisfied_version?(major, minor, micro)
      omit("Require cairo >= #{major}.#{minor}.#{micro}")
    end
  end

  def only_win32
    omit("Only for Win32 platform") unless win32
  end

  def win32?
    /cygwin|mingw|mswin32|bccwin32/.match(RUBY_PLATFORM) ? true : false
  end

  def only_device(name)
    only_cairo_version(1, 10)

    unless Cairo::Device.supported?(name)
      omit("Only for #{name} device available")
    end
  end

  def only_surface(name)
    unless Cairo::Surface.supported?(name)
      omit("Only for #{name} device available")
    end
  end

  def only_pattern(name)
    unless Cairo::Pattern.supported?(name)
      omit("Only for #{name} device available")
    end
  end
end
