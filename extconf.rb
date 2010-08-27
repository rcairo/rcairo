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

Dir.chdir(ext_dir.to_s) do
  system(ruby, "extconf.rb", *ARGV)
end

create_makefile("cairo")
FileUtils.mv("Makefile", "Makefile.lib")

File.open("Makefile", "w") do |makefile|
  makefile.puts(<<-EOM)
all:
	$(MAKE) $(MAKEFLAGS) -C ext/cairo
	$(MAKE) $(MAKEFLAGS) -f Makefile.lib

install:
	$(MAKE) $(MAKEFLAGS) -C ext/cairo install
	$(MAKE) $(MAKEFLAGS) -f Makefile.lib install

site-install:
	$(MAKE) $(MAKEFLAGS) -C ext/cairo site-install
	$(MAKE) $(MAKEFLAGS) -f Makefile.lib site-install

clean:
	$(MAKE) $(MAKEFLAGS) -C ext/cairo clean
	$(MAKE) $(MAKEFLAGS) -f Makefile.lib clean

distclean:
	$(MAKE) $(MAKEFLAGS) -C ext/cairo distclean
	$(MAKE) $(MAKEFLAGS) -f Makefile.lib distclean
	@rm -f Makefile.lib
EOM
end
