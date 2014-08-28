#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <functional>
using namespace std;
#define MAXN 131072
int A[MAXN];
int main() {
    int testcase, n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        sort(A, A+n, greater<int>());
        int ret = 0, r = n - 1;
        for (int l = 0; l <= r; l++) {
            if (l != r && A[l] + A[r] <= m)
                r--;
            ret ++;
        }
        printf("%d\n", ret);
        if (testcase) {
            puts("");
        }
    }
    return 0;
}
/*

 */