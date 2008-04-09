#!/usr/bin/env ruby

base_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
src_dir = File.join(base_dir, "src")
lib_dir = File.join(src_dir, "lib")

$LOAD_PATH.unshift(base_dir)
$LOAD_PATH.unshift(src_dir)
$LOAD_PATH.unshift(lib_dir)

require 'test/unit'

Dir.glob("test/**/test_*.rb") do |file|
  require file.sub(/\.rb$/, '')
end
