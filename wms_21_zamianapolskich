#include <stdio.h>
#include <conio.h>
#include <string.h>

main()
{

	FILE *f1, *f2;
	char znak;
	printf("Program usuwa polskie litery z tekstu :).\n");
	f1=fopen("oda.txt", "r");
	f2=fopen("odabezogonkow.txt", "w+");

	while(!feof(f1))
	{
		znak=fgetc(f1);
		switch (znak)
		{
		case '¥': fputc('A', f2); break;
		case '¹': fputc('a', f2); break;
		case 'Æ': fputc('C', f2); break;
		case 'æ': fputc('c', f2); break;
		case 'Ê': fputc('E', f2); break;
		case 'ê': fputc('e', f2); break;
		case '¯': fputc('Z', f2); break;
		case '¿': fputc('z', f2); break;
		case '': fputc('Z', f2); break;
		case '': fputc('z', f2); break;
		case 'Ñ': fputc('N', f2); break;
		case 'ñ': fputc('n', f2); break;
		case 'Ó': fputc('O', f2); break;
		case 'ó': fputc('o', f2); break;
		case '': fputc('S', f2); break;
		case '': fputc('s', f2); break;
		case '£': fputc('L', f2); break;
		case '³': fputc('l', f2); break;
		default: fputc(znak, f2);
		}
	}
	
	fclose(f1);
	fclose(f2);
	printf("\nPlik stworzony.\n");
	getch();
	return 0;
	
}
