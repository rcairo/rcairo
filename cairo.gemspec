# -*- ruby -*-

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
  s.licenses = ["Ruby", "GPL-2.0-or-later"]
  s.require_paths = ["lib"]
  s.extensions = ["ext/cairo/extconf.rb"]
  s.metadata = {
    "bug_tracker_uri" => "https://github.com/rcairo/rcairo/issues",
    "changelog_uri" => "https://github.com/rcairo/rcairo/blob/master/NEWS",
    "documentation_uri" => "https://rcairo.github.io/doc/",
    "mailing_list_uri" => "https://cairographics.org/cgi-bin/mailman/listinfo/cairo",
    "source_code_uri" => "https://github.com/rcairo/rcairo",
  }
  s.required_ruby_version = ">= 2.2.1"

  s.files = ["AUTHORS", "COPYING", "GPL", "Gemfile", "NEWS", "README.rdoc"]
  s.files += ["Rakefile"]
  s.files += Dir.glob("{lib,samples}/**/*.rb")
  s.files += Dir.glob("ext/**/{*.def,depend,*.rb,*.c,*.h}")
  s.test_files = Dir.glob("test/**/*.rb")
  s.extra_rdoc_files = ["README.rdoc"]

  s.add_runtime_dependency("native-package-installer", ">= 1.0.3")
  s.add_runtime_dependency("pkg-config", ">= 1.2.2")
  s.add_runtime_dependency("red-colors")

  s.metadata["msys2_mingw_dependencies"] = "cairo"

  [
    ["alpine_linux", "cairo-dev"],
    ["alt_linux", "bzlib-devel"],
    ["alt_linux", "libXdmcp-devel"],
    ["alt_linux", "libbrotli-devel"],
    ["alt_linux", "libcairo-devel"],
    ["alt_linux", "libexpat-devel"],
    ["alt_linux", "libffi-devel"],
    ["alt_linux", "libpixman-devel"],
    ["arch_linux", "cairo"],
    ["conda", "cairo"],
    ["conda", "expat"],
    ["conda", "xorg-kbproto"],
    ["conda", "xorg-libxau"],
    ["conda", "xorg-libxext"],
    ["conda", "xorg-libxrender"],
    ["conda", "xorg-renderproto"],
    ["conda", "xorg-xextproto"],
    ["conda", "xorg-xproto"],
    ["conda", "zlib"],
    ["debian", "libcairo2-dev"],
    ["gentoo_linux", "x11-libs/cairo"],
    ["homebrew", "cairo"],
    ["macports", "cairo"],
    ["pld_linux", "cairo-devel"],
    ["suse", "cairo-devel"],
  ].each do |platform, package|
    s.requirements << "system: cairo >= 1.2.0: #{platform}: #{package}"
  end
end
