#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <math.h>
#include <iostream>
#include <map>
using namespace std;
// random algroithm, identify A * A = B
// (A * (A * C)) = B * C => O(n^2)
#define MAXN 1024
int A[MAXN][MAXN], B[MAXN][MAXN];
int C[MAXN], D[MAXN], E[MAXN], F[MAXN];
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &A[i][j]);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &B[i][j]);
        for (int i = 0; i < n; i++)
            C[i] = rand() + 1;
        for (int i = 0; i < n; i++) {
            int x = 0, y = 0;
            for (int j = 0; j < n; j++)
                x += C[j] * A[i][j], y += C[j] * B[i][j];
            D[i] = x, E[i] = y;
        }
        int ok = 1;
        for (int i = 0; i < n && ok; i++) {
            int x = 0;
            for (int j = 0; j < n; j++)
                x += D[j] * A[i][j];
            F[i] = x;
            ok &= F[i] == E[i];
        }
        puts(ok ? "YES" : "NO");
    }
    return 0;
}
/*
 3
 2 0 1
 1 0 3
 1 1 0
 5 1 2
 5 3 1
 3 0 4
 
 3
 2 0 1
 1 0 3
 1 1 0
 5 1 2
 5 3 2
 3 0 4
 
 0
 */