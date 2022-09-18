#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "grafika.h"
#include "gs_lin.h"
#include "disnrutil.h"

typedef struct rF{
double a,b;	                                        // dziedzina rownania
double (*f)(double), (*p)(double), (*q)(double);    // funkcje w rownaniu
double u_a,u_b;
int N, M;                                           // N - liczba przedzialow na odcinku [0,1]; M=2*N
double h;                                           // h=1/N
double *x;                                          // tablica wezlow
double **ksi;                                       // macierz wezlow kollokacji, czyli wezlow kwadratur Gaussa-Legendrea
double **mac,*lambda;                               // macierz ukladu, wektor prawych stron = rozwi¹zanie
double ar,br,cr,dr;   								// narozniki okna graficznego
double *odc, *wart;
}RF;

double ef(double x);
double pe(double t);
double qu(double t);
void zainicjuj_RF(RF *s);
void rozwiaz(RF *q);
void zwolnij_pamiec(RF *s);
void inicjuj_grafike_czysc_SP(RF *q);
void okno_osie_SP(RF *q);
void narysuj_SP(RF *q);
double Phi(double arg, int i, RF *s);
double Psi(double arg, int i, RF *s);
double Phi_prim(double arg, int i, RF *s);
double Psi_prim(double arg, int i, RF *s);
double Phi_bis(double arg, int i, RF *s);
double Psi_bis(double arg, int i, RF *s);
double PhiD(double arg, int i, RF *s);             // baza funkcji sklejanych
double PhiD_prim(double arg, int i, RF *s);
double PhiD_bis(double arg, int i, RF *s);
int parzysta(int m);
void test_PhiD(RF *s);                             // testuje kolejnosc wybierania elementow bazy
void narysuj_baze(RF *s);                          // rysuje funkcje bazowe
void narysuj_baze_prim(RF *s);
void narysuj_baze_bis(RF *s);
double um(double xx, RF *s);                       // rozwiazanie
void utworz_macierz_ukladu(RF *s);                 // tworzy macierz ukladu
int index(int i, int l);                           // indeksuje wezly kolokacji
void oblicz_prawa_strone(RF *s);                   // oblicza prawa strone ukladu
void test_uklad(RF *s);                            // wypisuje do pliku macierz i prawa strone ukladu r. liniowych


int main(void) {
	RF q;
	zainicjuj_RF(&q);
	//test_PhiD(&q);              // test "wybierania" funkcji bazowych
	//narysuj_baze(&q);
	//narysuj_baze_prim(&q);
	//narysuj_baze_bis(&q);
    rozwiaz(&q);
	zwolnij_pamiec(&q);
	return 0;
}

void zainicjuj_RF(RF *s){
	int j,i ;
	double sq3,margines;
	FILE *fp;
	s->a=-1.0;
	s->b=2.0;
	margines=(s->b-s->a)/30.0;
	s->ar=s->a-margines;
	s->br=s->b+margines;
	s->cr=-0.1;
	s->dr=1.1;
	s->f=ef;      // prawa strona
	s->p=pe;      // wspolczynnik rownania
	s->q=qu;      // wspolczynnik rownania
	s->u_a=2.0;
	s->u_b=5.0;
	s->N=10;
	s->M=2*s->N;
	s->h=(s->b-s->a)/s->N;
	s->x= dvector(0, s->N);
	for(i=0;i<=s->N;s->x[i]=s->a+i*s->h,i++);
	s->ksi=dmatrix(1,s->N,1,2);  // wezly kwadratur Gaussa-Legendrea
	sq3=sqrt(3.0)/3.0;
	for(i=1;i<=s->N;i++){
		s->ksi[i][1]=s->x[i-1]+0.5*s->h*(1.0-sq3);
		s->ksi[i][2]=s->x[i-1]+0.5*s->h*(1.0+sq3);
	}

	fp=fopen("weryfikacja.txt","wt");
	fprintf(fp,"a=%lf b=%lf\n",s->a,s->b);
	fprintf(fp,"u_a=%lf u_b=%lf\n",s->u_a,s->u_b);
	fprintf(fp,"ar=%lf br=%lf cr=%lf dr=%lf\n",s->ar,s->br,s->cr,s->dr);
	fprintf(fp,"N=%d M=%d\n",s->N,s->M);
	fprintf(fp,"h=%lf\n",s->h);
	fprintf(fp,"x:\n");
	for(i=0;i<=s->N;i++){
		fprintf(fp,"%lf ",s->x[i]);
	}
	fprintf(fp,"\nksi\n");
		for(i=1;i<=s->N;i++){
		fprintf(fp,"%lf %lf\n",s->ksi[i][1],s->ksi[i][2]);
	}
    fclose(fp);

	s->mac=dmatrix(1,s->M,1,s->M);
	s->lambda=dvector(1,s->M);
	utworz_macierz_ukladu(s);
}

double um(double xx, RF *s){
    double temp=0.0;
    int i;
    for(i=1;i<=s->M;i++){
    	temp+=s->lambda[i]*PhiD(xx,i,s);
	}
	temp+=(s->u_a+(s->u_b-s->u_a)*(xx-s->a)/(s->b-s->a));
	return temp;
}


void utworz_macierz_ukladu(RF *s){      // macierz ukladu
	int i,l,j,m,r,c;
	for(i=1;i<=s->N;i++){
		for(l=1;l<=2;l++){
			r=index(i,l);
			for(j=1;j<=s->N;j++){
				for(m=1;m<=2;m++){
					c=index(j,m);
					s->mac[r][c]=PhiD_bis(s->ksi[i][l],c,s)+(*s->p)(s->ksi[i][l])*PhiD_prim(s->ksi[i][l],c,s)+(*s->q)(s->ksi[i][l])*PhiD(s->ksi[i][l],c,s);
					}
			}
		}
	}

}

void oblicz_prawa_strone(RF *s){ // prawa strona ukladu przy wyliczaniu wspolczynnikow
	int i,l,r;                   // kombinacji rozwiazania
	for(i=1; i<=s->N; i++){
		for(l=1; l<=2; l++){
			r=index(i, l);
			s->lambda[r]=(*s->f)(s->ksi[i][l])-(*s->p)(s->ksi[i][l])*(s->u_b-s->u_a)/(s->b-s->a)-(*s->q)(s->ksi[i][l])*(s->u_a+(s->u_b-s->u_a)*(s->ksi[i][l]-s->a)/(s->b-s->a));
		}
	}
}

int index(int i, int l){
	return 2*(i-1)+l;
}

void zwolnij_pamiec(RF *s){
	free_dvector(s->x,0, s->N);
	free_dmatrix(s->ksi,1,s->N,1,2);
	free_dmatrix(s->mac,1,s->M,1,s->M);
	free_dvector(s->lambda,1,s->M);
}

void rozwiaz(RF *s){
	int i,n;
	FILE *f;
	int *indx;
	double d,w_u;
	f=fopen("wynik_kolokacja2.txt", "wt");
	fclose(f);
	f = fopen("wynik_kolokacja2.txt", "at");
	inicjuj_grafike_czysc_SP(s);
	okno_osie_SP(s);
	oblicz_prawa_strone(s);
	test_uklad(s);
	indx=ivector(1,s->M);
	ludcmp(s->mac,s->M,indx,&d);
	lubksb(s->mac,s->M,indx,s->lambda);
	free_ivector(indx,1,s->M);
	s->cr=0.0; s->dr=0.0;
	n = 200;
	d = (s->b - s->a) / n;
	for (i = 0; i <= n; i++)
	{
		w_u = um(s->a + i*d, s);
		fprintf(f, "%lf %lf \n", s->a + i*d, w_u);
		if(w_u < s->cr) s->cr = w_u;
		if(w_u > s->dr) s->dr = w_u;
	}
	fclose(f);

 	narysuj_SP(s);
	GrKeyRead();
}

double ef(double x){
	return 2.0+2.0*x*cos(x)+(x*x+1.0)*sin(x);
}

double pe(double x){
	return cos(x);
}
double qu(double x){
	return sin(x);
}

void test_uklad(RF *s){
	int r,c;
	FILE *fp;
	fp=fopen("test_uklad.txt","wt");

    for(r=1;r<=s->M;r++){
    	for(c=1;c<=s->M;c++){
    		fprintf(fp,"%lf ",s->mac[r][c]);
		}
		fprintf(fp," | %lf\n",s->lambda[r]);
	}
	fclose(fp);
}

double Phi(double arg, int i, RF *s){
	double xm,xw,temp,wart=0.0;
	xm=s->x[i]-s->h;
	xw=s->x[i]+s->h;
	if((arg <= s->x[i])&&(arg >= xm)){
		temp=arg-xm;
		wart=temp*temp*(-2.0*temp/s->h+3.0)/(s->h*s->h);
	}
	if((arg <= xw)&&(arg >= s->x[i])){
		temp=arg-xw;
		wart=temp*temp*(2.0*temp/s->h+3.0)/(s->h*s->h);
	}
  return wart;
}

double Psi(double arg, int i, RF *s){
	double xm,xw,temp,wart=0.0;
	xm=s->x[i]-s->h;
	xw=s->x[i]+s->h;
	if((arg <= s->x[i])&&(arg >= xm)){
		temp=arg-xm;
		wart=temp*temp*(arg-s->x[i])/(s->h*s->h);
	}
	if((arg <= xw)&&(arg >= s->x[i])){
		temp=arg-xw;
		wart=temp*temp*(arg-s->x[i])/(s->h*s->h);
	}
  return wart;
}

double Phi_prim(double arg, int i, RF *s){
	double xm,xw,temp,wart=0.0;
	xm=s->x[i]-s->h;
	xw=s->x[i]+s->h;
	if((arg <= s->x[i])&&(arg >= xm)){
		temp=arg-xm;
		wart=6.0*temp*(1.0-temp/s->h)/(s->h*s->h);
	}
	if((arg <= xw)&&(arg >= s->x[i])){
		temp=arg-xw;
		wart=6.0*temp*(1.0+temp/s->h)/(s->h*s->h);
	}
  return wart;
}

double Psi_prim(double arg, int i, RF *s){
	double xm,xw,temp,wart=0.0;
	xm=s->x[i]-s->h;
	xw=s->x[i]+s->h;
	if((arg <= s->x[i])&&(arg >= xm)){
		temp=arg-xm;
		wart=temp*(3.0*arg-2.0*s->x[i]-xm)/(s->h*s->h);
	}
	if((arg <= xw)&&(arg >= s->x[i])){
		temp=arg-xw;
		wart=temp*(3.0*arg-2.0*s->x[i]-xw)/(s->h*s->h);
	}
  return wart;
}

double Phi_bis(double arg, int i, RF *s){
	double xm,xw,temp,wart=0.0;
	xm=s->x[i]-s->h;
	xw=s->x[i]+s->h;
	if((arg <= s->x[i])&&(arg >= xm)){
		temp=arg-xm;
		wart=6.0*(-2.0*temp/s->h+1.0)/(s->h*s->h);
	}
	if((arg <= xw)&&(arg >= s->x[i])){
		temp=arg-xw;
		wart=6.0*(2.0*temp/s->h+1.0)/(s->h*s->h);
	}
  return wart;
}

double Psi_bis(double arg, int i, RF *s){
	double xm,xw,wart=0.0;
	xm=s->x[i]-s->h;
	xw=s->x[i]+s->h;
	if((arg <= s->x[i])&&(arg >= xm)){
		wart=2.0*(3.0*arg-s->x[i]-2.0*xm)/(s->h*s->h);
	}
	if((arg <= xw)&&(arg >= s->x[i])){
		wart=2.0*(3.0*arg-s->x[i]-2.0*xw)/(s->h*s->h);
	}
  return wart;
}

double PhiD(double arg, int i, RF *s){        // baza
	if(i==1)       return Psi(arg,0,s);
	if(i==s->M)    return Psi(arg,s->N,s);
	if((i>1)&&(i<s->M)){
	if(parzysta(i))return Phi(arg,i/2,s);
	else           return Psi(arg,i/2,s);
   }
}

double PhiD_prim(double arg, int i, RF *s){    // pierwsze pochodne bazy
	if(i==1)       return Psi_prim(arg,0,s);
	if(i==s->M)    return Psi_prim(arg,s->N,s);
	if((i>1)&&(i<s->M)){
	if(parzysta(i))return Phi_prim(arg,i/2,s);
	else           return Psi_prim(arg,i/2,s);
   }
}

double PhiD_bis(double arg, int i, RF *s){    // drugie pochodne bazy
	if(i==1)       return Psi_bis(arg,0,s);
	if(i==s->M)    return Psi_bis(arg,s->N,s);
	if((i>1)&&(i<s->M)){
	if(parzysta(i))return Phi_bis(arg,i/2,s);
	else           return Psi_bis(arg,i/2,s);
   }
}

void test_PhiD(RF *s){
	FILE *fp;
	int i;
	fp=fopen("test_PhiD.txt","wt");
	for(i=1;i<=s->M;i++){
	if(i==1)        fprintf(fp,"Psi %d\n",0);
	if(i==s->M)     fprintf(fp,"Psi %d\n",s->N);
	if((i>1)&&(i<s->M)){
	if(parzysta(i)) fprintf(fp,"Phi %d\n",i/2);
	else            fprintf(fp,"Psi %d\n",i/2);
    }
   }

  fclose(fp);
}

int parzysta(int m){
	if((m/2)*2==m)return 1;
	else          return 0;
}

void inicjuj_grafike_czysc_SP(RF *q)
 {
 	Initialize();
 	GrClearScreen(GrWhite());
 	_setwindow(0,q->ar,q->cr,q->br,q->dr);
 }

void okno_osie_SP(RF *q)
 {
 	//GrClearScreen(GrWhite());
    _osx_w(q->ar,q->br,GrBlack());
    _osy_w(q->cr,q->dr,GrBlack());
 }

void narysuj_SP(RF *q)
  {
  	GrColor koloru,kolorv,kolorw;
  	int i,n;
  	double d;
  	inicjuj_grafike_czysc_SP(q);
	okno_osie_SP(q);
	 n=200;
	 d=(q->b-q->a)/n;
  	koloru=GrAllocColor(255,0,0); kolorv=GrAllocColor(0,255,0); kolorw=GrAllocColor(0,0,255);
  	   for(i=0;i<n;i++)_line_w(q->a+i*d,um(q->a+i*d,q),q->a+(i+1.0)*d,um(q->a+(i+1.0)*d,q),koloru);
  }

void narysuj_baze(RF *s){                         // ilustracja funkcji bazowych
	int i,j,n=500;
	double h, *w;
	GrColor kolor;
	inicjuj_grafike_czysc_SP(s);
	okno_osie_SP(s);
	h=(s->b-s->a)/n;
	w=dvector(0,n);
	for(i=0;i<=n;w[i]=s->a+i*h,i++);
	for(j=1;j<=s->M;j++){
	  if(j==1)        kolor=GrAllocColor(255,0,0);
	  if(j==s->M)     kolor=GrAllocColor(255,0,0);
	  if((j>1)&&(j<s->M)){
	  if(parzysta(j)) kolor=GrAllocColor(0,0,255);
	  else            kolor=GrAllocColor(255,0,0);
      }
		printf("j=%d\n",j);
		for(i=1;i<=n;i++){
			_line_w(w[i-1],PhiD(w[i-1],j,s),w[i],PhiD(w[i],j,s),kolor);
		}
		GrKeyRead();
	}
 GrKeyRead();
}

void narysuj_baze_prim(RF *s){                     // ilustracja drugich pochodnych funkcji bazowych
	int i,j,n=500;
	double h, *w;
	GrColor kolor;
	s->cr=-10.0; s->dr=10.0;
	inicjuj_grafike_czysc_SP(s);
	okno_osie_SP(s);
	h=(s->b-s->a)/n;
	w=dvector(0,n);
	for(i=0;i<=n;w[i]=s->a+i*h,i++);
	for(j=1;j<=s->M;j++){
	  if(j==1)        kolor=GrAllocColor(255,0,0);
	  if(j==s->M)     kolor=GrAllocColor(255,0,0);
	  if((j>1)&&(j<s->M)){
	  if(parzysta(j)) kolor=GrAllocColor(0,0,255);
	  else            kolor=GrAllocColor(255,0,0);
      }
		printf("j=%d\n",j);
		for(i=1;i<=n;i++){
			_line_w(w[i-1],PhiD_prim(w[i-1],j,s),w[i],PhiD_prim(w[i],j,s),kolor);
		}
		GrKeyRead();
	}
 GrKeyRead();
}

void narysuj_baze_bis(RF *s){                     // ilustracja drugich pochodnych funkcji bazowych
	int i,j,n=500;
	double h, *w;
	GrColor kolor;
	s->cr=-160.0; s->dr=160.0;
	inicjuj_grafike_czysc_SP(s);
	okno_osie_SP(s);
	h=(s->b-s->a)/n;
	w=dvector(0,n);
	for(i=0;i<=n;w[i]=s->a+i*h,i++);
	for(j=1;j<=s->M;j++){
	  if(j==1)        kolor=GrAllocColor(255,0,0);
	  if(j==s->M)     kolor=GrAllocColor(255,0,0);
	  if((j>1)&&(j<s->M)){
	  if(parzysta(j)) kolor=GrAllocColor(0,0,255);
	  else            kolor=GrAllocColor(255,0,0);
      }
		printf("j=%d\n",j);
		for(i=1;i<=n;i++){
			_line_w(w[i-1],PhiD_bis(w[i-1],j,s),w[i],PhiD_bis(w[i],j,s),kolor);
		}
		GrKeyRead();
	}
 GrKeyRead();
}


