#include<iostream>
#include<cstdio>
using namespace std;
#define MOD 9999997


int dp[2002][2002],ans,n;

int main(){
	
	dp[1][1] = 1;
	
	for(int fh1=1;fh1<=2000;fh1++)
	{
		for(int fh2=1;fh2<=fh1;fh2++)
		{
			(dp[fh1+1][fh2+1] += dp[fh1][fh2])%=MOD;
			(dp[fh1+1][fh2] += ((long long)dp[fh1][fh2]*fh2)%MOD)%=MOD;
		}
	}
	while(~scanf("%d",&n))
	{
		int ans=0;
		for(int fh1=0;fh1<=n;fh1++)
			(ans += dp[n][fh1])%=MOD;
		cout<<ans<<endl;
	}
}
