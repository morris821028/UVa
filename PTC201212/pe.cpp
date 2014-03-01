#include<iostream> 
#include<map> 
#include<math.h> 
#include<vector> 
#include<string> 
#include<string.h> 
#include<cstdio> 
#include<queue> 
#include<algorithm> 
#include<sstream> 
#define all(X) (X).begin(),(X).end() 
#define mem(X) memset(X,0,sizeof(X)) 
#define debug_v(v) for(int db=0;db<(v).size();db++)cout<<v[db]<<','<<;cout<<endl; 
#define pqpush(pq,x,cmp) (pq).push_back(x);push_heap((pq).begin(),(pq).end(),cmp); 
#define pqpop(pq,cmp) pop_heap((pq).begin(),(pq).end(),cmp);(pq).pop_back(); 
#define PB(x) push_back(x) 
using namespace std; 
typedef long long ll; 
typedef vector<int>::iterator iv; 
typedef map<string,int>::iterator msii; 
typedef map<int,int>::iterator miii; 
typedef map<int,bool>::iterator mibi; 
typedef map<string,bool>::iterator msbi; 
typedef map<string,int> msi; 
typedef map<int,int> mii; 
typedef map<int,bool> mib; 
typedef map<string,bool> msb; 
typedef vector<int> vi; 
typedef vector<string> vs; 


bool done[10001];
int dp[10001],n,m,p[10001],h1,h2;

ll ans;

int dfs(int nd)
{
	if(!done[nd])
	{
		done[nd] = 1;
		
		dp[nd]=0;
		
		for(int h1=min(m,nd);h1>0;h1--)
			dp[nd] = max(dp[nd],dfs(nd-h1)+p[h1]);
		
	}
	//cout<<nd<<' '<< dp[nd]<<endl;
	return dp[nd];
}

bool first = 1;

int main(){
	while(~scanf("%d",&m),m)
	{
		if(first)first = 0;
		else putchar(10);
		mem(done);
		for(h1=1;h1<=m;h1++)
			scanf("%d",&p[h1]);
		scanf("%d",&n);
		done[0] = 1;
		dp[0] = 0;
		ans = 0;
		for(h1=0;h1<n;h1++)
		{
			scanf("%d",&h2);
			ans += dfs(h2);
		}
		cout<<ans;
	}
}


