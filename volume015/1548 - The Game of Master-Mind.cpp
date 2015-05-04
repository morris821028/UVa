#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXM = 128;
const int MAXP = 11;
const int MAXC = 128;
int P, C, M;
int B[MAXM], W[MAXM], G[MAXM][MAXP], CG[MAXM][MAXC];
int path[MAXP], bcnt[MAXM], bwcnt[MAXM], CGcnt[MAXC];
// B[i] = |vector_intersection(G, S)|
// W[i] = |set_intersection(G, S)| - B[i]
// ===>|set_intersection(G, S)| = B[i] + W[i]
int checkValid(int p, int c) {
	for (int i = 0; i < M; i++) {
		if (G[i][p] == c && bcnt[i] == B[i])
			return 0; // BLACK exceeded
		if (CGcnt[c] < CG[i][c] && bwcnt[i] == B[i] + W[i])
			return 0; // |set_intersection(G, S)| > B[i] + W[i]
	}
	return 1;
}
void remove(int p, int c) {
	for (int i = 0; i < M; i++) {
		if (G[i][p] == c)
			bcnt[i]++;
		if (CGcnt[c] < CG[i][c])
			bwcnt[i]++;
	}
	CGcnt[c]++;
}
void resume(int p, int c) {
	for (int i = 0; i < M; i++) {
		if (G[i][p] == c)
			bcnt[i]--;
		if (CGcnt[c] <= CG[i][c])
			bwcnt[i]--;
	}
	CGcnt[c]--;
}
int dfs(int idx) {
	if (idx == P) {
		int ok = 1;
		for (int i = 0; i < M && ok; i++)
			ok &= bcnt[i] == B[i] && bwcnt[i] == B[i] + W[i];
		return ok;
	}
	for (int i = 1; i <= C; i++) {
		if (!checkValid(idx, i))
			continue;
		remove(idx, i);
		path[idx] = i;
		if (dfs(idx+1))
			return 1;
		resume(idx, i);
	}
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &P, &C, &M);
		for (int i = 0; i < M; i++) {
			memset(CG[i], 0, sizeof(CG[i]));
			for (int j = 0; j < P; j++) {
				scanf("%d", &G[i][j]);
				CG[i][G[i][j]]++;
			}
			scanf("%d %d", &B[i], &W[i]);
		}
		
		memset(bcnt, 0, sizeof(bcnt));
		memset(bwcnt, 0, sizeof(bwcnt));
		memset(CGcnt, 0, sizeof(CGcnt));
		int f = dfs(0);
		if (f) {
			for (int i = 0; i < P; i++)
				printf("%d%c", path[i], i == P-1 ? '\n' : ' ');
		} else {
			puts("You are cheating!");
		}
	}
	return 0;
}
