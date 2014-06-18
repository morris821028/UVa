#include <stdio.h>
#include <string.h>

void solve(int n, int f, int A[]) {
    int i, j, k;
    int sum = 0, goal, NOT;
    for(i = 0; i < n; i++)
        sum += A[i];
    if(f < 0)   goal = -f, NOT = 1;
    else        goal = f, NOT = 0;
    for(i = 0; i < n; i++) {
        char dp[30000] = {};
        for(j = 0; j < n; j++) {
        }
    }
}
int main() {
    int n, f, A[50], i;
    while(scanf("%d %d", &n, &f) == 2 && n) {
        for(i = 0; i < n; i++)
            scanf("%d", &A[i]);
        solve(n, f, A);
    }
    return 0;
}
