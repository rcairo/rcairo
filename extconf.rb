#!/usr/bin/env ruby

require 'pathname'
require 'mkmf'
require 'rbconfig'
require 'fileutils'

base_dir = Pathname(__FILE__).dirname.expand_path
ext_dir = base_dir + "ext" + "cairo"

ruby = File.join(RbConfig::CONFIG['bindir'],
                 RbConfig::CONFIG['ruby_install_name'] +
                 RbConfig::CONFIG["EXEEXT"])

build_ext_dir = Pathname(".") + "ext" + "cairo"
FileUtils.mkdir_p(build_ext_dir.to_s)
Dir.chdir(build_ext_dir.to_s) do
  system(ruby, (ext_dir + "extconf.rb").to_s, *ARGV) || exit(false)
end

create_makefile("cairo")
FileUtils.mv("Makefile", "Makefile.lib")

File.open("Makefile", "w") do |makefile|
  makefile.puts(<<-EOM)
all:
	(cd ext/cairo && $(MAKE))
	$(MAKE) -f Makefile.lib

install:
	(cd ext/cairo && $(MAKE) install)
	$(MAKE) -f Makefile.lib install

site-install:
	(cd ext/cairo && $(MAKE) site-install)
	$(MAKE) -f Makefile.lib site-install

clean:
	(cd ext/cairo && $(MAKE) clean)
	$(MAKE) -f Makefile.lib clean

distclean:
	(cd ext/cairo && $(MAKE) distclean)
	$(MAKE) -f Makefile.lib distclean
	@rm -f Makefile.lib
EOM
end
