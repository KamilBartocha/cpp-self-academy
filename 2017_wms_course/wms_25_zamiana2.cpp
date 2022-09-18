#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

main()
{
	char R[32];
	int n=0, i=0;
	printf("Program zamienia liczbe w systemie dwojkowym na liczbe w systemie dziesietnym :>\n");
	printf("Podaj liczbe: ");
	scanf("%s", R);
	
	int k=strlen(R);
	
	while (i<k)
	{
		if(R[i]!='0')
		n=n+pow(2,k-i-1);
		i++;
	}

	printf("%d", n);
	printf("\n\nDziala =)");
	getch();
	return 0;
}
