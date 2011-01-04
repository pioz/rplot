require 'bundler'
Bundler::GemHelper.install_tasks

require 'rake/rdoctask'
Rake::RDocTask.new do |rdoc|
  rdoc.rdoc_dir = 'rdoc'
  rdoc.rdoc_files.include('README*')
  rdoc.main = 'README.rdoc'
  rdoc.options = ["--exclude=lib/rplot/", "--exclude=ext/"]
end