#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct  Trie {
	int n;
	int link[10];
}Node[200000];
int TrieSize;
void insertTrie(const char* str) {
	static int i, idx;
	idx = 0;
	for(i = 0; str[i]; i++) {
		if(Node[idx].link[str[i]-'0'] == 0) {
			TrieSize++;
			memset(&Node[TrieSize], 0, sizeof(Node[0]));
			Node[idx].link[str[i]-'0'] = TrieSize;
		}
		idx = Node[idx].link[str[i]-'0'];
	}
	Node[idx].n ++;
}
int max, maxNum;
void findAns(int now) {
	if(Node[now].n != 0) {
		if(max == Node[now].n) {
			maxNum += Node[now].n;
		} else if(max < Node[now].n){
			max = Node[now].n;
			maxNum = max;
		}
	}
	int i;
	for(i = 0; i < 10; i++) {
		if(Node[now].link[i] != 0) {
			findAns(Node[now].link[i]);
		}
	}
}
int cmp(const void *i, const void *j) {
	return *(int *)i - *(int *)j;
}
int main() {
	int n, A[5];
	char buf[20];
	while(scanf("%d", &n) == 1 && n) {
		TrieSize = 0;
		memset(&Node[0], 0, sizeof(Node[0]));
		while(n--) {
			scanf("%d %d %d %d %d", &A[0], &A[1], &A[2], &A[3], &A[4]);
			qsort(A, 5, sizeof(int), cmp);
			sprintf(buf, "%d%d%d%d%d", A[0], A[1], A[2], A[3], A[4]);
			insertTrie(buf);
		}
		max = 0, maxNum = 0;
		findAns(0);
		printf("%d\n", maxNum);
	}
    return 0;
}
