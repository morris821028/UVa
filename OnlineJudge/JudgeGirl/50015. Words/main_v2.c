#include <stdio.h>
#include <string.h>
#include <ctype.h>

char s[32], rule[8], path[32];
int letter[26] = {}, g[26][26];
int n, m;
void dfs(int u) {
	if (u == n)  {
		path[u] = '\0';
		int valid = 1;
		for (int i = 1; i < n; i++)
			valid &= g[path[i]-'a'][path[i-1]-'a'] == 0;
		if (valid)
			puts(path);
		return ;
	}
	for (int i = 0; i < 26; i++) {
		if (!letter[i])	
			continue;
		letter[i]--;
		path[u] = 'a' + i;
		dfs(u+1);
		letter[i]++;
	}
}
int main() {
	while (scanf("%s", s) == 1) {
		n = strlen(s);
		memset(g, 0, sizeof(g));
		for (int i = 0; i < n; i++)
			letter[s[i] - 'a']++;
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
