# -*- encoding: utf-8 -*-
$:.push File.expand_path("../lib", __FILE__)
require "rplot/version"

Gem::Specification.new do |s|
  s.name        = "rplot"
  s.version     = Rplot::VERSION
  s.platform    = Gem::Platform::RUBY
  s.authors     = ["Enrico Pilotto"]
  s.email       = ["enrico@megiston.it"]
  s.homepage    = ""
  s.summary     = %q{Ruby extension for GNU libplot}
  s.description = %q{TODO: Write a gem description}

  s.rubyforge_project = "rplot"

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ["lib"]
end
