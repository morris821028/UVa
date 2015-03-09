#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#define mem(x) memset(x,0,sizeof(x));
#define PB(x) push_back(x)
using namespace std;

bool tem[10000000];
vector<int>pm;
typedef long long ll;

ll ans,h1,h2,q;

int main(){
    pm.PB(2);
    pm.PB(3);
    for(h1=3;h1*h1<10000000;h1+=2)
    {
        if(!tem[h1])
            for(h2=h1*h1;h2<10000000;h2+=h1+h1)
                tem[h2]=1;

    }
    for(;h1<10000000;h1+=2)
        if(!tem[h1])
            pm.PB(h1);

    while((cin>>q)&&q)
    {
        ans = 1;
        q += q;
        for(h1=0;h1<pm.size()&&q!=1;h1++)
        {
            if(q%pm[h1]==0)
            {
                int t=2;
                while((q/=pm[h1])%pm[h1]==0)t++;
                ans *= t;
            }
        }
        if(q!=1)ans *=2;
        cout<<ans<<endl;
    }

}
