#include <stdio.h>
#include <stdlib.h>
#include "disnrutil.h"
#include <math.h>

typedef struct RP{
    double a, b;
    double (*f)(double), (*p)(double), (*q)(double);
    int N;
    double *x, *un;
    double h;
    double *C0, *C1, *C2, *P, *R;
    double u_a,u_b;
}RP;

void rozwiaz_trojdiag_Thomas(RP *q);
void zainicjuj_i_rozwiaz_RP(RP *s);
void zdefiniuj_macierz_R(RP *s);
void zdefiniuj_prawa_strone_S(RP *s);
void zdefiniuj_prawa_strone_S_bis(RP *s);
double calka_Cji(int j, int i, RP *s);
double calka_Cfji(int j, int i, RP *s);
double calka_Cjmi(int j, int m, int i, RP *s);
double calka_Cdjm_i(int j, int m, int i, RP *s);
void zapisz_do_pliku(RP *s);
void zwolnij_pamiec(RP *s);
double ef(double), lb(double), pb(double);

int main(int argc, char *argv[]) {
    RP q;
    zainicjuj_i_rozwiaz_RP(&q);

    return 0;
}

double lb(double x){
    return 1.0;
}

double ef(double x){
    return x;
}

double pb(double x){
    return 1.0;
}

void zainicjuj_i_rozwiaz_RP(RP *s){
    int j,i ;
    s->a=0.0;
    s->b=1.0;
    s->f=ef;
    s->p=lb;
    s->q=pb;
    s->N=10;
    s->h=(s->b - s->a)/(s->N+1.0);
    s->x= dvector(0, s->N+1);
    s->un= dvector(0, s->N+1);
    s->C0= dvector(1, s->N);
    s->C1= dvector(1, s->N);
    s->C2= dvector(1, s->N);
    s->P= dvector(1, s->N);
    s->R= dvector(1, s->N);
    s->u_a=0.0;
    s->u_b=0.0;

    for(i=0; i<=s->N+1; i++){
        s->x[i]=s->a+i*s->h;
        s->un[i]=0.0;
    }
    printf("definuje macierz");
    zdefiniuj_macierz_R(s);
    printf("definuje praw¹ strone");
    zdefiniuj_prawa_strone_S(s);
    printf("rozwi¹zuje uk³ad");
    rozwiaz_trojdiag_Thomas(s);
    printf("zapisuje rozwi¹zanie");
    s->un[0] = s->u_a;
    for(i=1; i<= s->N; i++) s->un[i] = s->R[i];
    s->un[s->N+1] = s->u_b;
    zapisz_do_pliku(s);

    zwolnij_pamiec(s);
}

void zwolnij_pamiec(RP *s){
    free_dvector(s->x, 0, s->N+1);
    free_dvector(s->un, 0, s->N+1);
    free_dvector(s->C0, 1, s->N);
    free_dvector(s->C1, 1, s->N);
    free_dvector(s->C2, 1, s->N);
    free_dvector(s->P, 1, s->N);
    free_dvector(s->R, 1, s->N);
}

void zapisz_do_pliku(RP *s){
    FILE *f;
    f=fopen("wynik.txt", "wt");
    fprintf(f, "Results:\n");
    fclose(f);
    f = fopen("wynik.txt", "at");
    for (int i = 0; i<=s->N+1; i++){
        printf("%d", i);
        fprintf(f, "%lf, ", s->un[i]);
    }
    fclose(f);
}

void zdefiniuj_macierz_R(RP *s){
    int j=1, m, i;
    s->C0[1] = 0.0;
    s->C1[1] = -calka_Cfji(1,1,s);
    s->C2[1] = -calka_Cfji(1,2,s);
    for(m=j-1; m<=j+1; m++){
        s->C1[1] += (*s->p)(s->x[m])*calka_Cdjm_i(1,m,1,s) + (*s->q)(s->x[m])*calka_Cjmi(1,m,1,s);
        s->C2[1] += (*s->p)(s->x[m])*calka_Cdjm_i(1,m,2,s) + (*s->q)(s->x[m])*calka_Cjmi(1,m,2,s);
    }
    for(j=2; j<s->N; j++){
        s->C0[j] = -calka_Cfji(j,j-1,s);
        s->C1[j] = -calka_Cfji(j,j,s);
        s->C2[j] = -calka_Cfji(j,j+1,s);
        for(m=j-1; m<=j+1; m++){
            s->C0[j] += (*s->p)(s->x[m])*calka_Cdjm_i(j,m,j-1,s) + (*s->q)(s->x[m])*calka_Cjmi(j,m,j-1,s);
            s->C1[j] += (*s->p)(s->x[m])*calka_Cdjm_i(j,m,j,s) + (*s->q)(s->x[m])*calka_Cjmi(j,m,j,s);
            s->C2[j] += (*s->p)(s->x[m])*calka_Cdjm_i(j,m,j+1,s) + (*s->q)(s->x[m])*calka_Cjmi(j,m,j+1,s);
        }
    }
    s->C0[s->N] = -calka_Cfji(s->N,j-1,s);
    s->C1[s->N] = -calka_Cfji(s->N,s->N,s);
    for(m=j-1; m<=j+1; m++){
        s->C0[s->N] += (*s->p)(s->x[m])*calka_Cdjm_i(s->N,m,s->N-1,s) + (*s->q)(s->x[m])*calka_Cjmi(s->N,m,s->N-1,s);
        s->C1[s->N] += (*s->p)(s->x[m])*calka_Cdjm_i(s->N,m,s->N,s) + (*s->q)(s->x[m])*calka_Cjmi(s->N,m,s->N,s);
    }
    s->C2[s->N] = 0.0;
}

void zdefiniuj_prawa_strone_S(RP *s){
    int j,m;
    double temp;
    for(j=1; j<=s->N; j++){
        temp=0.0;
        for(m=j-1; m<=j+1; m++){
            temp+=(*s->f)(s->x[m])*calka_Cji(j,m,s);
            temp-=(*s->p)(s->x[m])*(s->u_a*calka_Cdjm_i(j,m,0,s)+s->u_b*calka_Cdjm_i(j,m,s->N+1,s));
            temp-=(*s->q)(s->x[m])*(s->u_a*calka_Cjmi(j,m,0,s)+s->u_b*calka_Cjmi(j,m,s->N+1,s));
            temp+=s->u_a*calka_Cfji(j,0,s)+s->u_b*calka_Cfji(j,s->N+1,s);
        }
        s->P[j] = temp;
    }
}

void zdefiniuj_prawa_strone_S_bis(RP *s){
    int j;
    double temp;
    s->P[1] = (*s->f)(s->x[0])*calka_Cji(1,0,s) + (*s->f)(s->x[1])*calka_Cji(1,1,s) + (*s->f)(s->x[2])*calka_Cji(1,2,s);
    temp = calka_Cfji(1,0,s) - (*s->p)(s->x[0])*calka_Cdjm_i(1,0,0,s) - (*s->p)(s->x[1])*calka_Cdjm_i(1,1,0,s)
           - (*s->q)(s->x[0])*calka_Cjmi(1,0,0,s) - (*s->q)(s->x[1])*calka_Cjmi(1,1,0,s);
    s->P[1] += s->u_a * temp;
    for(j=2; j<=s->N-1; j++){
        s->P[j] = (*s->f)(s->x[j-1])*calka_Cji(j,j-1,s) + (*s->f)(s->x[j])*calka_Cji(j,j,s) + (*s->f)(s->x[j+1])*calka_Cji(j,j+1,s);
    }
    s->P[s->N] = (*s->f)(s->x[s->N-1])*calka_Cji(s->N,s->N-1,s) + (*s->f)(s->x[s->N])*calka_Cji(s->N,s->N,s) + (*s->f)(s->x[s->N+1])*calka_Cji(s->N,s->N+1,s);
    temp = calka_Cfji(s->N,s->N+1,s) - (*s->p)(s->x[s->N])*calka_Cdjm_i(s->N,s->N,s->N+1,s) - (*s->p)(s->x[s->N+1])*calka_Cdjm_i(s->N,s->N+1,s->N+1,s)
           - (*s->q)(s->x[s->N])*calka_Cjmi(s->N,s->N,s->N+1,s) - (*s->q)(s->x[s->N+1])*calka_Cjmi(s->N,s->N+1,s->N+1,s);
    s->P[s->N] += s->u_b * temp;
}

double calka_Cji(int j, int i, RP *s){
    if ((i!=(j-1)) && (i!=j) && (i!=(j+1))) return 0.0;
    if(i==j) return 2.0*s->h/3.0;
    else return s->h/6.0;
}
double calka_Cfji(int j, int i, RP *s){
    if ((i!=(j-1)) && (i!=j) && (i!=(j+1))) return 0.0;
    if(i==j) return 2.0/s->h;
    else return -1.0/s->h;
}
double calka_Cjmi(int j, int m, int i, RP *s){
    if ((abs(j-i)>1) || (abs(j-m)>1) || (abs(i-m)>1)) return 0.0;
    if (j==m && m==i) return 0.5*s->h;
    else return s->h/12.0;

}
double calka_Cdjm_i(int j, int m, int i, RP *s){
    if ((abs(j-i)>1) || (abs(j-m)>1) || (abs(i-m)>1)) return 0.0;
    if (j==m && m==i) return 0.0;
    if (j==m && m==(i-1)) return 1.0/3.0;
    if (j==m && m==(i+1)) return -1.0/3.0;
    if (j==i && i==(m-1)) return -1.0/6.0;
    if (j==i && i==(m+1)) return 1.0/6.0;
    if (j==(m+1) && i==m) return -1.0/6.0;
    if (j==(m-1) && i==m) return 1.0/6.0;
}
void rozwiaz_trojdiag_Thomas(RP *q)
{
    int i,j,k;
    double *beta, *gamma;
    beta=dvector(1,q->N);
    gamma=dvector(1,q->N);
    beta[1]=q->C1[1]; gamma[1]=q->P[1]/q->C1[1];
    for(i=2;i<=q->N;i++)
    {
        beta[i]=q->C1[i]-q->C0[i]*q->C2[i-1]/beta[i-1];
        gamma[i]=(q->P[i]-q->C0[i]*gamma[i-1])/beta[i];
    }
    q->R[q->N]=gamma[q->N];
    for(i=q->N-1;i>=1;q->R[i]=gamma[i]-q->C2[i]*q->R[i+1] / beta[i],i--);
    free_dvector(beta,1,q->N);
    free_dvector(gamma,1,q->N);
}
