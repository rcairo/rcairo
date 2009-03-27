# Copyright 2008-2009 Kouhei Sutou <kou@cozmixng.org>
# This file is made available under the same terms as Ruby.

require "rbconfig"

require 'mkmf'
require 'shellwords'
require 'English'
require 'pathname'

class PackageConfig
  attr_accessor :msvc_syntax
  def initialize(name, path=nil, msvc_syntax=false)
    @name = name
    @path = path || ENV["PKG_CONFIG_PATH"]
    @path = [@path, guess_default_path].compact.join(separator)
    @msvc_syntax = msvc_syntax
    @variables = @declarations = nil
    override_variables = with_config("override-variables", "")
    @override_variables = parse_override_variables(override_variables)
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
    path_flags, other_flags = collect_cflags
    (other_flags + path_flags).join(" ")
  end

  def cflags_only_I
    collect_cflags[0].join(" ")
  end

  def libs
    path_flags, other_flags = collect_libs
    (other_flags + path_flags).join(" ")
  end

  def libs_only_l
    collect_libs[1].find_all do |arg|
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

  def variable(name)
    parse_pc if @variables.nil?
    expand_value(@override_variables[name] || @variables[name])
  end

  def declaration(name)
    parse_pc if @declarations.nil?
    expand_value(@declarations[name])
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

  def collect_cflags
    all_cflags = (requires_private + requires.reverse).collect do |package|
      self.class.new(package, @path, @msvc_syntax).cflags
    end
    all_cflags = [declaration("Cflags")] + all_cflags
    all_cflags = all_cflags.join(" ").gsub(/-I /, '-I').split.uniq
    path_flags, other_flags = all_cflags.partition {|flag| /\A-I/ =~ flag}
    path_flags = path_flags.reject do |flag|
      flag == "-I/usr/include"
    end
    if @msvc_syntax
      path_flags = path_flags.collect do |flag|
        flag.gsub(/\A-I/, "/I")
      end
    end
    [path_flags, other_flags]
  end

  def collect_libs
    all_libs = requires.collect do |package|
      self.class.new(package, @path, @msvc_syntax).libs
    end
    all_libs = [declaration("Libs")] + all_libs
    all_libs = all_libs.join(" ").gsub(/-([Ll]) /, '\1').split.uniq
    path_flags, other_flags = all_libs.partition {|flag| /\A-L/ =~ flag}
    path_flags = path_flags.reject do |flag|
      /\A-L\/usr\/lib(?:64)?\z/ =~ flag
    end
    if @msvc_syntax
      path_flags = path_flags.collect do |flag|
        flag.gsub(/\A-L/, "/libpath:")
      end
      other_flags = other_flags.collect do |flag|
        if /\A-l/ =~ flag
          "#{$POSTMATCH}.lib"
        else
          flag
        end
      end
    end
    [path_flags, other_flags]
  end

  IDENTIFIER_RE = /[\w\d_.]+/
  def parse_pc
    raise ".pc for #{@name} doesn't exist." unless exist?
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

  def parse_override_variables(override_variables)
    variables = {}
    override_variables.split(",").each do |variable|
      name, value = variable.split("=", 2)
      variables[name] = value
    end
    variables
  end

  def expand_value(value)
    return nil if value.nil?
    value.gsub(/\$\{(#{IDENTIFIER_RE})\}/) do
      variable($1)
    end
  end

  def search_pkg_config_from_path(pkg_config)
    (ENV["PATH"] || "").split(separator).each do |path|
      try_pkg_config = Pathname(path) + pkg_config
      return try_pkg_config if try_pkg_config.exist?
    end
    nil
  end

  def search_pkg_config_by_dln_find_exe(pkg_config)
    begin
      require "dl/import"
    rescue LoadError
      return nil
    end
    dln = Module.new
    dln.module_eval do
      if DL.const_defined?(:Importer)
        extend DL::Importer
      else
        extend DL::Importable
      end
      begin
        dlload RbConfig::CONFIG["LIBRUBY"]
      rescue RuntimeError
        return nil if $!.message == "unknown error"
        return nil if /: image not found\z/ =~ $!.message
        raise
      rescue DL::DLError
        return nil
      end
      extern "const char *dln_find_exe(const char *, const char *)"
    end
    dln.dln_find_exe(pkg_config.to_s, ".")
  end

  def guess_default_path
    default_path = ["/usr/local/lib64/pkgconfig",
                    "/usr/local/lib/pkgconfig",
                    "/usr/local/libdata/pkgconfig",
                    "/opt/local/lib/pkgconfig",
                    "/usr/lib64/pkgconfig",
                    "/usr/lib/pkgconfig",
                    "/usr/X11/lib/pkgconfig/",
                    "/usr/share/pkgconfig"].join(separator)
    libdir = ENV["PKG_CONFIG_LIBDIR"]
    default_path = [libdir, default_path].join(separator) if libdir

    pkg_config = with_config("pkg-config", ENV["PKG_CONFIG"] || "pkg-config")
    pkg_config = Pathname.new(pkg_config)
    unless pkg_config.absolute?
      found_pkg_config = search_pkg_config_from_path(pkg_config)
      pkg_config = found_pkg_config if found_pkg_config
    end
    unless pkg_config.absolute?
      found_pkg_config = search_pkg_config_by_dln_find_exe(pkg_config)
      pkg_config = found_pkg_config if found_pkg_config
    end

    return default_path unless pkg_config.absolute?
    [(pkg_config.parent.parent + "lib" + "pkgconfig").to_s,
     (pkg_config.parent.parent + "libdata" + "pkgconfig").to_s,
     default_path].join(separator)
  end
end

module PKGConfig
  module_function
  def msvc?
    /mswin32/.match(RUBY_PLATFORM) and /^cl\b/.match(Config::CONFIG['CC'])
  end

  def package_config(package)
    PackageConfig.new(package, nil, msvc?)
  end

  def exist?(pkg)
    package_config(pkg).exist?
  end

  def libs(pkg)
    package_config(pkg).libs
  end

  def libs_only_l(pkg)
    package_config(pkg).libs_only_l
  end

  def cflags(pkg)
    package_config(pkg).cflags
  end

  def cflags_only_I(pkg)
    package_config(pkg).cflags_only_I
  end

  def modversion(pkg)
    package_config(pkg).version
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
