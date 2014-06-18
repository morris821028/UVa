#include<iostream>
#include<cstdio>
using namespace std;
#define MOD 9999997


int n,m;
double dp[1000][100],dp2[1000], pam[1000][100],pbm[1000][100],pa,pb;
int vam[1000][100],vbm[1000][100],va,vb;
bool done2[1000],done[1000][100];


double dfs(int a,int b);

double dfs2(int a)
{
	if(a==n)
	{
		return pa*va+pb*vb;
	}
	if(!done2[a])
	{
		done2[a]=1;
		dp2[a]=0;
		for(int fh1=0;fh1<m;fh1++)
			dp2[a]=max(dp2[a],dfs(a,fh1));
	}
	return dp2[a];
}

double dfs(int a,int b)
{
	if(!done[a][b])
	{
		done[a][b]=1;
		double mx = dfs2(a+1);
		
		dp[a][b] = max((double)vam[a][b],mx)*pam[a][b]+max((double)vbm[a][b],mx)*pbm[a][b];
		
	}
	return dp[a][b];
}
int t,h1, h2;
int main(){
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&m);
		for(h1=0;h1<n;h1++)
		{
			done2[h1]=0;
			for(h2=0;h2<m;h2++)
				scanf("%lf%d%lf%d",&pam[h1][h2],&vam[h1][h2],&pbm[h1][h2],&vbm[h1][h2]),done[h1][h2]=0;
			
		}
		scanf("%lf%d%lf%d",&pa,&va,&pb,&vb);
		printf("%.0lf\n",dfs2(0)-0.5);
	}
}
