# -*- coding: utf-8; mode: ruby -*-

require 'English'

require 'find'
require 'fileutils'
require 'rubygems'
require 'hoe'
require 'rake/extensiontask'

base_dir = File.join(File.dirname(__FILE__))
truncate_base_dir = Proc.new do |x|
  x.gsub(/^#{Regexp.escape(base_dir + File::SEPARATOR)}/, '')
end

cairo_ext_dir = File.join(base_dir, 'ext', 'cairo')
cairo_lib_dir = File.join(base_dir, 'lib')
$LOAD_PATH.unshift(cairo_ext_dir)
$LOAD_PATH.unshift(cairo_lib_dir)
ENV["RUBYLIB"] = "#{cairo_lib_dir}:#{cairo_ext_dir}:#{ENV['RUBYLIB']}"

def guess_rcairo_version
  require 'cairo'
  Cairo.bindings_version
end

manifest = File.join(base_dir, "Manifest.txt")
manifest_contents = []
base_dir_included_components = %w(AUTHORS COPYING ChangeLog GPL
                                  NEWS README.doc Rakefile
                                  extconf.rb pkg-config.rb)
excluded_components = %w(.cvsignore .gdb_history CVS depend Makefile pkg
                         .test-result .gitignore .git vendor)
excluded_suffixes = %w(.png .ps .pdf .o .so .a .txt .~ .log)
Find.find(base_dir) do |target|
  target = truncate_base_dir[target]
  components = target.split(File::SEPARATOR)
  if components.size == 1 and !File.directory?(target)
    next unless base_dir_included_components.include?(components[0])
  end
  Find.prune if (excluded_components - components) != excluded_components
  next if excluded_suffixes.include?(File.extname(target))
  manifest_contents << target if File.file?(target)
end

File.open(manifest, "w") do |f|
  f.puts manifest_contents.sort.join("\n")
end

# For Hoe's no user friendly default behavior. :<
File.open("README.txt", "w") {|file| file << "= Dummy README\n== XXX\n"}
FileUtils.cp("NEWS", "History.txt")
at_exit do
  FileUtils.rm_f("README.txt")
  FileUtils.rm_f("History.txt")
  FileUtils.rm_f(manifest)
end

ENV["VERSION"] ||= guess_rcairo_version
version = ENV["VERSION"]
project = Hoe.spec('cairo') do |project|
  project.version = version
  project.rubyforge_name = 'cairo'
  authors = File.join(base_dir, "AUTHORS")
  project.author = File.readlines(authors).collect do |line|
    if /\s*<[^<>]*>$/ =~ line
      $PREMATCH
    else
      nil
    end
  end.compact
  project.email = ['cairo@cairographics.org']
  project.summary = 'Ruby bindings for cairo'
  project.url = 'http://cairographics.org/rcairo'
  project.test_globs = []
  project.spec_extras = {
    :extensions => ['ext/cairo/extconf.rb'],
    :require_paths => ['lib'],
    :has_rdoc => false,
  }
  project.extra_deps << ['pkg-config', '>= 0']
  platform = ENV["FORCE_PLATFORM"]
  project.spec_extras[:platform] = platform if platform
  news = File.join(base_dir, "NEWS")
  project.changes = File.read(news).gsub(/\n+^Release(?m:.*)/, '')
  project.description = "Ruby bindings for cairo"
  project.need_tar = false
  project.remote_rdoc_dir = "doc"
end

project.spec.dependencies.delete_if {|dependency| dependency.name == "hoe"}

Rake::ExtensionTask.new("cairo", project.spec) do |ext|
  ext.cross_compile = true
  ext.cross_compiling do |spec|
    if /mingw|mswin/ =~ spec.platform.to_s
      cairo_win32_dir = File.join("vendor", "local")
      cairo_files = []
      Find.find(cairo_win32_dir) do |f|
        cairo_files << f
      end
      spec.files += cairo_files
    end
  end
end

# fix Hoe's incorrect guess.
project.spec.executables.clear

task(:release).prerequisites.reject! {|name| name == "clean"}
task(:release_to_rubyforge).prerequisites.reject! {|name| name == "clean"}

# for releasing
task :dist => [:docs] do
  sh "./dist.sh", version
end
task :gem => [:docs]

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
