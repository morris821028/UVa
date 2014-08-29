#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

int A[131072], B[131072], C[131072], D[131072];
int main() {
    int testcase, n, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < m; i++)
            scanf("%d", &A[i]);
        
        for (int i = 0; i <= n; i++)
            B[i] = 0;
        for (int i = 0, diff = 0; i <= m; i++) {
            if (B[A[i]] == 0)
                diff++;
            B[A[i]]++;
            if (i >= n) {
                if (B[A[i-n]] == 1)
                    diff--;
                B[A[i-n]]--;
            }
            C[i] = diff;
        }
        
        for (int i = 0; i <= n; i++)
            B[i] = 0;
        for (int i = m - 1, diff = 0; i >= 0; i--) {
            if (B[A[i]] == 0)
                diff++;
            B[A[i]]++;
            if (i + n < m) {
                if (B[A[i+n]] == 1)
                    diff--;
                B[A[i+n]]--;
            }
            D[i] = diff;
        }
        
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int ok = 1, pre = -1;
            for (int j = n - i - 1; j < m && ok; j += n) {
                ok &= C[j] == (j - pre);
                pre = j;
            }
            if (pre != m - 1)
                ok &= D[pre + 1] == (m - 1 - pre);
            ret += ok;
        }
        printf("%d\n", ret);
    }
    return 0;
}

/*
 4
 4 10
 3 4 4 1 3 2 1 2 3 4
 6 6
 6 5 4 3 2 1
 3 5
 3 3 1 1 1
 7 3
 5 7 3
 */