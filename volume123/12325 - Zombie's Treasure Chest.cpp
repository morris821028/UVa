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

int main() {
    int testcase, cases = 0;
    long long N, S1, V1, S2, V2;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%lld %lld %lld %lld %lld", &N, &S1, &V1, &S2, &V2);
        long long ret = 0;
        if (S1 > S2)
            swap(S1, S2), swap(V1, V2);
        if (S2 > sqrt(N)) {
            for (int i = 0; i * S2 <= N; i++) {
                ret = max(ret, (N - i * S2)/S1 * V1 + i * V2);
            }
        } else {
            if (V1 * S2 > V2 * S1)
                swap(S1, S2), swap(V1, V2);
            for (int i = 0; i <= S2 && N - S1 * i >= 0; i++) {
                ret = max(ret, (N - i * S1)/S2 * V2 + i * V1);
            }
        }
        printf("Case #%d: %lld\n", ++cases, ret);
    }
    return 0;
}

/*
 2
 100 1 1 2 2
 100 34 34 5 3
 */
