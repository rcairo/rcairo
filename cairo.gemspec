# -*- mode: ruby; coding: utf-8 -*-

base_dir = File.dirname(__FILE__)
cairo_ext_dir = File.join(base_dir, "ext", "cairo")

guess_rcairo_version = lambda do |cairo_ext_dir|
  version = {}
  File.open(File.join(cairo_ext_dir, "rb_cairo.h"), "r:utf-8") do |rb_cairo_h|
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
  s.homepage = "https://rcairo.github.io/"
  s.licenses = ["Ruby"]
  s.require_paths = ["lib"]
  s.extensions = ["ext/cairo/extconf.rb"]

  s.files = ["AUTHORS", "COPYING", "GPL", "Gemfile", "NEWS", "README.rdoc"]
  s.files += ["Rakefile"]
  s.files += Dir.glob("{lib,samples}/**/*.rb")
  s.files += Dir.glob("ext/**/{*.def,depend,*.rb,*.c,*.h}")
  s.test_files = Dir.glob("test/**/*.rb")
  s.extra_rdoc_files = ["README.rdoc"]

  s.add_runtime_dependency("pkg-config", ">= 1.2.2")
  s.add_runtime_dependency("native-package-installer", ">= 1.0.3")
  s.add_development_dependency("bundler")
  s.add_development_dependency("test-unit")
  s.add_development_dependency("rake-compiler")
  s.add_development_dependency("packnga")
  s.add_development_dependency("poppler", ">= 3.1.1")

  s.metadata["msys2_mingw_dependencies"] = "cairo"
end
