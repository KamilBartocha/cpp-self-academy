#include <stdio.h>
#include <conio.h>
#include <string.h>



int palindrom (char slowo[20])
{
	int k=strlen(slowo);
	for(int i=0; i<k/2; i++)
	{
		if(slowo[i]!=slowo[k-i-1]) return 0;
	}	
	return 1;
}




main()
{
	FILE *f1, *f2;
	char slowo[20];
	printf("Program tworzy plik z palindromami.\n");
	
	f1=fopen("slownik.txt", "r");
	f2=fopen("palindromy.txt", "w+");
	
	while(!feof(f1))
	{
		fscanf (f1, "%s", slowo);	
		if(palindrom(slowo)==1)
			fprintf(f2, "%s\n", slowo);
	}
	
	fclose(f1);
	fclose(f2);	
		printf("\nProgram stworzyl plik z palindromami.\n");
	getch();
	return 0;
	
}
