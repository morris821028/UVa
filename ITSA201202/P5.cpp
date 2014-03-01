#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main() {
	int n, i, j, k;
	char map[100][20];
	int DP[20] = {1, 1};
	for(i = 2; i < 20; i++) {
		DP[i] = DP[i-1]*i;
	}
	while(scanf("%d", &n) == 1) {
		int Ans[100], tmp = 0;
		for(i = 0; i < n; i++) {
			scanf("%s", map[i]);
			int way = DP[strlen(map[i])], ASCII[128] = {};
			for(j = 0; map[i][j]; j++)
				ASCII[map[i][j]]++;
			for(j = 0; j < 128; j++)
				way /= DP[ASCII[j]];
			Ans[i] = way;
			if(way > tmp)	tmp = way;
		}
		for(i = 0; i < n; i++)
			if(tmp == Ans[i])
				printf("%s\n", map[i]);
	}
    return 0;
}
