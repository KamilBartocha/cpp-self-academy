/**********************************************
 * grafika.h - zbior naglowkowy dla grafika.c *
 **********************************************/
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define BGI_PATH "\\usr\\local\\"
#include <libbcc.h>
#include <bgiext.h>
#include <grx20.h>
#include <grxkeys.h>
#include <grfontdv.h>
#define Random(r) (random() % (r))
#define Seed(s) srandom(s)
#define itoa(value,str,radix) sprintf((str),"%d",(value))
//#define getch() getkey()

typedef struct tag_double_okno
        {
        double d_tx;
        double d_cx;
        double d_ty;
        double d_cy;
        } double_okno;

extern char PauseMsg[];
extern char StopMsg[];

#define ESC     0x1b                    
#ifndef TRUE
#  define TRUE  1                       
#endif
#ifndef FALSE
#  define FALSE 0                       
#endif
#ifndef PI
#  define PI    3.141592653589793238    
#endif
#define ON      1                       
#define OFF     0                       

#ifndef NFONTS
 #define NFONTS 11
#endif

void Initialize(void);
void _setviewport(int lewy, int prawy, int gora, int dol);
void _setwindow_viewport(int flaga, double x_l, double y_g, double x_p, double y_d);
void _setwindow(int flaga, double x_l, double y_g, double x_p, double y_d);
void _setwindow_konior(int flaga, double x_l, double y_g, double x_p, double y_d,int x_min,int y_min,int x_max,int y_max);
void _line_w(double x1, double y1, double x2, double y2, GrColor kolor) ;
void _rectangle_w(double   x1, double y1, double x2, double y2, GrColor kolor);
void _setpixel_w( double x1, double y1, GrColor kolor);
void _ellipse_w(double x1, double y1, double x2, double y2,  GrColor kolor);
void _osx_w(double x1, double x2, GrColor kolor);
void _osy_w(double y1, double y2, GrColor kolor);
void napis_w(double x1, double y1, GrFont *font, char *text, int len, GrColor kolor);
void napis_w_gore_w(double x1, double y1, GrFont *font, char *text, int len, GrColor kolor);
void napis(int cx, int cy, GrFont *font, char *text, int len, GrColor kolor);
void DisplayTekscik( char *tekscik, GrColor color, GrFont *font);
void DisplayTitle(char *tekscik, GrColor color);
void ZrobNapis(double px, double py, int font, int wielkosc, int *kolor, char *napis);
void _setcolor(GrColor kolor);

#define Pause() NewPause(TRUE)

