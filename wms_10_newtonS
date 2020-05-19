#include <stdio.h>
#include <conio.h>




int silnia(int n)
{
	if(n==0) return 1;
	else return silnia(n-1)*n;	
}


int SymbolNewtona1 (int n, int k)
{
	return silnia(n)/(silnia(k)*silnia(n-k));
}

int SymbolNewtona2 (int n, int k)
{
	if(k==n||k==0) return 1;
	else return SymbolNewtona2(n-1, k-1)+SymbolNewtona2(n-1,k);
}

int SymbolNewtona3 (int n, int k)
{
	if(k==n||k==0) return 1;
	else return SymbolNewtona2(n-1, k-1)*(n/k);
}

main()
{
	int n, k;
	printf("Program liczy symbol Newtona\n");

	printf("\nPodaj n: ");
	scanf("%d", &n);
	printf("\nPodaj k: ");
	scanf("%d", &k);
	
	printf("\nSymbol Newtona(1) wynosi %d", SymbolNewtona1(n, k));
	printf("\nSymbol Newtona(2) wynosi %d", SymbolNewtona2(n, k));
	printf("\nSymbol Newtona(3) wynosi %d", SymbolNewtona3(n, k));

	getch();
	return 0;
}
