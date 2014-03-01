#include <stdio.h>

int main() {
	int n, m, i, j, k;
	char map[101][101];
	while(scanf("%d", &n) == 1 && n) {
		scanf("%d", &m);
		for(i = 0; i < n; i++)
			scanf("%s", &map[i]);
		int ans = 0, length, width, tmp;
		for(i = 0; i < n; i++) {
			int sum[101] = {};
			for(j = i; j < n; j++) {
				for(k = 0; k < m;  k++) {
					sum[k] += map[j][k]-'0';
					if(k == 0 || tmp != length*width)
						tmp = 0, length = 0;
					tmp += sum[k];
					length++, width = j-i+1;
					if(tmp == length*width)
						ans += length;
				}
			}
		}
		printf("%d\n", ans);
	}
    return 0;
}
