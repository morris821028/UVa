#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
struct TrieNode {
    int n;
    int link[27];
} Node[1048576<<2];
int TrieSize;
int rename(char c) {
	if ('a' <= c && c <= 'z')
		return c - 'a';
	return 26;
}
void insertTrie(const char* str, int root) {
	static int i, idx, c;
	for(i = 0, idx = root; str[i]; i++) {
		c = rename(str[i]);
		if(Node[idx].link[c] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[c] = TrieSize;
		}
		idx = Node[idx].link[c];
	}
}
TrieNode* getTrieNode(const char* str, int root) {
	static int i, idx, c;
	for(i = 0, idx = root; str[i]; i++) {
		c = rename(str[i]);
		if(Node[idx].link[c] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[c] = TrieSize;
		}
		idx = Node[idx].link[c];
	}
	return &Node[idx];
}
const int MAXQL = 10 - 1;
const int MAXQ = 50000;
char ms[MAXQ][32];
int main() {
	int testcase, q, cases = 0;
	char s1[32], s2[32], s[1024];
	int A[1024], B[1024];
	scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%s", s);
		scanf("%d", &q);
		int sn = strlen(s), s1n, s2n, an, bn;
		TrieSize = 2;
		int root1 = 0, root2 = 1;
		memset(&Node[root1], 0, sizeof(Node[root1]));
		memset(&Node[root2], 0, sizeof(Node[root2]));
		for (int i = 0; i < q; i++) {
			scanf("%s %s", s1, s2);
			s1n = strlen(s1), s2n = strlen(s2);
			int m = 0;
			for (int j = 0; j < s1n; j++)
				ms[i][m++] = s1[j];
			ms[i][m++] = '#';
			for (int j = s2n - 1; j >= 0; j--)
				ms[i][m++] = s2[j];
			ms[i][m] = '\0';
			insertTrie(ms[i], root2);
		}
		
		for (int i = 0; i < sn; i++) {
			int idx = root1, idx2, c;
			for (int j = i; j < sn; j++) { // add s[l, r]
				c = rename(s[j]);
				if(Node[idx].link[c] == 0) {
					TrieSize++;
					memset(&Node[TrieSize], 0, sizeof(Node[0]));
					Node[idx].link[c] = TrieSize;
					// create new node == create distinct substring
					int idx2 = root2;
					int L = min(j, i + MAXQL);
					for (int k = i; k <= L; k++) { // brute head
						if (Node[idx2].link[rename(s[k])] == 0)	break;
						idx2 = Node[idx2].link[rename(s[k])];
						if (Node[idx2].link[rename('#')]) {
							int idx3 = Node[idx2].link[rename('#')];
							int R = max(i, j - MAXQL);
							for (int l = j; l >= R; l--) { // brute tail
								if (Node[idx3].link[rename(s[l])] == 0)	break;
								idx3 = Node[idx3].link[rename(s[l])];
								Node[idx3].n ++; // [l, r] = strA + ... + strB
							}
						}
					}
				}
				idx = Node[idx].link[c];
			}
		}
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			TrieNode *p = getTrieNode(ms[i], root2);
			printf("%d\n", p->n);
		}
    }
    return 0;
}
/*
1
abab
3
a a
a b
ba ab
*/
