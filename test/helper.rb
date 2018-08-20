require "cairo"
require "poppler"
require "stringio"

module Helper
  private
  def only_cairo_version(major, minor, micro=nil)
    unless Cairo.satisfied_version?(major, minor, micro)
      omit("Require cairo >= #{major}.#{minor}.#{micro}")
    end
  end

  def only_windows
    omit("Only for Windows platform") unless windows?
  end

  def only_not_windows
    omit("Only for not Windows platform") if windows?
  end

  def windows?
    /cygwin|mingw|mswin|bccwin/ === RUBY_PLATFORM
  end

  def quartz?
    Cairo::FontFace.quartz_supported?
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

  def fixture_path(*components)
    File.join(__dir__, "fixture", *components)
  end
end
