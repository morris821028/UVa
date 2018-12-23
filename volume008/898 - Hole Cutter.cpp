#include <bits/stdc++.h>
using namespace std;

#define eps 1e-8

struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0): x(a), y(b) {}
};

struct Seg {
    Pt s, e;
    Seg(Pt a = Pt(), Pt b = Pt()):s(a), e(b) {}
};

int g[205][205][4];
vector<int> X, Y;

int relabel_x(int x) {
	return lower_bound(X.begin(), X.end(), x) - X.begin();
}
int relabel_y(int y) {
	return lower_bound(Y.begin(), Y.end(), y) - Y.begin();
}
Seg relabel_seg(Seg seg) {
	seg.s.x = relabel_x(seg.s.x);
	seg.e.x = relabel_x(seg.e.x);
	seg.s.y = relabel_y(seg.s.y);
	seg.e.y = relabel_y(seg.e.y);
	return seg;
}

int parent[205*205], weight[205*205];
int findp(int x) {
    return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y)	return 0;
    if (weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
void init(int n)  {
    for (int i = 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}


int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		vector<Seg> segs(n);
		X.clear(), Y.clear();
		for (int i = 0; i < n; i++) {
			int xa, xb, ya, yb;
			scanf("%d %d %d %d", &xa, &ya, &xb, &yb);
			xa++, ya++, xb++, yb++;
			segs[i] = Seg(Pt(xa, ya), Pt(xb, yb));
			X.push_back(xa);
			X.push_back(xb);
			Y.push_back(ya);
			Y.push_back(yb);
		}
		X.push_back(0), Y.push_back(0);
		X.push_back(10000), Y.push_back(10000);
		sort(X.begin(), X.end());
		sort(Y.begin(), Y.end());
		X.resize(unique(X.begin(), X.end())-X.begin());
		Y.resize(unique(Y.begin(), Y.end())-Y.begin());

		memset(g, 0, sizeof(g));
		for (int i = 0; i < n; i++) {
			segs[i] = relabel_seg(segs[i]);
			if (segs[i].s.x == segs[i].e.x) {
				int l = min(segs[i].s.y, segs[i].e.y);
				int r = max(segs[i].s.y, segs[i].e.y);
				int x = segs[i].s.x;
				for (int i = l; i < r; i++)
					g[x][i][1] = g[x-1][i][0] = 1;
			} else if (segs[i].s.y == segs[i].e.y) {
				int l = min(segs[i].s.x, segs[i].e.x);
				int r = max(segs[i].s.x, segs[i].e.x);
				int y = segs[i].s.y;
				for (int i = l; i < r; i++)
					g[i][y][3] = g[i][y-1][2] = 1;
			}
		}
		
		init(X.size()*Y.size());
		for (int i = 0; i < X.size(); i++) {
			for (int j = 0; j < Y.size(); j++) {
				if (g[i][j][0] == 0 && i+1 < X.size())
					joint(i*Y.size()+j, (i+1)*Y.size()+j);
				if (g[i][j][1] == 0 && i-1 >= 0)
					joint(i*Y.size()+j, (i-1)*Y.size()+j);
				if (g[i][j][2] == 0 && j+1 < Y.size())
					joint(i*Y.size()+j, i*Y.size()+j+1);
				if (g[i][j][3] == 0 && j-1 >= 0)
					joint(i*Y.size()+j, i*Y.size()+j-1);
			}
		}

		int external = findp(0);
		for (int i = 0; i < X.size(); i++) {
			for (int j = 0; j < Y.size(); j++) {
				int u = findp(i*Y.size()+j);
				if (u == external)
					continue;
				if (g[i][j][0] == 1 && i+1 < X.size() && findp((i+1)*Y.size()+j) != external)
					joint(i*Y.size()+j, (i+1)*Y.size()+j);
				if (g[i][j][1] == 1 && i-1 >= 0 && findp((i-1)*Y.size()+j) != external)
					joint(i*Y.size()+j, (i-1)*Y.size()+j);
				if (g[i][j][2] == 1 && j+1 < Y.size() && findp(i*Y.size()+j+1) != external)
					joint(i*Y.size()+j, i*Y.size()+j+1);
				if (g[i][j][3] == 1 && j-1 >= 0 && findp(i*Y.size()+j-1) != external)
					joint(i*Y.size()+j, i*Y.size()+j-1);
			}
		}
		int ret = 0;
		set<int> T;
		for (int i = 0; i < X.size(); i++) {
			for (int j = 0; j < Y.size(); j++) {
				int u = findp(i*Y.size()+j);
				T.insert(u);
			}
		}
		printf("%d\n", T.size()-1);
	}
	return 0;
}
/*
6
1 0 1 1
2 0 2 2
3 1 3 2
1 0 2 0
1 1 3 1
2 2 3 2
2
0 1 2 1
1 2 1 0
0
*/
