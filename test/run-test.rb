#!/usr/bin/env ruby

require 'test/unit'

Dir.glob("test/**/test_*.rb") do |file|
  require file.sub(/\.rb$/, '')
end
