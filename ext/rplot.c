/***********************************************************
 * Copyright (C) 2011 Enrico Pilotto (enrico@megiston.it)
 *
 * Binding all functions of C libplot in 'Rplot' Ruby class.
 ***********************************************************/

#include "rplot.h"

#define CREATE_PLOTTER_ERROR -1
#define SELECT_PLOTTER_ERROR -2
#define OPEN_PLOTTER_ERROR   -3
#define CLOSE_PLOTTER_ERROR  -4
#define DELETE_PLOTTER_ERROR -5
#define OPERATION_ERROR      -6

static int
get_handler (VALUE self)
{
  int handler = NUM2INT (rb_iv_get (self, "@handler"));
  if (pl_selectpl (handler) < 0)
    {
      fprintf (stderr, "Couldn't select Plotter\n");
      return SELECT_PLOTTER_ERROR;
    }
  return handler;
}

// BINDING
///////////

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
    {
      fprintf (stderr, "Couldn't create Plotter\n");
      return INT2FIX (CREATE_PLOTTER_ERROR);
    }
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
  if (pl_closepl () < 0)
    {
      fprintf (stderr, "Couldn't close Plotter\n");
      return INT2FIX (CLOSE_PLOTTER_ERROR);
    }
  pl_selectpl (0);
  if (pl_deletepl (handler) < 0)
    {
      return INT2FIX (DELETE_PLOTTER_ERROR);
    }
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
  if (pl_openpl () < 0)
    fprintf (stderr, "Couldn't open Plotter\n");
  return INT2FIX (OPEN_PLOTTER_ERROR);
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
  if (pl_closepl () < 0)
    fprintf (stderr, "Couldn't close Plotter\n");
  return INT2FIX (CLOSE_PLOTTER_ERROR);
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

/* TEST FUNCTIONS */

static VALUE
test (VALUE self) {

  int angle = 0;

  /* create an X Plotter with the specified parameters */
  int handler = get_handler (self);
  printf ("handler: %d\n---\n", handler);

  /* open X Plotter, initialize coordinates, pen, and font */
  if (pl_openpl () < 0)
    {
      fprintf (stderr, "Couldn't open Plotter\n");
      return 1;
    }
  pl_fspace (0.0, 0.0, 1.0, 1.0);  /* use normalized coordinates */
  pl_pencolorname ("red");
  pl_ffontsize (1.0);
  //pl_fontname ("NewCenturySchlbk-Roman");

  pl_fmove (.50,.50);           /* move to center */
  int i = 0;
  while (i < 100)                     /* loop endlessly */
    {
      pl_erase ();
      pl_textangle (angle++);      /* set new rotation angle */
      pl_alabel ('c', 'c', "A");   /* draw a centered `A' */
      i++;
    }
  return Qnil;
}

void
Init_rplot ()
{
  VALUE rplot = rb_define_class ("Rplot", rb_cObject);
  rb_define_method (rplot, "initialize", newpl, 4);
  rb_define_method (rplot, "delete", deletepl, 0);
  rb_define_singleton_method (rplot, "param", parampl, 2);
  /* Setup functions */
  rb_define_method (rplot, "open", openpl, 0);
  rb_define_method (rplot, "bgcolor", bgcolor, 3);
  rb_define_method (rplot, "bgcolorname", bgcolorname, 1);
  rb_define_method (rplot, "erase", erase, 0);
  rb_define_method (rplot, "space", space, 4);
  rb_define_method (rplot, "fspace", fspace, 4);
  rb_define_method (rplot, "space2", space2, 6);
  rb_define_method (rplot, "fspace2", fspace2, 6);
  rb_define_method (rplot, "havecap", havecap, 1);
  rb_define_method (rplot, "flush", flushpl, 0);
  rb_define_method (rplot, "close", closepl, 0);
  /* Object-drawing functions */
  rb_define_method (rplot, "alabel", alabel, 3);
  rb_define_method (rplot, "arc", arc, 6);
  rb_define_method (rplot, "farc", farc, 6);
  rb_define_method (rplot, "arcrel", arcrel, 6);
  rb_define_method (rplot, "farcrel", farcrel, 6);
  rb_define_method (rplot, "bezier2", bezier2, 6);
  rb_define_method (rplot, "fbezier2", fbezier2, 6);
  rb_define_method (rplot, "bezier2rel", bezier2rel, 6);
  rb_define_method (rplot, "fbezier2rel", fbezier2rel, 6);
  rb_define_method (rplot, "bezier3", bezier3, 8);
  rb_define_method (rplot, "fbezier3", fbezier3, 8);
  rb_define_method (rplot, "bezier3rel", bezier3rel, 8);
  rb_define_method (rplot, "fbezier3rel", fbezier3rel, 8);
  rb_define_method (rplot, "box", box, 4);
  rb_define_method (rplot, "fbox", fbox, 4);
  rb_define_method (rplot, "boxrel", boxrel, 4);
  rb_define_method (rplot, "fboxrel", fboxrel, 4);
  rb_define_method (rplot, "circle", circle, 3);
  rb_define_method (rplot, "fcircle", fcircle, 3);
  rb_define_method (rplot, "circlerel", circlerel, 3);
  rb_define_method (rplot, "fcirclerel", fcirclerel, 3);
  rb_define_method (rplot, "cont", cont, 2);
  rb_define_method (rplot, "fcont", fcont, 2);
  rb_define_method (rplot, "contrel", contrel, 2);
  rb_define_method (rplot, "fcontrel", fcontrel, 2);
  rb_define_method (rplot, "ellarc", ellarc, 6);
  rb_define_method (rplot, "fellarc", fellarc, 6);
  rb_define_method (rplot, "ellarcrel", ellarcrel, 6);
  rb_define_method (rplot, "fellarcrel", fellarcrel, 6);
  rb_define_method (rplot, "ellipse", ellipse, 6);
  rb_define_method (rplot, "fellipse", fellipse, 6);
  rb_define_method (rplot, "ellipserel", ellipserel, 6);
  rb_define_method (rplot, "fellipserel", fellipserel, 6);
  rb_define_method (rplot, "endpath", endpath, 0);
  rb_define_method (rplot, "label", label, 1);
  rb_define_method (rplot, "labelwidth", labelwidth, 1);
  rb_define_method (rplot, "flabelwidth", flabelwidth, 1);
  rb_define_method (rplot, "line", line, 4);
  rb_define_method (rplot, "fline", fline, 4);
  rb_define_method (rplot, "linerel", linerel, 4);
  rb_define_method (rplot, "flinerel", flinerel, 4);
  rb_define_method (rplot, "marker", marker, 4);
  rb_define_method (rplot, "fmarker", fmarker, 4);
  rb_define_method (rplot, "markerrel", markerrel, 4);
  rb_define_method (rplot, "fmarkerrel", fmarkerrel, 4);
  rb_define_method (rplot, "point", point, 2);
  rb_define_method (rplot, "fpoint", fpoint, 2);
  rb_define_method (rplot, "pointrel", pointrel, 2);
  rb_define_method (rplot, "fpointrel", fpointrel, 2);

  rb_define_method (rplot, "test", test, 0);
}

