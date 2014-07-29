#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

// #define DEBUG
long long inv(long long n, long long m) { // get n*? = 1 (mod m)
    long long la = 1, lb = 0, ra = 0, rb = 1;
    long long i = 0, t, mod = m;
    while(n%m) {
        if(!i) {
            la -= n/m*ra;
            lb -= n/m*rb;
        } else {
            ra -= n/m*la;
            rb -= n/m*lb;
        }
        i = !i;
        t = n, n = m, m = t%m;
    }
    return i ? (la%mod+mod)%mod : (ra%mod+mod)%mod;
}
int X[1024], Xn[1024], C, S, a[1024];
long long Y[1024][128];
vector<long long> solution;
long long chinese_remainder(int n, int m[], int a[]) {
    long long M = 1, ret = 0;
    for(int i = 0; i < n; i++)
        M *= m[i];
    for(int i = 0; i < n; i++) {
        ret += a[i] * inv(M/m[i], m[i]) %M * M/m[i];
        ret %= M;
    }

    return (ret%M + M)%M;
}
void dfs(int idx) {
    if(idx == C) {
        long long smallest = chinese_remainder(C, X, a);
		solution.push_back(smallest);
        return ;
    }
    for(int i = 0; i < Xn[idx]; i++) {
        a[idx] = Y[idx][i];
        dfs(idx+1);
    }
}
void test(int C, int res) {
	printf("[%d] ", res);
	for(int i = 0; i < C; i++) {
		printf("%d: %d, ", X[i], res%X[i]);
	}
	puts("");
}
int main() {
    while(scanf("%d %d", &C, &S) == 2 && C + S) {
        set<long long> remainder[1024];
        for(int i = 0; i < C; i++) {
            scanf("%d %d", &X[i], &Xn[i]);
            for(int j = 0; j < Xn[i]; j++)
                scanf("%lld", &Y[i][j]), remainder[i].insert(Y[i][j]);
            sort(Y[i], Y[i] + Xn[i]);
        }
		solution.clear();
        long long o = 1, M = 1;
        for(int i = 0; i < C; i++) {
            o *= Xn[i], M *= X[i];
		}
        if(o < 10000) {
            dfs(0);
            sort(solution.begin(), solution.end());
	        for(int i = 0, ratio = 0; i < S; ratio++) {
                for(int j = 0; j < solution.size() && i < S; j++) {
                    long long mn = solution[j] + ratio * M;
                    if(mn == 0)
                        continue;
                    printf("%lld\n", mn);
                    i++;
                }
		    }
        } else {
            int base = 0;
            for(int i = 0; i < C; i++)
                if(X[base] * Xn[i] < X[i] * Xn[base])
                    base = i;
            for(int i = 0, ratio = 0; i < S; ratio++) {
                for(int j = 0; j < Xn[base] && i < S; j++) {
                    long long mn = (long long) ratio * X[base] + Y[base][j];
                    if(mn == 0) continue;
                    int f = 1;
                    for(int k = 0; k < C; k++)
                        f &= remainder[k].find(mn%X[k]) != remainder[k].end();
                    if(f) {
                        printf("%lld\n", mn);
                        i++;
                    }
                }
			}
        }
        puts("");
    }
    return 0;
}
