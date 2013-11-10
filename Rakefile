# -*- ruby -*-
require "pathname"
require "mkmf"
require "yaml"

########################################
# Variables

CC      = ENV["CC"]      || "gcc"
CFLAGS  = ENV["CFLAGS"]  || "-Wall "
LDFLAGS = ENV["LDFLAGS"] || ""
LIBS    = ENV["LIBS"]    || ""

rakefiledir  = Pathname.new(__FILE__).expand_path.dirname
sourcedir    = rakefiledir.join("src").relative_path_from(Pathname.new(Rake.original_dir)).to_s
sourcesfiles = Dir["src/**/*.{c,h}"]
objectfiles  = sourcesfiles.select{|path| File.extname(path) == ".c"}.map{|path| File.join("objects", File.basename(path.sub(/\.c$/, ".o")))}
starttime    = Time.now

########################################
# Helper methods

def checkpkg(pkgname, required = true)
  print "Checking for package #{pkgname}... "

  if ary = pkg_config(pkgname)
    puts green("found")

    CFLAGS  << ary[0]
    LDFLAGS << ary[1]
    LIBS    << ary[2]

    ary
  else
    puts red("Not found")
    raise("Required package not found: #{pkgname}") if required

    nil
  end
end

def green(str)
  "\e[32;1m#{str}\e[0m"
end

def red(str)
  "\e[31;1m#{str}\e[0m"
end

def bold(str)
  "\e[1m#{str}\e[0m"
end

########################################
# Task definitions

# We want to work (compile) below the current directory, not
# somewhere in the source tree
Dir.chdir(Rake.original_dir)

rule %r{objects/.*\.o$} => ["#{sourcedir}/%n.c"] do |t|
  mkdir "objects" unless File.directory?("objects")

  sh "#{CC} -c #{CFLAGS} #{t.source} -o #{t.name}"
end

file "tilepass" => objectfiles do |t|
  sh "#{CC} #{LDFLAGS} #{t.prerequisites.join(' ')} -o #{t.name} #{LIBS}"
end

file "buildconfig.yml" do
  checkpkg "gtk+-3.0"

  File.open("buildconfig.yml", "w") do |f|
    hsh = {"cflags" => CFLAGS, "ldflags" => LDFLAGS, "libs" => LIBS}
    YAML.dump(hsh, f)
  end
end

task :configure => "buildconfig.yml" do
  hsh = YAML.load_file("buildconfig.yml")

  CFLAGS.replace(hsh["cflags"])
  LDFLAGS.replace(hsh["ldflags"])
  LIBS.replace(hsh["libs"])

  puts
  puts bold("Build flags:")
  puts "CFLAGS:  #{CFLAGS}"
  puts "LDFLAGS: #{LDFLAGS}"
  puts "LIBS:    #{LIBS}"
  puts
end

task :compile => [:configure, "tilepass"]

task :default => :compile do
  puts green("Build complete. Time taken was #{(Time.now - starttime).round(2)} seconds.")
end
