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

#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
long long P[1048576];
int Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 10000000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
vector< pair<long long, int> > factor(long long n) {
	vector< pair<long long, int> > R;
	
	for(int i = 0, j; i < Pt && P[i] * P[i] <= n; i++) {
		if(n%P[i] == 0) {
			for(j = 0; n%P[i] == 0; n /= P[i], j++);
			R.push_back(make_pair(P[i], j));
		}
	}
	if(n != 1)	R.push_back(make_pair(n, 1));
	return R;
}
// http://flere114.blogspot.tw/2012/11/uva-12355-consecutive-sums.html
int main() {
    sieve();
    long long n;
    while (scanf("%lld", &n) == 1 && n) {
        long long ret = 2;
        while (n%2 == 0)
            n /= 2;
        vector< pair<long long, int> > f = factor(n);
        for (int i = 0; i < f.size(); i++) {
            ret *= f[i].second * 2 + 1;
        }
        printf("%lld\n", ret);
    }
    return 0;
}

/*
 5
 1
 0
 */
