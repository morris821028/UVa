#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int n, m, dic_sz[128];
char dic[128][16][128], s1[128], s2[128];
int indexOf(char s1[]) {
	for (int i = 0; i < n; i++) {
		if (!strcmp(dic[i][0], s1))
			return i;
	}
	return -1;
}
void common(char s1[], char s2[]) {
	int x = indexOf(s1), y = indexOf(s2), f = 0;
	if (x == -1 || y == -1) {
		puts("nothing");
		return ;
	}
	for (int i = 1; i <= dic_sz[x]; i++) {
		int ok = 1;
		for (int j = 1; j <= dic_sz[y]; j++) {
			if (!strcmp(dic[x][i], dic[y][j])) {
				ok = 1;
				if (f)	putchar(' ');
				f = 1;
				printf("%s", dic[x][i]);
				break;
			}
		}
	}
	if (!f)	puts("nothing");
	else	puts("");
}
int cmp(const void* a, const void* b) {
    const char *ia = (const char *)a;
    const char *ib = (const char *)b;
    return strcmp(ia, ib);
}
int main() {
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%s %d", dic[i][0], &dic_sz[i]);
			for (int j = 1; j <= dic_sz[i]; j++)
				scanf("%s", dic[i][j]);
			qsort(dic[i]+1, dic_sz[i], sizeof(dic[i][0]), cmp);
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s %s", s1, s2);
			common(s1, s2);
		}
	}
	return 0;
}

