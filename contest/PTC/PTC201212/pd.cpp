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


bool done[100];
int dp[100],n,m,h1,h2,ans,w[100],h[100],l[100],r[100],m1[100];

void upt(int fh1,int fw)
{
	ans = max(ans,fw);
	if(!done[fh1]||dp[fh1]<fw)
	{
		done[fh1] = 1;
		dp[fh1] = fw;
	}
}

bool cmp(int fh1,int fh2)
{
	return w[fh1]*h[fh1]<w[fh2]*h[fh2];
}

bool chk(int fh1,int fh2)
{
	bool ret = 0;
	if(cmp(m1[fh1],m1[fh2]))
	{
		int x1 = l[m1[fh1]], x2 = l[m1[fh1]]+w[m1[fh1]], y1 = r[m1[fh1]], y2 = r[m1[fh1]]+h[m1[fh1]];
		int xx1 = l[m1[fh2]], xx2 = l[m1[fh2]]+w[m1[fh2]], yy1 = r[m1[fh2]], yy2 = r[m1[fh2]]+h[m1[fh2]];
		if((x1<=xx1 && xx1 <= x2)|| (x1<=xx2 && xx2 <= x2))ret = 1;
		else ret = 0;
		swap(x1,xx1);
		swap(x2,xx2);
		if(ret==0){
		if((x1<=xx1 && xx1 <= x2)|| (x1<=xx2 && xx2 <= x2))ret = 1;
		else ret = 0;}
		if(ret)
		{
			if((y1<=yy1 && yy1 <= y2)|| (y1<=yy2 && yy2 <= y2))ret = 1;
			else ret = 0;
			swap(y1,yy1);
			swap(y2,yy2);
			if(ret==0){
			if((y1<=yy1 && yy1 <= y2)|| (y1<=yy2 && yy2 <= y2))ret = 1;
			else ret = 0;}
			if(ret)return 1;
		}
	}
	return 0;
}

int main(){
	while(~scanf("%d%d%d",&n,&h1,&h2)&&(n||h1||h2))
	{
		mem(done);
		for(h1=0;h1<n;h1++)
		{
			scanf("%d%d%d%d",&l[h1],&r[h1],&w[h1],&h[h1]);
			m1[h1]=h1;
			upt(h1,1);
		}
		sort(m1,m1+n,cmp);
		
		ans = 0;
		
		
		for(h1=0;h1<n;h1++)
		{
			if(done[h1])
			{
				for(h2=h1+1;h2<n;h2++)
					if(chk(h1,h2))
					{
						//cout<<"yes"<<h1<<' '<<h2<<endl;
						upt(h2,dp[h1]+1);
					}
			}
		}
		cout<<ans<<endl;
		
	}
}


