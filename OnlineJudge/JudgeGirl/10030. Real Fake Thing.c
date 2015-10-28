#include <stdio.h>
#include <string.h>

int main() {
	int n, m;
	char s[1024];
	while (scanf("%d %d", &n, &m) == 2) {
		unsigned long attr[1024][16] = {};
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			for (int j = 0; j < m; j++) {
				if (s[j] == '1')
					attr[i][j>>5] |= 1U<<(j&31);
			}
		}
		
		int ret = 0;
		m = m/32 + (m%32 != 0);
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				int a = 0, b = 0;
				unsigned long t1, t2;
				for (int k = 0; k < m; k++) {
					t1 = attr[i][k]&attr[j][k];
					t2 = attr[i][k]|attr[j][k];
					a += __builtin_popcountl(t1);
					b += __builtin_popcountl(t2);
				}
				if (5 * a >= 4 * b)
					ret++;
			}
		}
		printf("%.2lf\n", ret * 100.f / (n * (n-1)/2));
	}
	return 0;
}
