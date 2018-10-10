#include <stdio.h>
#define MAXN (1048576>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[MAXN] = {};
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char c;
			while ((c = getchar()) <= ' ');
			c -= '0';
			if (c)
				SET(i*n+j);
		}
	}
	
	int ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0, c = 0; j < n; j++) {
			if (GET(i*n+j)) {
				c++;
				if (c > ret)
					ret = c;
			} else {
				c = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0, c = 0; j < n; j++) {
			if (GET(i+j*n)) {
				c++;
				if (c > ret)
					ret = c;
			} else {
				c = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0, c = 0; i+j < n; j++) {
			if (GET(j+(i+j)*n)) {
				c++;
				if (c > ret)
					ret = c;
			} else {
				c = 0;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0, c = 0; i+j < n; j++) {
			if (GET(j*n+(i+j))) {
				c++;
				if (c > ret)
					ret = c;
			} else {
				c = 0;
			}
		}
	}
	printf("%d\n", ret);
	return 0;
}
