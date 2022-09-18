#include <stdio.h>
#include <conio.h>
#include <time.h>

int l=0;
int Fibrek(int n)
{
	l++;
	if(n<2) return 1;
	else return Fibrek(n-1)+Fibrek(n-2);	
}

int Fibit(int n)
{
	int F[55];
	F[0]=1;
	F[1]=1;
	
	if(n<2) return F[n];
	else
	{	
		for(int i=2; i<=n; i++)
			F[i]=F[i-1]+F[i-2];
		return F[n];
	}	
	
}

main()
{
	int n;
	printf("Program liczy ciag Fibonacciego\n");

	printf("\nPodaj n: ");
	scanf("%d", &n);

	clock_t start=clock();
	printf("\nWyraz %d wynosi(1) %d", n, Fibrek(n));
	clock_t koniec=clock();
	printf("\nCzas: %f", (koniec-start)/(float(CLOCKS_PER_SEC)));
	printf("\nWyraz %d wynosi(2) %d", n, Fibit(n));
	printf("\nLicznik wynosi %d", l);
	
	getch();
	return 0;
}
