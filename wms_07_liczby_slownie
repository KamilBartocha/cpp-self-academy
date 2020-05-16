#include <stdio.h>
#include <conio.h>

main()
{
	
	int n;
	
	printf("Program wypisuje slownie liczbe.\n");
	printf("Podaj liczbe: ");
	scanf("%d", &n);
	
	int t=n/1000;
	int s=n/100%10;
	int d=n/10%10;
	int j=n%10;
	
	
	switch(t)
	{
		case 1: printf("tysiac "); break;
		case 2: printf("dwa tysiace "); break;
		case 3: printf("trzy tysiace ");break;
		case 4: printf("cztery  ");break;
		case 5: printf("piec tysiecy ");break;
		case 6: printf("szesc tysiecy ");break;
		case 7: printf("siedem tysiecy ");break;
		case 8: printf("osiem tysiecy ");break;
		case 9: printf("dziewiec tysiecy ");break;
	}
	
	
	switch(s)
	{
		case 1: printf("sto "); break;
		case 2: printf("dwiescie "); break;
		case 3: printf("trzysta ");break;
		case 4: printf("czterysta ");break;
		case 5: printf("piecset ");break;
		case 6: printf("szescset ");break;
		case 7: printf("siedemset ");break;
		case 8: printf("osiemset ");break;
		case 9: printf("dziewiecset ");break;
	}
	
	
	switch(d)
	{
		case 1: 
			{switch(j)
			{
				case 0: printf("dziesiec"); break;
				case 1: printf("jede"); break;
				case 2: printf("dwa"); break;
				case 3: printf("trzy");break;
				case 4: printf("czter");break;
				case 5: printf("piet");break;
				case 6: printf("szes");break;
				case 7: printf("siedem");break;
				case 8: printf("osiem");break;
				case 9: printf("dziewiet");break;
				
			}
			if (j!=0) printf("nascie"); break;}
		case 2: printf("dwadziescia "); break;
		case 3: printf("trzydziesci ");break;
		case 4: printf("czterdziesci ");break;
		case 5: printf("piedziesiat ");break;
		case 6: printf("szescdziesiat ");break;
		case 7: printf("siedemdziesiat ");break;
		case 8: printf("osiemdziesiat ");break;
		case 9: printf("dziewiecdziesiat ");break;
	}
	
	if(d!=1)
	switch(j)
	{
		case 1: printf("jeden"); break;
		case 2: printf("dwa"); break;
		case 3: printf("trzy");break;
		case 4: printf("cztery");break;
		case 5: printf("piec");break;
		case 6: printf("szesc");break;
		case 7: printf("siedem");break;
		case 8: printf("osiem");break;
		case 9: printf("dziewiec");break;
	}
	getch();
	return 0;		
}
		
