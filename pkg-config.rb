require "rbconfig"

require 'mkmf'
require 'shellwords'
require 'English'
require 'pathname'

class PackageConfig
  attr_accessor :msvc_syntax
  def initialize(name, path=nil, msvc_syntax=false)
    @name = name
    @path = path || ENV["PKG_CONFIG_PATH"] || guess_path
    @msvc_syntax = msvc_syntax
    @variables = @declarations = nil
  end

  def exist?
    not pc.nil?
  end

  def requires
    parse_requires(declaration("Requires"))
  end

  def requires_private
    parse_requires(declaration("Requires.private"))
  end

  def cflags
    all_cflags = (requires_private + requires.reverse).collect do |package|
      self.class.new(package, @path, @msvc_syntax).cflags
    end
    all_cflags = [declaration("Cflags")] + all_cflags
    all_cflags = all_cflags.join(" ").gsub(/-I /, '-I').split.uniq
    path_flags, other_flags = all_cflags.partition {|flag| /\A-I/ =~ flag}
    path_flags = path_flags.reject do |flag|
      flag == "-I/usr/include"
    end
    (other_flags + path_flags).join(" ")
  end

  def libs
    all_libs = requires.collect do |package|
      self.class.new(package, @path, @msvc_syntax).libs
    end
    all_libs = [declaration("Libs")] + all_libs
    all_libs = all_libs.join(" ").gsub(/-([Ll]) /, '\1').split.uniq
    path_flags, other_flags = all_libs.partition {|flag| /\A-L/ =~ flag}
    path_flags = path_flags.reject do |flag|
      /\A-L\/usr\/lib(?:64)?\z/ =~ flag
    end
    libs = (other_flags + path_flags).join(" ")
    if @msvc_syntax
      libs = libs.gsub(/\A-L/, "/libpath:")
      libs = libs.gsub(/\A-l(\S+)/) {"#{$1}.lib"}
    end
    libs
  end

  def libs_only_l
    libs.split.find_all do |arg|
      if @msvc_syntax
        /\.lib\z/ =~ arg
      else
        /\A-l/ =~ arg
      end
    end.join(" ")
  end

  def version
    declaration("Version")
  end

  private
  def pc
    @path.split(separator).each do |path|
      pc_name = File.join(path, "#{@name}.pc")
      return pc_name if File.exist?(pc_name)
    end
    return nil
  end

  def separator
    File.expand_path(".").index(":") ? ";" : ":"
  end

  def variable(name)
    parse_pc if @variables.nil?
    expand_value(@variables[name])
  end

  def declaration(name)
    parse_pc if @declarations.nil?
    expand_value(@declarations[name])
  end

  IDENTIFIER_RE = /[\w\d_.]+/
  def parse_pc
    @variables = {}
    @declarations = {}
    File.open(pc) do |input|
      input.each_line do |line|
        line = line.gsub(/#.*/, '').strip
        next if line.empty?
        case line
        when /^(#{IDENTIFIER_RE})=/
          @variables[$1] = $POSTMATCH.strip
        when /^(#{IDENTIFIER_RE}):/
          @declarations[$1] = $POSTMATCH.strip
        end
      end
    end
  end

  def parse_requires(requires)
    return [] if requires.nil?
    requires_without_version = requires.gsub(/[<>]?=\s*[\d.]+\s*/, '')
    requires_without_version.split(/[,\s]+/)
  end

  def expand_value(value)
    return nil if value.nil?
    value.gsub(/\$\{(#{IDENTIFIER_RE})\}/) do
      variable($1)
    end
  end

  def guess_path
    pkg_config = with_config("pkg-config", ENV["PKG_CONFIG"] || "pkg-config")
    pkg_config = Pathname.new(pkg_config)
    unless pkg_config.absolute?
      require "dl/import"
      dln = Module.new
      dln.module_eval do
        extend DL::Importable
        dlload RbConfig::CONFIG["LIBRUBY"]
        extern "const char *dln_find_exe(const char *, const char *)"
      end
      pkg_config = dln.dln_find_exe(pkg_config.to_s, nil)
      return "/usr/local/lib/pkgconfig:/usr/lib/pkgconfig" if pkg_config.nil?
      pkg_config = Pathname.new(pkg_config)
    end
    (pkg_config.parent.parent + "lib" + "pkgconfig").to_s
  end
end

module PKGConfig
  module_function
  def exist?(pkg)
    PackageConfig.new(pkg).exist?
  end

  def libs(pkg)
    PackageConfig.new(pkg).libs
  end

  def libs_only_l(pkg)
    PackageConfig.new(pkg).libs_only_l
  end

  def cflags(pkg)
    PackageConfig.new(pkg).cflags
  end

  def modversion(pkg)
    PackageConfig.new(pkg).version
  end

  def check_version?(pkg, major = 0, minor = 0, micro = 0)
    return false unless exist?(pkg)
    ver = modversion(pkg).split(".").collect{|item| item.to_i}
    (0..2).each {|i| ver[i] = 0 unless ver[i]}

    (ver[0] > major ||
     (ver[0] == major && ver[1] > minor) ||
     (ver[0] == major && ver[1] == minor &&
      ver[2] >= micro))
  end

  def have_package(pkg, major = nil, minor = 0, micro = 0)
    if major.nil?
      STDOUT.print("checking for #{pkg}... ")
    else
      STDOUT.print("checking for #{pkg} version (>= #{major}.#{minor}.#{micro})... ")
    end
    major ||= 0
    STDOUT.flush
    if check_version?(pkg, major, minor, micro)
      STDOUT.print "yes\n"
      libraries = libs_only_l(pkg)
      dldflags = libs(pkg)
      dldflags = (Shellwords.shellwords(dldflags) -
                  Shellwords.shellwords(libraries))
      dldflags = dldflags.map {|s| /\s/ =~ s ? "\"#{s}\"" : s }.join(' ')
      $libs   += ' ' + libraries
      if /mswin32/ =~ RUBY_PLATFORM
	$DLDFLAGS += ' ' + dldflags
      else
	$LDFLAGS += ' ' + dldflags
      end
      $CFLAGS += ' ' + cflags(pkg)
      true
    else
      STDOUT.print "no\n"
      false
    end
  end
end
