#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

require 'mkmf'

$CFLAGS  = "-Wall "+`pkg-config --cflags cairo`
$LDFLAGS = `pkg-config --libs cairo`
create_makefile("cairo")

