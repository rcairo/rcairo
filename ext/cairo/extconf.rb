#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

require 'pathname'
require 'English'
require 'mkmf'
require 'fileutils'

base_dir = (Pathname(__FILE__).dirname + ".." + "..").expand_path
$LOAD_PATH.unshift(base_dir.to_s)

require 'pkg-config'

checking_for(checking_message("GCC")) do
  if macro_defined?("__GNUC__", "")
    $CFLAGS += ' -Wall'
    true
  else
    false
  end
end

pkg = "cairo"
module_name = "cairo"
major, minor, micro = 1, 2, 0

PKGConfig.have_package(pkg, major, minor, micro) or exit 1

have_header("ruby/st.h") unless have_macro("HAVE_RUBY_ST_H", "ruby.h")
have_header("ruby/io.h") unless have_macro("HAVE_RUBY_IO_H", "ruby.h")
have_func("rb_errinfo", "ruby.h")
have_type("enum ruby_value_type", "ruby.h")

checking_for(checking_message("Win32 OS")) do
  case RUBY_PLATFORM
  when /cygwin|mingw|mswin32/
    $defs << "-DRUBY_CAIRO_PLATFORM_WIN32"
    import_library_name = "libruby-#{module_name}.a"
    $DLDFLAGS << " -Wl,--out-implib=#{import_library_name}"
    $cleanfiles << import_library_name
    local_cairo_install_dir = base_dir + "vendor" + "local"
    $CFLAGS += " -I#{local_cairo_install_dir}/include"
    local_cairo_lib_dir = local_cairo_install_dir + "lib"
    ["libcairo.lib", "libcairo.dll.a"].each do |libcairo_base|
      libcairo = local_cairo_lib_dir + libcairo_base
      if libcairo.exist?
        $DLDFLAGS += " -L#{local_cairo_lib_dir}"
        break
      end
    end
    true
  else
    false
  end
end

checking_for(checking_message("Mac OS X")) do
  case RUBY_PLATFORM
  when /darwin/
    if have_macro("CAIRO_HAS_QUARTZ_SURFACE", ["cairo.h"])
      checking_for("RubyCocoa") do
        begin
          require 'osx/cocoa'
          $defs << "-DHAVE_RUBY_COCOA"
          $DLDFLAGS << " -Wl,-framework,RubyCocoa"
          true
        rescue LoadError
          false
        end
      end
    end
    true
  else
    false
  end
end

$defs << "-DRB_CAIRO_COMPILATION"
create_makefile(module_name)
