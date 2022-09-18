#include <stdio.h>
#include <conio.h>
#include <string.h>


int skrotka (char A[31], char B[31])
{
	int a=strlen(A), b=strlen(B);
	if(a-b!=1) return 0;
	for(int i=0; i<b; i++)
	{
		if(A[i]!=B[i])
		{
			for(int j=i+1; j<a; j++)
			if(A[j]!=B[j-1]) return 0;
			break;
		}
		
	}
	
	return 1;

}


main()
{
	char A[31], B[31];
	printf("Program sprawdza czy slowa sa skrotkami.\n");
	
	scanf ("%s", A);
	scanf ("%s", B);
	
	if (skrotka(A, B)==0) printf("\nTe slowa nie sa skrotkami. :(");
	else printf("\nTe slowa sa skrotkami. :)");
	
	getch();
	return 0;
}
