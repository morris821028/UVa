#include <stdio.h>
#include <stdint.h>

char TLB[64];
static inline unsigned int reverse(register unsigned int x) {
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));
}
int main() {
	int n;
	while (scanf("%s", TLB) == 1) {
		scanf("%d", &n);
		uint32_t mark[2];
		int l = 0, r, x = 0;
		scanf("%u", &mark[0]);
		mark[0] = reverse(mark[0]);
		for (int i = 1; i < n; i++) {
			scanf("%u", &mark[1]);
			mark[1] = reverse(mark[1]);
			
#define test(i) { \
				for (r = ((i+1)<<5) / 5; l < r; l++) { \
					char v = 0; \
					v = v<<1 | ((mark[x>>5]>>(x&31))&1), x++; \
					v = v<<1 | ((mark[x>>5]>>(x&31))&1), x++; \
					v = v<<1 | ((mark[x>>5]>>(x&31))&1), x++; \
					v = v<<1 | ((mark[x>>5]>>(x&31))&1), x++; \
					v = v<<1 | ((mark[x>>5]>>(x&31))&1), x++; \
					putchar(TLB[v]); \
				} \
				x -= 32; \
			}
			test(i);
			mark[0] = mark[1];
		}
		if (n == 1)
			test(0);
		putchar('\n');
	}
	return 0;
}

