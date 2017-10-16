#include <bits/stdc++.h> 
using namespace std;

const int MAXT = (1e+7) + 5;
struct BIT {
	int tree[MAXT], n;
	void init(int n) {
		this->n = n;
		memset(tree, 0, sizeof(tree[0])*n);
	}
	void add(int x, int val) {
		for (; x < n; x += x&(-x))
			tree[x] += val;
	}
	int query(int x) {
		int ret = 0;
		for (; x; x -= x&(-x))
			ret += tree[x];
		return ret;
	}
	int query(int l, int r) {
		return query(r) - query(l-1);
	}
} tree;

static const int MAXN = 32;
static const int MAXM = 1<<24;
static int n, miss[MAXN], cache[MAXN];
static int stamp[MAXM], mtime;

void access(int addr) {
	int &st = stamp[addr];
	if (st == 0) {
		for (int i = 0; i < n; i++)
			miss[i]++;
	} else {
		int cnt = tree.query(st, mtime);
		for (int i = 0; i < n && cnt > cache[i]; i++)
			miss[i]++;
		tree.add(st, -1);
	}
	st = ++mtime;
	tree.add(st, 1);
}

int main() {
	static char cmd[8];
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++)
			scanf("%d", &cache[i]);
			
		memset(stamp, 0, sizeof(stamp));
		mtime = 0;
		tree.init(MAXT);
		
		int addr, b, y, k;
		while (scanf("%s", cmd) == 1 && cmd[0] != 'E') {
			if (cmd[0] == 'A') {
				scanf("%d", &addr);
				access(addr);
			} else if (cmd[0] == 'R') {
				scanf("%d %d %d", &b, &y, &k);
				for (int i = 0; i < k; i++)
					access(b+y*i);
			} else {
				for (int i = 0; i < n; i++)
					printf("%d%c", miss[i], " \n"[i==n-1]);
				memset(miss, 0, sizeof(miss[0])*n);
			}
		}
	}
	return 0;
}
/*
2
4 8
RANGE 1 1 5
RANGE 2 1 2
ADDR   99
STAT
ADDR   2
RANGE 5 -1 2
STAT
RANGE 0 10000 10
RANGE 0 20000 5
RANGE 0 30000 4
STAT
END
*/
