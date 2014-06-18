#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;
struct Node {
	int index;
	int val, lson, rson, parent;
};
Node D[50005];
char s[50005][105];
bool cmp(int a, int b) {
	return strcmp(s[a], s[b]) < 0;
}
void insertCartesianTree(int index, Node D[]) {
	int p = index - 1;
	while(D[p].val < D[index].val)
		p = D[p].parent;
	D[index].lson = D[p].rson;
	D[p].rson = index;
	D[index].parent = p;
}
void dfsPrint(int node) {
	if(node == 0)	return;
	putchar('(');
	dfsPrint(D[node].lson);
	printf("%s/%d", s[D[node].index], D[node].val);
	dfsPrint(D[node].rson);
	putchar(')');
}
int main() {
	int N, x[50005], A[50005];
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 1; i <= N; i++) {
			scanf(" %[a-z]/%d", s[i], &x[i]);
			A[i] = i;
		}
		sort(A+1, A+1+N, cmp);
		D[0].val = 0x3f3f3f3f;
		D[0].lson = D[0].rson = D[0].parent = 0;
		for(int i = 1; i <= N; i++) {
			D[i].lson = D[i].rson = D[i].parent = 0;
			D[i].val = x[A[i]], D[i].index = A[i];
		}
		for(int i = 1; i <= N; i++) {
			insertCartesianTree(i, D);
		}
		dfsPrint(D[0].rson);
		puts("");
	}
	return 0;
}
