#include <stdio.h>
#include <conio.h>

int n, k;
int P[11];

void kombinacja (int l)
{
	P[0]=0;
	int j,i;
	if(l>k)
	{//printf("\nDziala kombinacja z l=%d\n", l);
	for (i=1; i<k; i++)
	
		printf("%d ", P[i]);
		printf("%d\n", P[k]);
		
	}
	else 
	{
		
		for(j=P[l-1]+1; j<=n; j++)
		{
			P[l]=j;
			//printf("\nDziala kombinacja z l=%d i j=%d\n", l, j);
			kombinacja (l+1);
		}
	}
}

main()
{

	printf("Program wypisuje wszystkie kombinacje k-elementowe o elementach ze zbioru od 0 do n\n");

	printf("\nPodaj n: ");
	scanf("%d", &n);
	printf("\nPodaj k: ");
	scanf("%d", &k);

	kombinacja(1);
	getch();
	return 0;
}
