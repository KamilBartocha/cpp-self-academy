#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

main()
{

	FILE *f1, *f2;
	char slowo[31];
	f1=fopen("sms.txt", "r");
	f2=fopen("smsbezspacji.txt", "w+");
	
	while(!feof(f1))
	{
		fscanf (f1, "%s", slowo);
		slowo[0]=toupper(slowo[0]);
		fprintf(f2, "%s", slowo);
	}

	fclose(f1);
	fclose(f2);
	printf("\nPlik stworzony.\n");
	getch();
	return 0;
}
