/*#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

double x;
int xm[10001],ym[10001],n;

bool check(double r){
	
	double mnx = -100000, mxx = 100000;
	
	for(int fh1=0;fh1<n;fh1++){
		double d = r*r - ym[fh1]*ym[fh1];
		if(d<0){
			return 0;
		}
		
		d = sqrt(d);
		
		double nmnx = xm[fh1]-d,nmxx = xm[fh1]+d;
		
		if(nmnx > mxx || mnx > nmxx)
			return 0;
		
		mnx = max(mnx, nmnx);
		mxx = min(mxx, nmxx);
		
	}
	x = mxx;
	return 1;
}

int y,h1;

int main(){
	while(~scanf("%d",&n)&&n){
		scanf("%d",&y);
		
		for(h1=0;h1<n;h1++){
			scanf("%d%d",&xm[h1],&ym[h1]);
			ym[h1] -= y;
		}
		
		double upper = 70711, lower = 0;
		
		int iter = 1000;
		
		while(iter --){
			double mid = (upper + lower)*0.5;
			if(check(mid)){
				upper = mid;
			}
			else
				lower = mid;
		}
		printf("%.0lf %.0lf\n", x, upper);
		
	}
}

*/
#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;


bool dfs(int* m1, int* m2, int idx){
	if(idx == 0){
		return m1[0]>=m2[0];
	}
	if(m2[idx]>m1[idx])
		return 0;
	m1[idx]-=m2[idx];
	m1[idx-1] = m1[idx]*4;
	return dfs(m1,m2,idx-1);
}

bool check(int k, int* m2){
	int m1[7]={};
	int val[7]={1,2,4,8,16,32,64};
	int rx = k, ry = k, prex = 0, prey = 0;
	for(int fh1=6;fh1>=0;fh1--){
		m1[fh1] += (rx/val[fh1])*prey+(ry/val[fh1])*prex + (rx/val[fh1])*(ry/val[fh1]);
		prex += rx - (rx%val[fh1]);
		prey += ry - (ry%val[fh1]);
		rx %= val[fh1];
		ry %= val[fh1];
		
	}
	dfs(m1,m2,6);
}

int main(){
	int h1,m1[7];
	while(~scanf("%d",&m1[0])&&m1[0]){
		for(h1=1;h1<7;h1++){
			scanf("%d",&m1[h1]);
		}
		
		int upper = 320000, lower = 0;
		while(upper > lower){
			int mid = (upper+lower)/2;
			int mm[7];
			memcpy(mm,m1,sizeof(mm));
			if(check(mid,mm)){
				upper = mid;
			}
			else{
				lower = mid + 1;
			}
		}
		
		
		if(upper-1>=0&&check(upper,m1))upper --;
		cout<<upper<<endl;
		
	}
}
