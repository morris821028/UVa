#include <stdio.h> 
#include <algorithm>
using namespace std;
long long llabs(long long v) {
	return v < 0 ? -v : v;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		long long a[1024], a10[1024], x;
		for(int i = 0; i < n; i++) {
			a[i] = 0;
			for(int j = 1; j <= 9; j++)
				scanf("%lld", &x), a[i] += x;
			scanf("%lld", &a10[i]);
		}
		
		long long g = llabs(a10[0] - a[0]);
		for(int i = 0; i < n; i++)
			g = __gcd(g, llabs(a10[i] - a[i]));
		if(g <= 1)
			puts("impossible");
		else {
			int valid = 1;
			for(int i = 0; i < n; i++)
				valid &= 0 <= a10[i] && a10[i] < g;
			if(!valid)
				puts("impossible");
			else
				printf("%lld\n", g);
		}
	}
	return 0;
}
/*
4
2
1 1 1 1 1 1 1 1 1 9
2 4 6 8 10 12 14 16 18 90
3
1 1 1 1 1 1 1 1 1 1
5 4 7 2 6 4 2 1 3 2
1 2 3 4 5 6 7 8 9 5
2
1 1 1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1 1 0
2
2 2 2 2 2 2 2 2 2 0
1 1 1 1 1 1 1 1 1 1 
*/
