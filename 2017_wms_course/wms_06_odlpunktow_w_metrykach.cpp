#include <stdio.h>
#include <conio.h>
#include <math.h>


float X[10], Y[10];
int n;



void wczytajpkt (int n, float A[10])
{
	for(int i=0; i<n; i++)
	{
	printf("A[%d]= ", i);
	scanf("%f", &A[i]);
	}
	
}


void wypiszpkt (int n, float A[10])
{
	for(int i=0; i<n; i++)
	{
	printf("%.2f   ", A[i]);
	}
}

float euklides (int n, float A[10], float B[10])
{
	float ha=0;
	for(int i=0; i<n; i++)
		{
			ha=ha+pow((A[i]-B[i]), 2);
		}
	return sqrt(ha);
}


float taxi (int n, float A[10], float B[10])
{
	float ha=0;
	for(int i=0; i<n; i++)
		{
			ha=ha+fabs(A[i]-B[i]);
		}
	return ha;
}


float maks (int n, float A[10], float B[10])
{
	float ha=0;
	for(int i=0; i<n; i++)
		{
			if(ha<fabs(A[i]-B[i]))
			ha=fabs(A[i]-B[i]);
		}
	return ha;
}

float rzeka (int n, float A[10], float B[10])
{
	if (A[0]==B[0]) return fabs(A[1]-B[1]);
	else return fabs(A[1])+fabs(B[1])+fabs(A[0]-B[0]);
}

main()
{
	int d;
	printf("Program wczytuje punkty w R^n i liczy odleglosc miedzy nimi.\n");
	printf("Podaj wymiar: \n");
	scanf("%d", &n);
do
{
	wczytajpkt(n, X);
	printf("\n\n\n");
	wczytajpkt(n, Y);
	
	printf("\nWspolrzedne pkt x: ");
	wypiszpkt(n, X);
	printf("\nWspolrzedne pkt y: ");
	wypiszpkt(n, Y);
	
	
	
	printf("\n\nMetryki:\n1. Euklidesowa\n2. Taksowkowa\n3. Maksymalna\n4. Rzeka");
	int baka;
	printf("\nJakiej metryki uzyc? ");
	scanf("%d", &baka);

	switch(baka)
	{
	case 1: printf("\nOdleglosc tych punktow (euklides) wynosi: %f \n", euklides(n, X, Y)); break;
	case 2: printf("\nOdleglosc tych punktow (taxi) wynosi: %f \n", taxi(n, X, Y)); break;
	case 3: printf("\nOdleglosc tych punktow (maks) wynosi: %f \n", maks(n, X, Y)); break;
	case 4: if (n==2) printf("\n\nOdleglosc tych punktow (rzeka) wynosi: %f \n", rzeka(n, X, Y)); 
			else printf("Tylko w dwoch wymiarach"); break;
	default: printf("Jestes idiota.");
	}
	printf ("Jesli chcesz skonczyc napisz 0, jesli nie to podaj inna liczbe. ");
	scanf("%d", &d);
	printf("\n\n");
}
while (d!=0);
	getch();
	return 0;
}
