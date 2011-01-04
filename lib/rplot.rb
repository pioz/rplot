require 'ext/rplot'

# This class rappresents a Plotter.
#
# The graphical objects that libplot can draw include paths, circles and
# ellipses, points, markers, and "adjusted labels" (justified text strings). A
# path is a sequence of line segments, circular arcs, elliptic arcs, quadratic
# Bezier curves, and/or cubic Bezier curves. Paths may be open or closed.
# User-specified filling of paths, circles, and ellipses is supported (fill
# rule and fill color, as well as pen color, may be specified). There is
# support for maintaining a Postscript-style stack of graphics contexts, i.e.,
# a stack of drawing attribute sets. Path-related attributes include line
# thickness, line type, cap type, and join type, and text-related attributes
# include font name, font size, and text angle.
#
# The fundamental abstraction provided is that of a Plotter. A Plotter is an
# object with an interface for the drawing of vector graphics which is similar
# to the interface provided by a traditional pen plotter. There are many types
# of Plotter, which differ in the output format they produce. Any number of
# Plotters, of the same or different types, may exist simultaneously in an
# application.
#
# The drawing operations supported by Plotters of different types are
# identical, in agreement with the principle of device independence. So a
# graphics application that is linked with libplot may easily be written so as
# to produce output in any or all of the supported output formats.
#
# The following are the currently supported types of Plotter:
#
# [X Plotters] An X Plotter, when opened, pops up a window on an X Window
#              System display and draws graphics in it. The window will be
#              "spun off" when the Plotter is closed; if it is subsequently
#              reopened, a new window will be popped up. A spun-off window will
#              remain on the screen but will vanish if you type +q+ or click
#              your mouse in it. Future releases may permit X Plotters, when
#              reopened, to reuse an existing window.
# [X Drawable Plotters] An X Drawable Plotter draws graphics in one or two
#                       specified drawables associated with an X Window System
#                       display. A "drawable" is either a window or a pixmap.
# [PNM Plotters] A PNM Plotter produces a single page of output in "portable
#                anymap" format, and directs it to a file or other specified
#                output stream. There are three types of portable anymap: PBM
#                (portable bitmap, for monochrome graphics), PGM (portable
#                graymap), and PPM (portable pixmap, for colored graphics).
#                The output file will be in whichever of these three formats
#                is most appropriate. The file may be viewed or edited with
#                many applications, such as the free image display application
#                xv.
# [GIF Plotters] A GIF Plotter produces a single page of output in a pseudo-GIF
#                format. Unlike true GIF format, the pseudo-GIF format does not
#                use LZW compression: it uses run-length encoding instead. So
#                it does not transgress the Unisys patent that restricts the
#                use of LZW compression. However, the output file may be viewed
#                or edited with any application that understands GIF format,
#                such as xv. The creation of animated pseudo-GIFs is supported.
# [Illustrator Plotters] An Illustrator Plotter produces a single page of
#                        output in the format used by Adobe Illustrator, and
#                        directs it to a file or other specified output stream.
#                        The file may be edited with Adobe Illustrator (version
#                        5, and more recent versions), or other applications.
# [Postscript Plotters] A Postscript Plotter produces Postscript output and
#                       directs it to a file or other specified output stream.
#                       If only a single page of graphics is drawn on the
#                       Plotter then its output is in EPS (encapsulated
#                       Postscript) format, so it may be included in another
#                       document. It may also be edited with the idraw drawing
#                       editor.
# [Fig Plotters] A Fig Plotter produces a single page of output in Fig format
#                and directs it to a file or other specified output stream. The
#                output may be edited with the xfig drawing editor. The xfig
#                editor will export drawings in various other formats for
#                inclusion in documents.
# [PCL Plotters] A PCL Plotter produces output in PCL 5 format and directs it
#                to a file or other specified output stream. PCL 5 is a
#                powerful version of Hewlett--Packard's Printer Control
#                Language, which supports vector graphics. The output may be
#                sent to a PCL 5 device such as a LaserJet printer or high-end
#                inkjet.
# [HP-GL Plotters] An HP-GL Plotter produces output in the Hewlett--Packard
#                  Graphics Language (by default, in HP-GL/2), and directs it
#                  to a file or other specified output stream. The output may
#                  be imported into another application, or sent to a plotter.
# [Tektronix Plotters] A Tektronix Plotter produces output in Tektronix 4014
#                      format and directs it to a file or other specified
#                      output stream. The output may be displayed on any
#                      Tektronix 4014 emulator. Such an emulator is built into
#                      xterm, the X Window System terminal emulation program.
#                      The MS-DOS version of kermit also includes such an
#                      emulator.
# [Metafile Plotters] A Metafile Plotter produces output in GNU graphics
#                     metafile format and directs it to a file or other
#                     specified output stream. This format is an extended
#                     version of the "plot(5)" format found on some other
#                     operating systems.
#
# A distinction among these types of Plotter is that all except X and X
# Drawable Plotters write graphics to a file or other output stream. An X
# Plotter pops up its own windows, and an X Drawable Plotter draws graphics
# in one or two X drawables.
#
# Another distinction is that the first four types of Plotter (X, X Drawable,
# PNM, and GIF) produce bitmap output, while the remaining types produce output
# in a vector graphics format. In bitmap output the structure of the graphical
# objects is lost, but in a vector format it is retained.
#
# An additional distinction is that X, X Drawable, Tektronix and Metafile
# Plotters are real-time. This means that they draw graphics or write to an
# output stream as the drawing operations are invoked on them. The remaining
# types of Plotter are not real-time, since their output streams can only be
# emitted after all functions have been called. For PNM and GIF Plotters, this
# is because the bitmap must be constructed before it is written out. For
# Illustrator and Postscript Plotters, it is because a "bounding box" line must
# be placed at the head of the output file. For a Fig Plotter, it is because
# color definitions must be placed at the head of the output file.
#
# The most important operations supported by any Plotter are +open+ and
# +close+, which open and close it. Graphics may be drawn, and drawing
# attributes set, only within an +open+...+close+ pair or as block passed to
# +draw+ method. The graphics produced within each +open+...+close+ pair
# constitute a _page_. In principle, any Plotter may be opened and closed
# arbitrarily many times. An X Plotter displays each page in a separate
# X window, and Postscript, PCL, and HP-GL Plotters render each page as a
# separate physical page. X Drawable Plotters and Tektronix Plotters manipulate
# a single drawable or display, on which pages are displayed in succession.
# Plotters that do not draw in real time (PNM, GIF, Illustrator, Postscript,
# Fig, PCL, and HP-GL Plotters) may wait until their existence comes to an end
# (i.e., until they are deleted) before outputting their pages of graphics.
#
# In the current release of libplot, Postscript Plotters delay outputting
# graphics in this way, but PCL and HP-GL Plotters output each page of graphics
# individually, i.e., when closepl is invoked. PNM, GIF, Illustrator and Fig
# Plotters are similar, but output only the first page. That is because PNM,
# GIF, Illustrator and Fig formats support only a single page of graphics.
#
# There are several other basic operations which any Plotter supports. The
# "graphics display" drawn in by a Plotter is a square or rectangular region on
# a display device. But when using any Plotter to draw graphics, a user will
# specify the coordinates of graphical objects in device-independent "user
# coordinates", rather than in device coordinates. A Plotter relates the user
# coordinate system to the device coordinate system by performing an affine
# transformation, which must be specified by the user.
#
# Immediately after invoking +open+ to open a Plotter, an application should
# invoke the +space+ operation to initialize this transformation. This
# invocation specifies the rectangular region (in user coordinates) that will
# be mapped by the Plotter to the graphics display. The affine transformation
# may be updated at any later time by invoking +space+ again, or by invoking
# +concat+. The +concat+ method will _concatenate_ (i.e., compose) the current
# affine transformation with any specified affine transformation. This sort of
# concatenation is a capability familiar from, e.g., Postscript.
#
# Each Plotter maintains a Postscript-style stack of graphics contexts. This
# makes possible the rapid, efficient drawing of complicated pages of graphics.
# A graphics context includes the current affine transformation from the user
# coordinate system to the device coordinate system. It also includes such
# modal drawing attributes as graphics cursor position, linemode, line
# thickness, pen and fill colors, and the font used for drawing text. The state
# of any uncompleted path (if any) is included as well, since paths may be
# drawn incrementally, one portion (line segment or arc) at a time. The current
# graphics context is pushed onto the stack by calling +savestate+, and popped
# off by calling +restorestate+.
#
# To permit vector graphics animation, any page of graphics may be split into
# "frames". A frame is ended, and a new frame is begun, by invoking the +erase+
# method. On a Plotter that does real-time plotting (i.e., an X, X Drawable,
# Tektronix, or Metafile Plotter), this erases all plotted objects from the
# graphics display, allowing a new frame to be drawn. Displaying a sequence of
# frames in succession creates the illusion of smooth animation.
#
# On most Plotters that do not do real-time plotting (i.e., PNM, Illustrator,
# Postscript, Fig, PCL, or HP-GL Plotters), invoking +erase+ deletes all
# plotted objects from an internal buffer. For this reason, most Plotters that
# do not do real-time plotting will display only the final frame of any
# multiframe page.
#
# GIF Plotters are in a class by themselves. Even though they do not do real
# time plotting, a GIF Plotter can produce multi-image output, i.e., an
# animated pseudo-GIF file, from a multiframe page. As noted above, the
# pseudo-GIF file produced by a GIF Plotter will contain only the first page of
# graphics. But if this page consists of multiple frames, then each invocation
# of erase, after the first, will be treated by default as a separator between
# successive images.
class Plotter < Rplot

  # Creates a Plotter of type +type+, where +type+ may be "X", "Xdrawable",
  # "pnm", "gif", "ai", "ps", "fig", "pcl", "hpgl", "tek", or "meta".
  # The Plotter will have input path +in_path+, output path +out_path+, and
  # error path +err_path+. Any or all of these three may be +nil+. Currently,
  # all Plotters are write-only, so +in_path+ is ignored. X Plotters and X
  # Drawable Plotters write graphics to an X Window System display rather than
  # to an output stream, so if +type+ is "X" or "Xdrawable" then +out_path+ is
  # ignored as well. Error messages (if any) are written to the stream created
  # with +err_path+, unless +err_path+ is +nil+.
  # TODO: AN EXCEPTION may be raise if...
  def initialize(type, out_path, in_path = nil, err_path = nil)
    super(type, in_path, out_path, err_path)
  end

  def delete
    super
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

  def open
    super
  end



end
