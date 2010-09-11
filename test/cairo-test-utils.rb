require 'cairo'

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
    device_class = "#{name}Device"
    unless Cairo.const_defined?(device_class)
      omit("Only for #{device_class} device available")
    end
  end

  def only_surface(name)
    surface_class = "#{name}Surface"
    unless Cairo.const_defined?(surface_class)
      omit("Only for #{surface_class} surface available")
    end
  end
end
