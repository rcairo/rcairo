#!/usr/bin/env ruby
# vim: set ts=2 sw=2 et :

def load_api(fn)
  funcs = []
  structs = []
  enums = []

  file = File.open(fn).read
  file.gsub!(/\/\*.*?\*\//m, '')
  file.gsub!(/^#.*?\n/, '')
  file.gsub!(/^extern "C" \{\s*/, '')
  file.gsub!(/\}\s*$/, '')
  file.gsub!(/\n\n/, "\n")
  file.gsub!(/^\s*/, "")
  file.split(/;\s*/).each { |decl|
    decl.gsub!(/\n/, " ")
    decl.gsub!(/\s+/, " ")
    case decl
    when /^extern (.+?) (?:__external_linkage) (\w+) \((.+?)\)$/
      ret, func, args = $1, $2, $3.strip
      ret = nil if ret == 'void'
      if args == 'void'
        args = nil
      else
        args = args.split(/\s*,\s*/).map { |arg|
          arg.gsub!(/\s+/, ' ')
          if arg == 'void'
            nil
          elsif arg =~ /^(.+?)\s*(\w+)$/
            [$1, $2]
          else
            raise ArgumentError  # just some error.
          end
        }
      end
      #puts "-->func<-- #{ret} :: #{func} :: #{args.inspect}"
      funcs << [func, ret, args]
    when /^typedef struct (.*?) (\w+)$/
      decl, type = $1, $2
      #puts "-->type<-- #{type}"
      structs << type
    when /^typedef enum (.*?) \{(.*?)\} (\w+)$/
      tag, content, type = $1, $2, $3
      defs = content.split(/,\s*/).map { |value|
        value.gsub!(/^\s*(\w+).*?$/) { $1 }
      }
      #puts "-->type<-- #{type} [#{defs.join(':')}]"
      enums << [type, defs]
    else
      puts "-->err<-- #{decl}"
    end
  }
  [funcs, structs, enums]
end


