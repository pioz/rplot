require 'ext/rplot'

# This class rappresents a Plotter.
#
# The graphical objects that libplot can draw include paths, circles and
# ellipses, points, markers, and <i>adjusted labels</i> (justified text
# strings). A path is a sequence of line segments, circular arcs, elliptic
# arcs, quadratic Bezier curves, and/or cubic Bezier curves. Paths may be open
# or closed. User-specified filling of paths, circles, and ellipses is
# supported (fill rule and fill color, as well as pen color, may be specified).
# There is support for maintaining a Postscript-style stack of graphics
# contexts, i.e., a stack of drawing attribute sets. Path-related attributes
# include line thickness, line type, cap type, and join type, and text-related
# attributes include font name, font size, and text angle.
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
#              <i>spun off</i> when the Plotter is closed; if it is
#              subsequently reopened, a new window will be popped up. A
#              spun-off window will remain on the screen but will vanish if you
#              type +q+ or click your mouse in it. Future releases may permit X
#              Plotters, when reopened, to reuse an existing window.
# [X Drawable Plotters] An X Drawable Plotter draws graphics in one or two
#                       specified drawables associated with an X Window System
#                       display. A _drawable_ is either a window or a pixmap.
# [PNM Plotters] A PNM Plotter produces a single page of output in <i>portable
#                anymap</i> format, and directs it to a file or other specified
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
#                     version of the <i>plot(5)</i> format found on some other
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
# Illustrator and Postscript Plotters, it is because a <i>bounding box</i> line
# must be placed at the head of the output file. For a Fig Plotter, it is
# because color definitions must be placed at the head of the output file.
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
# <i>graphics display</i> drawn in by a Plotter is a square or rectangular
# region on a display device. But when using any Plotter to draw graphics, a
# user will specify the coordinates of graphical objects in device-independent
# <i>user coordinates</i>, rather than in device coordinates. A Plotter relates
# the user coordinate system to the device coordinate system by performing an
# affine transformation, which must be specified by the user.
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
# _frames_. A frame is ended, and a new frame is begun, by invoking the +erase+
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

  # Creates a Plotter of type +type+, where +type+ may be _X_, _Xdrawable_,
  # _pnm_, _gif_, _ai_, _ps_, _fig_, _pcl_, _hpgl_, _tek_, or _meta_.
  # The Plotter will have input path +in_path+, output path +out_path+, and
  # error path +err_path+. Any or all of these three may be +nil+. Currently,
  # all Plotters are write-only, so +in_path+ is ignored. X Plotters and X
  # Drawable Plotters write graphics to an X Window System display rather than
  # to an output stream, so if +type+ is _X_ or _Xdrawable_ then +out_path+ is
  # ignored as well. Error messages (if any) are written to the stream created
  # with +err_path+, unless +err_path+ is +nil+.
  #
  # +OpenPlotterError+ exception will be raise if the Plotter could not be
  # create.
  def initialize(type, out_path, in_path = nil, err_path = nil)
    super(type, in_path, out_path, err_path)
  end

  # Delete the Plotter.
  #
  # +DeletePlotterError+ exception will be raise if the Plotter could not be
  # delete.
  def delete
    super
  end

  # Sets the value of the device driver parameters. The parameter values in
  # effect at the time any Plotter is created are copied into it.
  # Unrecognized parameters are ignored.
  #
  # The list of the recognized parameters:
  # [DISPLAY] (Default +nil+.) The X Window System display on which the
  #           graphics display will be popped up, as an X window. This is
  #           relevant only to X Plotters.
  # [BITMAPSIZE] (Default "570x570".) The size of the graphics display in terms
  #              of pixels. This is relevant only to X Plotters, PNM Plotters,
  #              and GIF Plotters. For X Plotters, the value of this parameter
  #              will automatically, if it is not set, be taken from the X
  #              resource Xplot.geometry. This is for backward compatibility.
  # [PAGESIZE] (Default "letter".) The size of the page on which the graphics
  #            display will be positioned. This is relevant only to
  #            Illustrator, Postscript, Fig, PCL, and HP-GL Plotters. "letter"
  #            means an 8.5in by 11in page. Any ISO page size in the range
  #            "a0"..."a4" or ANSI page size in the range "a"..."e" may be
  #            specified ("letter" is an alias for "a" and "tabloid" is an
  #            alias for "b"). "legal", "ledger", and "b5" are recognized page
  #            sizes also. For Illustrator and Postscript Plotters, the
  #            graphics display will be a square region centered on the
  #            specified page and occupying its full width, with allowance
  #            being made for margins. For Fig Plotters, the graphics display
  #            will be a square region of the same size, positioned in the
  #            upper left corner of an xfig display. For PCL and HP-GL
  #            Plotters, the graphics display will be a square region of the
  #            same size, but may be positioned differently. For PCL Plotters,
  #            fine control over its positioning on the page may be
  #            accomplished by setting the PCL_XOFFSET and PCL_YOFFSET
  #            parameters. For HP-GL Plotters, +HPGL_XOFFSET+ and
  #            +HPGL_YOFFSET+ are used similarly.
  # [BG_COLOR] (Default "white".) The initial background color of the graphics
  #            display, when drawing each page of graphics. This is relevant to
  #            X Plotters, PNM Plotters, GIF Plotters, and X Drawable Plotters
  #            (for the last, the background color shows up only if erase is
  #            invoked). The background color may be changed at any later time
  #            by invoking the bgcolor (or bgcolorname) and erase operations.
  #            An unrecognized color name sets the background color to the
  #            default.
  # [GIF_ANIMATION] (Default "yes".) Relevant only to GIF Plotters. "yes" means
  #                 that the erase operation will have special semantics: with
  #                 the exception of its first invocation, it will act as a
  #                 separator between successive images in the written-out
  #                 pseudo-GIF file. "no" means that erase should act as it
  #                 does on other Plotters that do not write graphics in real
  #                 time, i.e., it should erase the image under construction by
  #                 filling it with the background color. If "no" is specified,
  #                 the pseudo-GIF file will contain only a single image.
  # [GIF_DELAY] (Default "0".) Relevant only to GIF Plotters. The delay, in
  #             hundredths of a second, after each image in a written-out
  #             animated pseudo-GIF file. The value should be an integer in the
  #             range "0"..."65535".
  # [GIF_ITERATIONS] (Default "0".) Relevant only to GIF Plotters. The number
  #                  of times that an animated pseudo-GIF file should be
  #                  _looped_. The value should be an integer in the range
  #                  "0"..."65535".
  # [HPGL_ASSIGN_COLORS] (Default "no".) Relevant only to HP-GL Plotters, and
  #                      only if the value of +HPGL_VERSION+ is "2". "no" means
  #                      to draw with a fixed set of pens, specified by setting
  #                      the +HPGL_PENS+ parameter. "yes" means that pen colors
  #                      will not restricted to the palette specified in
  #                      +HPGL_PENS+: colors will be assigned to <i>logical
  #                      pens</i> in the range #1...#31, as needed. Other than
  #                      color LaserJet printers and DesignJet plotters, not
  #                      many HP-GL/2 devices allow the assignment of colors to
  #                      logical pens. So this parameter should be used with
  #                      caution.
  # [HPGL_OPAQUE_MODE] (Default "yes".) Relevant only to HP-GL Plotters, and
  #                    only if the value of HPGL_VERSION is "2". "yes" means
  #                    that the HP-GL/2 output device should be switched into
  #                    opaque mode, rather than transparent mode. This allows
  #                    objects to be filled with opaque white and other opaque
  #                    colors. It also allows the drawing of visible white
  #                    lines, which by convention are drawn with pen #0. Not
  #                    all HP-GL/2 devices support opaque mode or the use of
  #                    pen #0 to draw visible white lines. In particular,
  #                    HP-GL/2 pen plotters do not. Some older HP-GL/2 devices
  #                    reportedly malfunction if asked to switch into opaque
  #                    mode. If the output of an HP-GL Plotter is to be sent to
  #                    such a device, a "no" value is recommended.
  # [HPGL_PENS] (Default "+1=black:2=red:3=green:4=yellow:5=blue:6=magenta:7=cyan+"
  #             if the value of +HPGL_VERSION+ is "1.5" or "2" and "1=black" if
  #             the value of HPGL_VERSION is "1"). Relevant only to HP-GL
  #             Plotters. The set of available pens; the format should be
  #             self-explanatory. The color for any pen in the range #1...#31
  #             may be specified. For information on what color names are
  #             recognized, see section Specifying Colors by Name. Pen #1 must
  #             always be present, though it need not be black. Any other pen
  #             in the range #1...#31 may be omitted.
  # [HPGL_ROTATE] (Default "0".) Relevant only to HP-GL Plotters. The angle, in
  #               degrees, by which the graphics display should be rotated on
  #               the page relative to the default orientation. Recognized
  #               values are "0", "90", "180", and "270"; "no" and "yes" are
  #               equivalent to "0" and "90" respectively. This parameter is
  #               provided to facilitate switching between portrait and
  #               landscape orientations. For HP-GL devices this is frequently
  #               a concern, since some HP-GL devices (_plotters_) draw with a
  #               default landscape orientation, and others (_printers_) draw
  #               with a default portrait orientation. "180" and "270" are
  #               supported only if +HPGL_VERSION+ is "2".
  # [HPGL_VERSION] (Default "2".) Relevant only to HP-GL Plotters. "1" means
  #                that the output should be generic HP-GL, "1.5" means that
  #                the output should be suitable for the HP7550A graphics
  #                plotter and the HP758x, HP7595A and HP7596A drafting
  #                plotters (HP-GL with some HP-GL/2 extensions), and "2" means
  #                that the output should be modern HP-GL/2. If the version is
  #                less than "2" then the only available fonts will be vector
  #                fonts, and all paths will be drawn with a default thickness,
  #                so that invoking capmod, joinmod, and fmiterlimit will have
  #                no effect. Also, the <i>nonzero winding number rule</i> will
  #                not be supported when filling paths, so invoking fillmod
  #                will have no effect. Additionally, if the version is "1"
  #                then the filling of arbitrary paths will not be supported
  #                (circles and rectangles aligned with the coordinate axes
  #                may be filled, however).
  # [HPGL_XOFFSET, HPGL_YOFFSET] (Defaults "0.0cm" and "0.0cm".) Relevant only
  #                              to HP-GL Plotters. Adjustments, in the x and y
  #                              directions, of the position of the graphics
  #                              display on the page. They may be specified in
  #                              centimeters, millimeters, or inches. For
  #                              example, an offset could be specified as "2cm"
  #                              or "1.2in".
  # [INTERLACE] (Default "no".) Relevant only to GIF Plotters. If the value is
  #             "yes", the pseudo-GIF output file will be interlaced. That
  #             means that it will be displayed in an interlaced (nonlinear)
  #             way by many applications.
  # [MAX_LINE_LENGTH] (Default "500".) The maximum number of points that a path
  #                   may contain, before it is flushed to the display device.
  #                   If this flushing occurs, the path will be split into two
  #                   or more sub-paths, though the splitting should not be
  #                   noticeable. Splitting will not be performed if the path
  #                   is filled. This parameter is relevant to all Plotters
  #                   except Tektronix and Metafile Plotters. The reason for
  #                   splitting long paths is that some display devices (e.g.,
  #                   old Postscript printers and HP-GL pen plotters) have
  #                   limited buffer sizes. It is not relevant to Tektronix or
  #                   Metafile Plotters, since they draw paths in real time and
  #                   have no buffer limitations.
  # [META_PORTABLE] (Default "no".) Relevant only to Metafile Plotters. "yes"
  #                 means that the output should be in a portable
  #                 (human-readable) version of the metafile format, rather
  #                 than the default (binary) version. See section The Graphics
  #                 Metafile Format.
  # [PCL_ASSIGN_COLORS] (Default "no".) Relevant only to PCL Plotters. "no"
  #                     means to draw with a fixed set of pens. "yes" means
  #                     that pen colors will not restricted to this palette:
  #                     colors will be assigned to <i>logical pens</i>, as
  #                     needed. Other than color LaserJet printers, not many
  #                     PCL 5 devices allow the assignment of colors to logical
  #                     pens. So this parameter should be used with caution.
  # [PCL_BEZIERS] (Default "yes".) Relevant only to PCL Plotters. "yes" means
  #               that when drawing Bezier curves, the special <i>Bezier
  #               instructions</i> will be used. "no" means that these
  #               instructions will not be used. Instead, each Bezier curve
  #               will be approximated and drawn as a polygonal line. Other
  #               than the LaserJet III, which was Hewlett--Packard's first PCL
  #               5 printer, all Hewlett--Packard's PCL 5 printers support the
  #               Bezier instructions.
  # [PCL_ROTATE] (Default "0".) Relevant only to PCL Plotters. The angle, in
  #              degrees, by which the graphics display should be rotated on
  #              the page relative to the default orientation. Recognized
  #              values are "0", "90", "180", and "270"; "no" and "yes" are
  #              equivalent to "0" and "90" respectively. This parameter is
  #              provided to facilitate switching between portrait and
  #              landscape orientations. For PCL 5 devices this is frequently a
  #              concern, since some PCL 5 devices (_plotters_) draw with a
  #              default landscape orientation, and others (_printers_) draw
  #              with a default portrait orientation.
  # [PCL_XOFFSET, PCL_YOFFSET] (Defaults "0.0cm" and "0.0cm".) Relevant only to
  #                            PCL Plotters. Adjustments, in the x and y
  #                            directions, of the position of the graphics
  #                            display on the page. They may be specified in
  #                            centimeters, millimeters, or inches. For
  #                            example, an offset could be specified as "2cm"
  #                            or "1.2in".
  # [PNM_PORTABLE] (Default "no".) Relevant only to PNM Plotters. "yes" means
  #                that the output should be in a portable (human-readable)
  #                version of PBM/PGM/PPM format, rather than the default
  #                (binary) version. `Portable' is something of a misnomer,
  #                since binary PBM/PGM/PPM files are also portable, in the
  #                sense that they are machine-independent.
  # [TERM] (Default +nil+.) Relevant only to Tektronix Plotters. If the value
  #        is _xterm_, _xterms_, or _kterm_, it is taken as a sign that the
  #        current application is running in an X Window System VT100 terminal
  #        emulator: an xterm. Before drawing graphics, a Tektronix Plotter
  #        will emit an escape sequence that causes the terminal emulator's
  #        auxiliary Tektronix window, which is normally hidden, to pop up.
  #        After the graphics are drawn, an escape sequence that returns
  #        control to the original VT100 window will be emitted. The Tektronix
  #        window will remain on the screen. If the value is _kermit_,
  #        _ansi.sys_, _ansissys_, _ansi.sysk_, or _ansisysk_, it is taken as a
  #        sign that the current application is running in the VT100 terminal
  #        emulator provided by the MS-DOS version of kermit. Before drawing
  #        graphics, a Tektronix Plotter will emit an escape sequence that
  #        switches the terminal emulator to Tektronix mode. Also, some of the
  #        Tektronix control codes emitted by the Plotter will be
  #        kermit-specific. There will be a limited amount of color support,
  #        which is not normally the case (the 16 ansi.sys colors will be
  #        supported). The _dotdotdashed_ line style will be supported, which
  #        is also not normally the case. After drawing graphics, the Plotter
  #        will emit an escape sequence that returns the emulator to VT100
  #        mode. The key sequence <i>ALT minus</i> may be employed manually
  #        within kermit to switch between the two modes.
  # [TRANSPARENT_COLOR] (Default "none".) Relevant only to GIF Plotters. If the
  #                     value is a recognized color name, that color, if it
  #                     appears in the pseudo-GIF output file, will be treated
  #                     as transparent by most applications that display GIF
  #                     files. For information on what names are recognized,
  #                     see section Specifying Colors by Name. If
  #                     +TRANSPARENT_COLOR+ is set and an animated pseudo-GIF
  #                     file is produced, the <i>restore to background</i>
  #                     disposal method will be used for each image in the
  #                     file. Otherwise, the _unspecified_ disposal method will
  #                     be used.
  # [USE_DOUBLE_BUFFERING] (Default "no".) Relevant only to X Plotters and X
  #                        Drawable Plotters. If the value is "yes", a double
  #                        buffering scheme will be used when drawing graphics.
  #                        Each frame of graphics, within a +open+...+close+
  #                        pair, will be written to an off-screen buffer rather
  #                        than to the Plotter's display. When erase is invoked
  #                        to end a frame, or when closepl is invoked, the
  #                        contents of the off-screen buffer will be copied to
  #                        the Plotter's display, pixel by pixel. If successive
  #                        frames differ only slightly, this will create the
  #                        illusion of smooth animation. Some X displays
  #                        provide special hardware support for double
  #                        buffering. If this support is available, the X
  #                        Plotter will detect its presence, and will draw
  #                        graphics using the appropriate extension to the X11
  #                        protocol (either DBE or MBX). In this case the
  #                        animation will be significantly faster; on high-end
  #                        graphics hardware, at least.
  # [VANISH_ON_DELETE] (Default "no".) Relevant only to X Plotters. If the
  #                    value is "yes", when a Plotter is deleted, the window or
  #                    windows that it has popped up will vanish. Otherwise,
  #                    each such window will remain on the screen until it is
  #                    removed by the user (by typing "q" in it, or by clicking
  #                    with a mouse).
  # [XDRAWABLE_COLORMAP] (Default +nil+.) Relevant only to X Drawable Plotters.
  #                      If the value is non-nil, it should be a Colormap *, a
  #                      pointer to a colormap from which colors should be
  #                      allocated. nil indicates that the colormap to be used
  #                      should be the default colormap of the default screen
  #                      of the X display.
  # [XDRAWABLE_DISPLAY] (Default +nil+.) Relevant only to X Drawable Plotters.
  #                     The value should be a Display *, a pointer to the X
  #                     display with which the drawable(s) to be drawn in are
  #                     associated.
  # [XDRAWABLE_DRAWABLE1, XDRAWABLE_DRAWABLE2] (Default +nil+.) Relevant only
  #                                            to X Drawable Plotters. If set,
  #                                            the value of each of these
  #                                            parameters should be a Drawable
  #                                            *, a pointer to a drawable to
  #                                            be drawn in. A _drawable_ is
  #                                            either a window or a pixmap. At
  #                                            the time an X Drawable Plotter
  #                                            is created, at least one of the
  #                                            two parameters must be set. X
  #                                            Drawable Plotters support
  #                                            simultaneous drawing in two
  #                                            drawables because it is often
  #                                            useful to be able to draw
  #                                            graphics simultaneously in both
  #                                            an X window and its background
  #                                            pixmap. If two drawables are
  #                                            specified, they must have the
  #                                            same dimensions and depth, and
  #                                            be associated with the same
  #                                            screen of the X display.
  def self.params(options = {})
    options.each do |k,v|
      Rplot.param(k.to_s.upcase, v.to_s)
    end
  end

  # Create a new plotter that live inside the +block+ passed to +draw+.
  # Operations in +block+ are wrapped between +open+, +erase+ and +delete+
  # methods.
  def self.draw(type, out_path, in_path = nil, err_path = nil)
    plotter = Plotter.new(type, out_path, in_path, err_path)
    plotter.open
    plotter.erase
    yield(plotter)
    plotter.delete
  end

  # Wrap Plotter operations between +open+, +erase+ and +delete+ methods.
  def draw
    self.open
    self.erase
    yield
    self.delete
  end

  # Open a Plotter, i.e., begins a page of graphics. This resets the Plotter's
  # drawing attributes to their default values. A negative return value
  # indicates the Plotter could not be opened. Currently, an X Plotter pops up
  # a new window on an X Window System display for each page of graphics, i.e.,
  # with each invocation of +open+. Future releases may support window re-use.
  #
  # +OpenPlotterError+ exception will be raise if the Plotter could not be
  # open.
  def open
    super
  end

  # Sets the background color for the Plotter's graphics display, using a
  # 48-bit RGB color model. The arguments red, green and blue specify the red,
  # green and blue intensities of the background color. Each is an integer in
  # the range 0x0000...0xffff, i.e., 0...65535. The choice (0, 0, 0) signifies
  # black, and the choice (65535, 65535, 65535) signifies white. bgcolor
  # affects only Plotters that produce bitmaps, i.e., X Plotters, X Drawable
  # Plotters, PNM Plotters, and GIF Plotters. Its effect is simple: the next
  # time the erase operation is invoked on such a Plotter, its display will be
  # filled with the specified color.
  # If the first parameter is a string, it is considered as color name. +green+
  # and +blue+ parameters may be +nil+.
  # If +:erase+ option is passed then call +erase+ too.
  def bgcolor(red_or_name, green = nil, blue = nil, options = {})
    if red_or_name.class == Fixnum && green.class == Fixnum && blue.class == Fixnum
      super(red_or_name, green, blue)
    else
      self.bgcolorname(red_or_name.to_s)
    end
    erase if options[:erase]
  end

  # +erase+ begins the next frame of a multiframe page, by clearing all
  # previously plotted objects from the graphics display, and filling it with
  # the background color (if any). It is frequently useful to invoke erase at
  # the beginning of each page, i.e., immediately after invoking +open+. That
  # is because some Plotters are persistent, in the sense that objects drawn
  # within an +open+...+close+ pair remain on the graphics display even after a
  # new page is begun by a subsequent invocation of +open+. Currently, only X
  # Drawable Plotters and Tektronix Plotters are persistent. Future releases
  # may support optional persistence for X Plotters also. On X Plotters and X
  # Drawable Plotters the effects of invoking erase will be altogether
  # different if the device driver parameter +USE_DOUBLE_BUFFERING+ is set to
  # "yes". In this case, objects will be written to an off-screen buffer rather
  # than to the graphics display, and invoking erase will (1) copy the contents
  # of this buffer to the display, and (2) erase the buffer by filling it with
  # the background color. This <i>double buffering</i> feature facilitates
  # smooth animation.
  def erase
    super
  end

  # +space+ take two pairs of arguments, specifying the positions of the lower
  # left corner and upper right corner of the graphics display, in user
  # coordinates. In other words, calling +space+ sets the affine transformation
  # from user coordinates to device coordinates. One of these operations must
  # be performed at the beginning of each page of graphics, i.e., immediately
  # after +open+ is invoked. Default is 0,0,1,1.
  def space(x0, y0, x1, y1)
    fspace(x0.to_f, y0.to_f, x1.to_f, y1.to_f)
  end

  # +space2+ are extended versions of +space+, and may be used instead. Their
  # arguments are the three defining vertices of an <i>affine window</i> (a
  # drawing parallelogram), in user coordinates. The specified vertices are the
  # lower left, the lower right, and the upper left. This window will be mapped
  # affinely onto the graphics display.
  def space2(x0, y0, x1, y1, x2, y2)
    fspace2(x0.to_f, y0.to_f, x1.to_f, y1.to_f, x2.to_f, y2.to_f)
  end

  # +havecap+ tests whether or not a Plotter, which need not be open, has a
  # specified capability. The return value is 0, 1, or 2, signifying
  # no/yes/maybe. For unrecognized capabilities the return value is zero.
  # Recognized capabilities include:
  # [WIDE_LINES] The ability to draw lines with a non-default thickness
  # [DASH_ARRAY] The ability to draw in arbitrary dashing styles, as requested
  #              by the linedash function)
  # [SETTABLE_BACKGROUND] The ability to set the color of the background
  # [SOLID_FILL]
  # The "HERSHEY_FONTS", "PS_FONTS", "PCL_FONTS", and "STICK_FONTS"
  # capabilities indicate whether or not fonts of a particular class are
  # supported. All Plotters except Tektronix Plotters have the "SOLID_FILL"
  # capability, meaning they can fill paths with solid color. Each such Plotter
  # has at least one of the "EVEN_ODD_FILL" and "NONZERO_WINDING_NUMBER_FILL"
  # capabilities. These indicate the supported rules for determining the
  # _inside_ of a path. The _maybe_ value is returned for most capabilities by
  # Metafile Plotters, which do no drawing themselves. The output of a Metafile
  # Plotter must be translated to another format, or displayed, by invoking
  # plot.
  def havecap(s)
    super(s.to_s)
  end

  # +flush+ flushes (i.e., pushes onward) all plotting commands to the display
  # device. This is useful only if the currently selected Plotter does
  # real-time plotting, since it may be used to ensure that all previously
  # plotted objects have been sent to the display and are visible to the user.
  # It has no effect on Plotters that do not do real-time plotting.
  def flush
    super
  end

  # +close+ closes a Plotter, i.e., ends a page of graphics.
  #
  # +ClosePlotterError+ exception will be raise if the Plotter could not be
  # close.
  def close
    super
  end

  def line(x0, y0, x1, y1)
    fline(x0.to_f, y0.to_f, x1.to_f, y1.to_f)
  end

end