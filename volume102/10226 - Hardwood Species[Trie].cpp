#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct  Trie {
	int n;
	int link[128];
}Node[400000];
int TrieSize;
void insertTrie(const char* str) {
	static int i, idx;
	idx = 0;
	for(i = 0; str[i]; i++) {
		if(Node[idx].link[str[i]] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[str[i]] = TrieSize;
		}
		idx = Node[idx].link[str[i]];
	}
	Node[idx].n ++;
}
char buf[35];
void printAns(int n, int now, int slen) {
	if(Node[now].n != 0) {
		buf[slen] = '\0';
		printf("%s %.4f\n", buf, Node[now].n*100.0/n);
	}
	int i;
	for(i = 0; i < 128; i++) {
		if(Node[now].link[i] != 0) {
			buf[slen] = i;
			printAns(n, Node[now].link[i], slen+1);
		}
	}
}
int main() {
	int t;
	char buf[35];
	scanf("%d", &t);
	getchar();
	getchar();
	while(t--) {
		int n = 0;
		memset(&Node[0], 0, sizeof(Node[0]));
		TrieSize = 0;
		while(gets(buf)) {
			if(buf[0] == '\0')	
				break;
			insertTrie(buf);
			n++;
		}
		printAns(n, 0, 0);
		if(t)
			puts("");
	}
    return 0;
}
