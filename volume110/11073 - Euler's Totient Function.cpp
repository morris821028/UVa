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
void make(int idx, int n, int m, vector< pair<int, int> > &v, vector<int> &f, int limit) {
    if (m > limit) {
        return;
    }
	if(idx == v.size()) {
        f.push_back(m);
		return;
	}
	int a = m, b = v[idx].first;
	for(int i = v[idx].second; i >= 0; i--)
		make(idx + 1, n, a, v, f, limit), a *= b;
}
long long mpow(long long x, long long y) {
    long long ret = 1;
    while (y) {
        if (y&1) {
            ret *= x;
        }
        y >>= 1, x = x * x;
    }
    return ret;
}
void dfs(int x, long long n, int max_pf, vector<long long> &ret) {
    if (x == 1) {
        ret.push_back(n);
//        printf("%lld ----\n", n);
        if (max_pf != 2) {
//            printf("%lld ----\n", n * 2);
            ret.push_back(n * 2);
        }
        return ;
    }
    vector< pair<int, int> > v = factor(x);
    int pf = v[v.size()-1].first, pfp = v[v.size()-1].second;
//    printf("%d %lld %d %d\n", x, n, pf, pfp);
    if (x%(pf - 1) == 0) {
        dfs(x / (pf - 1) / mpow(pf, pfp), n * mpow(pf, pfp + 1), pf, ret);
    }
    vector<int> f;
    make(0, x, 1, v, f, max_pf);
    sort(f.begin(), f.end());
    for (int i = 0; i < f.size() && f[i] + 1 < max_pf; i++) {
//        printf("%d\n", f[i]);
        if (f[i] + 1 > pf && isPrime(f[i] + 1)) {
            dfs(x / f[i], n * (f[i] + 1), f[i] + 1, ret);
        }
    }
}
int main() {
    sieve();
    int n;
    while (scanf("%d", &n) == 1) {
        vector<long long> ret;
        dfs(n, 1, 0x3f3f3f3f, ret);
        sort(ret.begin(), ret.end());
        if (ret.size() == 0) {
            puts("No solution.");
        } else {
            vector<long long>::iterator it;
            it = unique (ret.begin(), ret.end());
            ret.resize( distance(ret.begin(),it) );
            for (int i = 0; i < ret.size(); i++) {
                printf("%lld%c", ret[i], i == ret.size() - 1 ? '\n' : ' ');
            }
//            printf("%d\n", ret.size());
        }
    }
    return 0;
}
/*
 19639
*/