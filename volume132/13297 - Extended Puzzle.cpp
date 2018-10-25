#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
int tree[MAXN];
int query(int x) {
	int sum = 0;
	while (x) {
		sum += tree[x];
		x -= x&(-x);
	}
	return sum;
}
void add(int x, int n) {
	while (x <= n) {
		tree[x]++;
		x += x&(-x);
	}
}
int solvable(int n, int m, int g[]) {
	int64_t inv = 0, row, col;
	memset(tree, 0, sizeof(tree[0])*(n*m+1));
	for (int i = n*m-1; i >= 0; i--) {
		if (g[i] == n*m) {
			row = i/m, col = i%m;
			inv += query(n*m);
		} else {
			inv += query(g[i]);
			add(g[i], n*m);
		}
	}
	return (inv+(n-1-row+m-1-col))%2 == 0;
}

int main() {
	int n, m;
	static int g[MAXN];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n*m; i++)
			scanf("%d", &g[i]);
		
	    int ret = solvable(n, m, g);
	    puts(ret ? "Y" : "N");
	}
	return 0;
}
/*
4 4
1 2 3 4
5 6 7 8
9 10 11 12
13 15 14 16
2 2
4 3
2 1
2 3
4 1 3
6 2 5
2 3
4 1 3
6 5 2
*/
