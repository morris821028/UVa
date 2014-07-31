#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int B, valid[16], path[128];
vector<string> ret[128];
void dfs(int idx) {
	for(int i = idx == 0; i < B; i++) {
		if(!valid[i])	continue;
		path[idx] = i;
		int f = 0;
		for(int j = 0; j <= idx; j++)
			f = (f * B + path[j])%(idx+1);
		if(f == 0) {
			string s = "";
			for(int j = 0; j <= idx; j++)
				s += (path[j] + '0');
			ret[s.length()].push_back(s);
			dfs(idx+1);
		}
	}
}
int main() {
	char s[1024];
	while(scanf("%d %s", &B, &s) == 2) {
		memset(valid, 0, sizeof(valid));
		for(int i = 0; i < 128; i++)
			ret[i].clear();
		for(int i = 0; s[i]; i++)
			valid[s[i]-'0'] = 1;
		dfs(0);
		for(int i = 127; i >= 0; i--) {
			if(ret[i].size()) {
				sort(ret[i].begin(), ret[i].end());
				printf("%s\n", ret[i][ret[i].size()-1].c_str());
				break;
			}
		}
	}
	return 0;
}
