#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

require "mkmf"
require "fileutils"

require "pkg-config"

checking_for(checking_message("GCC")) do
  if macro_defined?("__GNUC__", "")
    $CFLAGS += ' -Wall'
    true
  else
    false
  end
end

package = "cairo"
module_name = "cairo"
major, minor, micro = 1, 2, 0

brew_path = find_executable("brew")
if brew_path
  # We don't use brew_path here to avoid quoting.
  libffi_prefix = `brew --prefix libffi`.chomp
  PKGConfig.add_path("#{libffi_prefix}/lib/pkgconfig")
end

unless PKGConfig.have_package(package, major, minor, micro)
  $stderr.puts("#{package} >= #{major}.#{minor}.#{micro} doesn't exist.")
  $stderr.puts("If you want to install " +
               "#{package} #{major}.#{minor}.#{micro} or later automatically, " +
               "install rubygems-requirements-system as a normal gem or " +
               "a Bundler plugin.")
  $stderr.puts("See the following documentation for details:")
  $stderr.puts("  https://github.com/ruby-gnome/rubygems-requirements-system/#usage-for-users")
  exit(false)
end

PKGConfig.have_package("cairo-ft")

checking_for(checking_message("macOS")) do
  case RUBY_PLATFORM
  when /darwin/
    if have_macro("CAIRO_HAS_QUARTZ_SURFACE", ["cairo.h"])
      checking_for("RubyCocoa") do
        begin
          require "osx/cocoa"
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

have_header("ruby/st.h") unless have_macro("HAVE_RUBY_ST_H", "ruby.h")
have_header("ruby/io.h") unless have_macro("HAVE_RUBY_IO_H", "ruby.h")
have_func("rb_errinfo", "ruby.h")
have_func("rb_gc_adjust_memory_usage", "ruby.h")
have_type("enum ruby_value_type", "ruby.h")

create_makefile(module_name)
