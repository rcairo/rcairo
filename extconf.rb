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

def create_makefile_at_srcdir(pkg_name, srcdir, defs=nil)
  begin
    Dir.mkdir(srcdir) unless File.exist?(srcdir)
    Dir.chdir(srcdir)

    yield if block_given?

    $defs << defs if defs
    create_makefile(pkg_name, srcdir)
  ensure
    Dir.chdir('..')
  end
end

def create_top_makefile(sub_dirs=["src"])
  File.open("Makefile", "w") do |mfile|
    if /mswin32/ =~ RUBY_PLATFORM
      mfile.print <<MSWIN32_END

all:
#{sub_dirs.map{|d| "	@cd #{d}\n	@nmake -nologo all\n	@cd ..\n"}.join('')}
install:
#{sub_dirs.map{|d| "	@cd #{d}\n	@nmake -nologo install DESTDIR=$(DESTDIR)\n	@cd ..\n"}.join('')}
site-install:
#{sub_dirs.map{|d| "	@cd #{d}\n	@nmake -nologo site-install DESTDIR=$(DESTDIR)\n	@cd ..\n"}.join('')}
clean:
#{sub_dirs.map{|d| "	@cd #{d}\n	@nmake -nologo clean\n	@cd ..\n"}.join('')}	@if exist extconf.h del extconf.h
	@if exist conftest.* del conftest.*
	@if exist *.lib del *.lib
	@if exist *~ del *~
	@if exist mkmf.log del mkmf.log
MSWIN32_END
    else
      mfile.print <<END
all:
#{sub_dirs.map{|d| "	@cd #{d}; make all\n"}.join('')}

install:
#{sub_dirs.map{|d| "	@cd #{d}; make install\n"}.join('')}
site-install:
#{sub_dirs.map{|d| "	@cd #{d}; make site-install\n"}.join('')}
clean:
#{sub_dirs.map{|d| "	@cd #{d}; make clean\n"}.join('')}
distclean:	clean
#{sub_dirs.map{|d| "	@cd #{d}; make distclean\n"}.join('')}
	@rm -f Makefile extconf.h conftest.*
	@rm -f core *~ mkmf.log
END
    end
  end
end


pkg = "cairo"
modname = "cairo"
srcdir = File.join(File.expand_path(File.dirname(__FILE__)), "src")
major, minor, micro = 1, 2, 0

PKGConfig.have_package(pkg, major, minor, micro) or exit 1

setup_win32(File.basename(modname))
create_makefile_at_srcdir(modname, srcdir, "-DRUBY_CAIRO_COMPILATION")

create_top_makefile
