#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <iostream>
#include <assert.h>
using namespace std;
#define MAXN 1024
int A[16] = {}, N, K;
int path[MAXN];
void dfs(int idx) {
    if (idx == N) {
        K--;
        if (K == 0) {
            for (int i = 0; i < N; i++)
                printf("%d", path[i]);
            puts("");
        }
        return ;
    }
    for (int i = 1; i <= 9; i++) {
        if (A[i] > 0) {
            path[idx] = i;
            A[i]--;
            dfs(idx+1);
            A[i]++;
            if (K == 0)
                return;
        }
    }
}
int main() {
    int testcase;
    char s[MAXN];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d", &N, &K);
        scanf("%s", s);
        
        memset(A, 0, sizeof(A));
        for (int i = 0; i < N; i++)
            A[s[i] - '0']++;
        
        dfs(0);
        
        if (K)
            puts("Fake cheque!");
    }
    return 0;
}
/*
 3
 2 100
 34
 4 5
 5513
 9 666 
 123498765
 */