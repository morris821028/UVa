#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <algorithm>
#define MAX 1<<29
using namespace std;

typedef struct List{
    int x,y;
}LIST;
LIST list[1005];
int dp[1005];

int com(const void *a,const void *b);

main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);

    int T,t,N,n,i,j;
    scanf(" %d",&T);
    for(t=0;t<T;t++){
        scanf(" %d",&N);
        for(n=0;n<N;n++)
            scanf(" %d %d",&list[n].x,&list[n].y);
        qsort(list,N,sizeof(list[0]),com);
        memset(dp,0,sizeof(dp));
        for(i=0;i<N;i++){
            int c = 0;
            if(i+1<N && list[i+1].x==list[i].x)
                continue;
            for(j=i;j>=0;j--){
                if(list[i].x>=list[j].x && list[i].x<=list[j].y)    c++;
                int tmp = c;
                if(tmp<3)
                    tmp = 0;
                if(j!=0)
                    dp[i] = max(dp[i],dp[j-1]+tmp);
                else
                    dp[i] = max(dp[i],tmp);
            }
        }
        int M = 0;
        for(i=0;i<N;i++)
            M = max(M,dp[i]);
        printf("Case #%d: %d\n",t+1,M);
    }
}
int com(const void *a,const void *b)
{
    LIST c,d;
    c = *(LIST*)(a);
    d = *(LIST*)(b);
    if(c.x!=d.x)
        return c.x>d.x?1:-1;
    else if(c.y!=d.y)
        return c.y>d.y?1:-1;
    return 0;
}
