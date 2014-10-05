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
#define eps 1e-9

int main() {
    int n, A[32767];
    while (scanf("%d", &n) == 1 && n) {
        long long tot = 1, mirror = 1;
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            tot *= A[i];
        }
        for (int i = 0, j = n - 1; i <= j; i++, j--)
            mirror *= min(A[i], A[j]);
        printf("%lld\n", tot - mirror);
    }
    return 0;
}

/*
 2 2 2
 4 2 2 2 2
 6 2 2 2 2 2 2
 0
 */
