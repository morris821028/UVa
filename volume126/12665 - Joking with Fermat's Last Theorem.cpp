#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
	int L, R, cases = 0;
	while(scanf("%d %d", &L, &R) == 2) {
		int limit = min(1005, R); // (10^3)^3 = 10^9 
		int ret = 0;
		for(long long a = L; a <= limit; a++) {
			for(long long b = L; b <= limit; b++) {
				long long t = (a*a*a+b*b*b);
				long long c = t/10;
				if(t%10 != 3)	continue;
				if(L <= c && c <= R)
					ret++;
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
1 10
1 20
123 456789
*/
