#include <stdio.h>
#include <stdlib.h>
int A[1000][1000];
int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        int tot = 0, i, j;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &A[i][j]);
            }
        }
        for(i = 0; i < n; i++)
            tot += A[i][i];
        int test = 500, err = 0, m, s;
        int M, st[2050] = {}, prev, last, sum;
        for(M = 1; M < n+1; M <<= 1);
        while(test--) {
            for(i = 2*M-1; i > 0; i--) {
                if(i >= M)
                    st[i] = 1;
                else
                    st[i] = st[i<<1] + st[i<<1|1];
            }
            prev = 0;
            sum = 0;
            for(i = 1; i <= n; i++) {
                m = (rand()+prev)%(n-i+1);
                if(m == 0)  m = n-i+1;
                prev = m-1;
                for(s = 1; s < M; ) {
                    if(st[s<<1] < m)
                        m -= st[s<<1], s = s<<1|1;
                    else
                        s = s <<1;
                }
                last = s-M+1;
                sum += A[i-1][last-1];
                while(s)
                    st[s]--, s >>= 1;
            }
            if(sum != tot) {
                err = 1;
                break;
            }
        }
        if(err)
            puts("not homogeneous");
        else
            puts("homogeneous");
    }
    return 0;
}
