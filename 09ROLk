#include <iostream>
using namespace std;
int main()
{
    int liczba , m, n=0, s=0, t=1;
    cin>>liczba>>m;
    int tab[liczba],tab2[liczba];
 
    // wczytywanie tablicy
    for(int l=1; l<=liczba; l++)
    {
        cin>>tab[l-1];
    }
    // zamiana
    while(t<=liczba)
    {
        if (m<=liczba-1)
        {
            tab2[s]=tab[m];
            s++;
        }
        else if (m>liczba-1)
        {
            tab2[s]=tab[n];
            n++, s++;
        }
        m++,  t++;
    }
// wyswietalnie tablicy
    for(int a=1; a<=liczba; a++)
    {
        cout<<tab2[a-1]<<" ";
    }
    cout<<""<<endl;
    return 0;
} 
