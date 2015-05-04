#include <stdio.h> 
#include <algorithm>
#include <set>
#include <queue>
using namespace std;

const unsigned int hash_mod = 100019;
set< pair<int, int> > R[hash_mod];
unsigned int hash(int x, int y) {
	unsigned int a = 63689, b = 378551;
	unsigned int value = 0;
	int c[4] = {x, y, y, x};
	for (int i = 0; i < 4; i++) {
		value = value * a + c[i];
		a *= b;
	}
	return value % hash_mod;
}

const int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
const int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};
int bfs(int sx[], int sy[], int dstep[], int n) {		
	for (int i = 0; i < hash_mod; i++)
		R[i].clear();
		
	queue<int> X[64], Y[64];
	int step, tx, ty, x, y;
	
	for (int i = 63; i >= 0; i--) {
		for (int j = 0; j < n; j++) { 
			if (dstep[j] == i) {		
				X[i].push(sx[j]), Y[i].push(sy[j]);
				R[hash(sx[j], sy[j])].insert(make_pair(sx[j], sy[j]));
			} 
		} 
		while (!X[i].empty()) {
			x = X[i].front(), X[i].pop();
			y = Y[i].front(), Y[i].pop();
			
			if (i == 0)	continue;
			for (int k = 0; k < 8; k++) {
				tx = x + dx[k], ty = y + dy[k];
				if (!R[hash(tx, ty)].count(make_pair(tx, ty))) {
					R[hash(tx, ty)].insert(make_pair(tx, ty));
					X[i-1].push(tx), Y[i-1].push(ty);
				}
			}
		}
	}	
	
	int ret = 0;	
	for (int i = 0; i < hash_mod; i++)
		ret += R[i].size();
	return ret;
}
int main() {
	int x[64], y[64], step[64];
	int n;
	int h[64] = {};
	for (int i = 0; i <= 50; i++) {
		x[0] = y[0] = 0, step[0] = i;
		h[i] = bfs(x, y, step, 1);
	}
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &x[i], &y[i], &step[i]);
		
		int independent = 0;
		for (int i = 0; i < n; i++) {
			int d = 0x3f3f3f3f;
			for (int j = 0; j < n; j++) {
				if (i == j)	continue;
				d = min(d, max(abs(x[i] - x[j]) + abs(y[i] - y[j]) - 3 * (step[i] + step[j]), 0));
			}
			if (d > 0)
				independent += h[step[i]], step[i] = -1;
		}
				
		int ret = bfs(x, y, step, n) + independent;

		printf("%d\n", ret);
	}
	return 0;
}

/*
5
1 1 0
2 2 0
3 3 0
4 4 0
5 5 0

5
1 1 1
2 2 1
3 3 1
4 4 1
5 5 1

4
-1 -1 2
2 2 1
3 3 3
4 4 3

30
0 0 50
1 1000 50
2 2000 50
3 3000 50
4 4000 50
5 5000 50
6 6000 50
7 7000 50
8 8000 50
9 9000 50
10 10000 50
11 11000 50
12 12000 50
13 13000 50
14 14000 50
15 15000 50
16 16000 50
17 17000 50
18 18000 50
19 19000 50
20 20000 50
21 21000 50
22 22000 50
23 23000 50
24 24000 50
25 25000 50
26 26000 50
27 27000 50
28 28000 50
29 29000 50
*/
