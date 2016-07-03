#include <stdio.h>
int st[1<<21];
int main() {
    int n, k;
    while (scanf("%d %d", &n, &k) == 2 && n) {
        int M;
        for (M = 1; M < n+1; M <<= 1);
        for (int i = 2*M-1; i > 0; i--) {
            if (i >= M)
                st[i] = 1;
            else
                st[i] = st[i<<1]+st[i<<1|1];
        }
        int m, last, prev = 1, s;
        for (int i = 1; i <= n; i++) {
        	if (i%2 == 1)
            	m = (k-1+prev)%(n-i+1);
            else
            	m = (-k+1 + prev)%(n-i+1);
            if (m <= 0)
                m += n-i+1;
            if (i%2 == 1)
            	prev = m;
            else
            	prev = m-1;
//            printf("%d %d\n", i, prev);
            for (s = 1; s < M;) {
                if (st[s<<1] < m)
                    m -= st[s<<1], s = s<<1|1;
                else
                    s = s<<1;
            }
            last = s-M+1;
            printf("%d\n", last);
            while (s) { 
                st[s] --;
                s >>= 1;
            }
        }
        printf("%d\n", last);
    }
    return 0;
}
/*
10 7
5
9 7
3
8 7
5
7 7
3
6 7
5
5 7
3
4 7
1
*/ 
