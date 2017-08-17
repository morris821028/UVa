#include <bits/stdc++.h>
using namespace std;

const int MAXN = 128;
const double PI = acos(-1);
int main() {
	int cases = 0;
	int n, w, h;
	int m[MAXN], d[MAXN], pos[MAXN] = {};
	while (scanf("%d", &n) == 1 && n) {
		scanf("%d %d", &w, &h);
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &m[i], &d[i]);
			pos[i+1] = pos[i] + w + d[i];
		}
		scanf("%d", &m[n]);
		
		{
			printf("Apartment Complex: %d\n", ++cases);  
			int x;
			while (scanf("%d", &x) == 1 && x) {
				int u = x%100, v = x/100;
				if (u < 1 || u > n || v < 1 || v > m[u]) {
					printf("Apartment %d: Does not exist\n", x);
					continue;
				}
				
				double l = 0, r = 0;
				for (int i = 1; i < u; i++) {
					if (m[i] < v)
						continue;
					l = max(l, (double) (h*(m[i]-v+1))/(pos[u]-pos[i]-w));
				} 
				for (int i = u+1; i <= n; i++) {
					if (m[i] < v)
						continue;
					r = max(r, (double) (h*(m[i]-v+1))/(pos[i]-pos[u]-w));
				}
				
				const double ST = ( 5*60 + 37)*60; // 05:37 am
				const double ED = (18*60 + 17)*60; // 06:17 pm
				int st, ed;
				st = atan(l) * (ED-ST) / PI + ST;
				ed = ED - atan(r) * (ED-ST) / PI;
				printf("Apartment %d: %02d:%02d:%02d - %02d:%02d:%02d\n", 
					x, st/3600, st%3600/60, st%60
					 , ed/3600, ed%3600/60, ed%60);
			}
		}
	}
	return 0;
}
/*
3
6 4
5 6 3 3 4
302 401 601 303 0
4
5 3
4 5 7 8 5 4 3
101 302 503 0
0
*/
