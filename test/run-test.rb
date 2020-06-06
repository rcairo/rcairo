#!/usr/bin/env ruby

source_dir = File.expand_path(File.join(__dir__, ".."))
build_dir = File.expand_path(".")
ext_dir = File.join(build_dir, "ext", "cairo")
lib_dir = File.join(source_dir, "lib")
test_dir = File.join(source_dir, "test")

if system("which make >/dev/null 2>&1")
  Dir.chdir(build_dir) do
    if File.exist?("Makefile")
      system("make > /dev/null") or exit(1)
    end
  end
end

require "test-unit"

$LOAD_PATH.unshift(ext_dir)
$LOAD_PATH.unshift(lib_dir)

require_relative "helper"

exit(Test::Unit::AutoRunner.run(true, test_dir))
