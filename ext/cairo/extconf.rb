#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

base_dir = File.expand_path(File.join(File.dirname(__FILE__), "..", ".."))
$LOAD_PATH.unshift(base_dir)

require 'English'
require 'mkmf'
require 'pkg-config'
require 'fileutils'

# from mkmf-gnome2.rb
STDOUT.print("checking for GCC... ")
STDOUT.flush
if macro_defined?("__GNUC__", "")
  STDOUT.print "yes\n"
  $CFLAGS += ' -Wall'
  $cc_is_gcc = true
else
  STDOUT.print "no\n"
  $cc_is_gcc = false
end

def check_win32
  checking_for("Win32 OS") do
    win32_os = /cygwin|mingw|mswin32/ =~ RUBY_PLATFORM
    if win32_os
      $defs << "-DRUBY_CAIRO_PLATFORM_WIN32"
      if $cc_is_gcc
        if /^2\./ =~ `#{Config::CONFIG['CC']} -dumpversion`.chomp
          $CFLAGS += ' -fnative-struct'
        else
          $CFLAGS += ' -mms-bitfields'
        end
      end
    end
    win32_os
  end
end

def set_output_lib(target_name, directory=nil)
  case RUBY_PLATFORM
  when /cygwin|mingw/
    filename = File.join(*([directory, "libruby-#{target_name}.a"].compact))
    if RUBY_VERSION > "1.8.0"
      $DLDFLAGS << ",--out-implib=#{filename}"
    elsif RUBY_VERSION > "1.8"
      $DLDFLAGS.gsub!(/ -Wl,--out-implib=[^ ]+/, '')
      $DLDFLAGS << " -Wl,--out-implib=#{filename}"
    else
      $DLDFLAGS.gsub!(/ --output-lib\s+[^ ]+/, '')
      $DLDFLAGS << " --output-lib #{filename}"
    end
    $cleanfiles << filename
  when /mswin32/
    $DLDFLAGS.gsub!(/ --output-lib\s+[^ ]+/, '')
    $DLDFLAGS.gsub!(/ \/IMPLIB:[^ ]+/, '')
    $DLDFLAGS << " /IMPLIB:$(IMPLIB)"
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

check_win32
target_name = File.basename(module_name)
set_output_lib(target_name)
$defs << "-DRB_CAIRO_COMPILATION"
create_makefile(module_name)
