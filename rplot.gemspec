# -*- encoding: utf-8 -*-
$:.push File.expand_path('../lib', __FILE__)
require 'rplot/version'

Gem::Specification.new do |s|
  s.name          = 'rplot'
  s.version       = Rplot::VERSION
  s.platform      = Gem::Platform::RUBY
  s.authors       = ['Enrico Pilotto']
  s.email         = ['enrico@megiston.it']
  s.homepage      = 'https://github.com/pioz/rplot'
  s.summary       = %q{C extension for Ruby of GNU libplot}
  s.description   = %q{GNU libplot is a free function library for drawing two-dimensional vector graphics. It can produce smooth, double-buffered animations for the X Window System, and can export files in many graphics file formats. It is `device-independent' in the sense that its API (application programming interface) is to a large extent independent of the display type or output format. Rplot is a C extension for Ruby of GNU libplot.}
  s.license       = 'GPL-3'
  s.extensions    = ['ext/extconf.rb']
  s.requirements  = ['GNU libplot dev (plotutils package) version >= 2.6 - Debian package name: libplot-dev - Mac port package name: plotutils']
  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ['lib', 'ext']
end
