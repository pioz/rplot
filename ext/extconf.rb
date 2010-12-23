ENV['RC_ARCHS'] = '' if RUBY_PLATFORM =~ /darwin/

require 'mkmf'

LIBDIR      = Config::CONFIG['libdir']
INCLUDEDIR  = Config::CONFIG['includedir']

HEADER_DIRS = [
  # First search /opt/local for macports
  '/opt/local/include',
  # Then search /usr/local for people that installed from source
  '/usr/local/include',
  # Check the ruby install locations
  INCLUDEDIR,
  # Finally fall back to /usr
  '/usr/include',
]

LIB_DIRS = [
  # First search /opt/local for macports
  '/opt/local/lib',
  # Then search /usr/local for people that installed from source
  '/usr/local/lib',
  # Check the ruby install locations
  LIBDIR,
  # Finally fall back to /usr
  '/usr/lib',
]

dir_config('rplot', HEADER_DIRS, LIB_DIRS)

unless find_header('plot.h')
  abort "libplot is missing. Please install libplot (apt-get install libplot-dev)"
end

unless find_library('plot', 'pl_newpl')
  abort "libplot is missing. Please install libplot (apt-get install libplot-dev)"
end

create_makefile('rplot/rplot')

