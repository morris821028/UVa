#include <stdio.h>
#include <math.h>
int L, U;
int p[5200], pt = -1;
long long p2[50] = {1};
void sieve() {
    int i, j, mark[50005] = {};
    for(i = 2; i <= 50000; i++) {
        if(!mark[i]) {
            for(j = i+i; j <= 50000; j += i)
                mark[j] = 1;
            p[++pt] = i;
        }
    }
}
int ans, ans_num;
void dfs(int idx, long long num, int tot) {
    if(U/num == (L-1)/num)  return;
    if(tot > ans || (ans == tot && num < ans_num)) {
        ans_num = num;
        ans = tot;
    }
    int i, q;
    long long j;
    if(idx > pt)  return;
    q = log((double)U/num)/log(p[idx]);
    if(tot*p2[q] < ans || (tot*p2[q] == ans && num >= ans_num))  return;
    for(i = 0, j = 1; num*j <= U; i++, j *= p[idx]) {
        dfs(idx+1, num*j, tot*(i+1));
    }
}
int main() {
    sieve();
    int t;
    long long i, j;
    for(i = 1; i < 50; i++)
        p2[i] = p2[i-1]<<1;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &L, &U);
        if(U-L > 100000) {
            ans = 0;
            for(i = U-500; i <= U; i++) {
                int n = i, cnt = 0, tans = 1;
                for(j = 0; j <= pt && (long long)p[j]*p[j] <= n; j++) {
                    if(n%p[j] == 0) {
                        cnt = 0;
                        while(n%p[j] == 0)
                            cnt++, n /= p[j];
                        tans *= cnt+1;
                    }
                }
                if(n != 1)  tans *= 2;
                if(tans > ans)
                    ans = tans, ans_num = i;
            }
            dfs(0, 1, 1);
        } else {
            ans = 0;
            for(i = L; i <= U; i++) {
                int n = i, cnt = 0, tans = 1;
                for(j = 0; j <= pt && (long long)p[j]*p[j] <= n; j++) {
                    if(n%p[j] == 0) {
                        cnt = 0;
                        while(n%p[j] == 0)
                            cnt++, n /= p[j];
                        tans *= cnt+1;
                    }
                }
                if(n != 1)  tans *= 2;
                if(tans > ans)
                    ans = tans, ans_num = i;
            }
        }
        printf("Between %d and %d, %d has a maximum of %d divisors.\n", L, U, ans_num, ans);
    }
    return 0;
}
