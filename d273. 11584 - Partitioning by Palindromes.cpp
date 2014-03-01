#include<stdio.h>
#include<string.h>
#define oo 1002
char map[1001][1001];
int Build(char *s) {
	int i, j, k, l = strlen(s);
	memset(map, 0, sizeof(map));
	for(i = 0; i < l; i++) {
		j = i, k = i;
		while(j >= 0 && k < l && s[j] == s[k]) {
			map[j][k] = 1;
			j--, k++;
		}
	}
	for(i = 0; i < l-1; i++) {
		j = i, k = i+1;
		while(j >= 0 && k < l && s[j] == s[k]) {
			map[j][k] = 1;
			j--, k++;
		}
	}
}
int procee_DP(char *s) {
	int DP[1001] = {}, l = strlen(s);
	int i, j;
	DP[0] = 1;
	for(i = 1; i < l; i++) {
		DP[i] = oo;
		for(j = 0; j <= i; j++) {
			if(map[j][i]) {
				if(j != 0)
					DP[i] = DP[i] < DP[j-1]+1 ? DP[i] : DP[j-1]+1;
				else
					DP[i] = 1;
			}
		}
	}
	return DP[l-1];
}
main() {
	int t;
	char s[1001];
	scanf("%d", &t);
	while(t--) {
		scanf("%s", s);
		Build(s);
		printf("%d\n", procee_DP(s));
	}
	return 0;
}
