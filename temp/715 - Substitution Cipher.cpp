#include <stdio.h> 
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

char word[1024][1024], msg[1024];
char sbox[128];
int sfail[128];
int buildGraph(int n, int m)  {
	vector<int> g[128];
	int indeg[128] = {};
	for (int i = 1; i < n; i++) {
		int p = i-1, q = i;
		for (int j = 0; word[p][j] && word[q][j]; j++) {
			if (word[p][j] != word[q][j]) {
				g[word[p][j]].push_back(word[q][j]);
				indeg[word[q][j]]++;
				break;
			}
		}
	}
	
	deque<int> Q;
	for (int i = 'a'; i < 'a' + m; i++) {
		if (indeg[i] == 0) 
			Q.push_front(i);
	}
			
	int fail[128] = {}, order[128], ocnt = 0, u;
	while (!Q.empty()) {
		u = Q.front(), Q.pop_front();
		if (Q.size() >= 1) {
			for (deque<int>::iterator it = Q.begin();
				it != Q.end(); it++)
				fail[*it] = 1;
		}
		order[ocnt++] = u;
		for (int i = 0; i < g[u].size(); i++) {
			if (--indeg[g[u][i]] == 0) {
				Q.push_back(g[u][i]);
			}
		}
	}
	for (int i = 'a'; i < 'a' + m; i++)
		if (indeg[i] > 0)
			sfail[i] = 1;
		
	for (int i = 0; i < 128; i++)
		sbox[i] = i;
	for (int i = 0; i < ocnt; i++)
		sbox[order[i]] = 'a' + i, sfail[order[i]] = fail[order[i]];
	return 1;
}

int decode(char msg[]) {
	for (int i = 0; msg[i]; i++) {
		if (sfail[msg[i]])
			return 0;
		msg[i] = sbox[msg[i]];
	}
	return 1;
}
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &m, &n);
		for (int i = 0; i < n; i++)
			scanf("%s", word[i]);
		while (getchar() != '\n');
		gets(msg);
		
		buildGraph(n, m);
		int f = decode(msg);
		if (!f) {
			puts("Message cannot be decrypted.");
		} else {
			puts(msg);
		}
	}
	return 0;
}
/*
tricky case:

1
5 5
a
eb
eec
eeed
eeee
e 
*/
