#include <stdio.h>
#include <string.h>
int main() {
	int t, P, T;
	char blank[200];
	scanf("%d ", &t);
	while(t--) {
		scanf("%d %d ", &P, &T);
		int PT[101][101] = {};
		int i, j, k;
		while(gets(blank)) {
			if(strcmp(blank, "") == 0)
				break;
			sscanf(blank, "%d %d", &i, &j);
			PT[i][j] = 1;
		}
		int ans = 0, used[101] = {};
		for(i = 1; i <= P; i++) {
			if(used[i] == 0) {
				for(j = i+1; j <= P; j++) {
					if(used[j] == 0) {
						for(k = 1; k <= T; k++)
							if(PT[i][k] != PT[j][k])
								break;
						if(k == T+1)
							used[j] = 1;
					}
				}
				ans ++;
			}
		}
		printf("%d\n", ans);
		if(t)	puts("");
	}
    return 0;
}
