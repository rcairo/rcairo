#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

$LOAD_PATH.unshift(".")

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

def set_output_lib(target_name)
  case RUBY_PLATFORM
  when /cygwin|mingw/
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
  when /mswin32/
    filename = "libruby-#{target_name}.lib"
    $DLDFLAGS.gsub!(/ --output-lib\s+[^ ]+/, '')
    $DLDFLAGS.gsub!(/ \/IMPLIB:[^ ]+/, '')
    $DLDFLAGS << " /IMPLIB:#{filename}" if filename
  when /darwin/
    if have_macro("CAIRO_HAS_QUARTZ_SURFACE", ["cairo.h"])
      $DLDFLAGS << " -Wl,-framework,RubyCocoa"
    end
  end
end


pkg = "cairo"
modname = "cairo"
ext_dir_name = "src"
srcdir = File.join(File.expand_path(File.dirname(__FILE__)), ext_dir_name)
major, minor, micro = 1, 2, 0

PKGConfig.have_package(pkg, major, minor, micro) or exit 1

have_func("rb_errinfo")

check_win32
set_output_lib(File.basename(modname))
$defs << "-DRUBY_CAIRO_COMPILATION"
create_makefile(modname, srcdir)

makefile = File.read("Makefile")
File.open("Makefile", "w") do |f|
  objs = []
  co = nil
  makefile.each_line do |line|
    case line
    when /^TARGET\s*=\s*/
      f.print("TARGET = #{ext_dir_name}/#{$POSTMATCH}")
    when /^(SRCS)\s*=\s*/
      name = $1
      vars = $POSTMATCH.split.collect {|var| "$(srcdir)/#{var}"}.join(" ")
      f.puts("#{name} = #{vars}")
    when /^(OBJS|CLEANLIBS|CLEANOBJS)\s*=\s*/
      name = $1
      vars = $POSTMATCH.split.collect {|var| "#{ext_dir_name}/#{var}"}
      objs = vars if name == "OBJS"
      vars = vars.join(" ")
      f.puts("#{name} = #{vars}")
    when /^\t\$\(CC\)/
      line = "#{line.chomp} -o $@" if /-o/ !~ line
      co = line
      f.puts(line)
    else
      f.print(line)
    end
  end

  if co and !objs.empty?
    f.puts
    objs.each do |obj|
      f.puts "#{obj}: $(srcdir)/#{File.basename(obj).sub(/.o$/, '.c')}"
      f.puts co
    end
  end
end

FileUtils.mkdir_p(ext_dir_name)
