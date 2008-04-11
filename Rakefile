# -*- coding: utf-8 -*-
# -*- ruby -*-

require 'English'

require 'find'
require 'fileutils'
require 'rubygems'
require 'hoe'

base_dir = File.join(File.dirname(__FILE__))
truncate_base_dir = Proc.new do |x|
  x.gsub(/^#{Regexp.escape(base_dir + File::SEPARATOR)}/, '')
end

cairo_ext_dir = File.join(base_dir, 'src')
cairo_lib_dir = File.join(cairo_ext_dir, 'lib')
$LOAD_PATH.unshift(cairo_ext_dir)
$LOAD_PATH.unshift(cairo_lib_dir)
ENV["RUBYLIB"] = "#{cairo_lib_dir}:#{cairo_ext_dir}:#{ENV['RUBYLIB']}"
require 'cairo'

manifest = File.join(base_dir, "Manifest.txt")
manifest_contents = []
base_dir_included_components = %w(AUTHORS COPYING ChangeLog GPL
                                  NEWS README Rakefile
                                  extconf.rb pkg-config.rb)
excluded_components = %w(.cvsignore .gdb_history CVS depend Makefile pkg)
excluded_suffixes = %w(.png .ps .pdf .o .so .txt .~)
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

ENV["VERSION"] ||= Cairo.bindings_version
version = ENV["VERSION"]
project = Hoe.new('cairo', version) do |project|
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
    :extensions => ['extconf.rb'],
    :require_paths => ['src/lib', 'src'],
    :has_rdoc => false,
  }
  news = File.join(base_dir, "NEWS")
  project.changes = File.read(news).gsub(/\n+^Release(?m:.*)/, '')
  project.description = "Ruby bindings for cairo"
  project.need_tar = false
  project.remote_rdoc_dir = "doc"
end

project.spec.dependencies.delete_if {|dependency| dependency.name == "hoe"}

# fix Hoe's incorrect guess.
project.spec.executables.clear
project.lib_files = project.spec.files.grep(%r|^src/lib/|)

# fix Hoe's install and uninstall task.
task(:install).instance_variable_get("@actions").clear
task(:uninstall).instance_variable_get("@actions").clear

task :install do
  [
   [project.lib_files, "lib", Hoe::RUBYLIB, 0444],
   [project.bin_files, "bin", File.join(Hoe::PREFIX, 'bin'), 0555]
  ].each do |files, prefix, dest, mode|
    FileUtils.mkdir_p dest unless test ?d, dest
    files.each do |file|
      base = File.dirname(file.sub(/^#{prefix}#{File::SEPARATOR}/, ''))
      _dest = File.join(dest, base)
      FileUtils.mkdir_p _dest unless test ?d, _dest
      install file, _dest, :mode => mode
    end
  end
end

desc 'Uninstall the package.'
task :uninstall do
  Dir.chdir Hoe::RUBYLIB do
    rm_f project.lib_files.collect {|f| f.sub(/^lib#{File::SEPARATOR}/, '')}
  end
  Dir.chdir File.join(Hoe::PREFIX, 'bin') do
    rm_f project.bin_files.collect {|f| f.sub(/^bin#{File::SEPARATOR}/, '')}
  end
end


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

file doc_index => doc_dir do
  mkdir_p doc_dir
end

file doc_title_image => rcairo_doc_title_image do
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
  lang_doc_index = File.join(doc_dir, lang, "index.html")
  task doc_index => lang_doc_index
  file lang_doc_index do
    lang_doc_dir = File.join(doc_dir, lang)
    lang_rcairo_doc_dir = File.join(rcairo_doc_dir, lang)
    mkdir_p lang_doc_dir
    cp Dir[File.join(lang_rcairo_doc_dir, "*.rd")], lang_doc_dir
    ruby File.join(rcairo_doc_dir, "update-html.rb"), lang_doc_dir
    ruby File.join(rcairo_doc_dir, "update-html.rb"), lang_doc_dir
    rm Dir[File.join(lang_doc_dir, "*.{rd,rdc,rbl}")]
  end
end
