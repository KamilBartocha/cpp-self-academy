#include <iostream>
using namespace std;
int main()
{
    int a=0, b=0, c=1, d=0, tab[100000];
    while(cin>>tab[a])
    {
        a++;
    }
    while(c<=3)
    {
        if(tab[b+1]==42&&tab[b]!=42)
        {
            c++;
            b++;
        }
        else
        {
            b++;
        }
    }
    while(b>0)
    {
        cout<<tab[d]<<endl;
        b--;
        d++;
    }
    cout<<42<<endl;
    return 0;
}
