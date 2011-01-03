require 'ext/rplot'

class Plotter < Rplot

  def initialize(type, out_path, in_path = nil, err_path = nil)
    super(type, in_path, out_path, err_path)
  end

  def self.params(options = {})
    options.each do |k,v|
      Rplot.param(k.to_s.upcase, v.to_s)
    end
  end

  def self.draw(type, out_path, in_path = nil, err_path = nil)
    plotter = Plotter.new(type, out_path, in_path, err_path)
    plotter.open
    yield(plotter)
    plotter.delete
  end

  def draw
    self.open
    yield(self)
    self.delete
  end

end
