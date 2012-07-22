#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=2:tabstop=8:softtabstop=2 :

require 'pathname'
require 'English'
require 'mkmf'
require 'fileutils'

begin
  require 'pkg-config'
rescue LoadError
  require 'rubygems'
  require 'pkg-config'
end

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

base_dir = Pathname(__FILE__).dirname.parent.parent
checking_for(checking_message("Win32 OS")) do
  case RUBY_PLATFORM
  when /cygwin|mingw|mswin32/
    $defs << "-DRUBY_CAIRO_PLATFORM_WIN32"
    import_library_name = "libruby-#{module_name}.a"
    $DLDFLAGS << " -Wl,--out-implib=#{import_library_name}"
    $cleanfiles << import_library_name
    if with_config('vendor-override', true)
      binary_base_dir = base_dir + "vendor" + "local"
      $CFLAGS += " -I#{binary_base_dir}/include"
      pkg_config_dir = binary_base_dir + "lib" + "pkgconfig"
      PKGConfig.add_path(pkg_config_dir.to_s)
      PKGConfig.set_override_variable("prefix", binary_base_dir.to_s)
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

def package_platform
  if File.exist?("/etc/debian_version")
    :debian
  elsif File.exist?("/etc/fedora-release")
    :fedora
  elsif File.exist?("/etc/redhat-release")
    :redhat
  elsif find_executable("brew")
    :homebrew
  elsif find_executable("port")
    :macports
  else
    :unknown
  end
end

def super_user?
  Process.uid.zero?
end

def normalize_native_package_info(native_package_info)
  native_package_info ||= {}
  native_package_info = native_package_info.dup
  native_package_info[:fedora] ||= native_package_info[:redhat]
  native_package_info
end

def install_missing_native_package(native_package_info)
  platform = package_platform
  native_package_info = normalize_native_package_info(native_package_info)
  package = native_package_info[platform]
  return false if package.nil?

  need_super_user_priviledge = true
  case platform
  when :debian
    install_command = "apt-get install -V -y #{package}"
  when :fedora, :redhat
    install_command = "yum install -y #{package}"
  when :homebrew
    need_super_user_priviledge = false
    install_command = "brew install #{package}"
  when :macports
    install_command = "port install -y #{package}"
  else
    return false
  end

  have_priviledge = (not need_super_user_priviledge or super_user?)
  unless have_priviledge
    sudo = find_executable("sudo")
  end

  installing_message = "installing '#{package}' native package... "
  message("%s", installing_message)
  failed_to_get_super_user_priviledge = false
  if have_priviledge
    succeeded = xsystem(install_command)
  else
    if sudo
      install_command = "#{sudo} #{install_command}"
      succeeded = xsystem(install_command)
    else
      succeeded = false
      failed_to_get_super_user_priviledge = true
    end
  end

  if failed_to_get_super_user_priviledge
    result_message = "require super user privilege"
  else
    result_message = succeeded ? "succeeded" : "failed"
  end
  Logging.postpone do
    "#{installing_message}#{result_message}\n"
  end
  message("#{result_message}\n")

  error_message = nil
  unless succeeded
    if failed_to_get_super_user_priviledge
      error_message = <<-EOM
'#{package}' native package is required.
run the following command as super user to install required native package:
  \# #{install_command}
EOM
    else
      error_message = <<-EOM
failed to run '#{install_command}'.
EOM
    end
  end
  if error_message
    message("%s", error_message)
    Logging.message("%s", error_message)
  end

  Logging.message("--------------------\n\n")

  succeeded
end

def required_pkg_config_package(package_info, native_package_info=nil)
  if package_info.is_a?(Array)
    required_package_info = package_info
  else
    required_package_info = [package_info]
  end
  return true if PKGConfig.have_package(*required_package_info)

  native_package_info ||= {}
  return false unless install_missing_native_package(native_package_info)

  PKGConfig.have_package(*required_package_info)
end

unless required_pkg_config_package([package, major, minor, micro],
                                   :debian => "libcairo2-dev",
                                   :redhat => "cairo-devel",
                                   :homebrew => "cairo",
                                   :macports => "cairo")
  exit(false)
end

$defs << "-DRB_CAIRO_COMPILATION"

have_header("ruby/st.h") unless have_macro("HAVE_RUBY_ST_H", "ruby.h")
have_header("ruby/io.h") unless have_macro("HAVE_RUBY_IO_H", "ruby.h")
have_func("rb_errinfo", "ruby.h")
have_type("enum ruby_value_type", "ruby.h")

create_makefile(module_name)
