#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

#define BASE 26
const long long mod = 1000000007LL;

int n;
char pattern[128], token[32][32], foo[32];
int pattern_len, token_len[32];
// 
char path[128];
long long ret = 0, suffix[128];
int check(int idx) {
	for (int i = 0; i < n; i++) {
		if (idx < token_len[i])
			continue;
		int ok = 1;
		for (int j = 0, k = idx - token_len[i]; j < token_len[i] && ok; j++, k++) {
			ok &= path[k] == token[i][j];
		}
		if(ok) {
//			path[idx] = '\0';
//			printf("%s %lld\n", path, suffix[idx]);
//			getchar();
			ret = (ret + suffix[idx]);
			return 1;
		}
	}
	return 0;
}
void dfs(int idx) {
//	path[idx] = '\0';
//	puts(path);
	if(check(idx))
		return;
	if(idx == pattern_len)
		return;
	int L, R;
	if (pattern[idx] == '*')
		L = 'a', R = 'z';
	else
		L = R = pattern[idx];
	for (int i = L; i <= R; i++) {
		path[idx] = i;
		dfs(idx + 1);
	}
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out1.txt", "w+t", stdout); 
    while(scanf("%d %s", &n, &pattern) == 2) {
    	for (int i = 0; i < n; i++) {
    		scanf("%s", token[i]);
    		token_len[i] = strlen(token[i]);
    	}
    	pattern_len = strlen(pattern);
    	suffix[pattern_len] = 1;
    	for (int i = pattern_len - 1; i >= 0; i--) {
    		if(pattern[i] == '*')
    			suffix[i] = (suffix[i+1] * BASE)%mod;
    		else
    			suffix[i] = suffix[i+1];
    	}
    	ret = 0;
    	dfs(0); 
    	printf("%lld\n", ret);
    }
    return 0;
}
/*
1 m
m
1 moe**
moe
2 ***
moe ta
4 ***f*
v xf yzyfx objfx
5 ***e*
fme tge pue bse loew
*/
