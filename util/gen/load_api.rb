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
  file.strip!

  # we used to just split on semicolon.
  # but typedef struct { a; } b; needs to slurp as one line.
  # now we have an ugly re.
  file.scan(/\S+[^\}\{]*?(?:\{.*?\})?[^\}\{]*?;/m) { |decl|
    decl.gsub!(/\n/, " ")
    decl.gsub!(/\s+/, " ")
    decl.gsub!(/;\s*$/, '')
    #puts "-->decl<-- #{decl}"
    case decl
    when /^(.+?) (\w+) \((.+?)\)$/
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
    when /^typedef enum .*?\{(.*?)\} (\w+)$/
      content, type = $1, $2
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


