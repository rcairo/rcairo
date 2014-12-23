# -*- coding: utf-8; mode: ruby -*-

require "English"

require "find"
require "fileutils"
require "open-uri"
require "rubygems"
require "rubygems/package_task"
require "yard"
require "bundler/gem_helper"
require "rake/extensiontask"
require "packnga"

base_dir = File.join(File.dirname(__FILE__))

cairo_ext_dir = File.join(base_dir, "ext", "cairo")
cairo_lib_dir = File.join(base_dir, "lib")
$LOAD_PATH.unshift(cairo_ext_dir)
$LOAD_PATH.unshift(cairo_lib_dir)
ENV["RUBYLIB"] = "#{cairo_lib_dir}:#{cairo_ext_dir}:#{ENV['RUBYLIB']}"

helper = Bundler::GemHelper.new(base_dir)
helper.install
spec = helper.gemspec

Gem::PackageTask.new(spec) do |pkg|
  pkg.need_tar_gz = true
end

Packnga::DocumentTask.new(spec) do |task|
  task.original_language = "en"
  task.translate_languages = ["ja"]
end

Packnga::ReleaseTask.new(spec) do |task|
end

module RCairoBuild
  class << self
    def for_64bit?
      ENV["RCAIRO_WINDOWS_64"] == "yes"
    end
  end
end

binary_dir = File.join("vendor", "local")
Rake::ExtensionTask.new("cairo", spec) do |ext|
  if RCairoBuild.for_64bit?
    ext.cross_platform = ["x64-mingw32"]
  else
    ext.cross_platform = ["x86-mingw32"]
  end
  ext.cross_compile = true
  ext.cross_compiling do |_spec|
    if /mingw|mswin/ =~ _spec.platform.to_s
      binary_files = []
      Find.find(binary_dir) do |name|
        next unless File.file?(name)
        next if /\.zip\z/i =~ name
        binary_files << name
      end
      _spec.files += binary_files

      stage_path = "#{ext.tmp_dir}/#{_spec.platform}/stage"
      binary_files.each do |binary_file|
        stage_binary_file = "#{stage_path}/#{binary_file}"
        stage_binary_dir = File.dirname(stage_binary_file)
        directory stage_binary_dir
        file stage_binary_file => [stage_binary_dir, binary_file] do
          cp(binary_file, stage_binary_file)
        end
      end
    end
  end
end

class Package < Struct.new(:name,
                           :label,
                           :version,
                           :compression_method,
                           :download_site,
                           :download_base_url,
                           :windows)
  def initialize(parameters)
    super()
    parameters.each do |key, value|
      __send__("#{key}=", value)
    end
  end

  def label
    super || name
  end

  def base_name
    "#{name}-#{version}"
  end

  def compression_method
    super || "xz"
  end

  def archive_path
    "#{base_name}.tar.#{compression_method}"
  end

  def archive_url
    "#{download_base_url}/#{archive_path}"
  end

  def download_base_url
    super || download_site_base_url
  end

  def download_site_base_url
    case download_site
    when :cairo
      base_url = "http://cairographics.org/releases"
    when :gnome
      base_url = "http://ftp.gnome.org/pub/gnome/sources"
      release_series = version.gsub(/\A(\d+\.\d+).+\z/, '\1')
      base_url << "/#{name}/#{release_series}"
    else
      base_url = nil
    end
    base_url
  end

  def windows
    Windows.new(super || {})
  end

  class Windows < Struct.new(:builder,
                             :build_host,
                             :configure_args,
                             :built_file,
                             :patches,
                             :need_autoreconf)
    def initialize(parameters)
      super()
      parameters.each do |key, value|
        __send__("#{key}=", value)
      end
    end

    def build_host
      if RCairoBuild.for_64bit?
        "x86_64-w64-mingw32"
      else
        "i686-w64-mingw32"
      end
    end

    def configure_args
      super || []
    end

    def patches
      super || []
    end

    def need_autoreconf?
      need_autoreconf
    end
  end
end

class WindowsTask
  include Rake::DSL

  def initialize(spec, base_dir=".")
    @spec = spec
    @base_dir = Pathname.new(base_dir).expand_path
    yield(self)
  end

  def define
    define_download_task
  end

  def packages=(packages)
    @packages = packages.collect do |parameters|
      Package.new(parameters)
    end
  end

  private
  def define_download_task
    define_gcc_task
    define_source_download_task
    define_build_task
  end

  def define_gcc_task
    namespace :windows do
      namespace :gcc do
        namespace :dll do
          binary_path = install_dir + "bin"
          directory binary_path.to_s
          desc "Bundle GCC related DLLs"
          task :bundle => binary_path do
            dll_names = [
              "libstdc++-6.dll",
              "libwinpthread-1.dll",
              "libgcc_s_sjlj-1.dll",
              "libgcc_s_seh-1.dll",
            ]
            dll_names.each do |dll_name|
              destination_path = binary_path + dll_name
              dll_path = absolete_gcc_dll_path(dll_name)
              unless File.exist?(dll_path)
                puts("#{dll_name} doesn't exist.")
                next
              end
              cp(dll_path, destination_path)
              chmod(0755, destination_path)
            end
          end
        end
      end
    end
  end

  def absolete_gcc_dll_path(dll_name)
    build_host = @packages.first.windows.build_host
    `#{build_host}-gcc -print-file-name=#{dll_name}`.strip
  end

  def define_source_download_task
    namespace :source do
      tasks = []
      @packages.each do |package|
        namespace package.name do
          archive_path = downloaded_archive_path(package)
          file archive_path.to_s do
            mkdir_p(archive_path.dirname.to_s)
            download(package, archive_path)
          end

          desc "Download #{package.name} source"
          task :download => archive_path.to_s
          tasks << join_task_name(Rake.application.current_scope, "download")
        end
      end
      desc "Download sources"
      task :download => tasks
    end
  end

  def download(package, archive_path)
    rake_output_message "Downloading... #{package.archive_url}"
    open(package.archive_url) do |downloaded_archive|
      begin
        archive_path.open("wb") do |archive_file|
          buffer = ""
          while downloaded_archive.read(4096, buffer)
            archive_file.print(buffer)
          end
        end
      rescue Exception
        rm_rf(archive_path.to_s)
        raise
      end
    end
  end

  def define_build_task
    namespace :windows do
      tasks = []
      @packages.each do |package|
        namespace package.name do
          built_file = install_dir + package.windows.built_file
          file built_file.to_s do
            Rake::Task["source:#{package.name}:download"].invoke
            build(package)
          end

          desc "Build #{package.label} package"
          task :build => built_file.to_s
          tasks << join_task_name(Rake.application.current_scope, "build")
        end
      end
      desc "Build packages"
      task :build => ["windows:gcc:dll:bundle"] + tasks
    end
  end

  def join_task_name(current_scope, task_name)
    if Rake.const_defined?(:Scope)
      current_scope.path_with_task_name(task_name)
    else
      (current_scope + [task_name]).join(":")
    end
  end

  def build(package)
    ENV["PATH"] = ["#{install_dir}/bin", ENV["PATH"]].join(File::PATH_SEPARATOR)
    ENV["PKG_CONFIG_LIBDIR"] = "#{install_dir}/lib/pkgconfig"
    ENV["PKG_CONFIG_PATH"] = [
      ruby_glib2_pkg_config_path,
    ].join(":")

    package_build_dir = build_dir + package.name
    rm_rf(package_build_dir.to_s)
    mkdir_p(package_build_dir.to_s)

    archive_path = downloaded_archive_path(package).expand_path

    Dir.chdir(package_build_dir.to_s) do
      sh("tar", "xf", archive_path.to_s)
      Dir.chdir(package.base_name.to_s) do
        package.windows.patches.each do |patch|
          sh("patch", "-p1", "--input", (patches_dir + patch).to_s)
        end
        sh("autoreconf", "--install") if package.windows.need_autoreconf?
        custom_builder = package.windows.builder
        if custom_builder
          custom_builder.build(package, install_dir)
        else
          build_with_gnu_build_system(package)
        end
        package_license_dir = license_dir + package.name
        package_license_files = Dir.glob("{README*,AUTHORS,COPYING*}")
        mkdir_p(package_license_dir.to_s)
        cp(package_license_files, package_license_dir.to_s)
      end
    end
  end

  def build_with_gnu_build_system(package)
    configure_args = [
      "CPPFLAGS=#{cppflags(package)}",
      "LDFLAGS=#{ldflags(package)}",
      "--prefix=#{install_dir}",
      "--host=#{package.windows.build_host}",
    ]
    configure_args += package.windows.configure_args
    sh("./configure", *configure_args)
    ENV["GREP_OPTIONS"] = "--text"
    sh("nice", "make", *build_make_args(package))
    sh("nice", "make", "install", *install_make_args(package))
  end

  def cppflags(package)
    include_paths = [
      install_dir + "include",
    ]
    flags = include_paths.collect do |path|
      "-I#{path}"
    end
    flags.join(" ")
  end

  def ldflags(package)
    library_paths = [
      install_dir + "lib",
    ]
    flags = library_paths.collect do |path|
      "-L#{path}"
    end
    flags.join(" ")
  end

  def build_make_args(package)
    args = []
    make_n_jobs = ENV["MAKE_N_JOBS"]
    args << "-j#{make_n_jobs}" if make_n_jobs
    args
  end

  def install_make_args(package)
    []
  end

  def tmp_dir
    @base_dir + "tmp"
  end

  def download_dir
    tmp_dir + "download"
  end

  def build_dir
    tmp_dir + "build"
  end

  def install_dir
    @base_dir + "vendor" + "local"
  end

  def license_dir
    install_dir + "share" + "license"
  end

  def downloaded_archive_path(package)
    download_dir + package.archive_path
  end

  def patches_dir
    @base_dir + "patches"
  end

  def ruby_gnome2_dir
    if RCairoBuild.for_64bit?
      @base_dir.parent + "ruby-gnome2.win64"
    else
      @base_dir.parent + "ruby-gnome2.win32"
    end
  end

  def ruby_glib2_pkg_config_path
    ruby_gnome2_dir + "glib2/vendor/local/lib/pkgconfig"
  end
end

class ZlibBuilder
  include Rake::DSL

  def build(package, install_dir)
    sh("make",
       "PREFIX=#{package.windows.build_host}-",
       "-f",
       "win32/Makefile.gcc")
    include_path = install_dir + "include"
    library_path = install_dir + "lib"
    binary_path  = install_dir + "bin"
    sh("make",
       "INCLUDE_PATH=#{include_path}",
       "LIBRARY_PATH=#{library_path}",
       "BINARY_PATH=#{binary_path}",
       "SHARED_MODE=1",
       "-f",
       "win32/Makefile.gcc",
       "install")
  end
end

windows_task = WindowsTask.new(spec) do |task|
  task.packages = [
    {
      :name => "zlib",
      :version => "1.2.8",
      :download_base_url => "http://sourceforge.net/projects/libpng/files/zlib/1.2.8",
      :compression_method => "gz",
      :windows => {
        :builder => ZlibBuilder.new,
        :built_file => "bin/zlib1.dll",
      },
    },
    {
      :name => "libpng",
      :version => "1.6.16",
      :download_base_url => "http://sourceforge.net/projects/libpng/files/libpng16/1.6.16",
      :windows => {
        :built_file => "bin/libpng16-16.dll",
      },
    },
    {
      :name => "freetype",
      :version => "2.5.4",
      :download_base_url => "http://sourceforge.net/projects/freetype/files/freetype2/2.5.4",
      :compression_method => "bz2",
      :windows => {
        :built_file => "bin/libfreetype-6.dll",
      },
    },
    {
      :name => "libxml2",
      :version => "2.9.2",
      :download_base_url => "ftp://xmlsoft.org/libxml2",
      :compression_method => "gz",
      :windows => {
        :built_file => "bin/libxml2-2.dll",
        :configure_args => [
          "--without-python",
        ],
        :patches => [
          "remove-empty-z_dir-ldflags.diff",
        ],
        :need_autoreconf => true,
      },
    },
    {
      :name => "fontconfig",
      :version => "2.11.1",
      :download_base_url => "http://www.freedesktop.org/software/fontconfig/release",
      :compression_method => "bz2",
      :windows => {
        :built_file => "bin/libfontconfig-1.dll",
        :configure_args => [
          "--enable-libxml2",
          "--disable-docs",
        ],
        :patches => [
          "fontconfig-2.11.1-disable-mktemp-s.diff",
        ],
        :need_autoreconf => true,
      },
    },
    {
      :name => "pixman",
      :version => "0.32.6",
      :download_site => :cairo,
      :compression_method => "gz",
      :windows => {
        :built_file => "bin/libpixman-1-0.dll",
      },
    },
    {
      :name => "cairo",
      :version => "1.14.0",
      :download_site => :cairo,
      :windows => {
        :built_file => "bin/libcairo-2.dll",
        :configure_args => [
          "--enable-gobject",
        ],
        :patches => [
          "cairo-1.14-missing-exeext-float-m4.diff"
        ],
        :need_autoreconf => true,
      },
    },
  ]
end
windows_task.define

# for releasing
task :dist do
  sh "./dist.sh", spec.version.to_s
end

# for documentation
langs = [
  ["en", "English"],
  ["ja", "日本語"],
]

rcairo_doc_dir = File.expand_path(File.join(base_dir, "..", "rcairo-doc"))
rcairo_doc_css = File.join(rcairo_doc_dir, "doc.css")
rcairo_doc_title_image = File.join(rcairo_doc_dir, "rcairo-title.png")
doc_dir = "doc"
doc_index = File.join(doc_dir, "index.html")
doc_css = File.join(doc_dir, "doc.css")
doc_title_image = File.join(doc_dir, "rcairo-title.png")
task(doc_index).instance_variable_get("@actions").clear

file doc_dir do
  mkdir_p doc_dir
end

file doc_title_image => [doc_dir, rcairo_doc_title_image] do
  cp rcairo_doc_title_image, doc_title_image
end

file doc_css => [rcairo_doc_css, doc_title_image] do
  cp rcairo_doc_css, doc_css
end

file doc_index => doc_css do
  File.open(doc_index, "w") do |index|
    index << <<-EOH
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <title>rcairo reference manual</title>
    <meta http-equiv="Content-type" content="text/html; charset=utf-8">
  </head>

  <body>
    <h1>rcairo reference manual</h1>

    <ul>
EOH

    langs.each do |lang, native_lang|
      index << <<-EOH
      <li><a href="#{lang}/">#{native_lang}</a></li>
EOH
    end

    index << <<-EOH
    </ui>

    <p><a href="../">Up</a></p>
  </body>
</html>
EOH
  end
end

langs.each do |lang,|
  lang_doc_dir = File.join(doc_dir, lang)
  directory lang_doc_dir
  lang_doc_index = File.join(lang_doc_dir, "index.html")
  file doc_index => lang_doc_index
  file lang_doc_index => [lang_doc_dir] do
    lang_doc_dir = File.join(doc_dir, lang)
    lang_rcairo_doc_dir = File.join(rcairo_doc_dir, lang)
    cp Dir[File.join(lang_rcairo_doc_dir, "*.rd")], lang_doc_dir
    ruby File.join(rcairo_doc_dir, "update-html.rb"), lang_doc_dir
    ruby File.join(rcairo_doc_dir, "update-html.rb"), lang_doc_dir
    rm Dir[File.join(lang_doc_dir, "*.{rd,rdc,rbl}")]
  end
end

file "Makefile" => ["extconf.rb", "ext/cairo/extconf.rb"] do
  ruby("extconf.rb")
end

namespace :make do
  namespace :debug_flags do
    task :reset do
      ENV["MAKE"] ||= "make debugflags="
    end
  end
end

task :cross => "make:debug_flags:reset"

desc "Configure"
task :configure => "Makefile"

desc "Run test"
task :test => :configure do
  ruby("test/run-test.rb")
end

task :default => :test
