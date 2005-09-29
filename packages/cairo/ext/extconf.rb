#!/usr/bin/env ruby
# vim: filetype=ruby:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :

require 'mkmf'
require 'fileutils'

pkg = "cairo"
modname = "cairo"
major, minor, micro = 1, 0, 0

check_version = Proc.new do
  modversion = `#{$PKGCONFIG} --modversion #{pkg}`.chomp
  ver = modversion.split(".").collect{|item| item.to_i}
  (0..2).each {|i| ver[i] ||= 0}
  (ver <=> [major, minor, micro]) >= 0
end

STDOUT.print("checking for #{pkg} version (>= #{major}.#{minor}.#{micro})... ")

if pkg_config(pkg) and check_version.call
  STDOUT.print("yes\n")
  create_makefile(modname)
else
  STDOUT.print("no\n")
  FileUtils.rm_f("Makefile")
end
