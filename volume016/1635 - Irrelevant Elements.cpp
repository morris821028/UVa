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
int g(int n, int p) {
    int ret = 0;
    long long pp = p;
    while (n >= pp) {
        ret += n / pp;
        pp *= p;
    }
    return ret;
}
int main() {
    sieve();
    int n, m;
    while (scanf("%d %d", &n, &m) == 2) {
        vector< pair<int, int> > f = factor(m);
        vector<int> solution;
        n--;
        for (int i = 0; i <= n; i++) {
            int ok = 1;
            for (int j = 0; j < f.size() && ok; j++) {
                int p = f[j].first;
                int cnt = g(n, p) - g(i, p) - g(n - i, p); // C(n, i) has p^cnt.
                if (cnt < f[j].second) {
                    ok = 0;
                }
            }
            if (ok) {
                solution.push_back(i + 1);
            }
        }
        printf("%d\n", (int)solution.size());
        for (int i = 0; i < solution.size(); i++) {
            printf("%d%s", solution[i], i == solution.size() - 1 ? "" : " ");
        }
        puts("");
    }
    return 0;
}