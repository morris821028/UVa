#include <stdio.h>
#include <string.h>

struct Trie {
    int link[52];
} Node[1000000];
int TrieSize;
void insertTrie(int A[], int n) {
	static int i, idx;
	idx = 0;
	for(i = 0; i < n; i++) {
		if(Node[idx].link[A[i]] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[A[i]] = TrieSize;
		}
		idx = Node[idx].link[A[i]];
	}
}
int transNum(char s[]) {
	int suit, rank;
	char sc;
	if(s[0] != '1')		sc = s[1];
	else				sc = s[2];
	switch(sc) {
		case 'C': suit = 0;break;
		case 'D': suit = 1;break;
		case 'H': suit = 2;break;
		case 'S': suit = 3;break;
		default:
			while(1);
	}
	switch(s[0]) {
		case '2'...'9': rank = s[0] - '0';break;
		case 'A': rank = 1;break;
		case '1': rank = 10;break;
		case 'J': rank = 11;break;
		case 'Q': rank = 12;break;
		case 'K': rank = 13;break;
		default:
			while(1);
	}
	return suit * 13 + rank - 1;
}
int main() {
	int n, m, A[100005];
	char s[128];
	while(scanf("%d", &n) == 1 && n) {
		TrieSize = 0;
        memset(&Node[0], 0, sizeof(Node[0]));
        while(n--) {
        	scanf("%d", &m);
        	for(int i = m - 1; i >= 0; i--) {
        		scanf("%s", s);
        		A[i] = transNum(s);
        	}
        	insertTrie(A, m);
        }
        printf("%d\n", TrieSize);
	}
	return 0;
}
