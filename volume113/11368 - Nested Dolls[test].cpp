#include <stdio.h>
#include <algorithm>
using namespace std;
struct Rect {
    int h, w;
    bool operator<(const Rect &A) const {
        if(A.h != h)
            return h < A.h;
        return w > A.w;
    }
};
Rect D[20000];
int query(int idx, int arr[]) {
    int ret = 0;
    while(idx) {
        ret = max(ret, arr[idx]);
        idx -= idx&(-idx);
    }
    return ret;
}
void modify(int idx, int arr[], int L, int argv) {
    while(idx <= L) {
        arr[idx] = max(arr[idx], argv);
        idx += idx&(-idx);
    }
}
int main() {
    int testcase;
    int n, i, j;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &D[i].h, &D[i].w);
        }
        sort(D, D+n);
        int dp[20005] = {};
        int wbit[10005] = {}, hbit[10005] = {};
        int ret = 0;
        for(i = 0; i < n; i++) {
            int f1 = query(10005-D[i].h, hbit);
            int f2 = query(10005-D[i].w, wbit);
            dp[i] = max(dp[i], f1+1);
            dp[i] = max(dp[i], f2+1);
            modify(10005-D[i].h, hbit, 10005, dp[i]);
            modify(10005-D[i].w, wbit, 10005, dp[i]);
            ret = max(ret, dp[i]);
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
1000
3
20 30 40 50 30 40
4
20 30 10 10 30 20 40 50
3
10 30 20 20 30 10
4
10 10 20 30 40 50 39 51
4
1 3 9 6 10 7 10 5
3
9 6 10 7 10 5
2
10 10 10 10

Output
1
2
3
2
2
2
2
*/
