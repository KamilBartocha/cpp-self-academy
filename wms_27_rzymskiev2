#include <stdio.h>
#include <conio.h>
#include <string.h>
char A[15];
int B[15];

main()
{
	int n=0;
	printf("Program zamiania liczbe rzymska na nasza.\n");
	scanf ("%s", A);
		
	int k=strlen(A);
	
	for(int i=0; i<=k; i++)
	{
	switch(A[i])
	{
		case 'M': B[i]=1000; break;
		case 'D': B[i]=500; break;
		case 'C': B[i]=100; break;
		case 'L': B[i]=50; break;
		case 'X': B[i]=10; break;
		case 'V': B[i]=5; break;
		case 'I': B[i]=1; break;
		default: B[i]=0;
	}
	}
	for ( int i=0; i<k; i++)
	{
		if (B[i]<B[i+1]) n=n-B[i];
		else n=n+B[i];
	}
	n=n+B[k];
	printf("Napisales: %d", n);
	getch();
	return 0;	
}
