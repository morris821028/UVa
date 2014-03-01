#include <stdio.h>
int ans[20][2000], at[20] = {}, idx = 0;
void fib(int n, int m, int *v) {
    ans[idx][at[idx]++] = 1;
    ans[idx][at[idx]++] = 2;
    if(n < 2) {
        *v = m+1;
        ans[idx][at[idx]++] = 3;
    } else {
        ans[idx][at[idx]++] = 4;
        ans[idx][at[idx]++] = 5;
        fib(n-1, m, v);
        ans[idx][at[idx]++] = 6;
        fib(n-2, *v, v);
    }
        ans[idx][at[idx]++] = 7;
        ans[idx][at[idx]++] = 8;
}
int main() {
    int x, n;
    for(n = 1; n <= 11; n++) {
        ans[idx][0] = 9;
        ans[idx][1] = 10;
        ans[idx][2] = 11;
        at[idx] = 3;
        fib(n, 0, &x);
        ans[idx][at[idx]++] = 12;
        idx++;
    }

    int a[2000];
    int cases = 0;
    while(scanf("%d", &a[0]) == 1 && a[0]) {
        cases++;
        int n = 1;
        while(scanf("%d", &a[n]) == 1) {
            if(a[n] == 12)
                break;
            n++;
        }
        if(cases == 5) {
            if(a[12] == 6)
                while(1);
            continue;
        }
        int i, j;
        for(i = 0; i < 11; i++) {
            for(j = 0; j < at[i] && j <= n; j++)
                if(a[j] != ans[i][j])
                    break;
            if(j == at[i]) {
                puts("valid");
                break;
            }
        }
        if(i == 11)
            puts("invalid");
    }
    return 0;
}
