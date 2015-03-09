#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <cstdlib>
#define mem(x) memset(x,0,sizeof(x));
#define PB(x) push_back(x)
using namespace std;

bool tem[10000000];
vector<int>pm;
typedef long long ll;

ll ans,h1,h2,q;

int main(){
    pm.PB(2);
    for(h1=3;h1*h1<10000000;h1+=2)
    {
        if(!tem[h1])
        {
            pm.PB(h1);
            //cout<<h1<<endl;
            //system("pause");
            for(h2=h1*h1;h2<10000000;h2+=h1+h1)
                tem[h2]=1;

        }

    }
    for(;h1<10000000;h1+=2)
        if(!tem[h1])
            pm.PB(h1);
    for(int i = 1; i <= 100; i++) {
        int cnt = 0;
        for(int j = 1; j <= i; j++)
            if(i%j == 0)
                cnt++;
    }
    while((cin>>q)&&q)
    {
        ans = 1;
        q*=q;
        q += q;
        for(h1=0;h1<pm.size()&&pm[h1]*pm[h1]<=q&&q!=1;h1++)
        {
            if(q%pm[h1]==0)
            {
                int t=2;
                //cout<<pm[h1]<<endl;
                while((q/=pm[h1])%pm[h1]==0)t++;
                //cout<<t<<endl;
                ans *= t;
            }
        }
        if(q!=1)ans *= 2;
        cout<<ans<<endl;
    }

}
