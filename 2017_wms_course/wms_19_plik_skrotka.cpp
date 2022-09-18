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
	
	FILE *f1, *f2, *f3;
	char slowoA[30];
	char slowoB[30];
	printf("Program tworzy plik ze slowami oraz ich skrotkami :).\n");
	
	f1=fopen("slownik.txt", "r");
	f3=fopen("skrotki.txt", "w+");
	
	while(!feof(f1))
	{
		fscanf (f1, "%s", slowoA);
		f2=fopen("slownik2.txt", "r");
		while(!feof(f2))
		{
			fscanf (f2, "%s", slowoB);	
			if(skrotka(slowoA, slowoB)==1)
				fprintf(f3, "%s  -  %s\n", slowoA, slowoB);
		}
		fclose(f2);	
	}
	
	fclose(f1);
	fclose(f3);	
	
	printf("\nPlik stworzony.\n");
	getch();
	return 0;
	
}
