#include <stdio.h>
#include <conio.h>

main()
{
	float a, b, c, d, e, f;
	float W, Wx, Wy, x, y;
	
	printf("Program sluzy do rozwiazywania ukladu rownan ax +by =e oraz cx + dy = f. \n");
	
	printf("Podaj wspolczynniki a, b, e:\n");
	scanf("%f%f%f",&a,&b,&e);
	
	printf("Podaj wspolczynniki c, d, f:\n");
	scanf("%f%f%f",&c,&d,&f);
	
	if(a!=0 || b!=0 || c!=0 || d!=0)
	{
		W=a*d-(b*c);
		Wx=e*d-(b*f);
		Wy=a*f-(c*e);
	
		if (W==0)
		{	
			if (Wy==0 && Wx==0)
			printf("Jest duzo rozwiazan."); //zalezy od jednego parametru
			else
			printf("Uklad nie ma rozwiazan.");
		}
		else
		{
			x=Wx/W;
			y=Wy/W;
			printf("x=%f,   ",x);
			printf("y=%f",y);
		}
	}
	else
		if (e!=0 || f!=0)
		printf("Uklad nie ma rozwiazan."); /*cos jest nie tak z ktoryms z rownan*/
		else
		printf("Szukasz dowolnej pary liczb."); //same zera
	
	
	getch();
	return 0;
}
