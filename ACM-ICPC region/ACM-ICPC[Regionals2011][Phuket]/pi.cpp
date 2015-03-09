#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#define mem(x) memset(x,0,sizeof(x));
using namespace std;

int m1[20001],ans,h1,h2,h3,t,n,cc;
vector<int> em[20001],em2[20001];

int c2(int nd,int pa);

int collect(int nd,int pa) // 扣多少，從哪裡過來
{
    int ss=0;
    for(int fh1=0;fh1<em[nd].size();fh1++)
    {
        if(pa!=em[nd][fh1])
        {

            ss += collect(em[nd][fh1],nd);
        }
    }
    for(int fh1=0;fh1<em2[nd].size();fh1++)
    {
        if(pa!=em2[nd][fh1])
        {
            cout<<em2[nd][fh1]<<'a'<<endl;
            int ret = c2(em2[nd][fh1],nd);
            ss -= ret;
            cout<<ret<<'a'<<endl;
        }
    }

    if(ss<=0)
    {
        ans += -ss;
        if(nd!=0)ans ++;
        return 1;
    }
    else
    return ss;
}

int c2(int nd,int pa) // 扣多少，從哪裡過來
{
    int ss=0;
    for(int fh1=0;fh1<em2[nd].size();fh1++)
    {
        if(pa!=em2[nd][fh1])
        {
            ss += c2(em2[nd][fh1],nd);
        }
    }
    for(int fh1=0;fh1<em[nd].size();fh1++)
    {
        if(pa!=em[nd][fh1])
        {
            ss -= collect(em[nd][fh1],nd);
        }
    }

    if(ss<=0)
    {
        ans += -ss;
        if(nd!=0)ans++;
        return 1;
    }
    else
    return ss;
}

int main() {
    cin>>t;
    while(t--)
    {
        cin>>n;

        for(h1=0;h1<n;h1++)
        {
            em[h1].clear();
            em2[h1].clear();
        }
        for(h1=1;h1<n;h1++){
            scanf("%d%d",&h2,&h3);
            em[h2].push_back(h3);
            em2[h3].push_back(h2);
        }
        int tar=99999999;
        ans = 0;

        collect(0,-1);
        tar = min(tar,ans);
        cout<<ans<<endl;

        c2(0,-1);

        cout<<ans<<endl;
        tar = min(tar,ans);
        cout<<"Case "<<++cc<<": "<<tar<<endl;
    }
}
/*
100
2
1 0
*/
