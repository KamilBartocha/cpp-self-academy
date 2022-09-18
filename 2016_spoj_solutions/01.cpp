#include <iostream>
 
using namespace std;
 
int main()
{
    int a, t;
    cin>>t;
    for(int l=1;l<=t;l++)
    {
        int suma=0;
        cin>>a;
        int tab[a];
        for(int i=1;i<=a;i++)
            {
            cin >> tab[i-1];
            suma = suma+tab[i-1];
            }
 
        cout<<suma<<endl;
    }
 
 
    return 0;
}
 
