clude <iostream>
#include <sstream>
 
using namespace std;
 
int main()
{
    int t;
    cin>>t;
    for(int i=1; i<=t; i++)
    {
        int l, j=0, x ;
        string a,b;
        cin>>a;
        l=a.length();
        while(l>j)
        {
            if (a[j]!=a[j+1])
            {
                b+=a[j];
                j++;
            }
            else if (a[j]==a[j+1])
            {
 
                if(a[j+1]!=a[j+2])
                {
                    b+=a[j];
                    j++;
 
                }
                else if(a[j+1]==a[j+2])
                {
                    if(a[j+2]!=a[j+3])
                    {
                        x=3;
                        ostringstream ss;
                        ss << x;
                        string str = ss.str();
                        b+=a[j];
                        b+=str;
                        j+=x;
                    }
                    else
                    {
                        x=0;
                        while(a[j+2]==a[j+3])
                        {
                            j++;
                            x++;
                        }
                        x+=3;
                        ostringstream ss;
                        ss << x;
                        string str = ss.str();
                        b+=a[j];
                        b+=str;
                        j+=3;
                    }
 
                }
            }
        }
 
        cout<<b<<endl;
    }
 
    return 0;
}
