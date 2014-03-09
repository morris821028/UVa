#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
int dp[10][1<<8][1<<8];
vector<int> getPlace(int O, int X, int W) {
	vector<int> ret;
	for(int i = (1<<W)-1; i >= 0; i--) {
		if((i&O) != O || (i&X) != 0)	continue;
		ret.push_back(i);
	}
	return ret;
}
int checkIntersect(int up, int down, int W) {
	// xo       ox
	// ox  and  xo are Intersect.
	for(int i = 1; i < W; i++) {
		int LL, LR, RL, RR;
		LL = (up>>(i-1))&1;
		LR = (up>>(i))&1;
		RL = (down>>(i-1))&1;
		RR = (down>>(i))&1;
		if(LL + LR + RL + RR != 2)
			continue;
		if(LL == RR || LR == RL)
			return 1;
	}
	return 0;
}
struct DisjointSet {
	int parent[20];
	void init(int n) {
		for(int i = 0; i < n; i++)
			parent[i] = i;
	}
	int findp(int x) {
		return parent[x] == x ? x : parent[x] = findp(parent[x]);
	}
	int joint(int x, int y) {
		x = findp(x), y = findp(y);
		if(x == y)	return 0;
		parent[x] = y;
		return 1;
	}
};
void solve(int H, int W, char g[][10]) {
	int last_row = 0;
	int rowO[10] = {}, rowX[10] = {};
	int i, j, k, p, q, r;
	int prev;
	for(i = 0; i < H; i++) {
		for(j = 0; j < W; j++) {
			if(g[i][j] == 'o')
				last_row = i;
			if(g[i][j] == 'o')
				rowO[i] |= 1<<j;
			if(g[i][j] == 'x')
				rowX[i] |= 1<<j; 
		}
	}
	memset(dp, 0x7f, sizeof(dp));
#define oo 0x7f7f7f7f
	dp[0][0][0] = 0;
	for(i = 0; i < H; i++) {
		vector<int> place = getPlace(rowO[i], rowX[i], W);
		for(j = 1<<W; j >= 0; j--) {
			for(k = 0; k < 256; k++) {
				if(dp[i][j][k] == oo)
					continue;
				int up = j, down;
				int upC[4] = {k&3, (k>>2)&3, (k>>4)&3, (k>>6)&3}, upCnt = 0;
				int upA[8] = {}, downA[8] = {};
				for(p = 0, prev = 0; p < 4; p++) {
					int cover = upC[p];
					while(prev < W && ((up>>prev)&1) == 0)
						prev++;
					if(prev < W)	upCnt++;
					while(prev < W && ((up>>prev)&1) == 1)
						upA[prev] = cover, prev++;
				}
				for(vector<int>::iterator it = place.begin();
					it != place.end(); it++) {
					down = *it;
					if(checkIntersect(up, down, W))
						continue;
					// build new component assign
					int mapped_upC[4] = {-1, -1, -1, -1};
					DisjointSet dset; // component[0~3], posY[4~3+W]
					dset.init(4+W);
					int cnt_upC[4] = {};
					for(p = 0, prev = -2; p < W; p++) {
						if((down>>p)&1) {
							if(prev == p-1)
								dset.joint(4+prev, 4+p); 
							prev = p;
						}
					}
					for(p = 0; p < W; p++) {
						if(((down>>p)&1) && ((up>>p)&1)) {
							int C = upA[p];
							cnt_upC[C]++;
							dset.joint(C, 4+p);
						}
					}
					int err = 0;
					for(p = 0; p < W; p++) {
						if((up>>p)&1) {
							int C = upA[p];
							if(cnt_upC[C] == 0)
								err = 1;
						}
					}
					if(err)	continue; // lost one kind of component.
					int downKind = 0, downCnt = 0;
					int mapped_cc[12];
					int downC = 0;
					for(p = 0; p < W+4; p++)
						mapped_cc[p] = -1;
					for(p = 0, prev = -2; p < W; p++) {
						if((down>>p)&1) {
							if(prev != p-1) {
								int parent = dset.findp(p+4);
								if(mapped_cc[parent] == -1)
									mapped_cc[parent] = downKind++;
								downC |= mapped_cc[parent]<<(2*downCnt);
								downCnt++;
							}
							prev = p;
						}
					}
					for(p = 0; p < W; ) { // check don't have a hole.
						while(p < W && ((down>>p)&1) == 0)
							p++;
						if(p >= W)	break;
						int kind[4] = {};
						while(p < W && ((down>>p)&1)) {
							if((up>>p)&1) {
								kind[upA[p]]++;
								if(kind[upA[p]] > 1) {
									err = 1;
								}
								while(p < W && ((down>>p)&1) && ((up>>p)&1))
									p++;
							} else
								p++;
						}
					}
					if(err)	{
						/*for(p = 0; p < W; p++)
							printf("%d", (up>>p)&1);
						puts("--- up");
						for(p = 0; p < W; p++) {
							if(((up>>p)&1) == 0) {
								printf("n");
								continue;
							}
							printf("%d", upA[p]);
						}
						puts("--- upkind");
						for(p = 0; p < W; p++)
							printf("%d", (down>>p)&1);
						puts("--- down");
						for(p = 0; p < W; p++) {
							if(((down>>p)&1) == 0) {
								printf("n");
								continue;
							}
							int parent = dset.findp(p+4);
							printf("%d", mapped_cc[parent]);
						}
						puts("--- downkind");
						puts("");*/
						continue; // have a hole.
					}
					if(downKind > 4 || downCnt > 4) {
						puts("error !!!");
					}
					int diff = 0;
					for(p = 0; p < W; p++) {
						if(((down>>p)&1) == 0)
							continue;
						int cost = 4;
						if(p-1 >= 0 && ((down>>(p-1))&1))
							cost -= 2;
						if((up>>p)&1)
							cost -= 2;
						diff += cost;
					}
					dp[i+1][down][downC] = min(dp[i+1][down][downC], dp[i][up][k] + diff);
				}
			}
		}
	}
	int ret = oo;
	for(i = last_row+1; i <= H; i++) {
		for(j = (1<<W)-1; j >= 0; j--)
			ret = min(ret, dp[i][j][0]);
	}
	if(ret == oo)	ret = -1;
	printf("%d\n", ret);
}
int main() {
	// freopen("in.txt", "r+t", stdin);
	int testcase, cases = 0;
	int H, W;
	int i, j, k;
	char g[10][10];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &H, &W);
		for(i = 0; i < H; i++)
			scanf("%s", g[i]);
		printf("Case #%d: ", ++cases);
		solve(H, W, g);
	}
	return 0;
}
/*
10
5 5
.....
..o..
..x..
..o..
.....

3
3 3
.o.
.x.
o.o
4 4
....
.ox.
.xo.
....
5 5
.ooo.
.x...
..xoo
x.xoo
.ox.x
*/
