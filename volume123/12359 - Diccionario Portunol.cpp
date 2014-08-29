#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

struct Trie {
    int link[26];
} Node[1<<21];
int TrieSize = 0;
// this problem
int suffix[26] = {}, ending[26] = {};
void insertTrie(int root, const char* str) {
	static int i, idx;
	for(i = 0, idx = root; str[i]; i++) {
		if(Node[idx].link[str[i]-'a'] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[str[i]-'a'] = TrieSize;
		}
		idx = Node[idx].link[str[i]-'a'];
	}
}

void insertTrieSuffix(int root, const char* str) {
	static int i, idx;
    int L = (int)strlen(str);
    ending[str[L - 1]-'a']++;
	for(i = L - 1, idx = root; i >= 0; i--) {
		if(Node[idx].link[str[i]-'a'] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[str[i]-'a'] = TrieSize;
            suffix[str[i]-'a']++;
		}
		idx = Node[idx].link[str[i]-'a'];
	}
}

long long ret = 0;
void dfs(int idx, int root) {
    for (int i = 0; i < 26; i++) {
        if (Node[idx].link[i]) {
            dfs(Node[idx].link[i], root);
            if (idx != root && ending[i])
                ret++; // greedy
        } else {
            if (idx != root)
                ret += suffix[i];
        }
    }
}

// divide two parts, 1) result string in Portuguese words 2) not in.
int main() {
    int n, m;
    char s[1024];
    while (scanf("%d %d", &n, &m) == 2 && n + m) {
        memset(suffix, 0, sizeof(suffix));
        memset(ending, 0, sizeof(ending));
        
        int root1 = 0, root2 = 1;
        TrieSize = 1;
        memset(&Node[root1], 0, sizeof(Node[root1]));
        memset(&Node[root2], 0, sizeof(Node[root2]));
        
        for (int i = 0; i < n; i++) {
            scanf("%s", s);
            insertTrie(root1, s);
        }
        for (int i = 0; i < m; i++) {
            scanf("%s", s);
            insertTrieSuffix(root2, s);
        }
        
        ret = 0;
        dfs(root1, root1);
        printf("%lld\n", ret);
    }
    return 0;
}

/*
 3 3
 mais
 grande
 mundo
 mas
 grande
 mundo
 1 5
 a
 aaaaa
 aaaaaa
 aaaaaaa
 a
 aaaaaaaaa
 1 1
 abc
 abc
 0 0
 */
