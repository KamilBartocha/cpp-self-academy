#include<iostream>
 
using namespace std;
 
int main()
{
    int a, b, c;
    int t;
    cin>>t;
    for(int i=1; i<=t; i++)
    {
        int d;
        double jednosci=0;
        cin>>a>>b;
        d=a;
        for(int l=1; l<=b-1; l++)
        {
            a*=d;
            jednosci=a%10;
        }
 
        cout<<jednosci<<endl;
    }
    return 0;
}
 
