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

char s[32];
int n = 0;
long long A[32], f[32];
long long ret;
void dfs(int idx, int i) {
    if (idx == n) {
        if (s[i] == '\0') {
            long long t = f[9], s = 1;
            A[n] = -1;
            for (int i = 1; i <= n; i++) {
                if (A[i] == A[i-1]) {
                    s++;
                } else {
                    t /= f[s];
                    s = 1;
                }
//                printf("%lld ", A[i]);
            }
            t /= f[9 - n];
//            puts("");
            ret += t;
        }
        return ;
    }
    long long num = 0;
    if (s[i] == '0')
        return;
    for (; s[i]; i++) {
        num = num * 10 + s[i] - '0';
        if (idx == 0 || A[idx-1] <= num) {
            A[idx] = num;
            dfs(idx+1, i+1);
        }
    }
}
int main() {
    f[0] = 1;
    for (int i = 1; i < 32; i++) {
        f[i] = f[i-1] * i;
    }
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%s", s);
        n = s[0] - '0';
        ret = 0;
        dfs(0, 1);
        printf("%lld\n", ret);
    }
    return 0;
}

/*
 4
 123
 213
 31312
 311111
 */
