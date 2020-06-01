#include <stdio.h>
#include <conio.h>
#include <string.h>


int zliczanie_literek (char litera, char A[31])
{
	int licznik=0;
	int a=strlen(A);
	for (int i=0; i<a; i++)
	if (A[i]==litera) licznik++;
	return licznik;
}

int skrotka_anagram (char A[30], char B[30])
{
	for (int i=0; i<strlen(A); i++)
	{
		if (zliczanie_literek(B[i], A)<zliczanie_literek(B[i], B)) return 0;
		
	}
	return 1;
}




main()
{
	
	FILE *f1, *f2;
	char slowoA[30];
	char slowoB[30];
	char nazwapliku[35];
	printf("Program tworzy plik ze slowami ktore sie skladaja z tych liter co podabe slowo :).\n");
	printf("Podaj slowo: ");
	scanf("%s", slowoA);
	
	f1=fopen("slownik.txt", "r");
	strcpy (nazwapliku, slowoA);
	strcat (nazwapliku, ".txt");
	f2=fopen(nazwapliku, "w+");
	
	while(!feof(f1))
	{
		fscanf (f1, "%s", slowoB);	
		if(skrotka_anagram(slowoA, slowoB)==1)
			fprintf(f2, "%s\n", slowoB);
	}
	fclose(f1);
	fclose(f2);	
	
	printf("\nPlik stworzony.\n");
	getch();
	return 0;
	
}
