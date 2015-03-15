#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <map>
#include <algorithm>
using namespace std;
#define MAXN 131072
pair<int, int> D[MAXN];
int parent[MAXN], weight[MAXN];
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)
		return 0;
	if (weight[x] > weight[y]) {
		weight[x] += weight[y];
		parent[y] = x;
		D[x].first = min(D[x].first, D[y].first);
		D[x].second = max(D[x].second, D[y].second);
	} else {
		weight[y] += weight[x];
		parent[x] = y;
		D[y].first = min(D[x].first, D[y].first);
		D[y].second = max(D[x].second, D[y].second);
	}
	return 1;
}
// binary indexed tree
pair<int, int> BIT[MAXN * 2];
void modify(int x, int L, pair<int, int> val, pair<int, int> BIT[]) {
	while (x <= L) {
		BIT[x].first += val.first;
		BIT[x].second += val.second;
		x += x&(-x);
	}
}
pair<int, int> query(int x, pair<int, int> BIT[]) {
	pair<int, int> ret(0, 0); 
	while (x) {
		ret.first += BIT[x].first;
		ret.second += BIT[x].second;
		x -= x&(-x);
	}
	return ret;
}
void modifyInterval(int x, int y, pair<int, int> s, pair<int, int> BIT[], int L) {
	modify(x, L, s, BIT);
	modify(y+1, L, pair<int, int>(-s.first, -s.second), BIT);
}
int main() {
	int testcase, n, m, x, y;
	char cmd[16];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		map<int, int> R;
		for (int i = 0; i < n; i++) {
			scanf("%*d %d", &y);
			D[i] = pair<int, int>(y, y);
			R[y] = 1;
		}
		
		// relabel
		int size = 0;
		for (map<int, int>::iterator it = R.begin(); 
			it != R.end(); it++)
				it->second = ++size;
		for (int i = 0; i < n; i++) {
			y = R[D[i].first];
			D[i] = pair<int, int>(y * 2, y * 2);
//			printf("%d -------\n", y * 2);
		}
		
		// disjoint set
		for (int i = 0; i < n; i++)
			parent[i] = i, weight[i] = 1;
		
		// binary indexed tree
		int L = R.size() * 2 + 5;
		memset(BIT, 0, sizeof(BIT));
		
		// query
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'r') {
				scanf("%d %d", &x, &y);
				if (findp(x) != findp(y)) {
					x = findp(x), y = findp(y);
//					printf("-[%d %d] %d\n", D[x].first, D[x].second, weight[x]);
					modifyInterval(D[x].first, D[x].second, pair<int, int>(-weight[x], -1), BIT, L);
//					printf("-[%d %d] %d\n", D[y].first, D[y].second, weight[y]);
					modifyInterval(D[y].first, D[y].second, pair<int, int>(-weight[y], -1), BIT, L);
					joint(x, y);
					y = findp(y);
//					printf("+[%d %d] %d\n", D[y].first, D[y].second, weight[y]);
					modifyInterval(D[y].first, D[y].second, pair<int, int>(weight[y], 1), BIT, L);
				}
			} else {
				scanf("%d.%d", &x, &y);
				x = (R.upper_bound(x) == R.end() ? size + 1 : R.upper_bound(x)->second);
				x = x * 2 - 1;
//				printf("%d\n", x);
				pair<int, int> ret = query(x, BIT);
				printf("%d %d\n", ret.second, ret.first);
			}
		}
	}
	return 0;
}
/*
3 
10 
1 7 
5 7 
8 6 
3 5 
5 5 
2 3 
10 3 
7 2 
4 1 
11 1 
14
road 0 1 
road 3 5 
line 6.5 
road 4 2 
road 3 8 
road 4 7 
road 6 9 
road 4 1 
road 2 7 
line 4.5 
line 6.5 
line 7.5
line 1.5
line 0.5
*/
