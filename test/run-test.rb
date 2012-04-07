#!/usr/bin/env ruby

base_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
ext_dir = File.join(base_dir, "ext", "cairo")
lib_dir = File.join(base_dir, "lib")
test_dir = File.join(base_dir, "test")

if system("which make >/dev/null 2>&1")
  Dir.chdir(base_dir) do
    system("make > /dev/null") or exit(1)
  end
end

require 'rubygems'
require 'bundler/setup'
require 'test-unit'

$LOAD_PATH.unshift(base_dir)
$LOAD_PATH.unshift(ext_dir)
$LOAD_PATH.unshift(lib_dir)

$LOAD_PATH.unshift(test_dir)
require 'cairo-test-utils'

Dir.glob("test/**/test_*.rb") do |file|
  require file.sub(/\.rb$/, '')
end

exit Test::Unit::AutoRunner.run(false)
