#include <bits/stdc++.h>
using namespace std;

#define MAXNODE 50000
#define MAXCOL 50
#define MAXN 50
#define INF 0x3f3f3f
struct DancingNode {
    int left, right, up, down;
    int ch, rh, w;
} DL[MAXNODE];
struct HelperNode {
    int head, size, next, prev;
} HN[MAXNODE];
int help_head;
int s[MAXCOL];
int head, size, Ans;
void Remove(int c) {
	DL[DL[c].right].left = DL[c].left;
    DL[DL[c].left].right = DL[c].right;
    for (int i = DL[c].down; i != c; i = DL[i].down) {
    	if (HN[DL[i].rh].head == i)
    		HN[DL[i].rh].head = DL[i].left;
    	HN[DL[i].rh].size--;
        DL[DL[i].right].left = DL[i].left;
        DL[DL[i].left].right = DL[i].right;
        s[DL[i].ch]--;
    }
}
void Resume(int c) {
    for (int i = DL[c].down; i != c; i = DL[i].down) {
    	if (HN[DL[i].rh].head == i)
    		HN[DL[i].rh].head = DL[i].right;
    	HN[DL[i].rh].size++;
        DL[DL[i].right].left = i;
        DL[DL[i].left].right = i;
        s[DL[i].ch]++;
    }
    DL[DL[c].right].left = c;
    DL[DL[c].left].right = c;
}
void Reduce(int i) {
    int t = DL[i].rh;
    HN[HN[t].next].prev = HN[t].prev;
    HN[HN[t].prev].next = HN[t].next;
    s[DL[i].ch]--;
    
    DL[DL[i].down].up = DL[i].up;
    DL[DL[i].up].down = DL[i].down;
    for (int k = DL[i].right; k != i; k = DL[k].right) {
        DL[DL[k].down].up = DL[k].up;
        DL[DL[k].up].down = DL[k].down;
        s[DL[k].ch]--;
    }
}
void Recover(int i) {
    int t = DL[i].rh;
    HN[HN[t].next].prev = t;
    HN[HN[t].prev].next = t;
    s[DL[i].ch]++;
    
    DL[DL[i].down].up = i;
    DL[DL[i].up].down = i;
    for (int k = DL[i].right; k != i; k = DL[k].right) {
        DL[DL[k].down].up = k;
        DL[DL[k].up].down = k;
        s[DL[k].ch]++;
    }
}

void Select(int i, int j) {
    int s = DL[i].rh;
    Reduce(i);
    Remove(j);
    HN[HN[s].next].prev = HN[s].prev;
    HN[HN[s].prev].next = HN[s].next;
}

void Cancel(int i, int j) {
	int s = DL[i].rh;
	Resume(j);
	Recover(i);
    HN[HN[s].next].prev = s;
    HN[HN[s].prev].next = s;
}

int new_node(int up, int down, int left, int right) {
    DL[size].up = up, DL[size].down = down;
    DL[size].left = left, DL[size].right = right;
    DL[up].down = DL[down].up = DL[left].right = DL[right].left = size;
    return size++;
}

void new_row(int n, int R[][2], int rh) {
    int r, row = -1, k;
    int h = size;
    for (int i = 0; i < n; i++) {
        r = R[i][0];
        DL[size].ch = r, s[r]++;
        DL[size].rh = rh;
        DL[size].w = R[i][1];
        if (row == -1) {
            row = new_node(DL[DL[r].ch].up, DL[r].ch, size, size);
        } else {
            k = new_node(DL[DL[r].ch].up, DL[r].ch, DL[row].left, row);
        }
    }
    HN[rh].size = n;
    HN[rh].head = h;
    HN[rh].next = HN[help_head].next;
    HN[rh].prev = help_head;
    HN[HN[help_head].next].prev = rh;
    HN[help_head].next = rh;
}
void init(int m) {
    size = 0;
    help_head = 0, HN[help_head].next = HN[help_head].prev = help_head;
    head = new_node(0, 0, 0, 0);
    for (int i = 1; i <= m; i++) {
        new_node(i, i, DL[head].left, head);
        DL[i].ch = i, s[i] = 0;
        DL[i].rh = 0;	// important pointer (fail pointer)
    }
}

int Dx[MAXN], Dy[MAXN];
int markRStk[MAXNODE*50], markRidx = -1;
int markCStk[MAXNODE*50], markCidx = -1;

void printDL(int n) {
	for (int i = HN[help_head].prev; i != help_head; i = HN[i].prev) {
		int j = HN[i].head, prev = 1;
		printf("%2d ", DL[j].rh);
		do {
			while (prev < DL[j].ch)
				prev++, printf(" -- ");
			prev = DL[j].ch+1;
			int rh = DL[j].rh, ch = DL[j].ch;
			printf("[%2d]", DL[j].w - Dx[rh] - Dy[ch]);
			j = DL[j].right;
		} while (j != HN[i].head);
		while (prev <= n)
			prev++, printf(" -- ");
		puts("");
	}
	puts("----------------------");
}
int cH(int limit = INF) {
	int ins = 0;
	for (int i = HN[help_head].prev; i != help_head; i = HN[i].prev) {
		if (HN[i].size == 0)
			return INF;
		int j = HN[i].head, v = INF;
		int rh = DL[j].rh, ch;
		do {
			ch = DL[j].ch;
			v = min(v, DL[j].w - Dx[rh] - Dy[ch]);
			j = DL[j].right;
		} while (j != HN[i].head);
		if (v == INF || ins+v >= limit)
			return INF;
		assert(v >= 0);
		ins += v;
		Dx[rh] += v;
		markRStk[++markRidx] = v;
		markRStk[++markRidx] = rh;
	}
//	printf("Reduce %d\n", ins);
//	printDL(5);
	for (int i = DL[head].right; i != head; i = DL[i].right) {
		if (DL[i].down == i)
			return INF;
		int j = DL[i].down, v = INF;
		int ch = DL[i].ch, rh;
		do {
			rh = DL[j].rh;
			v = min(v, DL[j].w - Dx[rh] - Dy[ch]);
			j = DL[j].down;
		} while (j != i);
		if (v == INF || ins+v >= limit)
			return INF;
		assert(v >= 0);
		ins += v;
		Dy[ch] += v;
		markCStk[++markCidx] = v;
		markCStk[++markCidx] = ch;
	}
	return ins;
}
void rH(int backRidx, int backCidx) {
	while (markRidx > backRidx) {
		int a = markRStk[markRidx--];
		int b = markRStk[markRidx--];
		Dx[a] -= b;
	}
	while (markCidx > backCidx) {
		int a = markCStk[markCidx--];
		int b = markCStk[markCidx--];
		Dy[a] -= b;
	}
}

int G[MAXN][MAXN];
int isSame(int vx, int vy) {
	int i = HN[vx].head, j = HN[vy].head;
	do {
		if (DL[i].ch != DL[j].ch && (DL[i].ch != vy && DL[j].ch != vx))
			return 0;
		int e1 = DL[i].w - Dx[vx] - Dy[DL[i].ch];
		int e2 = DL[j].w - Dx[vy] - Dy[DL[j].ch];
		if (e1 != e2)
			return 0;
		i = DL[i].right;
		j = DL[j].right;	
	} while (i != HN[vx].head && j != HN[vy].head);
	return i == HN[vx].head && j == HN[vy].head;
}

struct edge {
    int x, y, v;
    edge(int a = 0, int b = 0, int c = 0):
    x(a), y(b), v(c) {}
    bool operator<(const edge &a) const {
        return v < a.v;
    }
};
int parent[MAXN];
void initDisjoint(int n) {
    for (int i = 0; i <= n; i++)
        parent[i] = i;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y) return 0;
    parent[y] = x;
    return 1;
}
int MST(int st, int ed, int limit = INF) {
	int i = HN[help_head].prev;
	static edge e[MAXNODE];
	static int used[MAXN] = {}, cases = 0;
	int ecnt = 0, max_n = 0, n = 0;
	int ret = 0, in = INF, out = INF;
	cases++;
	do {
		int j = HN[i].head;
		do {
			int x = DL[j].rh, y = DL[j].ch;
			int w = DL[j].w - Dx[x] - Dy[y];
			if (x == st) {
				in = min(in, w);
			} else if (y == ed) {
				out = min(out, w);
			} else {
				e[ecnt++] = edge(x, y, w);
				if (used[x] != cases)
					used[x] = cases, n++;
				if (used[y] != cases)
					used[y] = cases, n++;
				max_n = max(max_n, x);
				max_n = max(max_n, y);
			}
			j = DL[j].right;
		} while (j != HN[i].head);
		i = HN[i].prev;
	} while (i != help_head);
	initDisjoint(max_n);
	ret = in + out;
	if (ret >= limit)
		return limit;
	sort(e, e+ecnt);
	for (int i = 0; i < ecnt && ret <= limit; i++) {
		if (joint(e[i].x, e[i].y))
			ret += e[i].v, n--;
	}
//	fprintf(stderr, "cost %d %d\n", ret, n);
	if (n > 1)
		return INF;
	return ret;
}

int path[MAXN];
void DFS(int u, int lower_bound, int idx) {
	if (lower_bound >= Ans) {
//	if (lower_bound + MST(u, 1, Ans - lower_bound) >= Ans) {
		return ;
	}

	if (HN[HN[help_head].prev].prev == help_head) {
		if (Ans >= lower_bound) {
/*
			path[0] = 1;
			int cc = 0;
			for (int i = 1; i < idx; i++) {
				cc += G[path[i-1]][path[i]];
			}
			cc += G[path[idx-1]][path[0]];
			for (int i = 0; i < idx; i++)
				fprintf(stderr, "%d ", path[i]);
			fprintf(stderr, "\n%d %d\n", lower_bound, cc);
*/
		}

		Ans = min(Ans, lower_bound);
		return ;
	}
	
	int i = HN[u].head;
	do {
		int v = DL[i].ch;
		int runnable = 1;
		if (v == 1)
			runnable = 0;
/*
		if (runnable) {
			int e1 = DL[i].w - Dx[u] - Dy[v];
			for (int j = HN[u].head; j != i && runnable; j = DL[j].right) {
				int e2 = DL[j].w - Dx[u] - Dy[DL[j].ch];
				if (e1 != e2)
					continue;
				if (isSame(v, DL[j].ch))
					runnable = 0;
			}
		}
*/

		if (runnable) {
			int backRidx = markRidx, backCidx = markCidx;
			int tu = HN[u].head;
			Select(tu, v);
			int c = cH(Ans - lower_bound);
			path[idx] = v;
			if (c != INF)
				DFS(v, lower_bound + c + DL[i].w - Dx[u] - Dy[v], idx+1);
			rH(backRidx, backCidx);
			Cancel(tu, v);
		}
		i = DL[i].right;
	} while (i != HN[u].head);
}

void test() {
	int n = 23;
	int ans[MAXN] = {1, 17, 15, 7, 14, 5, 13, 19, 18, 11, 6, 12, 8, 16, 2, 20, 21, 4, 9, 23, 3, 10, 22};
	int used[MAXN] = {};
	int cc = cH();
	int cmp = 0;
	printDL(n);
	for (int i = 1; i < n; i++) {
		assert(used[ans[i]] == 0);
		used[ans[i]] = 1;
		cmp += G[ans[i-1]][ans[i]];
		Select(HN[ans[i-1]].head, ans[i]);
		int c = cH() + G[ans[i-1]][ans[i]] - Dx[ans[i-1]] - Dy[ans[i]];
		printf("reduce %d select %d\n", c, ans[i]);
		printDL(n);
		cc += c;
	}
	cmp += G[ans[n-1]][1];
	printf("Origin Simulate %d\n", cmp);
	printf("My Algorithm Simluate %d\n", cc);
	exit(0);
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		init(n);
		for (int i = 1; i <= n; i++) {
			int R[128][2], Rcnt = 0;
			for (int j = 1; j <= n; j++) {
				assert(scanf("%d", &G[i][j]) == 1);
				if (G[i][j])
					R[Rcnt][0] = j, R[Rcnt][1] = G[i][j], Rcnt++;
			}
			new_row(Rcnt, R, i);
		}
	//	test();

		int backRidx = markRidx, backCidx = markCidx;
		Ans = INF;
		DFS(1, cH(), 1);
		rH(backRidx, backCidx);
		printf("%d\n", Ans);

	}
	return 0;
}
/*
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
5
0 20 30 10 11
15 0 16 4 2
3 5 0 2 4 
19 6 18 0 3
16 4 7 16 0

6
 0 39 37 37 39 37
39  0 36 38 35 35
37 36  0 36 39 36
37 38 36  0 35 37
39 35 39 35  0 38
37 35 36 37 38  0

*/



