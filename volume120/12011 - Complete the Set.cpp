#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int main() {
    int testcase, cases = 0;
    int n, x;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        set<int> S;
        int A[32] = {}, all = (1<<18) - 1; // used i-th bits minimum attachment.
        memset(A, -1, sizeof(A));
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            S.insert(x);
            all &= x; // used mask = 0
            for (int j = 0; j < 18; j++) {
                if ((x>>j)&1) {
                    if (A[j] == -1)
                        A[j] = x;
                    else
                        A[j] = A[j] & x;
                }
            }
        }
        S.insert(all);
        int m = 0;
        for (int i = 0; i < 18; i++) {
            if (A[i] != -1)
                A[m++] = A[i];
        }
        for (int i = 1; i < (1<<m); i++) { // used mask
            int num = 0;
            for (int j = 0; j < m; j++) {
                if ((i>>j)&1) {
                    num |= A[j];
                }
            }
            S.insert(num);
        }
        printf("Case #%d: %d\n", ++cases, (int)S.size() - n);
    }
    return 0;
}

/*
 4
 5
 0 1 3 5 7
 2
 2 4
 3
 3 7 11
 3
 1 2 4
 */