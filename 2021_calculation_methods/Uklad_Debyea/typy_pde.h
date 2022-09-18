typedef struct sp
 {
 	double a,b,T;
 	double (*wpu)(double x), (*wpv)(double x), (*fil)(double t), (*fip)(double t);
 	double czas;
 	double wsp_lambda,wsp_alpha1,wsp_alpha2,wsp_alpha1w,wsp_alpha2w;
 	int N,M;
 	double h,h2,k,kh2,h2k,k2h;
 	double *x,*Us,*Un, *Vs,*Vn, *Ws,*Wn;
 	FILE *fin,*fout;
 	double ar,br,cr,dr; // narozniki okna rysunku
    double *C0, *C1, *C2, *B;
    double *u;
}SP;

void rozwiaz_TROJDIAG(SP *q, int przypadek);
void rozwiaz_TROJDIAG_Thomas(SP *q, int przypadek);


