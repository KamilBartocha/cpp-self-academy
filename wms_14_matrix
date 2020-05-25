#include <stdio.h>
#include <conio.h>


void wczytaj_macierz ( int *wsk_w, int *wsk_k, int A[10][10])
{
	printf("Podaj w \n");
	scanf("%d", wsk_w);
	printf("Podaj k \n");
	scanf("%d", wsk_k);
	
	for(int i=0; i<*wsk_w; i++)
	{
		for(int j=0; j<*wsk_k; j++)
			{
				printf("A[%d][%d]=", i, j);
				scanf("%d", &A[i][j]);
				
			}
	}
	
	
}

void wypisz_macierz ( int w, int k, int A[10][10])
{

	for(int i=0; i<w; i++)
	{
		for(int j=0; j<k; j++)
			{
				printf("%d  ", A[i][j]);
				
			}
		printf("\n");
	}
	
	
}

int Diagonalna (int w, int k, int A[10][10])
{
 if(w!=k) return 0;
 else
 {

	for(int i=0; i<w; i++)
	{
		for(int j=0; j<k; j++)
			{
				if (i!=j)
					if(A[i][j]!=0) return 0;
			}
	}
 }
 return 1;
}


int najwiecej_zer_w_wierszu (int w, int k, int A[10][10])
{
	int licznik=0;
	



}





main()
{
	
	int k, w, A[10][10];
	
	printf("Program wczytuje i wypisuje macierz.\n");
	
	
	wczytaj_macierz(&w, &k, A);
	wypisz_macierz(w, k, A);
	if(Diagonalna(w,k,A)==1) printf("\nJest diagonalna.");
	else printf("\nNie jest diagonalna.");
	getch();
	return 0;
}
