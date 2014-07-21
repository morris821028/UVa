#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	int n, cases = 0;
	double v[32767];
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++)
			scanf("%lf", &v[i]);
			
		sort(v, v+n);
		int ret = 0, pos = 0;
		for(int i = 0; i < n; i++)
			if(v[i] > 0)
				pos ++;
		for(int i = 0; i < n; i++) {
			double a = -v[i], b = (1 - v[i]*v[i]), c = v[i];
			double r1, r2;
			if(b*b - 4*a*c < 0)	continue;
			if(fabs(a) < eps) {
				ret += pos;
				continue;
			}
			r1 = (-b - sqrt(b*b - 4*a*c))/2/a;
			r2 = (-b + sqrt(b*b - 4*a*c))/2/a;
			if(r1 > r2)	swap(r1, r2);
			
			int l = lower_bound(v, v + n, r1) - v;
			int r = upper_bound(v, v + n, r2) - v;
			int cnt = 0;
//			printf("%lf %lf %d %d\n", r1, r2, l, r);
			if(v[i] > 0) { // [l, r)
				while(l >= 0 && (v[l] + v[i])*(1 - v[l]*v[i]) > 1e-15)
					l--;
				l++;
				while(l < n && (v[l] + v[i])*(1 - v[l]*v[i]) <= 1e-15)
					l++;
				while(r < n && (v[r] + v[i])*(1 - v[r]*v[i]) > 1e-15)
					r++;
				if(l <= i && i < r)
					cnt--;
				cnt += r - l;
//				for(int j = 0; j < n; j++) {
//					if(j == i)	continue;
//					if(v[j] > r1 && v[j] < r2)
//						ret++;
//				}
			} else {
				while(l >= 0 && (v[l] + v[i])*(1 - v[l]*v[i]) <= 1e-15)
					l--;
				l++;
				while(l < n && (v[l] + v[i])*(1 - v[l]*v[i]) > 1e-15)
					l++;
				while(r < n && (v[r] + v[i])*(1 - v[r]*v[i]) <= 1e-15)
					r++;
				if(i < l || i >= r)
					cnt--;
				cnt += l + (n - r);
//				for(int j = 0; j < n; j++) {
//					if(j == i) 	continue;
//					if(v[j] < r1 || v[j] > r2)
//						ret++;
//				}
			}
//			int cnt2 = 0;
//			for(int j = 0; j < n; j++) {
//				if(i == j)	continue;
//				cnt2 += (v[i] + v[j]) * (1 - v[i]*v[j]) > 1e-15;
//			}
//			if(cnt != cnt2) {
//				printf("%lf %d %d %lf %lf, %lf %lf\n", v[i], cnt, cnt2, r1, r2, v[l], v[r-1]);
//				return 0;
//			}
			ret += cnt;
		}
		printf("Case %d: %d\n", ++cases, ret/2);
	}
	return 0;
}
/*
2
0
0

*/
