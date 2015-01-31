#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 1048576
#define INF 0x3f3f3f3f
int P[MAXN], S[MAXN];
int LEFT[MAXN], RIGHT[MAXN];
int main() {
    int testcase, N;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++) scanf("%d", &P[i]);
        for (int i = 0; i < N; i++) scanf("%d", &S[i]);
        
        for (int i = N-1, t = INF; i >= 0; i--) {
            t = min(t, S[i]);
            t = max(t, P[i]);
            RIGHT[i] = t;
        }
        for (int i = 0, t = INF; i < N; i++) {
            t = min(t, S[i]);
            t = max(t, P[i]);
            LEFT[i] = t;
        }
        int ret = 0;
        for (int i = 0; i < N; i++) {
            ret += min(RIGHT[i], LEFT[i]) - P[i];
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 1
 15
 6 6 7 5 5 5 5 5 5 1 1 3 3 2 2
 10 10 10 11 6 8 7 10 10 7 6 4 7 11 11
*/