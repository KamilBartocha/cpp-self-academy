#include <stdio.h>
#include <conio.h>
#include <math.h>


float A[20];
int n;



void wczytajciag()
{
	printf("Podaj ilosc elementow.  ");
	scanf("%d", &n);
	
	for(int i=0; i<n; i++)
	{
	printf("A[%d]= ", i);
	scanf("%f", &A[i]);
	}
}

void wypiszciag(int n, float A[20])
{
	for(int i=0; i<n; i++)
	{
	printf("%.2f   ", A[i]);
	}
}

int arytmetyczny(int n, float A[20])
{
	float r=A[1]-A[0];
	if(n<3) return 1;
	else
	{
		for(int i=2; i<n; i++)
		{
			if(A[i]!=A[i-1]+r) return 0;
		}
		return 1;
	}
}


int geometryczny(int n, float A[20])
{
	int i=0;
	if (A[0]==0) 
	{
		while (i<n)
		{
			if (A[i]!=0) return 0;
			i++;
		}
		return 1;
	}
	
	float q=A[1]/A[0];
	if(n<3) return 1;
	else
	{
		for(i=2; i<n; i++)
		{
			if(A[i]!=A[i-1]*q) return 0;
		}
		return 1;
	}
}

float sredniaary(int n, float A[20])
{
	float s=A[0];
	for(int i=1; i<n; i++)
		{
			s=s+A[i];
		}
		s=s/n;
	return s;
}

float sredniageo(int n, float A[20])
{
	float m=1;
	for(int i=0; i<n; i++)
		{
			m=m*A[i];
		}
		
		m=pow(m,1.0/n);
	return m;
}



float sredniageoo(int n, float A[20])
{
	float m=1;
	for(int i=0; i<n; i++)
		{
			
			m=m*pow(A[i],1.0/n);
		}
	return m;
}

float sredniageooo(int n, float A[20])
{
	float m=0;
	for(int i=0; i<n; i++)
		{
			if (A[i]==0) return 0;
			m=m+log(A[i]);
		}
		
	m=exp(m/n);
	return m;
}



main()
{
	
	printf("Program wczytuje i wypisuje ciagi.\n");
	
	wczytajciag();
	wypiszciag(n, A);	
	if (arytmetyczny(n, A)==1)
		printf("\nCiag jest arytmetyczny.");
	else
		printf("\nCiag nie jest arytmetyczny.");
	
	if (geometryczny(n, A)==1)
		printf("\nCiag jest geometryczny.");
	else
		printf("\nCiag nie jest geometryczny.");
		
	printf("\nSrednia arytmetyczna wynosi %.3f", sredniaary(n, A));
	printf("\nSrednia geometryczna (wersja 1) wynosi %.3f", sredniageo(n, A));
	printf("\nSrednia geometryczna (wersja 2) wynosi %.3f", sredniageoo(n, A));
	printf("\nSrednia geometryczna (wersja 3) wynosi %.3f", sredniageooo(n, A));
	
	getch();
	return 0;
	
}
