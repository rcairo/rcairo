#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

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

def check_win32()
  STDOUT.print("checking for Win32 OS... ")
  STDOUT.flush
  if /cygwin|mingw|mswin32/ =~ RUBY_PLATFORM
    $defs << "-DRUBY_CAIRO_PLATFORM_WIN32"
    STDOUT.print "yes\n"
    if $cc_is_gcc
      if /^2\./ =~ `#{Config::CONFIG['CC']} -dumpversion`.chomp
        $CFLAGS += ' -fnative-struct'
      else
        $CFLAGS += ' -mms-bitfields'
      end
    end
  else
    STDOUT.print "no\n"
  end
end

def set_output_lib(target_name)
  if /cygwin|mingw/ =~ RUBY_PLATFORM
    filename = "libruby-#{target_name}.a"
    if RUBY_VERSION > "1.8.0"
      $DLDFLAGS << ",--out-implib=#{filename}" if filename
    elsif RUBY_VERSION > "1.8"
      $DLDFLAGS.gsub!(/ -Wl,--out-implib=[^ ]+/, '')
      $DLDFLAGS << " -Wl,--out-implib=#{filename}" if filename
    else
      $DLDFLAGS.gsub!(/ --output-lib\s+[^ ]+/, '')
      $DLDFLAGS << " --output-lib #{filename}" if filename
    end
  elsif /mswin32/ =~ RUBY_PLATFORM
      filename = "libruby-#{target_name}.lib"
      $DLDFLAGS.gsub!(/ --output-lib\s+[^ ]+/, '')
      $DLDFLAGS.gsub!(/ \/IMPLIB:[^ ]+/, '')
      $DLDFLAGS << " /IMPLIB:#{filename}" if filename    
  end
end

def setup_win32(target_name)
  check_win32
  set_output_lib(target_name)
end


pkg = "cairo"
modname = "cairo"
major, minor, micro = 1, 0, 0

PKGConfig.have_package(pkg, major, minor, micro) or exit 1

setup_win32(modname)
$defs << "-DRUBY_CAIRO_COMPILATION"
create_makefile(modname)
