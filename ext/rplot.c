/***********************************************************
 * Copyright (C) 2011 Enrico Pilotto (enrico@megiston.it)
 *
 * Binding all functions of C libplot in 'Rplot' Ruby class.
 ***********************************************************/

#include "rplot.h"

static int
get_handler (VALUE self)
{
  int handler = NUM2INT (rb_iv_get (self, "@handler"));
  if (pl_selectpl (handler) < 0)
    rb_raise(select_plotter_error, "Couldn't select Plotter with id %d!", handler);
  return handler;
}

/* 4 base functions */

static VALUE
newpl (VALUE self, VALUE type, VALUE in_path, VALUE out_path, VALUE err_path)
{
  FILE *in_file, *out_file, *err_file;
  if (TYPE (in_path) == T_NIL)
    in_file = stdin;
  else
    in_file = fopen (StringValuePtr (in_path), "w");
  if (TYPE (out_path) == T_NIL)
    out_file = stdout;
  else
    out_file = fopen (StringValuePtr (out_path), "w");
  if (TYPE (err_path) == T_NIL)
    err_file = stderr;
  else
    err_file = fopen (StringValuePtr (err_path), "w");

  int handler = pl_newpl (StringValuePtr (type), stdin, out_file, stderr);
  if (handler < 0)
    rb_raise(create_plotter_error, "Couldn't create Plotter!");
  rb_iv_set (self, "@handler", INT2NUM (handler));
  return self;
}

// static VALUE
// selectpl (VALUE self)
// {
//   No need to bind this function.
//   Use an object-oriented style.
// }

static VALUE
deletepl (VALUE self) {
  int handler = get_handler (self);
  pl_closepl ();
  pl_selectpl (0);
  if (pl_deletepl (handler) < 0)
    rb_raise(delete_plotter_error, "Couldn't delete Plotter with id %d!", handler);
  return INT2FIX (0);
}

static VALUE
parampl (VALUE self, VALUE param, VALUE value)
{
  return INT2FIX (pl_parampl (StringValuePtr (param), (void*)(StringValuePtr (value))));
}

/* Setup functions */

static VALUE
openpl (VALUE self)
{
  get_handler (self);
  if (pl_openpl () < 0)
    rb_raise(open_plotter_error, "Couldn't open Plotter!");
  return INT2FIX (0);
}

static VALUE
bgcolor (VALUE self, VALUE red, VALUE green, VALUE blue)
{
  return INT2FIX (pl_bgcolor (FIX2INT (red),
                              FIX2INT (green),
                              FIX2INT (blue)));
}

static VALUE
bgcolorname (VALUE self, VALUE name)
{
  return INT2FIX (pl_bgcolorname (StringValuePtr (name)));
}

static VALUE
erase (VALUE self)
{
  return INT2FIX (pl_erase ());
}

static VALUE
space (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_space (FIX2INT (x0),
                            FIX2INT (y0),
                            FIX2INT (x1),
                            FIX2INT (y1)));
}

static VALUE
fspace (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_fspace (NUM2DBL (x0),
                             NUM2DBL (y0),
                             NUM2DBL (x1),
                             NUM2DBL (y1)));
}

static VALUE
space2(VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_space2 (FIX2INT (x0),
                             FIX2INT (y0),
                             FIX2INT (x1),
                             FIX2INT (y1),
                             FIX2INT (x2),
                             FIX2INT (y2)));
}

static VALUE
fspace2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_fspace2 (NUM2DBL (x0),
                              NUM2DBL (y0),
                              NUM2DBL (x1),
                              NUM2DBL (y1),
                              NUM2DBL (x2),
                              NUM2DBL (y2)));
}

static VALUE
havecap (VALUE self, VALUE s)
{
  return INT2FIX (pl_havecap (StringValuePtr (s)));
}

static VALUE
flushpl (VALUE self)
{
  return INT2FIX (pl_flushpl ());
}

static VALUE
closepl (VALUE self)
{
  get_handler (self);
  if (pl_closepl () < 0)
    rb_raise(close_plotter_error, "Couldn't close Plotter!");
  return INT2FIX (0);
}

/* Object-drawing functions */

static VALUE
alabel (VALUE self, VALUE horiz_justify, VALUE vert_justify, VALUE s)
{
  return INT2FIX (pl_alabel (FIX2INT (horiz_justify),
                             FIX2INT (vert_justify),
                             StringValuePtr (s)));
}

static VALUE
arc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_arc (FIX2INT (xc),
                          FIX2INT (yc),
                          FIX2INT (x0),
                          FIX2INT (y0),
                          FIX2INT (x1),
                          FIX2INT (y1)));
}

static VALUE
farc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_farc (NUM2DBL (xc),
                           NUM2DBL (yc),
                           NUM2DBL (x0),
                           NUM2DBL (y0),
                           NUM2DBL (x1),
                           NUM2DBL (y1)));
}

static VALUE
arcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_arcrel (FIX2INT (xc),
                             FIX2INT (yc),
                             FIX2INT (x0),
                             FIX2INT (y0),
                             FIX2INT (x1),
                             FIX2INT (y1)));
}

static VALUE
farcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_farcrel (NUM2DBL (xc),
                              NUM2DBL (yc),
                              NUM2DBL (x0),
                              NUM2DBL (y0),
                              NUM2DBL (x1),
                              NUM2DBL (y1)));
}

static VALUE
bezier2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_bezier2 (FIX2INT (x0),
                              FIX2INT (y0),
                              FIX2INT (x1),
                              FIX2INT (y1),
                              FIX2INT (x2),
                              FIX2INT (y2)));
}

static VALUE
fbezier2 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_fbezier2 (NUM2DBL (x0),
                               NUM2DBL (y0),
                               NUM2DBL (x1),
                               NUM2DBL (y1),
                               NUM2DBL (x2),
                               NUM2DBL (y2)));
}

static VALUE
bezier2rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_bezier2rel (FIX2INT (x0),
                                 FIX2INT (y0),
                                 FIX2INT (x1),
                                 FIX2INT (y1),
                                 FIX2INT (x2),
                                 FIX2INT (y2)));
}

static VALUE
fbezier2rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_fbezier2rel (NUM2DBL (x0),
                                  NUM2DBL (y0),
                                  NUM2DBL (x1),
                                  NUM2DBL (y1),
                                  NUM2DBL (x2),
                                  NUM2DBL (y2)));
}

static VALUE
bezier3 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  return INT2FIX (pl_bezier3 (FIX2INT (x0),
                              FIX2INT (y0),
                              FIX2INT (x1),
                              FIX2INT (y1),
                              FIX2INT (x2),
                              FIX2INT (y2),
                              FIX2INT (x3),
                              FIX2INT (y3)));
}

static VALUE
fbezier3 (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  return INT2FIX (pl_fbezier3 (NUM2DBL (x0),
                               NUM2DBL (y0),
                               NUM2DBL (x1),
                               NUM2DBL (y1),
                               NUM2DBL (x2),
                               NUM2DBL (y2),
                               NUM2DBL (x3),
                               NUM2DBL (y3)));
}

static VALUE
bezier3rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  return INT2FIX (pl_bezier3rel (FIX2INT (x0),
                                 FIX2INT (y0),
                                 FIX2INT (x1),
                                 FIX2INT (y1),
                                 FIX2INT (x2),
                                 FIX2INT (y2),
                                 FIX2INT (x3),
                                 FIX2INT (y3)));
}

static VALUE
fbezier3rel (VALUE self, VALUE x0, VALUE y0, VALUE x1, VALUE y1, VALUE x2, VALUE y2, VALUE x3, VALUE y3)
{
  return INT2FIX (pl_fbezier3rel (NUM2DBL (x0),
                                  NUM2DBL (y0),
                                  NUM2DBL (x1),
                                  NUM2DBL (y1),
                                  NUM2DBL (x2),
                                  NUM2DBL (y2),
                                  NUM2DBL (x3),
                                  NUM2DBL (y3)));
}

static VALUE
box (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_box (FIX2INT (x1),
                          FIX2INT (y1),
                          FIX2INT (x2),
                          FIX2INT (y2)));
}

static VALUE
fbox (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_fbox (NUM2DBL (x1),
                           NUM2DBL (y1),
                           NUM2DBL (x2),
                           NUM2DBL (y2)));
}

static VALUE
boxrel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_boxrel (FIX2INT (x1),
                             FIX2INT (y1),
                             FIX2INT (x2),
                             FIX2INT (y2)));
}

static VALUE
fboxrel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_fboxrel (NUM2DBL (x1),
                              NUM2DBL (y1),
                              NUM2DBL (x2),
                              NUM2DBL (y2)));
}

static VALUE
circle (VALUE self, VALUE xc, VALUE yc, VALUE r)
{
  return INT2FIX (pl_circle (FIX2INT (xc),
                             FIX2INT (yc),
                             FIX2INT (r)));
}

static VALUE
fcircle (VALUE self, VALUE xc, VALUE yc, VALUE r)
{
  return INT2FIX (pl_fcircle (NUM2DBL (xc),
                              NUM2DBL (yc),
                              NUM2DBL (r)));
}

static VALUE
circlerel (VALUE self, VALUE xc, VALUE yc, VALUE r)
{
  return INT2FIX (pl_circlerel (FIX2INT (xc),
                                FIX2INT (yc),
                                FIX2INT (r)));
}

static VALUE
fcirclerel (VALUE self, VALUE xc, VALUE yc, VALUE r)
{
  return INT2FIX (pl_fcirclerel (NUM2DBL (xc),
                                 NUM2DBL (yc),
                                 NUM2DBL (r)));
}

static VALUE
cont (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_cont (FIX2INT (x),
                           FIX2INT (y)));
}

static VALUE
fcont (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_fcont (NUM2DBL (x),
                            NUM2DBL (y)));
}

static VALUE
contrel (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_contrel (FIX2INT (x),
                              FIX2INT (y)));
}

static VALUE
fcontrel (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_fcontrel (NUM2DBL (x),
                               NUM2DBL (y)));
}

static VALUE
ellarc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_ellarc (FIX2INT (xc),
                             FIX2INT (yc),
                             FIX2INT (x0),
                             FIX2INT (y0),
                             FIX2INT (x1),
                             FIX2INT (y1)));
}

static VALUE
fellarc (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_fellarc (NUM2DBL (xc),
                              NUM2DBL (yc),
                              NUM2DBL (x0),
                              NUM2DBL (y0),
                              NUM2DBL (x1),
                              NUM2DBL (y1)));
}

static VALUE
ellarcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_ellarcrel (FIX2INT (xc),
                                FIX2INT (yc),
                                FIX2INT (x0),
                                FIX2INT (y0),
                                FIX2INT (x1),
                                FIX2INT (y1)));
}

static VALUE fellarcrel (VALUE self, VALUE xc, VALUE yc, VALUE x0, VALUE y0, VALUE x1, VALUE y1)
{
  return INT2FIX (pl_fellarcrel (NUM2DBL (xc),
                                 NUM2DBL (yc),
                                 NUM2DBL (x0),
                                 NUM2DBL (y0),
                                 NUM2DBL (x1),
                                 NUM2DBL (y1)));
}

static VALUE
ellipse (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle)
{
  return INT2FIX (pl_ellipse (FIX2INT (xc),
                              FIX2INT (yc),
                              FIX2INT (rx),
                              FIX2INT (ry),
                              FIX2INT (angle)));
}

static VALUE
fellipse (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle)
{
  return INT2FIX (pl_fellipse (NUM2DBL (xc),
                               NUM2DBL (yc),
                               NUM2DBL (rx),
                               NUM2DBL (ry),
                               NUM2DBL (angle)));
}

static VALUE
ellipserel (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle)
{
  return INT2FIX (pl_ellipserel (FIX2INT (xc),
                                 FIX2INT (yc),
                                 FIX2INT (rx),
                                 FIX2INT (ry),
                                 FIX2INT (angle)));
}

static VALUE
fellipserel (VALUE self, VALUE xc, VALUE yc, VALUE rx, VALUE ry, VALUE angle)
{
  return INT2FIX (pl_fellipserel (NUM2DBL (xc),
                                  NUM2DBL (yc),
                                  NUM2DBL (rx),
                                  NUM2DBL (ry),
                                  NUM2DBL (angle)));
}

static VALUE
endpath (VALUE self)
{
  return INT2FIX (pl_endpath ());
}

static VALUE
label (VALUE self, VALUE s)
{
  return INT2FIX (pl_label (StringValuePtr (s)));
}

static VALUE
labelwidth (VALUE self, VALUE s)
{
  return INT2FIX (pl_labelwidth (StringValuePtr (s)));
}

static VALUE
flabelwidth (VALUE self, VALUE s)
{
  return DBL2NUM (pl_flabelwidth (StringValuePtr (s)));
}

static VALUE
line (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_boxrel (FIX2INT (x1),
                             FIX2INT (y1),
                             FIX2INT (x2),
                             FIX2INT (y2)));
}

static VALUE
fline (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_fline (NUM2DBL (x1),
                            NUM2DBL (y1),
                            NUM2DBL (x2),
                            NUM2DBL (y2)));
}

static VALUE
linerel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_linerel (FIX2INT (x1),
                              FIX2INT (y1),
                              FIX2INT (x2),
                              FIX2INT (y2)));
}

static VALUE
flinerel (VALUE self, VALUE x1, VALUE y1, VALUE x2, VALUE y2)
{
  return INT2FIX (pl_flinerel (NUM2DBL (x1),
                               NUM2DBL (y1),
                               NUM2DBL (x2),
                               NUM2DBL (y2)));
}

static VALUE
marker (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size)
{
  return INT2FIX (pl_marker (FIX2INT (x),
                             FIX2INT (y),
                             FIX2INT (type),
                             FIX2INT (size)));
}

static VALUE
fmarker (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size)
{
  return INT2FIX (pl_fmarker (NUM2DBL (x),
                              NUM2DBL (y),
                              FIX2INT (type),
                              NUM2DBL (size)));
}

static VALUE
markerrel (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size)
{
  return INT2FIX (pl_markerrel (FIX2INT (x),
                                FIX2INT (y),
                                FIX2INT (type),
                                FIX2INT (size)));
}

static VALUE
fmarkerrel (VALUE self, VALUE x, VALUE y, VALUE type, VALUE size)
{
  return INT2FIX (pl_fmarkerrel (NUM2DBL (x),
                                 NUM2DBL (y),
                                 FIX2INT (type),
                                 NUM2DBL (size)));
}

static VALUE
point (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_point (FIX2INT (x),
                            FIX2INT (y)));
}

static VALUE
fpoint (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_fpoint (NUM2DBL (x),
                             NUM2DBL (y)));
}

static VALUE
pointrel (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_pointrel (FIX2INT (x),
                               FIX2INT (y)));
}

static VALUE
fpointrel (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_fpoint (NUM2DBL (x),
                             NUM2DBL (y)));
}

/* Attribute-setting functions */

static VALUE
capmod (VALUE self, VALUE s)
{
  return INT2FIX (pl_capmod (StringValuePtr (s)));
}

static VALUE
color (VALUE self, VALUE red, VALUE green, VALUE blue)
{
  return INT2FIX (pl_color (FIX2INT (red),
                            FIX2INT (green),
                            FIX2INT (blue)));
}

static VALUE
colorname (VALUE self, VALUE name)
{
  return INT2FIX (pl_colorname (StringValuePtr (name)));
}

static VALUE
fillcolor (VALUE self, VALUE red, VALUE green, VALUE blue)
{
  return INT2FIX (pl_fillcolor (FIX2INT (red),
                                FIX2INT (green),
                                FIX2INT (blue)));
}

static VALUE
fillcolorname (VALUE self, VALUE name)
{
  return INT2FIX (pl_fillcolorname (StringValuePtr (name)));
}

static VALUE
fillmod (VALUE self, VALUE s)
{
  return INT2FIX (pl_fillmod (StringValuePtr (s)));
}

static VALUE filltype (VALUE self, VALUE level)
{
  return INT2FIX (pl_filltype (FIX2INT (level)));
}

static VALUE
fmiterlimit (VALUE self, VALUE limit)
{
  return INT2FIX (pl_fmiterlimit (NUM2DBL (limit)));
}

static VALUE
fontname (VALUE self, VALUE font_name)
{
  return INT2FIX (pl_fontname (StringValuePtr (font_name)));
}

static VALUE
ffontname (VALUE self, VALUE font_name)
{
  return DBL2NUM (pl_ffontname (StringValuePtr (font_name)));
}

static VALUE
fontsize (VALUE self, VALUE size)
{
  return INT2FIX (pl_fontsize (FIX2INT (size)));
}

static VALUE ffontsize (VALUE self, VALUE size)
{
  return DBL2NUM (pl_ffontsize (NUM2DBL (size)));
}

static VALUE
joinmod (VALUE self, VALUE s)
{
  return INT2FIX (pl_joinmod (StringValuePtr (s)));
}

static VALUE
linedash (VALUE self, VALUE n, VALUE dashes, VALUE offset)
{
  return INT2FIX (pl_linedash (FIX2INT (n),
                               DATA_PTR (dashes),
                               FIX2INT (offset)));
}

static VALUE
flinedash (VALUE self, VALUE n, VALUE dashes, VALUE offset)
{
  return INT2FIX (pl_flinedash (FIX2INT (n),
                                DATA_PTR (dashes),
                                NUM2DBL (offset)));
}

static VALUE
linemod (VALUE self, VALUE s)
{
  return INT2FIX (pl_linemod (StringValuePtr (s)));
}

static VALUE
linewidth (VALUE self, VALUE size)
{
  return INT2FIX (pl_linewidth (FIX2INT (size)));
}

static VALUE
flinewidth (VALUE self, VALUE size)
{
  return INT2FIX (pl_flinewidth (NUM2DBL (size)));
}

static VALUE
move (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_move (FIX2INT (x),
                           FIX2INT (y)));
}

static VALUE
fmove (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_fmove (NUM2DBL (x),
                            NUM2DBL (y)));
}

static VALUE
moverel (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_moverel (FIX2INT (x),
                              FIX2INT (y)));
}

static VALUE
fmoverel (VALUE self, VALUE x, VALUE y)
{
  return INT2FIX (pl_fmoverel (NUM2DBL (x),
                               NUM2DBL (y)));
}

static VALUE
pencolor (VALUE self, VALUE red, VALUE green, VALUE blue)
{
  return INT2FIX (pl_pencolor (FIX2INT (red),
                               FIX2INT (green),
                               FIX2INT (blue)));
}

static VALUE
pencolorname (VALUE self, VALUE name)
{
  return INT2FIX (pl_pencolorname (StringValuePtr (name)));
}

static VALUE
restorestate (VALUE self)
{
  return INT2FIX (pl_restorestate ());
}

static VALUE
savestate (VALUE self)
{
  return INT2FIX (pl_savestate ());
}

static VALUE
textangle (VALUE self, VALUE angle)
{
  return INT2FIX (pl_textangle (FIX2INT (angle)));
}

static VALUE
ftextangle (VALUE self, VALUE angle)
{
  return DBL2NUM (pl_ftextangle (NUM2DBL (angle)));
}

/* Mapping functions */

static VALUE
fconcat (VALUE self, VALUE m0, VALUE m1, VALUE m2, VALUE m3, VALUE tx, VALUE ty)
{
  return INT2FIX (pl_fconcat (NUM2DBL (m0),
                              NUM2DBL (m1),
                              NUM2DBL (m2),
                              NUM2DBL (m3),
                              NUM2DBL (tx),
                              NUM2DBL (ty)));
}

static VALUE
frotate (VALUE self, VALUE theta)
{
  return INT2FIX (pl_frotate (NUM2DBL (theta)));
}

static VALUE
fscale (VALUE self, VALUE sx, VALUE sy)
{
  return INT2FIX (pl_fscale (NUM2DBL (sx),
                             NUM2DBL (sy)));
}

static VALUE
ftranslate (VALUE self, VALUE tx, VALUE ty)
{
  return INT2FIX (pl_ftranslate (NUM2DBL (tx),
                                 NUM2DBL (ty)));
}

/* Init rplot */

void
Init_rplot ()
{
  /* Define exceptions */
  create_plotter_error    = rb_define_class ("CreatePlotterError", rb_eStandardError);
  select_plotter_error    = rb_define_class ("SelectPlotterError", rb_eStandardError);
  open_plotter_error      = rb_define_class ("OpenPlotterError", rb_eStandardError);
  close_plotter_error     = rb_define_class ("ClosePlotterError", rb_eStandardError);
  delete_plotter_error    = rb_define_class ("DeletePlotterError", rb_eStandardError);
  operation_plotter_error = rb_define_class ("OperationPlotterError", rb_eStandardError);
  /* Define Rplot class */
  VALUE rplot = rb_define_class ("Rplot", rb_cObject);
  /* Base functions */
  rb_define_protected_method (rplot, "initialize", newpl, 4);
  rb_define_protected_method (rplot, "delete", deletepl, 0);
  rb_define_singleton_method (rplot, "param", parampl, 2);
  /* Setup functions */
  rb_define_protected_method (rplot, "open", openpl, 0);
  rb_define_protected_method (rplot, "bgcolor", bgcolor, 3);
  rb_define_protected_method (rplot, "bgcolorname", bgcolorname, 1);
  rb_define_protected_method (rplot, "erase", erase, 0);
  rb_define_protected_method (rplot, "space", space, 4);
  rb_define_protected_method (rplot, "fspace", fspace, 4);
  rb_define_protected_method (rplot, "space2", space2, 6);
  rb_define_protected_method (rplot, "fspace2", fspace2, 6);
  rb_define_protected_method (rplot, "havecap", havecap, 1);
  rb_define_protected_method (rplot, "flush", flushpl, 0);
  rb_define_protected_method (rplot, "close", closepl, 0);
  /* Object-drawing functions */
  rb_define_protected_method (rplot, "alabel", alabel, 3);
  rb_define_protected_method (rplot, "arc", arc, 6);
  rb_define_protected_method (rplot, "farc", farc, 6);
  rb_define_protected_method (rplot, "arcrel", arcrel, 6);
  rb_define_protected_method (rplot, "farcrel", farcrel, 6);
  rb_define_protected_method (rplot, "bezier2", bezier2, 6);
  rb_define_protected_method (rplot, "fbezier2", fbezier2, 6);
  rb_define_protected_method (rplot, "bezier2rel", bezier2rel, 6);
  rb_define_protected_method (rplot, "fbezier2rel", fbezier2rel, 6);
  rb_define_protected_method (rplot, "bezier3", bezier3, 8);
  rb_define_protected_method (rplot, "fbezier3", fbezier3, 8);
  rb_define_protected_method (rplot, "bezier3rel", bezier3rel, 8);
  rb_define_protected_method (rplot, "fbezier3rel", fbezier3rel, 8);
  rb_define_protected_method (rplot, "box", box, 4);
  rb_define_protected_method (rplot, "fbox", fbox, 4);
  rb_define_protected_method (rplot, "boxrel", boxrel, 4);
  rb_define_protected_method (rplot, "fboxrel", fboxrel, 4);
  rb_define_protected_method (rplot, "circle", circle, 3);
  rb_define_protected_method (rplot, "fcircle", fcircle, 3);
  rb_define_protected_method (rplot, "circlerel", circlerel, 3);
  rb_define_protected_method (rplot, "fcirclerel", fcirclerel, 3);
  rb_define_protected_method (rplot, "cont", cont, 2);
  rb_define_protected_method (rplot, "fcont", fcont, 2);
  rb_define_protected_method (rplot, "contrel", contrel, 2);
  rb_define_protected_method (rplot, "fcontrel", fcontrel, 2);
  rb_define_protected_method (rplot, "ellarc", ellarc, 6);
  rb_define_protected_method (rplot, "fellarc", fellarc, 6);
  rb_define_protected_method (rplot, "ellarcrel", ellarcrel, 6);
  rb_define_protected_method (rplot, "fellarcrel", fellarcrel, 6);
  rb_define_protected_method (rplot, "ellipse", ellipse, 6);
  rb_define_protected_method (rplot, "fellipse", fellipse, 6);
  rb_define_protected_method (rplot, "ellipserel", ellipserel, 6);
  rb_define_protected_method (rplot, "fellipserel", fellipserel, 6);
  rb_define_protected_method (rplot, "endpath", endpath, 0);
  rb_define_protected_method (rplot, "label", label, 1);
  rb_define_protected_method (rplot, "labelwidth", labelwidth, 1);
  rb_define_protected_method (rplot, "flabelwidth", flabelwidth, 1);
  rb_define_protected_method (rplot, "line", line, 4);
  rb_define_protected_method (rplot, "fline", fline, 4);
  rb_define_protected_method (rplot, "linerel", linerel, 4);
  rb_define_protected_method (rplot, "flinerel", flinerel, 4);
  rb_define_protected_method (rplot, "marker", marker, 4);
  rb_define_protected_method (rplot, "fmarker", fmarker, 4);
  rb_define_protected_method (rplot, "markerrel", markerrel, 4);
  rb_define_protected_method (rplot, "fmarkerrel", fmarkerrel, 4);
  rb_define_protected_method (rplot, "point", point, 2);
  rb_define_protected_method (rplot, "fpoint", fpoint, 2);
  rb_define_protected_method (rplot, "pointrel", pointrel, 2);
  rb_define_protected_method (rplot, "fpointrel", fpointrel, 2);
  /* Attribute-setting functions */
  rb_define_protected_method (rplot, "capmod", capmod, 1);
  rb_define_protected_method (rplot, "color", color, 3);
  rb_define_protected_method (rplot, "colorname", colorname, 1);
  rb_define_protected_method (rplot, "fillcolor", fillcolor, 3);
  rb_define_protected_method (rplot, "fillcolorname", fillcolorname, 1);
  rb_define_protected_method (rplot, "fillmod", fillmod, 1);
  rb_define_protected_method (rplot, "filltype", filltype, 1);
  rb_define_protected_method (rplot, "fmiterlimit", fmiterlimit, 1);
  rb_define_protected_method (rplot, "fontname", fontname, 1);
  rb_define_protected_method (rplot, "ffontname", ffontname, 1);
  rb_define_protected_method (rplot, "fontsize", fontsize, 1);
  rb_define_protected_method (rplot, "ffontsize", ffontsize, 1);
  rb_define_protected_method (rplot, "joinmod", joinmod, 1);
  rb_define_protected_method (rplot, "linedash", linedash, 3);
  rb_define_protected_method (rplot, "flinedash", flinedash, 3);
  rb_define_protected_method (rplot, "linemod", linemod, 1);
  rb_define_protected_method (rplot, "linewidth", linewidth, 1);
  rb_define_protected_method (rplot, "flinewidth", flinewidth, 1);
  rb_define_protected_method (rplot, "move", move, 2);
  rb_define_protected_method (rplot, "fmove", fmove, 2);
  rb_define_protected_method (rplot, "moverel", moverel, 2);
  rb_define_protected_method (rplot, "fmoverel", fmoverel, 2);
  rb_define_protected_method (rplot, "pencolor", pencolor, 3);
  rb_define_protected_method (rplot, "pencolorname", pencolorname, 1);
  rb_define_protected_method (rplot, "restorestate", restorestate, 0);
  rb_define_protected_method (rplot, "savestate", savestate, 0);
  rb_define_protected_method (rplot, "textangle", textangle, 1);
  rb_define_protected_method (rplot, "ftextangle", ftextangle, 1);
  /* Mapping functions */
  rb_define_protected_method (rplot, "fconcat", fconcat, 6);
  rb_define_protected_method (rplot, "frotate", frotate, 1);
  rb_define_protected_method (rplot, "fscale", fscale, 2);
  rb_define_protected_method (rplot, "ftranslate", ftranslate, 2);
}

