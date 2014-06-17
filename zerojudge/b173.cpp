#include <stdio.h>
char g[1005][2005];
char buf[10005];
int check(int m, int N, int K) {
    static int i, j, k, cnt, R, flag;
    N *= 2, R = 2*m+1;
    i = N/4;
    cnt = 1, flag = 0;
    for(j = 0; j < N;) {
        if(j+m >= N-m-1)    break;
        k = i+j;
        if(k+R > i+j && k+R > i+N)
            k--;
        while(k+R > i+j && buf[k+R] == '0')
            k--;
        if(k+R > i+j) {
            cnt++;
            if(cnt > K)
                return 0;
            j = k+R-i;
        } else {
            return 0;
        }
    }
    return 1;
}
void solve(int N, int K) {
    for(int i = 0, j = 2*N; i < 2*N; i++, j++)
        buf[j] = buf[i];
    buf[4*N] = '\0';
    int l = 0, r = N, m;
    while(l <= r) {
        m = (l+r)/2;
        if(check(m, N, K))
            r = m-1;
        else
            l = m+1;
    }
    printf("%d\n", r+1);
}
int main() {
    int N, M, K;
    int i, j;
    while(scanf("%d %d %d", &N, &M, &K) == 3) {
        for(i = 0; i < N; i++)
            scanf("%s", g[i]);
        for(i = 0; i < M; i++) {
            int idx = 0;
            for(j = 0; j < N; j++)
                buf[idx++] = g[j][i];
            for(j = N-1; j >= 0; j--)
                buf[idx++] = g[j][i+M];
            buf[idx] = '\0';
            solve(N, K);
        }
    }
    return 0;
}
