#include <stdio.h>
#include <stdlib.h>
#include "disnrutil.h"

typedef struct interp {
    double y0, y1;
    double x0, x1, x2, x3;
    double alpha, beta;
    double **z;
    double xs, ys;
    double Hx, Hy;
}INTERP;

void oblicz_pkt_centralny(INTERP *p);
void test_wczytywania (INTERP *p);
int main(void);
double u(double x, double y, INTERP *p);
double v(double x, double y, INTERP *p);
double H(double x, double y, INTERP *p);
double L(double u, double v, INTERP *p);
double fi(int i, double u, INTERP *p);
double psi(int i, double v, INTERP *p);
double fi_p(int i, double u, INTERP *p);
double psi_p(int i, double v, INTERP *p);
double dLu(double u, double v, INTERP *p);
double dLv(double u, double v, INTERP *p);
void oblicz_pochodne_H(INTERP *p);
double ux(double x, double y, INTERP *p);
double uy(double x, double y, INTERP *p);

double uy(double x, double y, INTERP *p){
    double licznik, mianownik;
    licznik = (x * (p->x0 - p->x1 + p->x2 - p->x3) + p->x1 * p->x3 - p->x0 * p->x2) * (p->y0 - p->y1);
    mianownik = (y - p->y0) * (p->x2 - p->x1) + (y - p->y1) * (p->x0 - p->x3);
    mianownik *= mianownik;
    return licznik / mianownik;
}


double ux(double x, double y, INTERP *p){
    double licznik, mianownik;
    licznik = p->y0 - p->y1;
    mianownik = (y - p->y0) * (p->x1 - p->x2) + (y - p->y1) * (p->x3 - p->x0);
    return licznik / mianownik;
}

void oblicz_pochodne_H(INTERP *p){
    p->Hx = dLu(1 - p->beta, 1 - p->alpha, p) * ux(p->xs, p->ys, p);
    p->Hy = dLu(1 - p->beta, 1 - p->alpha, p) * uy(p->xs, p->ys, p)
    + dLv(1 - p->beta, 1- p->alpha, p) / (p->y1 - p->y0);
    printf("xs = %lf, ys = %lf, Hx = %lf, Hy = %lf\n", p->xs, p->ys, p->Hx, p->Hy);
    fflush(stdin);
    getchar();
}


void oblicz_pkt_centralny(INTERP *p){
    double tmpx1, tmpx2, tmpy1, tmpy2;
    tmpx1 = p->alpha*p->x0+(1.0-p->alpha)*p->x1;
    tmpx2 = p->alpha*p->x3+(1.0-p->alpha)*p->x2;
    p->xs = p->beta*tmpx1+(1.0-p->beta)*tmpx2;

    tmpy1 = p->alpha*p->y0+(1.0-p->alpha)*p->y1;
    tmpy2 = p->alpha*p->y0+(1.0-p->alpha)*p->y1;
    p->ys = p->beta*tmpy1+(1.0-p->beta)*tmpy2;
}



void test_wczytywania(INTERP *p) {
    printf("%lf %lf %lf \n", p->y0, p->x0, p->x3);
    printf("%lf %lf %lf \n", p->y1, p->x1, p->x2);
    printf("%lf %lf \n", p->alpha, p->beta);
    printf("%lf %lf %lf \n", p->z[1][1], p->z[1][2], p->z[1][3]);
    printf("%lf %lf %lf \n", p->z[2][1], p->z[2][2], p->z[2][3]);
    printf("%lf %lf %lf \n", p->z[3][1], p->z[3][2], p->z[3][3]);

    fflush(stdin);
    getchar();
}

double u(double x, double y, INTERP *p) {
    double licznik, mianownik;
    licznik = x*(p->y1 - p->y0) + y*(p->x0 - p->x1) + p->x1 * p->y0 - p->x0 * p->y1;
    mianownik = y * (p->x0 - p->x1 + p->x2 - p->x3) + p->y0 * (p->x1 - p->x2) + p->y1 * (p->x3 - p->x0);
    return licznik / mianownik;
}

double v(double x, double y, INTERP *p) {
    double licznik, mianownik;
    licznik = y - p->y0;
    mianownik = p->y1 - p->y0;
    return licznik / mianownik;
}

double fi(int i, double u, INTERP *p){
    switch(i){
        case 1: return (u - 1.0 + p->beta)*(u - 1.0)/(1 - p->beta); break;
        case 2: return  u * (u - 1) / (p->beta*(p->beta - 1.0));     break;
        case 3: return u * (u - 1.0 + p->beta) / p->beta;           break;
    }
}
double psi(int i, double v, INTERP *p){
    switch(i){
        case 1: return (v - 1.0 + p->alpha)*(v - 1.0)/(1.0 - p->alpha); break;
        case 2: return v * (v - 1) / (p->alpha*(p->alpha - 1.0));     break;
        case 3: return v * (v - 1.0 + p->alpha) / p->alpha;           break;
    }
}
double fi_p(int i, double u, INTERP *p){
    switch(i){
        case 1: return (2.0*u - 2.0 + p->beta)/(1 - p->beta); break;
        case 2: return  (2.0*u-1.0) / (p->beta*(p->beta - 1.0));     break;
        case 3: return (2.0*u - 1.0 + p->beta) / p->beta;           break;
    }
}
double psi_p(int i, double v, INTERP *p){
    switch(i){
        case 1: return (2.0*v - 2.0 + p->alpha)/(1 - p->alpha); break;
        case 2: return  (2.0*v-1.0) / (p->alpha*(p->alpha - 1.0));     break;
        case 3: return (2.0*v - 1.0 + p->alpha) / p->alpha;           break;
    }
}

double H(double x, double y, INTERP *p){
    return L(u(x,y,p), v(x,y,p), p);
}

double L(double u, double v, INTERP *p){
    int i, j;
    double suma=0.0;
    for(i=1; i<=3; i++){
        for(j=1; j<=3; j++)
            suma+=p->z[i][j]*fi(i,u,p)*psi(j,v,p);
    }
    return suma;
}

double dLu(double u, double v, INTERP *p){
    int i, j;
    double suma=0.0;
    for(i=1; i<=3; i++){
        for(j=1; j<=3; j++)
            suma+=p->z[i][j]*fi_p(i,u,p)*psi(j,v,p);
    }
    return suma;
}

double dLv(double u, double v, INTERP *p){
    int i, j;
    double suma=0.0;
    for(i=1; i<=3; i++){
        for(j=1; j<=3; j++)
            suma+=p->z[i][j]*fi(i,u,p)*psi_p(j,v,p);
    }
    return suma;
}

int main(void) {
    INTERP q;
    FILE *fp;
    fp = fopen("dane_interpolacja.txt", "rt");
//    Checking if file does exists
    if(fp == NULL){
        printf("Nie ma pliku");
        fflush(stdin);
        getchar();
    }

    printf("DANE: \n");
    fscanf(fp, "%lf %lf %lf ", &q.y0, &q.x0, &q.x3);
    fscanf(fp, "%lf %lf %lf ", &q.y1, &q.x1, &q.x2);
    fscanf(fp, "%lf %lf ", &q.alpha, &q.beta);
    q.z = dmatrix(1, 3, 1, 3);
    fscanf(fp, "%lf %lf %lf ", &q.z[1][1], &q.z[1][2], &q.z[1][3]);
    fscanf(fp, "%lf %lf %lf ", &q.z[2][1], &q.z[2][2], &q.z[2][3]);
    fscanf(fp, "%lf %lf %lf ", &q.z[3][1], &q.z[3][2], &q.z[3][3]);
    fclose(fp);

    test_wczytywania(&q);
    printf("punkt centralny, pochodne H: \n");
    oblicz_pkt_centralny(&q);
    oblicz_pochodne_H(&q);


    return 0;
}
