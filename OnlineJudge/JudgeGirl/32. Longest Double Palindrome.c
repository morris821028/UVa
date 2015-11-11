#include <stdio.h>
#include <string.h>
#define MAXN 128
int isPalind[MAXN][MAXN];
void build(int s[], int n) {
    int i, j, k;
    memset(isPalind, 0, sizeof(isPalind));
    for (i = 0; i < n; i++) {
        j = i, k = i;
        while (j >= 0 && k < n && s[j] == s[k]) {
            isPalind[j][k] = 1;
            j--, k++;
        }
    }
    for (i = 0; i < n-1; i++) {
        j = i, k = i+1;
        while (j >= 0 && k < n && s[j] == s[k]) {
            isPalind[j][k] = 1;
            j--, k++;
        }
    }
}
int run(int s[], int n) {
    build(s, n);
    int dp[MAXN] = {}, i, j;
    dp[0] = 1;
    for (i = 1; i < n; i++) {
        dp[i] = MAXN;
        for (j = 0; j <= i; j++) {
            if (isPalind[j][i]) {
                if (j != 0)
                    dp[i] = dp[i] < dp[j-1]+1 ? dp[i] : dp[j-1]+1;
                else
                    dp[i] = 1;
            }
        }
    }
    return dp[n-1];
}

int main() {
    int n = 0, A[128];
    int ret = 0, rpos = 0;
    while (scanf("%d", &A[n]) == 1) n++;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (j-i+1 < ret)    continue;
            int f = run(A+i, j-i+1);
            if (f <= 2 && j-i+1 >= ret)
                ret = j-i+1, rpos = i;
        }
    }
    for (int i = 0; i < ret; i++)
        printf("%d%c", A[rpos+i], " \n"[i == ret-1]);
    return 0;
}
/*
7 1 3 5 3 1 1
*/

