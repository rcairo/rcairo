#!/usr/bin/env ruby
# vim: set ts=2 sw=2 et :

require 'load_api'

funcs, structs, enums = load_api(ARGV[0])

funcs.each { |func, ret, args|
  if args
    argstr = args.map { |type, name| "#{name} : #{type}" }.join(', ')
  else
    argstr = ""
  end
  retstr = " : #{ret}" if ret
  puts "#{func} (#{argstr})#{retstr}"
}
puts
structs.each { |type|
  puts "#{type}"
}
puts
enums.each { |type, vals|
  puts "#{type}:"
  vals.each { |v|
    puts "  #{v}"
  }
}
puts

