#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

struct SOL {
    long long L, W;
    SOL(long long a = 0, long long b = 0):
        L(a), W(b) {}
    bool operator<(const SOL &x) const {
        if (L * W != x.L * x.W)
            return L * W < x.L * x.W;
        return llabs(L - W) < llabs(x.L - x.W);
    }
};
int main() {
    int testcase;
    long long N;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%lld", &N);
        N = N/5 + (N%5 != 0);
        SOL best;
        for (long long i = 1; i * i <= N; i++) {
            SOL t(i * 44 + 4, (N/i + (N%i != 0)) * 10 + 2);
            if (i == 1)
                best = t;
            else
                best = min(best, t);
        }
        if (best.L < best.W) {
            swap(best.L, best.W);
        }
        printf("%lld X %lld = %lld\n", best.L, best.W, best.L * best.W);
    }
    return 0;
}

/*
 6
 1
 15
 22
 29
 36
 43
 */