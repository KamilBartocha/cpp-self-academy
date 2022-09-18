#include <iostream>
 
using namespace std;
float a, b, c, x;
 
int main()
{
    cin>>a>>b>>c;
    if((a!=0) && (b!=0) && (c!=0))
    {
         x=(c-b)/a;
         cout.precision(2);
         cout<<fixed<<x;
    }
    else if (a==0  && b!=0 && c!=0 && c!=b)
        cout<<\"BR\";
    else if (a==0 && b==c)
        cout<<\"NWR\";
 
    return 0;
}
 
