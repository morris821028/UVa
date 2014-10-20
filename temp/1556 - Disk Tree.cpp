#include <stdio.h> 
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
struct Node {
	string c;
    map<string, int> next;
    Node() {
    	next.clear();
    }
    void init(string s) {
    	c = s;
    	next.clear();
    }
} nodes[1048576];
int TrieSize = 0;
void insertTrie(vector<string> s) {
	int p = 0;
	for (int i = 0; i < s.size(); i++) {
		if (nodes[p].next.find(s[i]) == nodes[p].next.end()) {
			nodes[++TrieSize].init(s[i]);
			nodes[p].next[s[i]] = TrieSize;
		}
		p = nodes[p].next[s[i]];
	}
}
void dfs(int u, int depth) {
	if (u) {
		for (int i = 1; i < depth; i++)
			printf(" ");
		printf("%s\n", nodes[u].c.c_str());
	}
	for (map<string, int>::iterator it = nodes[u].next.begin();
		it != nodes[u].next.end(); it++)
		dfs(it->second, depth + 1);
}
int main() {
	int n;
	char s[1024];
	string token;
	while (scanf("%d", &n) == 1) {
		nodes[0].init("");
		TrieSize = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			for (int j = 0; s[j]; j++)
				if (s[j] == '\\')
					s[j] = ' ';
			stringstream sin(s);
			vector<string> d;
			while (sin >> token)
				d.push_back(token);
			insertTrie(d);
		}
		dfs(0, 0);
		puts("");
	}
	return 0;
}
