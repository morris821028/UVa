#include <bits/stdc++.h>
using namespace std;
class DLX {
	public:
	struct DancingLinks {
		int left, right, up, down, ch;
		int id, rotate, px, py; // extra data
	} DL[131072 + 256];
	int s[64], o[64], head, size;		
	void remove(int c) {
	    DL[DL[c].right].left = DL[c].left;
	    DL[DL[c].left].right = DL[c].right;
	    int i, j;
	    for(i = DL[c].down; i != c; i = DL[i].down) {
	        for(j = DL[i].right; j != i; j = DL[j].right) {
	            DL[DL[j].down].up = DL[j].up;
	            DL[DL[j].up].down = DL[j].down;
	            s[DL[j].ch]--;
	        }
	    }
	}
	void resume(int c) {
	    int i, j;
	    for(i = DL[c].down; i != c; i = DL[i].down) {
	        for(j = DL[i].left; j != i; j = DL[j].left) {
	            DL[DL[j].down].up = j;
	            DL[DL[j].up].down = j;
	            s[DL[j].ch]++;
	        }
	    }
	    DL[DL[c].right].left = c;
	    DL[DL[c].left].right = c;
	}
	int found;
	void dfs(int dep) {
	    if (DL[head].right == head) {
	        found++;
	        return;
	    }
	    int tmp = 0x3f3f3f3f, c, i, j;
	    for(i = DL[head].right; i != head; i = DL[i].right)
	        if(s[i] < tmp)
	            tmp = s[i], c = i;
	    remove(c);
	    for(i = DL[c].down; i != c; i = DL[i].down) {
	        o[dep] = DL[i].id;
	        for(j = DL[i].right; j != i; j = DL[j].right)
	            remove(DL[j].ch);
	        dfs(dep+1);
	        if (found)
	        	return;
	        for(j = DL[i].left; j != i; j = DL[j].left)
	            resume(DL[j].ch);
	    }
	    resume(c);
	}
	int getnode(int u, int d, int l, int r) {
	    DL[size].up = u, DL[size].down = d;
	    DL[size].left = l, DL[size].right = r;
	    DL[u].down = DL[d].up = DL[l].right = DL[r].left = size;
	    assert(size < 131072);
	    return size++;
	}
	void newrow(int r[], int rn, int id) {
	    int i, j, h;
	    for(i = 0; i < rn; i++) {
	        DL[size].ch = r[i], s[r[i]]++;
	        DL[size].id = id; // extra data
	        if(i) {
	            j = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, DL[h].left, h);
	        } else {
	            h = getnode(DL[DL[r[i]].ch].up, DL[r[i]].ch, size, size);
	        }
	    }
	}
	void init(int c) {// total column
	    size = 0;
	    head = getnode(0,0,0,0);
	    int i;
	    for(i = 1; i <= c; i++) {
	        getnode(i, i, DL[head].left, head);
	        DL[i].ch = i, s[i] = 0;
	    }
	}
} dlx;

char shape[12][3][6] = {
	{{"-----"}, {"*****"}, {"*****"}},
	{{"----*"}, {"-****"}, {"*****"}},
	{{"*-***"}, {"----*"}, {"*****"}},
	{{"-*-**"}, {"---**"}, {"*****"}},
	{{"*--**"}, {"--***"}, {"-****"}},
	{{"---**"}, {"--***"}, {"*****"}},
	{{"---**"}, {"-****"}, {"-****"}},
	{{"*--**"}, {"*-***"}, {"--***"}},
	{{"**-**"}, {"---**"}, {"**-**"}},
	{{"**-**"}, {"---**"}, {"*-***"}},
	{{"*-***"}, {"---**"}, {"*-***"}},
	{{"---**"}, {"*--**"}, {"*****"}}
};

vector<pair<int, int>> get_xy(int sid) {
	vector<pair<int, int>> r;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 5; j++) {
			if (shape[sid][i][j] == '-')
				r.emplace_back(i, j);
		}
	}
	assert(r.size() == 5);
	return r;
}
void normalize(vector<pair<int, int>> &a) {
	int lx = a[0].first, ly = a[0].second;
	for (auto &x : a)
		lx = min(lx, x.first), ly = min(ly, x.second);
	for (auto &x : a)
		x.first -= lx, x.second -= ly;
}
void rotate(vector<pair<int, int>> &a) {
	for (auto &e : a) {
		int x = e.first, y = e.second;
		e.first = -y, e.second = x;
	}
}
void reflect(vector<pair<int, int>> &a) {
	for (auto &e : a) {
		int x = e.first, y = e.second;
		e.first = x, e.second = -y;
	}
}

int g[8][8], gid[8][8], ssid;
vector<vector<pair<int, int>>> kinds;

vector<pair<int, int>> to_place(int x, int y, vector<pair<int, int>> &a) {
	vector<pair<int, int>> r;
	for (auto &e : a)
		r.emplace_back(x+e.first, y+e.second);
	return r;
}

void place(int x, int y, vector<pair<int, int>> &a) {
	int col[5], cn = 0;
	for (auto &e : a) {
		if (x+e.first >= 8 || y+e.second >= 8 || g[x+e.first][y+e.second])
			return;
		col[cn++] = gid[x+e.first][y+e.second];
	}
	dlx.newrow(col, cn, ssid);
	kinds.push_back(to_place(x, y, a));
	ssid++;
}

void place_shape(int sid) {
	vector<pair<int, int>> xy = get_xy(sid);
	set<vector<pair<int, int>>> S;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			normalize(xy);
			if (S.count(xy))
				continue;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++)
					place(i, j, xy);
			}
			S.insert(xy);
			rotate(xy);
		}
		reflect(xy);
	}
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		memset(g, 0, sizeof(g));
		dlx.init(60);
		for (int i = 0; i < 4; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--, y--;
			g[x][y] = 1;
		}
		
		for (int i = 0, id = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (g[i][j] == 0)
					gid[i][j] = ++id;
			}
		}
		
		ssid = 0, kinds.clear();
		for (int i = 0; i < 12; i++)
			place_shape(i);
		dlx.found = 0;
		dlx.dfs(0);
		if (!dlx.found) {
			puts("No solution."); 
		} else {
			char ret[8][8] = {};
			memset(ret, '*', sizeof(ret));
			for (int i = 0; i < 12; i++) {
				for (auto v : kinds[dlx.o[i]])
					ret[v.first][v.second] = 'a'+i;
			}
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++)
					putchar(ret[i][j]);
				puts("");
			}
		}
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
3 5
4 5
5 5
6 5
*/
