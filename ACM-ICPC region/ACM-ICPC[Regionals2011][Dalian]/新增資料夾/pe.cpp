#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
#include<map>
#define mem(x) memset(x,0,sizeof(x))
using namespace std;

typedef long long ll;

#define MOD 1000000007

ll sm[10000],dp[1003][1003];
int h1,h2;
char s[10000];

ll cons(int fh2,int fh3)
{
    return (sm[fh3]-sm[fh2-1]+MOD)%MOD;
}

int main(){
    while(~scanf("%s",s))
    {
        for(h1=1;h1<=1001;h1++)
        {
            dp[1][h1] = 0;
        }
        dp[1][1]=1;

        for(h1=0;s[h1];h1++)
        {
            //h1+2
            sm[0]=0;
            for(h2=1;h2<=h1+1;h2++)
            {
                (sm[h2]=dp[h1+1][h2]+sm[h2-1])%=MOD;
                //cout<<' '<<sm[h2];
            }
            //cout<<endl;

            for(h2=1;h2<=h1+2;h2++)
            {
                if(s[h1]=='I') dp[h1+2][h2] = cons(1,h2-1);
                else if(s[h1]=='D') dp[h1+2][h2] = cons(h2,h1+1);
                else dp[h1+2][h2] = cons(1,1+h1);
                //cout<<"DP"<<"[ "<<h1+2<<" , "<<h2<<" ]="<< dp[h1+2][h2]<<endl;
            }

        }
        ll ans = 0;
        h1++;
        //cout<<++h1<<endl;
        for(h2=1;h2<=h1;h2++)
        {
            (ans += dp[h1][h2])%=MOD;
        }
        cout<<ans<<endl;
    }
}
