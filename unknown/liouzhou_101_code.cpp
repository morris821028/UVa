//> http://140.122.185.166/ZeroJudge/ShowProblem?problemid=d012
//>
//> 如網址所附，一模一樣的題目，但測資不同，
//> 但不知道為什麼卡 WA line3，跪求指教。

//奇怪了，我的程式在那邊會莫名CE，真不知道是什麽回事。。。
//你看看吧：//當然，可能我的也會WA。。。

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<string>
#include<bitset>
#include<vector>
#include<set>
#include<map>
#include<queue>
#include<iomanip>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ld,ld> pdd;
typedef pair<ll,ll> pll;

#define X first
#define Y second

const int MaxN=110;
const ld pi=acos(-1);

int n;
pdd p[MaxN];
ld r[MaxN];

void init()
{
	cin>>n;
	for (int i=1;i<=n;++i)
		cin>>p[i].X>>p[i].Y>>r[i];
}

ld sqr(ld x)
{
	return x*x;
}

pdd operator - (pdd a,pdd b)
{
	return pdd(a.X-b.X,a.Y-b.Y);
}

pdd operator + (pdd a,pdd b)
{
	return pdd(a.X+b.X,a.Y+b.Y);
}

pdd operator * (pdd a,ld k)
{
	return pdd(a.X*k,a.Y*k);
}

ld mod(pdd a)
{
	return sqrt(sqr(a.X)+sqr(a.Y));
}

ld getdis(pdd a,pdd b)
{
	return mod(a-b);
}

ld atan2(pdd a)
{
	return atan2(a.Y,a.X);
}

void work()
{
	ld ans=0;
	for (int i=1;i<=n;++i)
	{
		vector<pdd> v;
		for (int j=1;j<=n;++j) if (i!=j)
		{
			ld d=getdis(p[i],p[j]);
			if (d>=r[i]+r[j]) continue;
			if (r[i]>r[j]&&d<=r[i]-r[j]) continue;
			if (r[i]<r[j]&&d<=r[j]-r[i])
			{
				v.push_back(pdd(-pi,pi));
				continue;
			}
			ld a=(d*d+r[i]*r[i]-r[j]*r[j])/2/d;
			ld x=sqrt(r[i]*r[i]-a*a);
			pdd w=p[j]-p[i];
			pdd e1=w*(a/d);
			pdd e2=pdd(-w.Y,w.X)*(x/d);
			pdd pL=e1-e2,pR=e1+e2;
			ld L=atan2(pL),R=atan2(pR);
			if (L<=R)
				v.push_back(pdd(L,R));
			else
			{
				v.push_back(pdd(L,pi));
				v.push_back(pdd(-pi,R));
			}
		}
		sort(v.begin(),v.end());
		ld x=-pi;
		ld s=0;
		for (int k=0;k<v.size();++k)
		{
			if (v[k].X>x)
				s+=v[k].X-x;
			x=max(x,v[k].Y);
		}
		s+=pi-x;
		ans+=s*r[i];
	}
	int x=0;
	while (ans>=10)
	{
		++x;
		ans/=10;
	}
	printf("%.2lf %d\n",(double)ans,x);
}

int main()
{
	int T;
	cin>>T;
	while (T--)
	{
		init();
		work();
	}
	return 0;
}
