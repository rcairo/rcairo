#!/usr/bin/env ruby

require 'mkmf'
$CFLAGS << " -g -Wall `pkg-config --cflags cairo`"
$LDFLAGS << " `pkg-config --libs cairo`"
create_makefile("cairo")
