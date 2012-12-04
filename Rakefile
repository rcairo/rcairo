# -*- coding: utf-8; mode: ruby -*-

require 'English'

require 'find'
require 'fileutils'
require 'rubygems'
require 'rubygems/package_task'
require 'yard'
require 'bundler/gem_helper'
require 'rake/extensiontask'
require 'packnga'

base_dir = File.join(File.dirname(__FILE__))

cairo_ext_dir = File.join(base_dir, 'ext', 'cairo')
cairo_lib_dir = File.join(base_dir, 'lib')
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
end

Packnga::ReleaseTask.new(spec) do |task|
end

binary_dir = File.join("vendor", "local")
Rake::ExtensionTask.new("cairo", spec) do |ext|
  ext.cross_compile = true
  ext.cross_compiling do |spec|
    if /mingw|mswin/ =~ spec.platform.to_s
      binary_files = []
      Find.find(binary_dir) do |name|
        next unless File.file?(name)
        next if /\.zip\z/i =~ name
        binary_files << name
      end
      spec.files += binary_files
    end
  end
end

task 'cross' => "download_windows_binaries"

def download_windows_binaries(binary_dir)
  base_url = "http://ftp.gnome.org/pub/gnome/binaries/win32/dependencies/"
  dependencies = [
                  ["cairo", "1.10.2-2"],
                  ["libpng", "1.4.12-1"],
                  ["zlib", "1.2.5-2"],
                  ["expat", "2.1.0-1"],
                  ["fontconfig", "2.8.0-2"],
                  ["freetype", "2.4.10-1"],
                 ]
  dependencies.each do |name, version|
    ["", "-dev"].each do |suffix|
      file_name = "#{name}#{suffix}_#{version}_win32.zip"
      full_file_name = File.join(binary_dir, file_name)
      next if File.exist?(full_file_name)
      open("#{base_url}#{file_name}", "rb") do |input|
        File.open(full_file_name, "wb") do |output|
          output.print(input.read)
        end
      end
      sh("unzip", "-o", full_file_name, "-d", binary_dir)
    end
  end
  Dir.glob("#{binary_dir}/lib/pkgconfig/*.pc") do |pc_path|
    pc = File.read(pc_path)
    pc = pc.gsub(/\Aprefix=.+$/) {"prefix=#{File.expand_path(binary_dir)}"}
    File.open(pc_path, "w") do |pc_file|
      pc_file.print(pc)
    end
  end
end

task "download_windows_binaries" do
  require 'open-uri'
  unless File.exist?(binary_dir)
    mkdir_p(binary_dir)
    download_windows_binaries(binary_dir)
  end
end

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
