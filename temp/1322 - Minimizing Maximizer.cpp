#include <stdio.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <functional>
#include <deque>
#include <assert.h>
#include <algorithm>
using namespace std;
#define INF 0x3f3f3f3f
#define MAXN 65536
int BIT[MAXN];
void modify(int x, int val, int L) {
    while (x <= L) {
        BIT[x] = min(BIT[x], val);
        x += x&(-x);
    }
}
int query(int x) {
    int ret = INF;
    while (x) {
        ret = min(ret, BIT[x]);
        x -= x&(-x);
    }
    return ret;
}
int main() {
    int testcase, N, M, x, y;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &M);
        vector< pair<int, int> > D;
        for (int i = 0; i <= N; i++)
            BIT[i] = INF;
        modify(N, 0, N); // [1, 1] => 0
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &x, &y);
            int val = query(N - x + 1) + 1;
            modify(N - y + 1, val, N);
        }
        int ret = query(1);
        printf("%d\n", ret);
        if (testcase)
            puts("");
    }
    return 0;
}
/*

*/