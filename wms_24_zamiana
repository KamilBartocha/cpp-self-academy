#include <stdio.h>
#include <conio.h>

main()
{
	int R[32];
	int p, n, i=0;
	printf("Program zamienia liczbe w systemie dziesietnym na liczbe w systemie o podstawie p :>\n");
	printf("Podaj p: ");
	scanf("%d", &p);
	printf("Podaj liczbe: ");
	scanf("%d", &n);
	while (n!=0)
	{
		R[i]=n%p;
		i++;
		n=n/p;	
	}
	
	for(i=i-1; i>=0; i--)
	{
		printf("%d", R[i]);		
	}
		
	getch();
	return 0;
}
