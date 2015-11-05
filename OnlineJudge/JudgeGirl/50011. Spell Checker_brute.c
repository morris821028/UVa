#include <stdio.h>
#include <string.h>
#define MAXN 100005
char dic[MAXN][128], s[MAXN];
int diclen[MAXN];
int N, Q;
int find(char s[]) {
	for (int i = 0; i < N; i++) {
		if (!strcmp(s, dic[i]))
			return 1;
	}
	return 0;
}
void edit(char s[]) {
	int n = strlen(s);
	int has = 0;
	for (int i = 0; i < N; i++) {
		if (diclen[i] < n-1 || diclen[i] > n+1)
			continue;
		int ok = 0;
		if (diclen[i] == n) {
			int diff = 0;
			for (int j = 0; j < n && diff < 2; j++)
				diff += dic[i][j] != s[j];
			ok = diff <= 1;
		} else if (diclen[i] == n-1) {
			int diff = 0;
			for (int j = 0, k = 0; j < n-1 && diff < 2; j++) {
				if (dic[i][j] != s[k])	k++, diff++, j--;
				else k++;
			}
			ok = diff <= 1;
		} else {
			int diff = 0;
			for (int j = 0, k = 0; k < n && diff < 2; j++) {
				if (dic[i][j] != s[k])	diff++;
				else k++;
			}
			ok = diff <= 1;
		}
		if (ok) {
			if (has != 0)	putchar(' ');
			else			putchar('?'), has = 1;
			printf("%s", dic[i]);
		}			
	}
	if (!has)	printf("!%s\n", s);
	else		printf("\n");
}
int main() {
	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; i++)
			scanf("%s", dic[i]), diclen[i] = strlen(dic[i]);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%s", s);
			if (find(s)) {
				printf(">%s\n", s);
				continue;
			}
			edit(s);
		}
	}
	return 0;
}
