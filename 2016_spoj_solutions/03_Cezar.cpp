#include <iostream>
 
using namespace std;
 
int main()
{
    string a;
    char tab[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    while (getline(cin, a))
    {
    	int l, i=0;
    	string b;
        l=a.length();
        while(i<l)
        {
            int j=0;
            while(j<26)
            {
                if (a[i]==tab[j])
                {
                    b+=tab[j+3];
                    j++;
                    break;
                }
				else if (int(a[i])==32)
                {	
                	b+=" ";
                    j++;
                    break;
                }
                else if (a[i]=='X')
                {
                    b+=tab[0];
                    j++;
                    break;
                }
                else if (a[i]=='Y')
                {
                    b+=tab[1];
                    j++;
                    break;
                }
                else if (a[i]=='Z')
                {
                    b+=tab[2];
                    j++;
                    break;
                }
				else
                {
                    j++;
                }
            }
            i++;
        }
 
        cout<<b<<endl;
    }
 
    return 0;
}
 
