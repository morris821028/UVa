#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
int A[131072], tree[131072];

void modify(int x, int N, int val) {
    while (x <= N) {
        tree[x] += val;
        x += x&(-x);
    }
}

int query(int x) {
    int ret = 0;
    while (x) {
        ret += tree[x];
        x -= x&(-x);
    }
    return ret;
}
int main() {
    int cases = 0;
    int N, M, K, l = 0, r;
    while (scanf("%d %d %d", &N, &M, &K) == 3) {
        for (int i = 1; i <= N; i++)
            scanf("%d", &A[i]);
        sort(A+1, A+1+N);
        memset(tree, 0, sizeof(tree));
        int p = 1;
        for (int i = 0; i < M; i++) {
            scanf("%d %d", &r, &l);
            p = upper_bound(A+1, A+1+N, p) - A;
            r = upper_bound(A+1, A+1+N, r) - A;
            if (p <= r) {
                modify(p, N, 1);
                modify(r, N, -1);
            }
            p = l;
        }
        
        int ret = 0;
        for (int i = 1; i <= N; i++) {
            int cnt = query(i);
            ret += cnt >= K;
        }
        printf("Case %d: %d\n", ++cases, ret);
    }
    return 0;
}
/*
 2 2 2
 2 5
 6 2
 8 3
 5 3 2
 2 3 4 5 6
 5 3
 4 2
 5 2
 */