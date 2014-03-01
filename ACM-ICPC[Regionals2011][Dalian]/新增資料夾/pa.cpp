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

int n,h1,lm[4],h2,llm[100];
char tars[10000];

bool dfs(int tar, int sno, int lp,vector<string> ans,vector<int> stk)
{
    while(1)
    {
        if(lp==lm[sno])
        {
            //cout<<tar<<" pop "<<endl;
            if(stk.empty())return !tars[tar];
            lp = stk.back();
            stk.pop_back();
            sno = stk.back();
            stk.pop_back();
        }
        else if(ans[sno][lp]=='?')
        {
            //cout<<sno<<' '<<lp<<endl;
            ////cout<<"current:\n";
            //for(int fh1=0;fh1<n;fh1++)
            //    cout<<ans[fh1]<<endl;
            //    cout<<"stk: ";
            //for(int fh1=0;fh1<stk.size();fh1++)
            //    cout<<stk[fh1]<<' ';
            //cout<<endl;

            ans[sno][lp]=tars[tar];
            //cout<<"to: "<<tars[tar]<<endl;
            //system("pause");
            if(dfs(tar+1,sno,lp+1,ans,stk))return 1;



            for(int fh1=sno+1;fh1<n;fh1++)
            {
                ans[sno][lp]=fh1+'0';
                //cout<<sno<<' '<<lp<<endl;
                //cout<<"to: "<<char(fh1+'0')<<endl;
                //system("pause");
                if(dfs(tar,sno,lp,ans,stk))return 1;
            }
            return 0;
        }
        else if(ans[sno][lp]<'0'+n)
        {
            //cout<<"number"<<sno<<' '<<lp+1<<endl;
            stk.push_back(sno);
            stk.push_back(lp+1);
            sno = ans[sno][lp]-'0';
            lp = 0;
        }
        else
        {
            //cout<<sno<<' '<<lp<<"mt"<<' '<<tars[tar]<<endl;
            if(!tars[tar])return 0;

            if(ans[sno][lp]!=tars[tar])
                return 0;
            //cout<<"successful\n";
            tar++;
            lp++;
        }
    }
}

bool dfs2(int aa)
{
    if(aa==n)
    {
        vector<string> ans;//lm[0]=lm[1]=2;
        for(h1=0;h1<n;h1++)
        {
            string ss="";
            for(h2=0;h2<lm[h1];h2++)ss+='?';
            ans.push_back(ss);
            //cout<<ss<<endl;
        }
        //cout<<endl;
        //system("pause");
        //cout<<"************************"<<endl;
        return dfs(0,0,0,ans,vector<int>());
    }
    else
    {
        for(int fh1=1;fh1<=llm[aa];fh1++)
        {
            lm[aa]=fh1;
            if(dfs2(aa+1))return 1;
        }
    }
    return 0;
}
int main(){
    while(~scanf("%d",&n))
    {

        for(h1=0;h1<n;h1++)
        {
            scanf("%d",&llm[h1]);
        }
        scanf("%s",tars);


        printf(dfs2(0)?"Yes":"No");
        cout<<endl;

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
