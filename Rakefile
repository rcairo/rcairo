# -*- ruby -*-

require 'English'

require 'find'
require 'fileutils'
require 'rubygems'
require 'hoe'

base_dir = File.join(File.dirname(__FILE__))
truncate_base_dir = Proc.new do |x|
  x.gsub(/^#{Regexp.escape(base_dir + File::SEPARATOR)}/, '')
end

$LOAD_PATH.unshift(File.join(base_dir, 'src'))
$LOAD_PATH.unshift(File.join('src', 'lib'))
require 'cairo'

manifest = File.join(base_dir, "Manifest.txt")
manifest_contents = []
base_dir_included_components = %w(AUTHORS COPYING ChangeLog GPL
                                  NEWS README Rakefile
                                  extconf.rb pkg-config.rb)
excluded_components = %w(.cvsignore .gdb_history CVS depend Makefile)
excluded_suffixes = %w(.png .ps .pdf .o .so .txt)
Find.find(base_dir) do |target|
  target = truncate_base_dir[target]
  components = target.split(File::SEPARATOR)
  if components.size == 1 and !File.directory?(target)
    next unless base_dir_included_components.include?(components[0])
  end
  Find.prune if (excluded_components - components) != excluded_components
  next if excluded_suffixes.include?(File.extname(target))
  manifest_contents << target if File.file?(target)
end

File.open(manifest, "w") do |f|
  f.puts manifest_contents.sort.join("\n")
end
at_exit do
  FileUtils.rm_f(manifest)
end

project = Hoe.new('cairo', Cairo.bindings_version) do |project|
  project.rubyforge_name = 'cairo'
  authors = File.join(base_dir, "AUTHORS")
  project.author = File.readlines(authors).collect do |line|
    if /\s*<[^<>]*>$/ =~ line
      $PREMATCH
    else
      nil
    end
  end.compact
  project.email = ['cairo@cairographics.org']
  project.summary = 'Ruby bindings for cairo'
  project.url = 'http://cairographics.org/rcairo'
  project.test_globs = []
  project.spec_extras = {
    :extensions => ['extconf.rb'],
    :require_paths => ['src/lib', 'src'],
    :has_rdoc => false,
  }
  news = File.join(base_dir, "NEWS")
  project.changes = project.paragraphs_of(news, 0..1).join("\n\n")
  project.description = "Ruby bindings for cairo"
end

project.spec.dependencies.delete_if {|dependency| dependency.name == "hoe"}

# fix Hoe's incorrect guess.
project.spec.executables.clear
project.lib_files = project.spec.files.grep(%r|^src/lib/|)

# fix Hoe's install and uninstall task.
task(:install).instance_variable_get("@actions").clear
task(:uninstall).instance_variable_get("@actions").clear

task :install do
  [
   [project.lib_files, "lib", Hoe::RUBYLIB, 0444],
   [project.bin_files, "bin", File.join(Hoe::PREFIX, 'bin'), 0555]
  ].each do |files, prefix, dest, mode|
    FileUtils.mkdir_p dest unless test ?d, dest
    files.each do |file|
      base = File.dirname(file.sub(/^#{prefix}#{File::SEPARATOR}/, ''))
      _dest = File.join(dest, base)
      FileUtils.mkdir_p _dest unless test ?d, _dest
      install file, _dest, :mode => mode
    end
  end
end

desc 'Uninstall the package.'
task :uninstall do
  Dir.chdir Hoe::RUBYLIB do
    rm_f project.lib_files.collect {|f| f.sub(/^lib#{File::SEPARATOR}/, '')}
  end
  Dir.chdir File.join(Hoe::PREFIX, 'bin') do
    rm_f project.bin_files.collect {|f| f.sub(/^bin#{File::SEPARATOR}/, '')}
  end
end
