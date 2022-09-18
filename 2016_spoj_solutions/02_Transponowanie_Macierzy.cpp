#include <iostream>
using namespace std;
int main()
{
    int x, y;
    cin>>x>>y;
    int tab [x] [y];
    for(int i=0; i<x; i++)
    {
        for(int j=0; j<y; j++)
        {
            cin>>tab[i][j];
        }
        cout<<endl;
    }
 
    for(int i=0; i<y; i++)
    {
        for(int j=0; j<x; j++)
        {
            cout<<tab[j][i]<<" ";
        }
        cout<<endl;
    }
    return 0;
}
