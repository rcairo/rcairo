#!/usr/bin/env ruby

=begin
extconf.rb for Ruby/GtkCairo extention library
=end

require 'mkmf-gnome2'

PKGConfig.have_package('gtkcairo') or exit 1

# pull in rbcairo.h path.
$CFLAGS += " -I ../../cairo/ext"

create_makefile('gtkcairo')

