#include <stdio.h>
#include <conio.h>
#include <math.h>

int doskonala (int n)
{
	int i=1;
	int s=0;
	
		while (i<n)
	{
		if(n%i==0) s=s+i;
		i++;
	}
	return s;
}



main()
{	
	int n;
	
	printf("Progrem sluzy do sprawdzania czy podana liczba jest doskonala. \n");
	printf("Podaj liczbe n     ");
	scanf("%d", &n);
	
	if (doskonala(n)==n)
	printf("Liczba %d jest doskonala.", n);
	else
	printf("Liczba %d nie jest doskonala.", n);
	
	getch();
	return 0;
}
