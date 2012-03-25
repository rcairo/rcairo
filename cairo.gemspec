# -*- mode: ruby; coding: utf-8 -*-

base_dir = File.dirname(__FILE__)
cairo_ext_dir = File.join(base_dir, "ext", "cairo")

guess_rcairo_version = lambda do |cairo_ext_dir|
  version = {}
  File.open(File.join(cairo_ext_dir, "rb_cairo.h")) do |rb_cairo_h|
    rb_cairo_h.each_line do |line|
      case line
      when /\A#define RB_CAIRO_VERSION_([A-Z]+) (\d+)/
        version[$1.downcase] = $2
      end
    end
  end
  [version["major"], version["minor"], version["micro"]].join(".")
end

Gem::Specification.new do |s|
  s.name = "cairo"
  s.version = guess_rcairo_version.call(cairo_ext_dir)
  s.authors = ["Kouhei Sutou"]
  s.email = ["kou@cozmixng.org"]
  s.summary = "Ruby bindings for cairo"
  s.description = "Ruby bindings for cairo"
  s.homepage = "http://cairographics.org/rcairo"
  s.licenses = ["Ruby's"]
  s.require_paths = ["lib"]
  s.rubyforge_project = "cairo"
  s.extensions = ["ext/cairo/extconf.rb"]

  s.files = ["AUTHORS", "COPYING", "GPL", "Gemfile", "NEWS", "README.rdoc"]
  s.files += ["Rakefile"]
  s.files += Dir.glob("{lib,samples}/**/*.rb")
  s.files += Dir.glob("ext/**/{*.def,depend,*.rb,*.c,*.h}")
  s.test_files = Dir.glob("test/**/*.rb")
  s.extra_rdoc_files = ["README.rdoc"]

  s.add_runtime_dependency("pkg-config")
  s.add_development_dependency("bundler")
  s.add_development_dependency("test-unit-notify")
  s.add_development_dependency("rake-compiler")
  s.add_development_dependency("packnga")
end
