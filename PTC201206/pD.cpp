#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int dir[2][4]={{-1,-1,0,0},{-1,0,-1,0}};
long long F[220][100][100];
int a[100][100];
int n,m;
int Max(int x,int y)
{
    if (x>y) return x;
    else return y;
}
int Min(int x,int y)
{
    if (x>y) return y;
    else return x;
}
int main()
{
    while(scanf("%d%d",&n,&m) == 2) {
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            scanf("%d",&a[i][j]);
    memset(F,0,sizeof(F));
    int x;
    for (int k=2;k<=n+m;k++)
        for (int i1=1;i1<=Min(n,k-1);i1++)
            for (int i2=1;i2<=Min(n,k-1);i2++)
            {
                x=a[i1][k-i1]+a[i2][k-i2];
                if (i1==i2) x=a[i1][k-i1];
                for (int i=0;i<=3;i++)
                    F[k][i1][i2]=Max(F[k][i1][i2],F[k-1][i1+dir[0][i]][i2+dir[1][i]]);
                F[k][i1][i2]+=x;
            }
    printf("%lld\n",F[n+m][n][n]);
    }
    return 0;
}
