#ifndef RUBY_PLOT
#define RUBY_PLOT

#include <ruby.h>
#include <plot.h>
#include <stdio.h>

/* 4 base functions */

static VALUE new_pl (VALUE self, VALUE type, VALUE in_path, VALUE out_path, VALUE err_path);
//static VALUE select_pl (VALUE self);
static VALUE delete_pl (VALUE self);
static VALUE parampl (VALUE self, VALUE param, VALUE value);

/* Setup functions */

static VALUE openpl (VALUE self);
static VALUE bgcolor (VALUE self, VALUE red, VALUE green, VALUE blue);
static VALUE bgcolorname (VALUE self, VALUE name);
static VALUE erase (VALUE self);
static VALUE space (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE fspace (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE space2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE fspace2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE havecap (VALUE self, VALUE s);
static VALUE flushpl (VALUE self);
static VALUE closepl (VALUE self);

/* Object-drawing functions */

static VALUE alabel (VALUE self, VALUE horiz_justify, VALUE vert_justify, VALUE s);
static VALUE arc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE farc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE arcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE farcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE bezier2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE fbezier2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE bezier2rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE fbezier2rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE bezier3 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
static VALUE fbezier3 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
static VALUE bezier3rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
static VALUE fbezier3rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3);
static VALUE box (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE fbox (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE boxrel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE fboxrel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE circle (VALUE self, VALUE xc, VALUE yc, VALUE r);
static VALUE fcircle (VALUE self, VALUE xc, VALUE yc, VALUE r);
static VALUE circlerel (VALUE self, VALUE xc, VALUE yc, VALUE r);
static VALUE fcirclerel (VALUE self, VALUE xc, VALUE yc, VALUE r);
static VALUE cont (VALUE self, VALUE x, VALUE y);
static VALUE fcont (VALUE self, VALUE x, VALUE y);
static VALUE contrel (VALUE self, VALUE x, VALUE y);
static VALUE fcontrel (VALUE self, VALUE x, VALUE y);
static VALUE ellarc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE fellarc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE ellarcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE fellarcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1);
static VALUE ellipse (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle);
static VALUE fellipse (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle);
static VALUE ellipserel (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle);
static VALUE fellipserel (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle);
static VALUE endpath (VALUE self);
static VALUE label (VALUE self, VALUE s);
static VALUE labelwidth (VALUE self, VALUE s);
static VALUE flabelwidth (VALUE self, VALUE s);
static VALUE line (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE fline (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE linerel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE flinerel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2);
static VALUE marker (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size);
static VALUE fmarker (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size);
static VALUE markerrel (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size);
static VALUE fmarkerrel (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size);
static VALUE point (VALUE self, VALUE x, VALUE y);
static VALUE fpoint (VALUE self, VALUE x, VALUE y);
static VALUE pointrel (VALUE self, VALUE x, VALUE y);
static VALUE fpointrel (VALUE self, VALUE x, VALUE y);

/* Attribute-setting functions */

static VALUE capmod (VALUE self, VALUE s);
static VALUE color (VALUE self, VALUE red, VALUE green, VALUE blue);
static VALUE colorname (VALUE self, VALUE name);
static VALUE fillcolor (VALUE self, VALUE red, VALUE green, VALUE blue);
static VALUE fillcolorname (VALUE self, VALUE name);
static VALUE fillmod (VALUE self, VALUE s);
static VALUE filltype (VALUE self, VALUE level);
static VALUE fmiterlimit (VALUE self, VALUE limit);
static VALUE fontname (VALUE self, VALUE font_name);
static VALUE ffontname (VALUE self, VALUE font_name);
static VALUE fontsize (VALUE self, VALUE size);
static VALUE ffontsize (VALUE self, VALUE size);
static VALUE joinmod (VALUE self, VALUE s);
static VALUE linedash (VALUE self, VALUE n, VALUE dashes, VALUE offset);
static VALUE flinedash (VALUE self, VALUE n, VALUE dashes, VALUE offset);
static VALUE linemod (VALUE self, VALUE s);
static VALUE linewidth (VALUE self, VALUE size);
static VALUE flinewidth (VALUE self, VALUE size);
static VALUE move (VALUE self, VALUE x, VALUE y);
static VALUE fmove (VALUE self, VALUE x, VALUE y);
static VALUE moverel (VALUE self, VALUE x, VALUE y);
static VALUE fmoverel (VALUE self, VALUE x, VALUE y);
static VALUE pencolor (VALUE self, VALUE red, VALUE green, VALUE blue);
static VALUE pencolorname (VALUE self, VALUE name);
static VALUE restorestate (VALUE self);
static VALUE savestate (VALUE self);
static VALUE textangle (VALUE self, VALUE angle);
static VALUE ftextangle (VALUE self, VALUE angle);

/* Mapping functions */

static VALUE fconcat (VALUE self, VALUE m0, VALUE m1, VALUE m2, VALUE m3, VALUE tx, VALUE ty);
static VALUE frotate (VALUE self, VALUE theta);
static VALUE fscale (VALUE self, VALUE sx, VALUE sy);
static VALUE ftranslate (VALUE self, VALUE tx, VALUE ty);

#endif

