#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

require 'mkmf'

$CFLAGS = " -I ../../cairo/ext "
$CFLAGS  += `pkg-config --cflags libsvg-cairo`
$LDFLAGS += `pkg-config --libs   libsvg-cairo`


create_makefile("svgcairo")

