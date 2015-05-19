#include <stdio.h> 
#include <string.h>
#include <iostream>
#include <vector>
using namespace std;

struct Node {
	Node *l, *r;
	char c;
	void init(char a) {
		c = a, l = r = NULL;
	}
} nodes[128];
int nsize;
void insert(Node* &u, char c) {
	if (u == NULL) {
		u = &nodes[nsize++];
		u->init(c);
		return ;
	}
	if (u->c > c)
		insert(u->l, c);
	else
		insert(u->r, c);
}
void dfs(Node *u) {
	if (u == NULL)
		return ;
	putchar(u->c);
	dfs(u->l);
	dfs(u->r);
}
int main() {
	while (true) {
		string line;
		vector<string> g;
		while (cin >> line) {
			if (line == "$" || line == "*")
				break;
			g.push_back(line);
		}
		memset(nodes, 0, sizeof(nodes));
		
		Node *root = NULL;
		nsize = 0;
		for (int i = g.size() - 1; i >= 0; i--) {
			for (int j = 0; j < g[i].size(); j++)
				insert(root, g[i][j]);
		}
		dfs(root);
		puts("");
		if (line == "$")
			return 0;
	}
	return 0;
}
