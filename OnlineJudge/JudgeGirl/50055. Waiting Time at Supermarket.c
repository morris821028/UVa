#include <stdio.h>
#include <stdlib.h>

static int s, t, has = 0;

int read() {
	if (has)	return 1;
	return has = scanf("%d %d", &t, &s) == 2;
}
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
#define TIME (1<<8)
		static short que[TIME] = {};
		
		int idx = 0, tidx = 0;
		int ret = 0;
		for (int time = 0; idx < m; time++) {
			n += que[tidx], que[tidx] = 0;
			while (n > 0 && idx < m && read() && t <= time) {
				ret += time - t;
				que[(tidx + s)&(TIME-1)]++, n--;
				n += que[tidx], que[tidx] = 0;
				has = 0, idx++;
			}
			tidx = (tidx + 1)&(TIME-1);
		}
		printf("%d\n", ret);
	}
	return 0;
}

