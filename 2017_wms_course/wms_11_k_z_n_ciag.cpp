#include <stdio.h>
#include <conio.h>

int n, k;
int P[11];
void wariacja (int l)
{
	int j,i;
	if(l>k)
	{printf("\nDziala wariacja z l=%d\n", l);
	for (i=1; i<k; i++)
	
		printf("%d", P[i]);
		printf("%d\n", P[k]);
		
	}
	else 
	{
		for(j=1; j<=n; j++)
		{
			P[l]=j;
			printf("\nDziala wariacja z l=%d i j=%d\n", l, j);
			wariacja (l+1);
		}
	}
}

main()
{

	printf("Program wypisuje wszystkie ciagi k-elementowe o elementach ze zbioru od 0 do n\n");

	printf("\nPodaj n: ");
	scanf("%d", &n);
	printf("\nPodaj k: ");
	scanf("%d", &k);

	wariacja(1);
	getch();
	return 0;
}
