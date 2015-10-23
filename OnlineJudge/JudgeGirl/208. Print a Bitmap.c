#include <stdio.h>
unsigned int reverse(register unsigned int x) {
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));
}
int main() {
	int n, m;
	unsigned int A[4096];
	char s[4];
	scanf("%d %d", &n, &m);
	scanf("%s", s+2);
	scanf("%s", s);
	s[1] = s[2];
	for (int i = 0; scanf("%u", &A[i]) == 1; i++) A[i] = reverse(A[i]);
	for (int i = 0; i < m; i++, puts("")) {
		for (int j = 0; j < n; j++) {
			int x = i*n+j;
			printf("%c", s[(A[x>>5]>>(x&31))&1]);
		}
	}
	return 0;
}
