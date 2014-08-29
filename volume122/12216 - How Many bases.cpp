#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

#define maxL (50000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[maxL];
int P[5500], Pt = 0;
void sieve() {
    register int i, j, k, l;
    SET(1);
    int n = 50000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(j = i + i; j <= n; j += i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
int isPrime(int n) {
    for(int i = 0; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {
			return 0;
		}
	}
    return 1;
}
vector< pair<int, int> > factor(int n) {
	vector< pair<int, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}

int main() {
    sieve();
    int N, M, T, cases = 0;
    const long long mod = 100000007LL;
    while (scanf("%d %d %d", &N, &M, &T) == 3 && N + M + T) {
        vector< pair<int, int> > f = factor(N);
        long long t1 = 1, t2 = 1;
        for (int i = 0; i < f.size(); i++) {
            t1 *= f[i].second * M / T + 1;
            t2 *= f[i].second * M / (T + 1) + 1;
            t1 %= mod;
            t2 %= mod;
        }
        printf("Case %d: %lld\n", ++cases, ((t1 - t2)%mod + mod)%mod);
    }
    return 0;
}