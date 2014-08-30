#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int n, m, A[16], B[16];

int dfs(int A[], int n) {
    if (n < m)  return 0;
    if (n == m) {
        int same = 1;
        for (int i = 0; i < n; i++)
            same &= A[i] == B[i];
        if (same)   return 1;
        same = 1;
        for (int i = 0; i < n; i++)
            same &= A[i] == B[n - i - 1];
        if (same)   return 1;
        return 0;
    }
    int C[16], cn;
    for (int i = 1; i < n; i++) {
        cn = n - min(i, n - i);
        int l, r;
        for(l = i - 1, r = i; l >= 0 && r < n; l--, r++)
            C[--cn] = A[l] + A[r];
        while (l >= 0)  C[--cn] = A[l--];
        while (r < n)   C[--cn] = A[r++];
        cn = n - min(i, n - i);
        if (dfs(C, cn)) return 1;
    }
    return 0;
}
int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        scanf("%d", &m);
        for (int i = 0; i < m; i++)
            scanf("%d", &B[i]);
        int f = dfs(A, n);
        puts(f ? "S" : "N");
    }
    return 0;
}

/*
 7
 5 6 23 8 19 7 10
 4
 5 16 30 27
 7
 1 2 3 4 5 6 7
 5
 7 6 5 5 5
 4
 1 2 3 4
 1
 10
 6
 19 23 3 51 2 0
 2
 34 64
 6
 1 2 3 4 5 6
 6
 1 2 3 4 5 6
 6
 1 2 3 4 5 6
 6
 6 5 4 3 2 1
 */