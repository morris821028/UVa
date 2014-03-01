#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<cstdlib>
#include <math.h>
#include<map>
#define mem(x) memset(x,0,sizeof(x))
using namespace std;

typedef long long ll;

#define MOD 1000000007LL


bool done[201][201][2],first;

int dp[201][201][2],h1,h2,h3,cm[300],dm[300],n,pre1[201][201][2],pre2[201][201][2],pre3[201][201][2];


void upt(int fh1,int fh2,int fh3,int fw,int p1,int p2,int p3)
{
    //cout<<"de"<<fh1<<' '<<fh2<<' '<<fh3<<' '<<fw<<' '<<p1<<' '<<p2<<' '<<p3<<endl;
    if(fh1==0&&fh2==n-1)
    {
        if(first)
        {
            pre1[fh1][fh2][fh3] = p1;
            pre2[fh1][fh2][fh3] = p2;
            pre3[fh1][fh2][fh3] = p3;
            for(;fh1!=fh2;)
            {
                int t1=pre1[fh1][fh2][fh3],t2=pre2[fh1][fh2][fh3],t3=pre3[fh1][fh2][fh3];
                if(t1!=fh1)cout<<fh1+1<<' ';
                else cout<<fh2+1<<' ';
                fh1 = t1;
                fh2 = t2;
                fh3 = t3;

            }
            cout<<fh1+1<<endl;
        }
        first=0;

    }
    else
    if(!done[fh1][fh2][fh3]||dp[fh1][fh2][fh3]>fw)
    {
        done[fh1][fh2][fh3]=1;
        dp[fh1][fh2][fh3]=fw;
        pre1[fh1][fh2][fh3] = p1;
        pre2[fh1][fh2][fh3] = p2;
        pre3[fh1][fh2][fh3] = p3;
    }
}

int main(){
    while(~scanf("%d",&n))
    {
        mem(done);
        for(h1=0;h1<n;h1++)
        {
            scanf("%d",&cm[h1]);
        }
        for(h1=0;h1<n;h1++)
        {
            scanf("%d",&dm[h1]);
            upt(h1,h1,0,0,-1,-1,-1);
        }

        first = 1;

        for(h1=0;h1<n;h1++)
            for(h2=0;h2+h1<n;h2++)
            {
                //h2 , h2+h1
                if(done[h2][h2+h1][0])
                {
                    if(h2!=0&&cm[h2-1]-dp[h2][h2+h1][0]>dm[h2]-dm[h2-1])
                    {
                        upt(h2-1,h2+h1,0,dp[h2][h2+h1][0]+(dm[h2]-dm[h2-1]),h2,h2+h1,0);
                    }
                    if(h2+h1+1<n&&cm[h2+h1+1]-dp[h2][h2+h1][0]>dm[h2+h1+1]-dm[h2])
                    {
                        upt(h2,h2+h1+1,1,dp[h2][h2+h1][0]+(dm[h2+h1+1]-dm[h2]),h2,h2+h1,0);
                    }
                }

                if(done[h2][h2+h1][1])
                {
                    if(h2!=0&&cm[h2-1]-dp[h2][h2+h1][1]>dm[h2+h1]-dm[h2-1])
                    {
                        upt(h2-1,h2+h1,0,dp[h2][h2+h1][1]+(dm[h2+h1]-dm[h2-1]),h2,h2+h1,1);
                    }
                    if(h2+h1+1<n&&cm[h2+h1+1]-dp[h2][h2+h1][1]>dm[h2+h1+1]-dm[h2+h1])
                    {
                        upt(h2,h2+h1+1,1,dp[h2][h2+h1][1]+(dm[h2+h1+1]-dm[h2+h1]),h2,h2+h1,1);
                    }
                }

            }
        if(first)cout<<"Mission Impossible"<<endl;
    }

    return 0;
}
/*
2
2 2
aaaa

4
4 4 4 4
ttttttttttttttt
ttttttttttttt


*/
