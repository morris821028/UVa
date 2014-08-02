#include <stdio.h> 
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

int able[128][1024];
void build() {
	int d1, d2, d3, d4;
	for(int i = 1; i <= 100; i++) {
		if(i < 100) {
			if(i < 10) {
				d1 = i;
				able[i][1<<d1] = 1;
			} else {
				d1 = i%10, d2 = i/10;
				if(d1 != d2)
					able[i][(1<<d1)|(1<<d2)] = 1;
			}
		}
		for(int j = 1; j < i; j++) {
			int a = j, b = i - j, mask = 0;

			if(a < 10) {
				mask |= 1<<a;
			} else {
				d1 = a%10, d2 = a/10;
				if(d1 == d2)
					continue;
				mask |= (1<<d1)|(1<<d2);
			}
			if(b < 10) {
				if(mask&(1<<b))
					continue;
				mask |= 1<<b;
			} else {
				d1 = b%10, d2 = b/10;
				if(d1 == d2)
					continue;
				if(mask&((1<<d1)|(1<<d2)))
					continue;
				mask |= (1<<d1)|(1<<d2);
			}
			able[i][mask] = 1;
		}
	}
	for(int i = 0; i < 128; i++) {
		for(int j = 0; j < 1024; j++) {
			for(int k = j; k; k = k&(k-1))
				able[i][j] |= able[i][j&(k-1)];
		}
	}
}
int main() {
	build();
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout);
	int n, A[10], cases = 0;
	while(scanf("%d", &n) == 1 && n) {
		map<int, int> R;
		for(int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		
		int ret = (1<<10)-1;
		for(int i = 0; i < (1<<10); i++) {
			if(__builtin_popcount(i) >= __builtin_popcount(ret))
				continue;
			int f = 1;
			for(int j = 0; j < n && f; j++)
				f &= able[A[j]][i];
			if(f) {
				ret = i;		

			}
		}							
		printf("Case %d: ", ++cases);
		for(int i = 9; i >= 0; i--) {
			if((ret>>i)&1)
				printf("%d", i);
		}
		puts("");
	}
	return 0;
}
