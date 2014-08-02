#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Trie {
    int n, label, dist;
    int link[26];
} Node[1048576];
int TrieSize;
int insertTrie(const char* str) {
	static int i, idx;
	for(i = idx = 0; str[i]; i++) {
		if(Node[idx].link[str[i]-'a'] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[TrieSize].label = TrieSize;
			Node[TrieSize].dist = i + 1;
			Node[idx].link[str[i]-'a'] = TrieSize;
		}
		idx = Node[idx].link[str[i]-'a'];
	}
	Node[idx].n ++;
	return Node[idx].label;
}

vector< pair<int, int> > Q[1048576];// query pair, v - input index.
int visited[1048576], F[1048576];
int LCA[1048576];//input query answer buffer.
int findF(int x) {
    return F[x] == x ? x : (F[x]=findF(F[x]));
}
void tarjan(int u) {// rooted-tree.
    F[u] = u;
    for(int i = 0; i < 26; i++) {//son node.
		int v = Node[u].link[i];
    	if(v == 0)	continue;
        tarjan(v);
        F[findF(v)] = u;
    }
    visited[u] = 1;
    for(int i = 0; i < Q[u].size(); i++) {
        if(visited[Q[u][i].second]) {
            LCA[Q[u][i].first] = findF(Q[u][i].second);
        }
    }
}
int main() {
	int testcase, cases = 0, x, y, n;
	int mp[131072];
	char s[32767];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        for(int i = 1; i <= n; i++) {
        	scanf("%s", s);
        	int x = insertTrie(s);
        	mp[i] = x;
        }
        scanf("%d", &n);
        
        for(int i = 0; i <= TrieSize; i++)
            visited[i] = 0, Q[i].clear();
        for(int i = 0; i < n; i++) {
        	scanf("%d %d", &x, &y);
        	Q[mp[x]].push_back(make_pair(i, mp[y]));
        	Q[mp[y]].push_back(make_pair(i, mp[x]));
		}
		tarjan(0);
		printf("Case %d:\n", ++cases);
		for(int i = 0; i < n; i++) {
			printf("%d\n", Node[LCA[i]].dist);
		}
	}
	return 0;
}
