/****************************************************
 * plik grafika.c - zawiera pewne funkcje graficzne *
 ****************************************************/
#include "grafika.h"
//#include <grx20.h>
#include <string.h>
int    GraphDriver,GraphMode,MaxX, MaxY,MaxColors,ErrorCode; 
double AspectRatio; 
struct palettetype palette; 
double_okno d_okno;
struct viewporttype vc;
GrContext BB_Gr;

char PauseMsg[] = "Esc aborts or press a key...";
char StopMsg[]  = "ESC Aborts - Press a Key to stop";

/* Inicjalizuje tryb graficzny  */
void Initialize(void)
 {
 GrSetDriver("win32 gw 1024 gh 800 nc 256");
 GrSetMode(GR_custom_graphics,1024,800);
 MaxX=GrMaxX();
 MaxY=GrMaxY();
 }

/* zmienne globalne
struct double_okno
        {
        double d_tx;
        double d_cx;
        double d_ty;
        double d_cy;
        }d_okno; 
struct viewporttype vc; 
*/

void _setviewport(int lewy, int prawy, int gora, int dol)
 {
   vc.left=lewy; vc.right=prawy;
   vc.top=gora; vc.bottom=dol;
   // defaultowe wywolanie: _setviewport(0,GrMaxX(),0,GrMaxY());
 }

void _setwindow_viewport(int flaga, double x_l, double y_g, double x_p, double y_d)
  {
   d_okno.d_tx=((double)(vc.right)-(double)(vc.left))/(x_p-x_l);
   d_okno.d_cx=(x_p*(double)(vc.left)-x_l*(double)(vc.right))/(x_p-x_l);
    if(flaga)
     {
      d_okno.d_ty=((double)(vc.top)-(double)(vc.bottom))/(y_g-y_d);
      d_okno.d_cy=(y_g*(double)(vc.bottom)-y_d*(double)(vc.top))/(y_g-y_d);
     }
    else
     {
      d_okno.d_ty=((double)(vc.bottom)-(double)(vc.top))/(y_g-y_d);
      d_okno.d_cy=(y_g*(double)(vc.top)-y_d*(double)(vc.bottom))/(y_g-y_d);
     }
  }

void _setwindow(int flaga, double x_l, double y_g, double x_p, double y_d)
  {
  /* getviewsettings(&vc); */
   vc.left=0; vc.right=GrMaxX();
   vc.top=0; vc.bottom=GrMaxY();
   d_okno.d_tx=((double)(vc.right)-(double)(vc.left))/(x_p-x_l);
   d_okno.d_cx=(x_p*(double)(vc.left)-x_l*(double)(vc.right))/(x_p-x_l);
    if(flaga)
     {
      d_okno.d_ty=((double)(vc.top)-(double)(vc.bottom))/(y_g-y_d);
      d_okno.d_cy=(y_g*(double)(vc.bottom)-y_d*(double)(vc.top))/(y_g-y_d);
     }
    else
     {
      d_okno.d_ty=((double)(vc.bottom)-(double)(vc.top))/(y_g-y_d);
      d_okno.d_cy=(y_g*(double)(vc.top)-y_d*(double)(vc.bottom))/(y_g-y_d);
     }
  }
  
void _setwindow_k(int flaga, double x_l, double y_g, double x_p, double y_d,int x_min,int y_min,int x_max,int y_max)
  {
/*        getviewsettings(&vc); */
//        vc.left=(GrMaxX()-GrMaxY())/2; vc.right=GrMaxY()+vc.left;
        vc.left=x_min; vc.right=x_max;
        vc.top=y_min; vc.bottom=y_max;
//        vc.top=(GrMaxY()-GrMaxX())/2; vc.top=GrMaxX()+vc.left;

        d_okno.d_tx=((double)(vc.right)-(double)(vc.left))/(x_p-x_l);
        d_okno.d_cx=(x_p*(double)(vc.left)-x_l*(double)(vc.right))/(x_p-x_l);   
        if(flaga)
                {
                d_okno.d_ty=((double)(vc.top)-(double)(vc.bottom))/(y_g-y_d);
                d_okno.d_cy=(y_g*(double)(vc.bottom)-y_d*(double)(vc.top))/(y_g-y_d);   
                }
        else
                {
                d_okno.d_ty=((double)(vc.bottom)-(double)(vc.top))/(y_g-y_d);
                d_okno.d_cy=(y_g*(double)(vc.top)-y_d*(double)(vc.bottom))/(y_g-y_d);   
                }
  }
  
void _line_w(double x1, double y1, double x2, double y2, GrColor kolor)
 {
  GrLine((int)(d_okno.d_tx*x1+ d_okno.d_cx),(int)(d_okno.d_ty*y1+d_okno.d_cy),(int)(d_okno.d_tx*x2+d_okno.d_cx),(int)(d_okno.d_ty*y2+d_okno.d_cy),kolor);
 }

void _rectangle_w(double   x1, double y1, double x2, double y2, GrColor kolor)
	{
	 GrBox((int)(d_okno.d_tx*x1+ d_okno.d_cx),(int)(d_okno.d_ty*y1+d_okno.d_cy),(int)(d_okno.d_tx*x2+d_okno.d_cx),(int)(d_okno.d_ty*y2+d_okno.d_cy),kolor);
	}

void _setpixel_w( double x1, double y1, GrColor kolor)
	{
    GrPlot((int)(d_okno.d_tx*x1+ d_okno.d_cx),(int)(d_okno.d_ty*y1+d_okno.d_cy),kolor);
	}

 void _ellipse_w(double x1, double y1, double x2, double y2,  GrColor kolor)
	{
    GrEllipse((int)(d_okno.d_tx*x1+ d_okno.d_cx),(int)(d_okno.d_ty*y1+d_okno.d_cy),(int)(d_okno.d_tx*x2+d_okno.d_cx),(int)(d_okno.d_ty*y2+d_okno.d_cy),kolor);
	}

void _osx_w(double x1, double x2, GrColor kolor)
	{
    GrHLine((int)(d_okno.d_tx*x1+ d_okno.d_cx),(int)(d_okno.d_tx*x2+d_okno.d_cx),(int)(d_okno.d_cy), kolor);
	}

void _osy_w(double y1, double y2, GrColor kolor)
	{
    GrVLine((int)( d_okno.d_cx),(int)(d_okno.d_ty*y1+d_okno.d_cy),(int)(d_okno.d_ty*y2+d_okno.d_cy),kolor);
	}

void napis_w(double x1, double y1, GrFont *font, char *text, int len, GrColor kolor)
{
	GrTextOption opt;
	unsigned int ww,hh;
	unsigned int bx,by;
	unsigned int bw,bh;
   unsigned int cx,cy;
   cx=(unsigned int)(d_okno.d_tx*x1+ d_okno.d_cx);
	cy=(unsigned int)(d_okno.d_ty*y1+d_okno.d_cy);
	memset(&opt,0,sizeof(opt));
	opt.txo_font   = font;
	opt.txo_xalign = GR_ALIGN_LEFT;
	opt.txo_yalign = GR_ALIGN_TOP;
	opt.txo_direct    = GR_TEXT_RIGHT;
	opt.txo_fgcolor.v = kolor;
	opt.txo_bgcolor.v = GrWhite();
	ww = GrStringWidth(text,len,&opt);
	hh = GrStringHeight(text,len,&opt);
	bw = ww+2*hh;
	bh = hh;
	bx = cx - bw/2;
	by = cy - bh/2;
	GrDrawString(text,len,bx+hh,by,&opt);
}

void napis_w_gore_w(double x1, double y1, GrFont *font, char *text, int len, GrColor kolor)
{
	GrTextOption opt;
	unsigned int ww,hh;
	unsigned int bx,by;
	unsigned int bw,bh;
   unsigned int cx,cy;
   cx=(unsigned int)(d_okno.d_tx*x1+ d_okno.d_cx);
   cy=(unsigned int)(d_okno.d_ty*y1+d_okno.d_cy);
	memset(&opt,0,sizeof(opt));
	opt.txo_font   = font;
	opt.txo_xalign = GR_ALIGN_LEFT;
	opt.txo_yalign = GR_ALIGN_TOP;
	opt.txo_direct    = GR_TEXT_UP;
	opt.txo_fgcolor.v = kolor;
	opt.txo_bgcolor.v = GrWhite();
	ww = GrStringWidth(text,len,&opt);
	hh = GrStringHeight(text,len,&opt);
	bw = ww+2*hh;
	bh = hh;
	bx = cx - bw/2;
	by = cy - bh/2;
	GrDrawString(text,len,bx+hh,by,&opt);
}

void napis(int cx, int cy, GrFont *font, char *text, int len, GrColor kolor)
{
	GrTextOption opt;
	unsigned int ww,hh;
	unsigned int bx,by;
	unsigned int bw,bh;
	memset(&opt,0,sizeof(opt));
	opt.txo_font      = font;
	opt.txo_xalign    = GR_ALIGN_LEFT;
	opt.txo_yalign    = GR_ALIGN_TOP;
	opt.txo_direct    = GR_TEXT_RIGHT;
	opt.txo_fgcolor.v = kolor;
	opt.txo_bgcolor.v = GrWhite();
	ww = GrStringWidth(text,len,&opt);
	hh = GrStringHeight(text,len,&opt);
	bw = ww+2*hh;
	bh = hh;
	bx = cx - bw/2;
	by = cy - bh/2;
	GrDrawString(text,len,bx+hh,by,&opt);
}

void DisplayTekscik( char *tekscik, GrColor color, GrFont *font)
 {
   napis(30,20,font,tekscik,strlen(tekscik),color);
 }
 
void DisplayTitle(char *tekscik, GrColor color)
 {
  GrFont *font;
  font=GrLoadFont("char23b.fnt");
   napis(400,10,font,tekscik,strlen(tekscik),color);
 }
 
void ZrobNapis(double px, double py, int font, int wielkosc, int *kolor, char *napis)
 {
  GrTextXY((int)(d_okno.d_tx*px+d_okno.d_cx)-vc.left,(int)(d_okno.d_ty*py+d_okno.d_cy)-vc.top,napis,GrAllocColor(kolor[1],kolor[2],kolor[3]),GrWhite()); 
 }

void _setcolor(GrColor kolor)
 {
  setcolor(kolor);
 }
 
