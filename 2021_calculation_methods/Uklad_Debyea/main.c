#include <stdio.h>
#include <stdlib.h>
#include "disnrutil.h"
#include "typy_pde.h"



void wczytaj_parametry_ukladu(SP *p);
void wypisz_parametry(SP *p);
void zaalokuj_pamiec(SP *p);
void zwolnij_pamiec(SP *p);
double alunia(double x);
double olunia(double x);
double zdzisio(double t);
double gabrys(double t);
void okresl_komponenty_struktury(SP *p);
void zapisz_stezenia_do_pliku(SP *p);
void zapisz_potencjal_do_pliku(SP *p);
int main(void);
void okresl_macierze_dla_potencjalu(SP *p);
void okresl_macierze_dla_stezenia_u(SP *p);
void okresl_macierze_dla_stezenia_v(SP *p);
void rozwiaz_trojdiag_Thomas(SP *q);
void rozwiaz_potencjal(SP *p);
void rozwiaz_stezenie_v(SP *p);
void rozwiaz_stezenie_u(SP *p);
void rozwiaz_uklad_Debaya(SP *p);
void przepisz_nowe_na_stare(SP *p);
void zapisz_wezly(SP *p);
void zapisz_czas(SP *p);
void wypisz_komponenty(SP *p);

int main(void) {
    SP q;
    int i;
    rozwiaz_uklad_Debaya(&q);
    getchar();

    return 0;

}

void rozwiaz_uklad_Debaya(SP *p)
{
    wczytaj_parametry_ukladu(p);
    wypisz_parametry(p);
    zaalokuj_pamiec(p);
    okresl_komponenty_struktury(p);
    wypisz_komponenty(p);
    int mi;
    zapisz_wezly(p);
    for(mi=0;mi<=p->M;mi++)
    {
        p->czas+=p->k;
        zapisz_czas(p);
        rozwiaz_potencjal(p);
        rozwiaz_stezenie_u(p);
        rozwiaz_stezenie_v(p);
        zapisz_stezenia_do_pliku(p);
        zapisz_potencjal_do_pliku(p);
        przepisz_nowe_na_stare(p);
    }

    zwolnij_pamiec(p);
}


void zapisz_wezly(SP *p)
{
    int i;
    FILE *f;
    f=fopen("wynik.txt", "at" );
    fprintf(f, "wezly siatka -1, 1 \n");
    for(i=0; i<=p->N+1; fprintf(f, "%lf, ", p->x[i]), i++);
    fprintf(f, "\n");
    fclose(f);
}

void zapisz_czas(SP *p)
{
    FILE *f;
    f=fopen("wynik.txt", "at" );
    fprintf(f, "%lf \n", p->czas);
    fclose(f);

    f=fopen("czas.txt", "at" );
    fprintf(f, "%lf, ", p->czas);
    fclose(f);
}

void przepisz_nowe_na_stare(SP *p)
{
    int i;
    for(i=0; i<=p->N+1; p->Ws[i]=p->Wn[i], p->Us[i]=p->Un[i], p->Vs[i]=p->Vn[i], i++);
}

double alunia(double x)
{
    return 0.01*x*x+1.0;
}

double olunia(double x)
{
    return 0.01*x*x+1.0;
}

double zdzisio(double t)
{
    return 0.0;
}

double gabrys(double t)
{
    return 0.01;
}

void okresl_komponenty_struktury(SP *p)
{
    int i;
    printf("uruchamiam funkcje");
    getchar();
    p->wpu=alunia;
    p->wpv=olunia;
    p->fil=zdzisio;
    p->fip=gabrys;
    p->a=-1.0;
    p->b=1.0;
    p->h=(p->b-p->a)/(p->N+1.0);
    p->czas = 0;

    for(i=0; i<=p->N+1; i++)
    {
        p->x[i]=p->a+i*p->h;
        p->Us[i]=  (*p->wpu)(p->x[i]);
        p->Vs[i]=  (*p->wpv)(p->x[i]);
        p->Un[i] = p->Us[i];
        p->Vn[i] = p->Vs[i];
    }

    p->k = p->T / (p->M + 1.0);

    FILE *f = fopen("wynik.txt", "wt");
    fclose(f);
}

void zapisz_stezenia_do_pliku(SP *p){
    FILE *f = fopen("wynik.txt", "at");
    int i;
    fprintf(f, "stezenie UN \n");
    for(i = 0; i <= p->N + 1; i++){
        fprintf(f, "%lf, ", p->Un[i]);
    }

    fprintf(f, "\n");
    fprintf(f, "stezenie VN \n");
    for(i = 0; i <= p->N + 1; i++){
        fprintf(f, "%lf, ", p->Vn[i]);
    }
    fprintf(f, "\n");
    fclose(f);

    f = fopen("stezenieun.txt", "at");
    fprintf(f, "{");
    for(i = 0; i <= p->N + 1; i++){
        if (i == p->N + 1)
            fprintf(f, "{%lf, %lf}},", p->x[i], p->Un[i]);
        else
            fprintf(f, "{%lf, %lf}, ", p->x[i], p->Un[i]);
    }
    fprintf(f, "\n");
    fclose(f);

    f = fopen("stezenievn.txt", "at");
    fprintf(f, "{");
    for(i = 0; i <= p->N + 1; i++){
        if (i == p->N + 1)
            fprintf(f, "{%lf, %lf}},", p->x[i], p->Vn[i]);
        else
            fprintf(f, "{%lf, %lf}, ", p->x[i], p->Vn[i]);
    }
    fprintf(f, "\n");
    fclose(f);
}

void zapisz_potencjal_do_pliku(SP *p){
    FILE *f = fopen("wynik.txt", "at");
    int i;
    fprintf(f, "potencial WN \n");
    for(i = 0; i <= p->N + 1; i++){
        fprintf(f, "%lf, ", p->Wn[i]);
    }
    fprintf(f,"\n");
    fclose(f);
    f = fopen("potencialwn.txt", "at");
    fprintf(f, "{");
    for(i = 0; i <= p->N + 1; i++){
        if (i == p->N + 1)
            fprintf(f, "{%lf, %lf}},", p->x[i], p->Wn[i]);
        else
            fprintf(f, "{%lf, %lf}, ", p->x[i], p->Wn[i]);
    }
    fprintf(f,"\n");
    fclose(f);
}

void wypisz_komponenty(SP *p){
    FILE *f;
    f=fopen("domcia.txt", "wt");
    fprintf(f,"czasmax=%lf \n", p->T);
    fprintf(f,"lambda=%lf alfa1=%lf alfa2=%lf alfa1w=%lf alfa2w=%lf \n" , p->wsp_lambda,p->wsp_alpha1,p->wsp_alpha2,p->wsp_alpha1w,p->wsp_alpha2w);
    fprintf(f,"N=%d M=%d \n", p->N, p->M);
    fclose(f);
}

void okresl_macierze_dla_potencjalu(SP *p){
    int i;
    p->C0[0] = 0; p->C1[0] = 1; p->C2[0] = 0; p->B[0] = (*p->fil)(p->czas);

    for(i =1; i <= p->N; i++){
        p->C0[i] = 1.0; p->C1[i] = -2.0; p->C2[i] = 1; p->B[i] = p->wsp_lambda * p->h * p->h * (p->Vs[i] - p->Us[i]);
    }

    p->C0[p->N + 1] = 0; p->C1[p->N + 1] = 1; p->C2[p->N + 1] = 0; p->B[p->N + 1] = (*p->fip)(p->czas);
}

void okresl_macierze_dla_stezenia_u(SP *p){
    double A, B, C;
    int j;
    p->C0[0]=0;
    p->C1[0]=p->Wn[1]-p->Wn[0]-1.0;
    p->C2[0]=1.0;
    p->B[0]=0;
    for(j=1;j<=p->N;j++)
    {
        A=p->wsp_alpha1*p->k/(p->h*p->h);
        B=p->wsp_alpha1*p->k*(p->Wn[j+1]-p->Wn[j-1])/(4.0*p->h*p->h);
        C=p->wsp_alpha1w*p->k*(p->Wn[j+1]-2*p->Wn[j]+p->Wn[j-1])/(p->h*p->h);
        p->C0[j]=-A+B;
        p->C1[j]=1.0+2*A-C;
        p->C2[j]=-A-B;
        p->B[j]=p->Us[j];
    }
    p->C0[p->N+1]=1.0;
    p->C1[p->N+1]=p->Wn[p->N+1]-p->Wn[p->N]-1.0;
    p->B[p->N+1]=0;
}

void okresl_macierze_dla_stezenia_v(SP *p){
    double A, B, C;
    int j;
    p->C0[0]=0;
    p->C1[0]=p->Wn[1]-p->Wn[0]+1.0;
    p->C2[0]=-1.0;
    p->B[0]=0;
    for(j=1;j<=p->N;j++)
    {
        A=p->wsp_alpha2*p->k/(p->h*p->h);
        B=-p->wsp_alpha2*p->k*(p->Wn[j+1]-p->Wn[j-1])/(4.0*p->h*p->h);
        C=-p->wsp_alpha2w*p->k*(p->Wn[j+1]-2*p->Wn[j]+p->Wn[j-1])/(p->h*p->h);
        p->C0[j]=-A+B;
        p->C1[j]=1.0+2*A-C;
        p->C2[j]=-A-B;
        p->B[j]=p->Vs[j];
    }
    p->C0[p->N+1]=1.0;
    p->C1[p->N+1]=p->Wn[p->N+1]-p->Wn[p->N]-1.0;
    p->B[p->N+1]=0;
}

void rozwiaz_potencjal(SP *p){
    okresl_macierze_dla_potencjalu(p);
    rozwiaz_trojdiag_Thomas(p);
    int i;
    for(i=0; i<=p->N+1; p->Wn[i]=p->u[i], i++);
}

void rozwiaz_stezenie_u(SP *p){
    okresl_macierze_dla_stezenia_u(p);
    rozwiaz_trojdiag_Thomas(p);
    int i;
    for(i=0; i<=p->N+1; p->Un[i]=p->u[i], i++);
}

void rozwiaz_stezenie_v(SP *p){
    okresl_macierze_dla_stezenia_v(p);
    rozwiaz_trojdiag_Thomas(p);
    int i;
    for(i=0; i<=p->N+1; p->Vn[i]=p->u[i], i++);
}

void zaalokuj_pamiec(SP *p)
{
    p->C0=dvector(0, p->N+1);
    p->C1=dvector(0, p->N+1);
    p->C2=dvector(0,p->N+1);
    p->B=dvector(0, p->N+1);
    p->x=dvector(0, p->N+1);
    p->Us = dvector(0, p->N+1);
    p->Vs = dvector(0, p->N+1);
    p->Un = dvector(0, p->N+1);
    p->Vn = dvector(0, p->N+1);
    p->Wn = dvector(0, p->N+1);
    p->Ws = dvector(0, p->N+1);
    p->u = dvector(0, p->N+1);
}

void zwolnij_pamiec(SP *p)
{
    free_dvector(p->C0, 0, p->N+1);
    free_dvector(p->C1, 0, p->N+1);
    free_dvector(p->C2, 0, p->N+1);
    free_dvector(p->B, 0, p->N+1);
    free_dvector(p->x, 0, p->N+1);
    free_dvector(p->Us, 0, p->N+1);
    free_dvector(p->Un, 0, p->N+1);
    free_dvector(p->Vs, 0, p->N+1);
    free_dvector(p->Vn, 0, p->N+1);
    free_dvector(p->Ws, 0, p->N+1);
    free_dvector(p->Wn, 0, p->N+1);
    free_dvector(p->u,0, p->N+1);

}

void wczytaj_parametry_ukladu(SP *p)
{
    FILE *f;
    f=fopen("parametry_np.dat", "rt");
    if (f == NULL){
        printf("nie ma pliku");
        getchar();
    }
    fscanf(f, "%lf", &p->T);
    fscanf(f, "%lf %lf %lf %lf %lf", &p->wsp_lambda,&p->wsp_alpha1,&p->wsp_alpha2,&p->wsp_alpha1w,&p->wsp_alpha2w);
    fscanf(f, "%d %d", &p->N, &p->M);
    fclose(f);
}

void wypisz_parametry(SP *p)
{
    printf("%lf \n", p->T);
    printf("%lf %lf %lf %lf %lf \n", p->wsp_lambda,p->wsp_alpha1,p->wsp_alpha2,p->wsp_alpha1w,p->wsp_alpha2w);
    printf("%d %d \n", p->N, p->M);
    fflush(stdin);
    getchar();
}

void rozwiaz_trojdiag_Thomas(SP *q)
{
    int i,j,k;
    double *beta, *gamma;
    beta=dvector(0,q->N+1);
    gamma=dvector(0,q->N+1);
    beta[0]=q->C1[0]; gamma[0]=q->B[0]/q->C1[0];
    for(i=1;i<=q->N+1;i++)
    {
        beta[i]=q->C1[i]-q->C0[i]*q->C2[i-1]/beta[i-1];
        gamma[i]=(q->B[i]-q->C0[i]*gamma[i-1])/beta[i];
    }
    q->u[q->N+1]=gamma[q->N+1];
    for(i=q->N;i>=0;q->u[i]=gamma[i]-q->C2[i]*q->u[i+1]/beta[i],i--);
    free_dvector(beta,0,q->N+1);
    free_dvector(gamma,0,q->N+1);
}

