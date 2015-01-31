#include <stdio.h>
#include <map>
#include <vector>
#include <set>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define eps 1e-6
#define MAXN 32767
#define INF 0x3f3f3f3f
int A[MAXN];
int dfs(int l, int r) {
    if (r - l + 1 < 4)
        return 0;
    int mx = 0, mid = -1, mn;
    for (int i = l; i <= r; i++) {
        if (A[i] > mx)
            mx = A[i], mid = i;
    }
    set<int> L, R;
    set<int>::iterator it;
    for (int i = l; i < mid; i++)
        L.insert(A[i]);
    for (int i = mid + 1; i <= r; i++)
        R.insert(A[i]);
    mn = INF;
    for (int i = mid - 1; i >= l; i--) {
        if (mn < A[i]) {
            it = R.lower_bound(mn);
            if (it != R.end()) {
                if (*it > mn && *it < A[i]) {
                    return 1;
                }
            }
        }
        mn = min(mn, A[i]);
    }
    mn = INF;
    for (int i = mid + 1; i <= r; i++) {
        if (mn < A[i]) {
            it = L.lower_bound(mn);
            if (it != L.end()) {
                if (*it > mn && *it < A[i]) {
                    return 1;
                }
            }
        }
        mn = min(mn, A[i]);
    }
    if (dfs(l, mid-1))
        return 1;
    if (dfs(mid+1, r))
        return 1;
    return 0;
}
int main() {
    int testcase, N;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &N);
        for (int i = 0; i < N; i++)
            scanf("%d", &A[i]);
        puts(dfs(0, N-1) ? "YES" : "NO");
    }
    return 0;
}
/*
 3
 6
 10 30 60 40 20 50
 8
 30 40 10 20 80 50 60 70
 4
 1 2 20 9
 
 999
 10
 1 7 5 4 2 3 10 8 9 6
 */