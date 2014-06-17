#include <cstdio>
#include <iostream>
#include <cstring>
#include <memory>
#define MAXN 10
#define MAXD 10000
using namespace std;

int dp[1<<MAXN][MAXD+1];
int factorial[MAXN+1],digit[MAXN+1],cnt[MAXN+1];
char s[MAXN+1];
int n,d;

void initialize()
{
    int i;
    factorial[0]=1;
    for(i=1;i<=MAXN;i++)
    {
        factorial[i]=factorial[i-1]*i;
    }
}

int DFS(int mask,int remainder)
{
    int i,sum;
    if(dp[mask][remainder]!=-1)
    {
        return dp[mask][remainder];
    }
    else
    {
        if(mask==(1<<n)-1)
        {
            if(remainder==0)
            {
                sum=1;
            }
            else
            {
                sum=0;
            }
        }
        else
        {
            sum=0;
            for(i=0;i<n;i++)
            {
                if((mask&(1<<i))==0)
                {
                    sum=sum+DFS(mask|(1<<i),(remainder*10+digit[i])%d);
                }
            }
        }
        dp[mask][remainder]=sum;
        return sum;
    }
}

int main()
{
    initialize();
    int i,k,t,ans;
    scanf("%d",&t);
    for(k=0;k<t;k++)
    {
        scanf("%s %d",s,&d);
        n=strlen(s);
        memset(dp,-1,sizeof(dp));
        memset(cnt,0,sizeof(cnt));
        for(i=0;i<n;i++)
        {
            digit[i]=(int)(s[i]-'0');
            cnt[digit[i]]++;
        }
        ans=DFS(0,0);
        for(i=0;i<MAXN;i++)
        {
            ans=ans/factorial[cnt[i]];
        }
        printf("%d\n",ans);
    }
    return 0;
}
