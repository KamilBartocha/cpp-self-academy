#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
struct wsp
{
    int x,y;
};
int main()
{
    int t;
    cin>>t;
    for(int y=1; y<=t; y++)
    {
        int i,det;
        wsp punkty[3];
        for (i=1; i<4; i++)
        {
            cin>>punkty[i-1].x;
            cin>>punkty[i-1].y;
        }
        det=punkty[0].x*punkty[1].y+punkty[1].x*punkty[2].y+punkty[2].x*punkty[0].y-punkty[2].x*punkty[1].y-punkty[0].x*punkty[2].y-punkty[1].x*punkty[0].y;
 
        if (det==0) cout<<"TAK"<<endl;
        else cout<<"NIE"<<endl;
    }
    return 0;
}
