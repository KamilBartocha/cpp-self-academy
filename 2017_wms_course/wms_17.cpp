#include <stdio.h>
#include <conio.h>
#include <string.h>



int rozne_literki (char slowo[20])
{
	int k=strlen(slowo);
	for(int i=0; i<k-1; i++)
	{
		for(int j=i+1; j<k; j++)
			if(slowo[i]==slowo[j]) return 0;
	}	
	return 1;
}




main()
{
	FILE *f1, *f2;
	char slowo[20];
	printf("Program tworzy plik ze slowami z roznymi literkami :).\n");
	
	f1=fopen("slownik.txt", "r");
	f2=fopen("rozne_literki.txt", "w+");
	
	while(!feof(f1))
	{
		fscanf (f1, "%s", slowo);	
		if(rozne_literki(slowo)==1)
			fprintf(f2, "%s\n", slowo);
	}
	
	fclose(f1);
	fclose(f2);	
		printf("\nPlik stworzony.\n");
	getch();
	return 0;
	
}
