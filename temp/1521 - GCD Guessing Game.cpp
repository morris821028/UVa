#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXL (50000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[6000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
// greedy
// make prime number into a group, product of number in group <= n
// minimum #group
int main() {
	sieve();
	int n;
	while (scanf("%d", &n) == 1) {
		vector<int> p;
		for (int i = 0; i < Pt; i++)
			if (P[i] <= n)
				p.push_back(P[i]);
		
		int ret = 0, used[32767] = {}; 
		
		for (int i = p.size() - 1; i >= 0; i--) {
			if (used[p[i]])
				continue;
			// new group
			ret++;
			
			int m = n / p[i];
			for (int j = i-1; j >= 0; j--) {
				if (used[p[j]] == 0 && m >= p[j]) {
					used[p[j]] = 1;
					m = m / p[j];
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
