#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int josephus(int n, int k) {
	static int st[1<<20];
	int M;
    for (M = 1; M < n+1; M <<= 1);
    for (int i = 2*M-1; i > 0; i--) {
        if(i >= M)
            st[i] = 1;
        else
            st[i] = st[i<<1]+st[i<<1|1];
    }
    int last, prev = 0;
    for (int i = 1; i <= n; i++) {
    	int m, s, sz = n-i+1;
        if (i%2)
        	m = ((prev+k)%sz + sz)%sz;
        else
            m = ((prev-k+2)%sz + sz)%sz;
        if (m == 0)
            m = sz;
        if (i%2)
        	prev = m-1;
        else
        	prev = m-2;
        for (s = 1; s < M;) {
            if (st[s<<1] < m)
                m -= st[s<<1], s = s<<1|1;
            else
                s = s<<1;
        }
        last = s-M+1;
        while (s) {
            st[s] --, s >>= 1;
        }
    }
	return last;
}
int main() {
	int n = 0;
	int ret[101] = {};
	for (int i = 1; i <= 10000 && n < 100; i++) {
		int live = josephus(100, i);
		if (ret[live] == 0)
			ret[live] = i, n++;
	}
	while (scanf("%d", &n) == 1 && n) {
		printf("%d\n", ret[n]);
	}
	return 0;
}
