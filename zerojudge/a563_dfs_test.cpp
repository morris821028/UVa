#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int g[100][100] = {}, gt[100] = {}, ans;
int used[100] = {}, chn[100] = {};
int n, m;
void dfs(int ch, int use) {
    if(ch >= ans)   return;
	if(use == n) {
		if(ch < ans)	ans = ch;
		for(int i = 0; i < ch; i++)
            printf("%d ", chn[i]);
        puts(" sol");
        for(int i = 0; i < n; i++)
            printf("%d ", used[i]);
        puts("");
		return ;
	}
	int i, j, idx, tmp;
	for(i = 0; i < n; i++) {
	    if(!used[i]) {
	        idx = i;
	        break;
	    }
	}
	tmp = use+1;
	used[idx]++;
	chn[ch] = idx;
	for(i = 0; i < gt[idx]; i++) {/*ch it*/
	    if(!used[g[idx][i]])    tmp++;
	    used[g[idx][i]]++;
	}
	printf("choose %d\n", idx);
	for(i = 0; i < n; i++)
        printf("%d ", used[i]);
    puts("");
	dfs(ch+1, tmp);
	used[idx]--;
	for(i = 0; i < gt[idx]; i++)
	    used[g[idx][i]]--;
    printf("back choose %d\n", idx);
	for(i = 0; i < n; i++)
        printf("%d ", used[i]);
    puts("");
	for(i = 0; i < gt[idx]; i++) {
	    tmp = use;
	    chn[ch] = g[idx][i];
	    if(!used[g[idx][i]])    tmp++;
	    used[g[idx][i]]++;/*ch g[idx][i]*/
	    for(j = 0; j < gt[g[idx][i]]; j++) {
	        if(!used[g[g[idx][i]][j]])    tmp++;
	        used[g[g[idx][i]][j]]++;
	    }
	    printf("other ch %d\n", g[idx][i]);
	    for(j = 0; j < n; j++)
            printf("%d ", used[j]);
        puts("");
	    dfs(ch+1, tmp);
	    used[g[idx][i]]--;
	    for(j = 0; j < gt[g[idx][i]]; j++)
	        used[g[g[idx][i]][j]]--;
	    printf("back other ch %d\n", g[idx][i]);
	    for(j = 0; j < n; j++)
            printf("%d ", used[j]);
        puts("");
	}
}
int main() {
    int x, y, i, j;
	while(scanf("%d %d", &m, &n) == 2) {
		memset(gt, 0, sizeof(gt));
		memset(used, 0, sizeof(used));
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x][gt[x]++] = y, g[y][gt[y]++] = x;
		}
		ans = n;
		dfs(0, 0);
		printf("%d\n", ans);
	}
    return 0;
}
