#include <stdio.h>
#include <string.h>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int dp[1<<18][11];
char used[1<<18][11] = {};
int trans[11][11], tri[10];
int countTri(int state) {
	int ret = 0;
	for (int i = 0; i < 9; i++) {
		if ((state&tri[i]) == tri[i])
			ret++;
	}
	return ret;
}
int dfs(int state, int score) {
	if (used[state][score])		return dp[state][score];
	used[state][score] = 1;
	
	int ret = 0, nstate, had = 9 - score, c, t;
	for (int i = 0; i < 18; i++) {
		if ((state>>i)&1) {
			nstate = state ^ (1<<i); // used it.
			c = countTri(((1<<18)-1)^nstate);
			if (c > had) { // create new
				t = c - had + dfs(nstate, score - (c - had));
				ret = max(ret, t);
			} else {
				t = score - dfs(nstate, score);
				ret = max(ret, t);
			}
		}
	}
	dp[state][score] = ret;
	return ret;
}
int main() {	
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	trans[1][2] = 0, trans[1][3] = 1;
	trans[2][3] = 2;
	trans[2][4] = 3, trans[2][5] = 4, trans[3][5] = 5, trans[3][6] = 6;
	trans[4][5] = 7, trans[5][6] = 8;
	trans[4][7] = 9, trans[4][8] = 10, trans[5][8] = 11, trans[5][9] = 12, trans[6][9] = 13, trans[6][10] = 14;
	trans[7][8] = 15, trans[8][9] = 16, trans[9][10] = 17;
	tri[0] = (1<<0)|(1<<1)|(1<<2);
	tri[1] = (1<<3)|(1<<4)|(1<<7);
	tri[2] = (1<<2)|(1<<4)|(1<<5);
	tri[3] = (1<<5)|(1<<6)|(1<<8);
	tri[4] = (1<<9)|(1<<10)|(1<<15);
	tri[5] = (1<<7)|(1<<10)|(1<<11);
	tri[6] = (1<<11)|(1<<12)|(1<<16);
	tri[7] = (1<<8)|(1<<12)|(1<<13);
	tri[8] = (1<<13)|(1<<14)|(1<<17);
	int testcase, cases = 0;
	int n, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		int state = 0, A = 0, B = 0, turn = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			if (x > y)	swap(x, y);
			int c = countTri(state|(1<<trans[x][y])) - countTri(state);
			if (c) {
				if (turn == 0)		A += c;
				else				B += c;
			} else {
				turn = !turn;
			}
			state |= 1<<trans[x][y];
		}
//		printf("score %d %d\n", A, B);
		state = ((1<<18)-1)^state; // unused: 1
		int had = A + B;
		int mx = dfs(state, 9 - had);
		if (turn == 0)	A += mx, B += 9 - had - mx;
		else			B += mx, A += 9 - had - mx;
		printf("Game %d: %s wins.\n", ++cases, A > B ? "A" : "B");
	}
	return 0;
}
/*
4
6
2 4
4 5
5 9
3 6
2 5
3 5
7
2 4
4 5
5 9
3 6
2 5
3 5
7 8
6
1 2
2 3
1 3
2 4
2 5
4 5
10
1 2
2 5
3 6
5 8
4 7
6 10
2 4
4 5
4 8
7 8
*/
