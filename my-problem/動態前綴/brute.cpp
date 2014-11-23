#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <string.h>
#include <assert.h>
using namespace std;

#define MAXN (1<<17)
char S[MAXN];
void change(char s[], int p, int x) {
	s[p] = x;
}
int query(char s[], int p, int q) {
	int ret = 0;
	for (; s[p] == s[q] && s[p] && s[q]; p++, q++, ret++);
	return ret;
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("brute_out.txt", "w+t", stdout); 
	char cmd[8], s[8];
	int Q, p, q, n;
	while (scanf("%s", S) == 1) {
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'Q') {
				scanf("%d %d", &p, &q);
				printf("%d\n", query(S, p, q));
			} else {
				scanf("%d %s", &p, s);
				change(S, p, s[0]);
			}
		}
	}
	return 0;
}
