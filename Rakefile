# -*- coding: utf-8; mode: ruby -*-

require "rubygems"
require "bundler/gem_helper"
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

Packnga::DocumentTask.new(spec) do |task|
  task.original_language = "en"
  task.translate_languages = ["ja"]
end

Packnga::ReleaseTask.new(spec) do |task|
end

# for releasing
desc "Release to cairographics.org"
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
    rm Dir[File.join(lang_doc_dir, "*.{rd,rdc,rbl}")]
  end
end

file "Makefile" => ["extconf.rb", "ext/cairo/extconf.rb"] do
  ruby("extconf.rb")
end

desc "Configure"
task :configure => "Makefile"

desc "Run test"
task :test => :configure do
  ruby("test/run-test.rb")
end

task :default => :test
