#!/usr/bin/env ruby

base_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
test_unit_dir = File.join(base_dir, "test-unit", "lib")
ext_dir = File.join(base_dir, "ext", "cairo")
lib_dir = File.join(base_dir, "lib")
test_dir = File.join(base_dir, "test")

if system("which make > /dev/null")
  system("cd #{base_dir.dump} && make > /dev/null") or exit(1)
end

$LOAD_PATH.unshift(test_unit_dir)

require 'test/unit'

$LOAD_PATH.unshift(base_dir)
$LOAD_PATH.unshift(ext_dir)
$LOAD_PATH.unshift(lib_dir)

$LOAD_PATH.unshift(test_dir)
require 'cairo-test-utils'

Dir.glob("test/**/test_*.rb") do |file|
  require file.sub(/\.rb$/, '')
end

exit Test::Unit::AutoRunner.run(false)
