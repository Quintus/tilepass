# -*- ruby -*-
require "pathname"
require "mkmf"
require "yaml"

########################################
# Variables

CC       = ENV["CC"]       || "gcc"
CXX      = ENV["CXX"]      || "g++"
CFLAGS   = ENV["CFLAGS"]   || "-Wall -g "
CXXFLAGS = ENV["CXXFLAGS"] || ""
LDFLAGS  = ENV["LDFLAGS"]  || ""
LIBS     = ENV["LIBS"]     || ""

rakefiledir    = Pathname.new(__FILE__).expand_path.dirname
sourcedir      = rakefiledir.join("src").relative_path_from(Pathname.new(Rake.original_dir)).to_s
sourcesfiles   = Dir["src/**/*.cpp"]
cppobjectfiles = sourcesfiles.select{|path| File.extname(path) == ".cpp"}.map{|path| File.join("objects", File.basename(path.sub(/\.cpp$/, ".cppobj")))}
objectfiles    = cppobjectfiles
starttime      = Time.now

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

rule %r{objects/.*\.cobj$} => ["#{sourcedir}/%n.c", "#{sourcedir}/%n.h"] do |t|
  sh "#{CC} -c #{CFLAGS} #{t.source} -o #{t.name}"
end

rule %r{objects/.*\.cppobj} => ["#{sourcedir}/%n.cpp"] do |t|
  sh "#{CXX} -c #{CFLAGS} #{CXXFLAGS} #{t.source} -o #{t.name}"
end

file "tilepass" => objectfiles do |t|
  sh "#{CXX} #{LDFLAGS} #{t.prerequisites.join(' ')} -o #{t.name} #{LIBS}"
end

file "buildconfig.yml" do
  checkpkg "gtkmm-3.0"

  File.open("buildconfig.yml", "w") do |f|
    hsh = {"cflags" => CFLAGS, "cxxflags" => CXXFLAGS, "ldflags" => LDFLAGS, "libs" => LIBS}
    YAML.dump(hsh, f)
  end
end

directory "objects"

task :configure => ["objects", "buildconfig.yml"] do
  hsh = YAML.load_file("buildconfig.yml")

  CFLAGS.replace(hsh["cflags"])
  CXXFLAGS.replace(hsh["cxxflags"])
  LDFLAGS.replace(hsh["ldflags"])
  LIBS.replace(hsh["libs"])

  puts
  puts bold("Build flags:")
  puts "CFLAGS:   #{CFLAGS}"
  puts "CXXFLAGS: #{CXXFLAGS}"
  puts "LDFLAGS:  #{LDFLAGS}"
  puts "LIBS:     #{LIBS}"
  puts
end

def scan_file_for_dependencies(path, dependencies = [])
  path = Pathname.new(path)

  # Change to the file's directory so we resolve #include-s
  # properly.
  Dir.chdir(path.dirname) do
    path.basename.open do |f|
      f.each_line do |line|
        if line =~ /^#\s*include "(.*)"$/
          fullpath = Pathname.new($1).expand_path

          # 0. If we already have this file as a dependency, ignore it
          next if dependencies.include?(fullpath)

          # 1. Add the found file's absolute path to the dependency list
          dependencies << fullpath

          # 2. Read in the file and repeat the process
          scan_file_for_dependencies(fullpath, dependencies)
        end
      end
    end
  end

  dependencies
end

task :scandeps do
  cppobjectfiles.each do |cpppath|
    task = Rake::Task[cpppath]
    deps = []

    task.prerequisites.each do |sourcepath|
      deps.concat(scan_file_for_dependencies(sourcepath))
    end

    task.prerequisites.concat(deps.map(&:to_s))
  end
end

task :compile => [:configure, :scandeps, "tilepass"]

task :default => :compile do
  puts green("Build complete. Time taken was #{(Time.now - starttime).round(2)} seconds.")
end
