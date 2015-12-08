#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[32], rule[8], path[32];
int letter[26] = {}, g[26][26];
int link[32][2];
int n, m;
void dfs(int u) {
	if (u == n)  {
		path[u] = '\0';
		puts(path);
		return ;
	}
	for (int e = link[0][0], pre = 0; e != -1; pre = e, e = link[e][0]) {
		int i = link[e][1];
		if ((u && g[i][path[u-1]-'a']))	continue;
		letter[i]--;
		if (letter[i] == 0)
			link[pre][0] = link[e][0];
		path[u] = 'a' + i;
		dfs(u+1);
		if (letter[i] == 0)
			link[pre][0] = e;
		letter[i]++;		
	}
}
int main() {
	while (scanf("%s", s) == 1) {
		n = strlen(s);
		memset(g, 0, sizeof(g));
		memset(letter, 0, sizeof(letter));
		for (int i = 0; i < n; i++)
			letter[s[i] - 'a']++;
		memset(link, -1, sizeof(link));
		int size = 1;
		for (int i = 0; i < 26; i++) {
			if (letter[i]) {
				link[size-1][0] = size;
				link[size][1] = i;
				size++;
			}
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", rule);
			g[rule[1] - 'a'][rule[0] - 'a'] = 1;
		}
		dfs(0);
	}
	return 0;
}

/*
egg
1
ge 
*/
