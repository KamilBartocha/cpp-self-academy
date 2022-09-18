#include <stdio.h>
#include "disnrutil.h"
#include <math.h>


typedef struct FK{
double a, b, t0, T, theta;
double (*f)(double,double), (*ua)(double), (*ub)(double), (*w)(double), (*ua_div)(double), (*ub_div)(double);
int N, M;
double *x, *u_old, *u_new;
double h, tau;
double time;
double *C0, *C1, *C2, *right_side, *R;


}FK;

double f_function(double t, double x);
double f_function_1(double t, double x);
double ua_function(double t);
double ub_function(double t);
double ua_div_0(double t);
double ub_div_0(double t);
double ua_div_1(double t);
double ub_div_1(double t);
double ua_1(double t);
double ub_1(double t);
double w_function(double x);
double w_function_1(double x);
void zainicjuj_RF(FK *s);
double c_matrix(int if_div, int index_i, int index_j, int k, FK *s);
void ObliczPrawaStrone(FK *s);
void rozwiaz_trojdiag_Thomas(FK *q);
void solve(FK *s);




int main(void) {
    FK structure;
    zainicjuj_RF(&structure);
    solve(&structure);

    return 0;
}

void zainicjuj_RF(FK *s){
    int j,i ;
    s->a=0.0;
    s->b=1.0;
    s->f=f_function_1;
    s->ua=ua_1;
    s->ub=ub_1;
    s->ua_div=ua_div_0;
    s->ub_div=ub_div_0;
    s->w=w_function_1;
    s->t0=0.0;
    s->T=2.0;
    s->theta=1.0;
    s->time=s->t0;
    s->N=12;
    s->M=8;
    s->tau=(s->T-s->t0)/s->M;
    s->h=(s->b - s->a)/(s->N+1.0);
    s->x= dvector(0, s->N+1);
    s->u_new= dvector(0, s->N + 1);
    s->u_old= dvector(0, s->N+1);
    s->C0= dvector(1, s->N);
    s->C1= dvector(1, s->N);
    s->C2= dvector(1, s->N);
    s->right_side= dvector(1, s->N);
    s->R= dvector(1, s->N);

    for(i=0; i<=s->N+1; i++){
        s->x[i]=s->a+i*s->h;
        s->u_old[i]=(*s->w)(s->x[i]);
        s->u_new[i]=s->u_old[i];
    }
    s->C0[1]=0.0;
    s->C1[1]=c_matrix(0,1,1,1,s)+c_matrix(0,1,1,2,s);
    s->C2[1]=c_matrix(0,1,2,2,s);
    for(j=2; j<s->N; j++){
        s->C0[j]=c_matrix(0,j,j-1,j,s);
        s->C1[j]=c_matrix(0,j,j,j,s)+c_matrix(0,j,j,j+1,s);
        s->C2[j]=c_matrix(0,j,j+1,j+1,s);
    }
    s->C0[s->N]=c_matrix(0,s->N,s->N-1,s->N,s);
    s->C1[s->N]=c_matrix(0,s->N,s->N,s->N,s)+c_matrix(0,s->N,s->N,s->N+1,s);

}
void ObliczPrawaStrone(FK *s){
    int j,i;
    double temp;
    for(j=1; j<=s->N; j++){
        s->right_side[j]=0.0;
        temp=0.0;
        temp+=(*s->f)(s->time, s->x[j-1])*c_matrix(0,j,j-1,j,s);
        temp+=(*s->f)(s->time, s->x[j])*(c_matrix(0,j,j,j,s)+c_matrix(0,j,j,j+1,s));
        temp+=(*s->f)(s->time, s->x[j+1])*c_matrix(0,j,j+1,j+1,s);
        s->right_side[j]+=temp;
        temp=0.0;
        if(j==1){
            temp+=s->u_old[1]*(c_matrix(1,1,1,1,s)+c_matrix(1,1,1,2,s));
            temp+=s->u_old[2]*c_matrix(1,1,2,2,s);
        }
        else if(j==s->N){
            temp+=s->u_old[s->N-1]*c_matrix(1,s->N,s->N-1,s->N,s);
            temp+=s->u_old[s->N]*(c_matrix(1,s->N,s->N,s->N,s)+c_matrix(1,s->N,s->N,s->N+1,s));
        }
        else{
            temp+=s->u_old[j-1]*c_matrix(1,j,j-1,j,s);
            temp+=s->u_old[j]*(c_matrix(1,j,j,j,s)+c_matrix(1,j,j,j+1,s));
            temp+=s->u_old[j+1]*c_matrix(1,j,j+1,j+1,s);
        }
        s->right_side[j]-=s->theta*temp;
    }
    s->right_side[1]-=s->theta*(*s->ua)(s->time)*c_matrix(1,1,0,1,s);
    s->right_side[1]-=(*s->ua_div)(s->time)*c_matrix(0,1,0,1,s);
    s->right_side[s->N]-=s->theta*(*s->ub)(s->time)*c_matrix(1,s->N,s->N+1,s->N+1,s);
    s->right_side[s->N]-=(*s->ub_div)(s->time)*c_matrix(0,s->N,s->N+1,s->N+1,s);
}

void solve(FK *s){
    int mi,i;
    FILE *f;
    f=fopen("wynik.txt", "wt");
    fprintf(f, "Wyniki:\n");
    fclose(f);
    f = fopen("wynik.txt", "at");
    //zapisac wezly
    for(mi=1; mi<=s->M; mi++){
        ObliczPrawaStrone(s);
        rozwiaz_trojdiag_Thomas(s);
        for(i=1; i<=s->N; i++){
            s->u_new[i]= s->u_old[i] + s->tau * s->R[i];
        }
        s->u_new[0]=(*s->ua)(s->time + s->tau);
        s->u_new[s->N + 1]=(*s->ub)(s->time + s->tau);
        s->time+=s->tau;
        fprintf(f, "%lf \n", s->time);
        for(i = 0; i <= s->N+1; i++)
        {
            fprintf(f, "%lf ", s->u_new[i]);
        }
        fprintf(f, "\n\n");
        //zapis do pliku : czas, wektor u_new
        for(i=0; i <= s->N+1; i++){
            s->u_old[i]=s->u_new[i];
        }
    }
    fclose(f);
}

double c_matrix(int ktora, int i, int j, int k, FK *s){

    if (ktora){
        if(( i==(k-1) || i==k) && ( j==(k-1) || j==k)){
            if(i==j) return 1.0*s->h;
            else     return -1.0*s->h;
        }
        else return 0.0;
        }
    else {
        if(( i==(k-1) || i==k) && ( j==(k-1) || j==k)){
            if(i==j) return s->h/3.0;
            else     return s->h/6.0;
        }
        else return 0.0;
    }
}

double f_function(double t, double x){
    return x*x-2.0*t;
}
double f_function_1(double t, double x){
    return -exp(-x)*(sin(t*x) + cos(t*x) + 2*t *sin(t*x) - t*t *cos(t*x));
}

double ua_function(double t){
    return 0.0;
}
double ub_function(double t){
    return t;
}
double w_function(double x){
    return 0.0;
}

double ua_1(double t){
    return 1.0;
}

double ub_1(double t){
    return (1/exp(1.0))*cos(t);
}

double w_function_1(double x){
    return exp(-x)*cos(x);
}

double ua_div_0(double t){
    return 0.0;
}
double ub_div_0(double t){
    return 1.0;
}

double ua_div_1(double t)
{
    return 0.0;
}
double ub_div_1(double t){
    return -(1/exp(1.0))*sin(t);
}

void rozwiaz_trojdiag_Thomas(FK *q)
{
    int i;
    double *beta, *gamma;
    beta=dvector(1,q->N);
    gamma=dvector(1,q->N);
    beta[1]=q->C1[1]; gamma[1]= q->right_side[1] / q->C1[1];
    for(i=2;i<=q->N;i++)
    {
        beta[i]=q->C1[i]-q->C0[i]*q->C2[i-1]/beta[i-1];
        gamma[i]= (q->right_side[i] - q->C0[i] * gamma[i - 1]) / beta[i];
    }
    q->R[q->N]=gamma[q->N];
    for(i=q->N-1;i>=1;q->R[i]=gamma[i]-q->C2[i]*q->R[i+1] / beta[i], i--);
    free_dvector(beta,1,q->N);
    free_dvector(gamma,1,q->N);
}

