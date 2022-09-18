#include <iostream>
 
using namespace std;
 
int main()
{
    int te;
    cin>>te;
    for(int i=1; i<=te; i++)
    {
        string pesel;
        cin>>pesel;
        int wynik;
        int x=pesel[0];
        x=(x-48)*1;
        int q=pesel[1];
        q=(q-48)*3;
        int w=pesel[2];
        w=(w-48)*7;
        int e=pesel[3];
        e=(e-48)*9;
        int r=pesel[4];
        r=(r-48)*1;
        int a=pesel[5];
        a=(a-48)*3;
        int t=pesel[6];
        t=(t-48)*7;
        int y=pesel[7];
        y=(y-48)*9;
        int u=pesel[8];
        u=(u-48)*1;
        int o=pesel[9];
        o=(o-48)*3;
        int p=pesel[10];
        p=(p-48)*1;
 
 
        wynik=(x+q+w+e+r+t+y+u+o+p+a)%10;
        if(wynik==0)
        {
            cout<<"D"<<endl;
        }
        else
        {
            cout<<"N"<<endl;
        }
    }
    return 0;
}
 
