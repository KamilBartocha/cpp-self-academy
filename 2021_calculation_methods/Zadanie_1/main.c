#include <stdio.h>
#include <stdlib.h>
#include "disnrutil.h"

typedef struct interp {
    double y0, y1;
    double x0, x1, x2, x3;
    double alpha, beta;
    double **z;
}INTERP;

void test_wczytywania (INTERP *p);
int main(void);
double u(double x, double y, INTERP *p);
//double v(double x, double y, INTERP *p);
double fi(int i, double u, INTERP *p);



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
//double v(double x, double y, INTERP *p) {
//    double licznik, mianownik;
//    licznik = x*(p->y1 - p->y0) + y*(p->x0 - p->x1) + p->x1 * p->y0 - p->x0 * p->y1;
//    mianownik = y * (p->x0 - p->x1 + p->x2 - p->x3) + p->y0 * (p->x1 - p->x2) + p->y1 * (p->x3 - p->x0);
//    return licznik / mianownik;
//}
double fi(int i, double u, INTERP *p){
    switch(i){
        case 1: (u - 1.0 + p->beta)*(u - 1.0)/(1 - p->beta); break;
        case 2: u * (u - 1) / (p->beta*(p->beta - 1.0));     break;
        case 3: u * (u - 1.0 + p->beta) / p->beta;           break;
    }
}
//double psi(int i, double u, INTERP *p){
//    switch(i){
//        case 1: (u - 1.0 + p->beta)*(u - 1.0)/(1 - p->beta); break;
//        case 2: u * (u - 1) / (p->beta*(p->beta - 1.0));     break;
//        case 3: u * (u - 1.0 + p->beta) / p->beta;           break;
//    }
//}

double dLu(double u, double v, INTERP *p){
    int i, j;
    double suma=0.0;
    for(i=1; i<=3; i++){
        for(j=1; j<=3; j++)
            suma+=p->z[i][j]*fip(i,u,p)*psi(j,v,p);
    }
    return suma;
}

double dLv(double u, double v, INTERP *p){
    int i, j;
    double suma=0.0;
    for(i=1; i<=3; i++){
        for(j=1; j<=3; j++)
            suma+=p->z[i][j]*fi(i,u,p)*psip(j,v,p);
    }
    return suma;
}

int main(void) {
    INTERP q;
    FILE *fp;
    fp = fopen("dane_interpolacja.txt", "rt");
    fscanf(fp, "%lf %lf %lf ", &q.y0, &q.x0, &q.x3);
    fscanf(fp, "%lf %lf %lf ", &q.y1, &q.x1, &q.x2);
    fscanf(fp, "%lf %lf ", &q.alpha, &q.beta);
    q.z = dmatrix(1, 3, 1, 3);
    fscanf(fp, "%lf %lf %lf ", &q.z[1][1], &q.z[1][2], &q.z[1][3]);
    fscanf(fp, "%lf %lf %lf ", &q.z[2][1], &q.z[2][2], &q.z[2][3]);
    fscanf(fp, "%lf %lf %lf ", &q.z[3][1], &q.z[3][2], &q.z[3][3]);
    fclose(fp);

    test_wczytywania(&q);

    return 0;
}