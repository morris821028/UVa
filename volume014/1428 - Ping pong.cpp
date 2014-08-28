#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

int A[131072];
long long Ls[131072], Rs[131072];
int BIT[131072];
void init(int n) {
    for (int i = 0; i <= n; i++)
        BIT[i] = 0;
}
void modify(int L, int x, int v) {
    for (; x <= L; BIT[x] += v, x += x&(-x));
}
int query(int x) {
    int ret = 0;
    for (; x; ret += BIT[x], x -= x&(-x));
    return ret;
}
int main() {
    int testcase, n, m;
    
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        m = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &A[i]);
            m = max(m, A[i]);
        }
        init(m);
        for (int i = 0; i < n; i++) {
            Ls[i] = query(A[i]);
            modify(m, A[i], 1);
        }
        init(m);
        for (int i = n - 1; i >= 0; i--) {
            Rs[i] = query(A[i]);
            modify(m, A[i], 1);
        }
        
        long long ret = 0;
        for (int i = 0; i < n; i++) {
            ret += Ls[i] * (n - i - 1 - Rs[i]) + Rs[i] * (i - Ls[i]);
        }
        printf("%lld\n", ret);
    }
    return 0;
}
/*
 1
 3 1 2 3
*/