#include <stdio.h>
#include <conio.h>
#include <string.h>



int palindrom (char slowo[20], int k)
{
	for(int i=0; i<k/2; i++)
	{
		if(slowo[i]!=slowo[k-i-1]) return 0;
	}	
	return 1;
}


int rozne_literki (char slowo[20], int k)
{
	for(int i=0; i<k-1; i++)
	{
		for(int j=i+1; j<k; j++)
			if(slowo[i]==slowo[j]) return 0;
	}	
	return 1;
}





main()
{
	char slowo[20];
	printf("Program sprawdza czy slowo jest palindromem.\n");
	printf("Program sprawdza czy slowo ma rozne literki.\n");
	
	printf("Podaj slowo: ");	
	scanf ("%s", slowo);	
	int k=strlen(slowo);
	
	
	if (palindrom(slowo, k)==0) printf("\nTo slowo nie jest palindromem. :(");
	else printf("\nTo slowo jest palindromem. :)");
	
	if (rozne_literki(slowo, k)==0) printf("\nTo slowo nie ma roznych literek. :(");
	else printf("\nTo slowo ma rozne literki. :)");
	
	
	

	
	getch();
	return 0;
	
}
