#include "rplot.h"

static int
get_handler (VALUE self)
{
  int handler = NUM2INT (rb_iv_get (self, "@handler"));
  pl_selectpl (handler);
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
      return 1;
    }
  rb_iv_set (self, "@handler", INT2NUM (handler));
  return self;
}

// No needed
// static VALUE selectpl (VALUE self) {}

static VALUE
deletepl (VALUE self) {
  int handler = get_handler (self);
  //pl_closepl ();
  if (pl_closepl () < 0)
    {
      fprintf (stderr, "Couldn't close Plotter\n");
      return 1;
    }
  pl_selectpl (0);
  pl_deletepl (handler);
  return Qnil;
}

static VALUE
parampl (VALUE self, VALUE param, VALUE value)
{
  pl_parampl (StringValuePtr (param), (void*)(StringValuePtr (value)));
  return Qnil;
}

/* Setup functions */

static VALUE
openpl (VALUE self)
{
  return INT2FIX (pl_openpl ());
}

static VALUE
bgcolor (VALUE self, VALUE red, VALUE green, VALUE blue)
{
  return INT2FIX (pl_bgcolor (FIX2INT (red),
                              FIX2INT (red),
                              FIX2INT (red)));
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
  return INT2FIX (pl_closepl ());
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
test (VALUE self) {

  int angle = 0;

  /* create an X Plotter with the specified parameters */
  int handler = NUM2INT (rb_iv_get (self, "@handler"));
  printf ("handler: %d\n---\n", handler);
  pl_selectpl (handler);

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
Init_rplot()
{
  VALUE rplot = rb_define_class("Rplot", rb_cObject);
  rb_define_method(rplot, "initialize", newpl, 4);
  rb_define_method(rplot, "delete", deletepl, 0);
  rb_define_singleton_method(rplot, "set_param", parampl, 2);

  rb_define_method(rplot, "test", test, 0);
}

