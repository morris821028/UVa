#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
	int n, m, w, r;
	char s[1024];
	while (scanf("%d %d %d %d", &n, &r, &w) == 3) {
		int mask[1024] = {};
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			int ans = 0;
			for (int j = 0; s[j]; j++)
				ans |= 1<<(toupper(s[j]) - 'A');
			mask[i] = ans;
		}
		scanf("%d", &m);
		
		for (int i = 0; i < m; i++) {
			int score = 0;
			for (int j = 0; j < n; j++) {
				scanf("%s", s);
				if (!strcmp(s, "N/A"))
					continue;
				int ans = 0;
				for (int k = 0; s[k]; k++)
					ans |= 1<<(toupper(s[k]) - 'A');
				score += ans == mask[j] ? r : -w;
			}
			printf("%d\n", score < 0 ? 0 : score);
		}
	}
	return 0;
}
