#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <ctime>
using namespace std;

const int Nd = 103;
int N,ok,tot = 0;
int s[Nd][Nd],n[Nd],stk[Nd][Nd],vis[Nd];

typedef struct A{
	int st,ed;
}AA;
AA a[1003];

void dfs(int x,int sc){
	if(vis[x]==1)	return ;
	vis[x] = 1;
	if(n[x]<sc-1){
		ok = 1;
		tot++;
		return ;
	}
	for(int i=1;i<=100;i++){
		if(s[x][i]>0){
			dfs(i,sc);
			if(ok==1){
				int w = -1;
				for(int j=0;j<n[x] && w==-1;j++)
					if(a[stk[x][j]].st <= i && a[stk[x][j]].ed >= i)
						w = j;
				int id = stk[x][w];
				for(int j=w+1;j<n[x];j++)
					stk[x][j-1] = stk[x][j];
				n[x]--;
				for(int j=a[id].st;j<=a[id].ed;j++)
					s[x][j]--;
				stk[i][n[i]] = id;
				n[i]++;
				for(int j=a[id].st;j<=a[id].ed;j++)
					s[i][j]++;
				break;
			}
		}
	}
}

int main(){
	
	int T,test = 0, cases = 0;
	scanf(" %d",&T);
	for(int t=0;t<T;t++){
		scanf(" %d",&N);
		if(N>1000)	while(1);
		memset(s,0,sizeof(s));
		memset(n,0,sizeof(n));
		for(int i=0;i<N;i++){
			int mini;
			scanf(" %d %d",&a[i].st,&a[i].ed);
			if(a[i].st>a[i].ed)	while(1);
			mini = a[i].st;
			for(int j=a[i].st;j<=a[i].ed;j++)
				if(n[j] < n[mini])
					mini = j;
			stk[mini][n[mini]] = i;
			n[mini]++;
			for(int j=a[i].st;j<=a[i].ed;j++)
				s[mini][j]++;
			memset(vis,0,sizeof(vis));
			ok = 0;
			dfs(mini,n[mini]);
		}
		int ans = 0;
		for(int i=1;i<=100;i++)
			ans += n[i]*n[i], test = max(test,n[i]);
		printf("%d\n",ans);
		cases++;
        fprintf (stderr, "%d / %d = %.2f | %.2f\n", cases, T, (double)clock () / CLOCKS_PER_SEC, ((double)clock () / cases * T) / CLOCKS_PER_SEC);
	}
//	printf("test = %d, total transmit = %d\n",test,tot);

	return 0;
}
