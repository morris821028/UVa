#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
#define MAXN 14
int A[2][MAXN][2], used[2][MAXN], n;
char stmt[4][32] = {
	"No players can win",
	"Only player Red can win",
	"Only player Green can win",
	"Both players can win"};
int ret;
void dfs(int turn, int head, int tail, int lA, int lB, int pass) {
	if (pass >= 2)	return ;
	if (lA == 0) 	{ret |= 1; return;}
	if (lB == 0) 	{ret |= 2; return;}
	int has = 0;
	for (int i = 0; i < n && ret != 3; i++) {
		if (used[turn][i])
			continue;
		if (A[turn][i][0] == head) {
			used[turn][i] = 1;
			dfs(1 - turn, A[turn][i][1], tail, lA - (turn == 0), lB - (turn == 1), 0);
			has = 1;
			used[turn][i] = 0;
		}
		if (A[turn][i][1] == head && A[turn][i][0] != A[turn][i][1]) {
			used[turn][i] = 1;
			dfs(1 - turn, A[turn][i][0], tail, lA - (turn == 0), lB - (turn == 1), 0);
			has = 1;
			used[turn][i] = 0;
		}
		if (A[turn][i][0] == tail) {
			used[turn][i] = 1;
			dfs(1 - turn, head, A[turn][i][1], lA - (turn == 0), lB - (turn == 1), 0);
			has = 1;
			used[turn][i] = 0;
		}
		if (A[turn][i][1] == tail && A[turn][i][0] != A[turn][i][1]) {
			used[turn][i] = 1;
			dfs(1 - turn, head, A[turn][i][0], lA - (turn == 0), lB - (turn == 1), 0);
			has = 1;
			used[turn][i] = 0;
		}
	}
	if (!has) {
		dfs(!turn, head, tail, lA, lB, pass + 1);
	}
} 
int main() {
	int cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &A[0][i][0], &A[0][i][1]);
		for (int i = 0; i < n; i++)
			scanf("%d %d", &A[1][i][0], &A[1][i][1]);
		
		int dA = -1, dB = -1;
		for (int i = 0; i < n; i++) {
			if (A[0][i][0] == A[0][i][1] && (dA == -1 || A[0][dA][0] < A[0][i][0]))
				dA = i;
			if (A[1][i][0] == A[1][i][1] && (dB == -1 || A[1][dB][0] < A[1][i][0]))
				dB = i;
		}
		
		if (cases++)
			puts("");
		if (dA == -1 && dB == -1) {
			puts(stmt[0]);
		} else {
			memset(used, 0, sizeof(used));
			ret = 0;
			if (A[0][dA][0] > A[1][dB][0]) {
				used[0][dA] = 1;
				dfs(1, A[0][dA][0], A[0][dA][0], n-1, n, 0);
			} else {
				used[1][dB] = 1;
				dfs(0, A[1][dB][0], A[1][dB][0], n, n-1, 0);
			}
			puts(stmt[ret]);
		}
	}
	return 0;
}
