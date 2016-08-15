#include <stdio.h>
#include <stdlib.h>
#define INF 0x3f3f3f3f
#define MAXN 1000
#define OPT_INPUT
int g[MAXN*MAXN];
inline int readchar() {
    static int N = 1048576;
    static char buf[1048576];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
	int n;
#ifndef OPT_INPUT
	while (scanf("%d", &n) == 1) {
#else
	while (ReadInt(&n) == 1) {
#endif
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
#ifndef OPT_INPUT
				scanf("%d", &g[i*n+j]);
#else
				ReadInt(&g[i*n+j]);
#endif
				if (g[i*n+j] == 0)
					g[i*n+j] = INF;
			}
		}
		#pragma offload target(mic) inout(g) in(n)
		{
			#pragma omp parallel
			for (int k = 0; k < n; k++) {
				#pragma omp for
				#pragma ivdep
				for (int i = 0; i < n; i++) {
					int base = g[i*n+k];
					int *g1 = g+i*n, *g2 = g+k*n;
					for (int j = 0; j < n; j++) {
						int cost = base + g2[j];
						if (g1[j] > cost)
							g1[j] = cost;
					}
				}
			}
		}
    	for (int i = 0; i < n; i++) {
			int *g1 = g+i*n;
    		for (int j = 0; j < n; j++) {
    			printf("%d%c", g1[j] == INF ? 0 : g1[j], " \n"[j==n-1]);
			}
		}
	}
	return 0;
}

