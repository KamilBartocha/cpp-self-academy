#include <iostream>
#include <math.h>
 
using namespace std;
int main()
{
    int a, t;
    float  p;
    long int b;
    cin>>t;
    for(int l=1; l<=t; l++)
    {
        int suma=0;
        float c=0;
        cin>>a;
        cin>>b;
        int tab[a];
 
        for(int i=1; i<=a; i++)
        {
            cin >> tab[i-1];
            floor(suma=86400/tab[i-1]);
            c=c+suma;
        }
        p=c/b;
        cout<<ceil(p)<<endl;
    }
 
 
    return 0;
}
 
