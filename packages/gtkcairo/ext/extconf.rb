=begin
extconf.rb for Ruby/GtkCairo extention library
=end

#$LOAD_PATH.unshift File.expand_path(File.dirname(__FILE__) + '/../glib/src/lib')require 'mkmf-gnome2'
$LOAD_PATH.unshift File.expand_path('/home/martine/projects/cvs/ruby-gnome2/glib/src/lib')

require 'mkmf-gnome2'

PKGConfig.have_package('gtkcairo') or exit 1

# pull in rbcairo.h path.
$CFLAGS += " -I ../src"

create_makefile('gtkcairo')

