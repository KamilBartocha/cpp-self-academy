#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <cctype>


main()
{

	FILE *f1, *f2;
	char znak;
	printf("Program usuwa wszystko porocz liter z tekstu :).\n");
	f1=fopen("allofme.txt", "r");
	f2=fopen("allofme2.txt", "w+");

	while(!feof(f1))
	{
		znak=fgetc(f1);
		if (isalpha(znak) || isspace(znak)) fputc(znak, f2);
	}
	
	fclose(f1);
	fclose(f2);
	printf("\nPlik stworzony.\n");
	getch();
	return 0;
	
}
