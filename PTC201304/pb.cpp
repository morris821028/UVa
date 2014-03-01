#include<iostream>
#include<cstdio>
using namespace std;

bool done[100][100][100],dp[100][100][100];

bool dfs(int fh1,int fh2, int fh3){
	
	int mn = min(fh1,min(fh2,fh3)), mx = max(fh1,max(fh2,fh3)), mid = fh1+fh2+fh3-mn-mx;
	
	if(!done[mn][mid][mx]){
		done[mn][mid][mx] = 1;
		dp[mn][mid][mx] = 0;
		for(int fh4 = 1;fh4<=mn;fh4++)
			if(!dfs(mn-fh4,mid,mx)||!dfs(mn,mid-fh4,mx)||!dfs(mn,mid,mx-fh4)||
			!dfs(mn-fh4,mid-fh4,mx)||!dfs(mn,mid-fh4,mx-fh4)||!dfs(mn-fh4,mid,mx-fh4)||
			!dfs(mn-fh4,mid-fh4,mx-fh4))
			{
				dp[mn][mid][mx] = 1;
				break;
			}
		if(dp[mn][mid][mx])return 1;
		
		for(int fh4 = mn+1;fh4<=mid;fh4++)
			if(!dfs(mn,mid-fh4,mx)||!dfs(mn,mid,mx-fh4)||!dfs(mn,mid-fh4,mx-fh4))
			{
				dp[mn][mid][mx] = 1;
				break;
			}
		if(dp[mn][mid][mx])return 1;
		for(int fh4 = mid+1;fh4<=mx;fh4++)
			if(!dfs(mn,mid,mx-fh4))
			{
				dp[mn][mid][mx] = 1;
				break;
			}
	}
	
	return dp[mn][mid][mx];
}

int main(){
	int h1,m1[3];
	while(1){
		for(h1=0;h1<3;h1++){
			if(!~scanf("%d",&m1[h1])){
				break;
			}
		}
		if(h1!=3)break;
		
		printf(dfs(m1[0],m1[1],m1[2])?"w\n":"l\n");
		
	}
}
