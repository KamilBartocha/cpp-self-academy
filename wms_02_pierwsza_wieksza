#include <stdio.h>
#include <conio.h>
#include <math.h>

int pierwsza (int n)
{
	int i=2;
	
		while (i<=sqrt(n))
	{
		if(n%i==0) return 0;
		i++;
	}
	return 1;
}



main()
{
	int n;
	printf("Progrem podaje najmniejsza liczbe pierwsza niemniejsza od n. \n");
	printf("Podaj liczbe n >1   ");
	scanf("%d", &n);
	
	
	while (pierwsza(n)==0)
	{
		n++;
	}
		
	printf("Liczba %d jest pierwsza.", n);
	
	getch();
	return 0;
}
