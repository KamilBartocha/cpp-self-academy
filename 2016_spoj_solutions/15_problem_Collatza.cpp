#include <iostream>
 
using namespace std;
 
int main()
{
    int t;
    cin>>t;
    for (int i=1; i<=t; i++)
    {
        int l=0, s;
        cin>>s;
        while(s!=1)
        {
            if (s%2==0)
            {
                s=s/2;
                l++;
            }
            else if (s%2!=0)
            {
                s=3*s+1;
                l++;
            }
        }
        cout<<l<<endl;
    }
 
    return 0;
}
 
