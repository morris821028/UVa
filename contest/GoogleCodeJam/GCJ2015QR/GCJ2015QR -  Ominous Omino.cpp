#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
#include <set> 
#include <string.h>
#include <assert.h>
using namespace std;

class DLX {
	public:
	struct DancingLinks {
		int left, right, up, down, ch;
		int id, rotate, px, py; // extra data
	} DL[262144];
	int s[1024], o[1024], head, size;		
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
		if (found) return;
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
	        o[dep] = i;
	        for(j = DL[i].right; j != i; j = DL[j].right)
	            remove(DL[j].ch);
	        dfs(dep+1);
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
	void newrow(int r[], int rn, int id, int rotate, int px, int py) {
	    int i, j, h;
	    for(i = 0; i < rn; i++) {
	        DL[size].ch = r[i], s[r[i]]++;
	        DL[size].id = id; // extra data
	        DL[size].rotate = rotate; // extra data
	        DL[size].px = px; // extra data
	        DL[size].py = py; // extra data
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
} DLX;

int g[64][64], n, m;
int used[64][64];
pair<int, int> path[64], pre[64][64];
const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
struct Area {
	vector<pair<int, int> > V;
	bool operator<(const Area &a) const {
		for (int i = 0; i < V.size(); i++) 
			if (V[i] != a.V[i])	return V[i] < a.V[i];
		return false;
	}
	Area() {
		V.clear();
	}
};
// Number of fixed polyominoes with n cells. https://oeis.org/A001168
set<Area> shape[16][16][16];
void formalArea(Area &a) {
	sort(a.V.begin(), a.V.end());
	int x, y, mx, my;
	x = a.V[0].first, y = a.V[0].second;
	mx = x, my = y;
	for (int i = 0; i < a.V.size(); i++) {
		x = min(x, a.V[i].first), y = min(y, a.V[i].second);
		mx = max(mx, a.V[i].first), my = max(my, a.V[i].second);
	}
	for (int i = 0; i < a.V.size(); i++)
		a.V[i].first -= x, a.V[i].second -= y;
	sort(a.V.begin(), a.V.end());
}
void storeArea(Area a) {
	sort(a.V.begin(), a.V.end());
	int x, y, mx, my;
	x = a.V[0].first, y = a.V[0].second;
	mx = x, my = y;
	for (int i = 0; i < a.V.size(); i++) {
		x = min(x, a.V[i].first), y = min(y, a.V[i].second);
		mx = max(mx, a.V[i].first), my = max(my, a.V[i].second);
	}
	for (int i = 0; i < a.V.size(); i++)
		a.V[i].first -= x, a.V[i].second -= y;
	sort(a.V.begin(), a.V.end());
	shape[a.V.size()][mx - x][my - y].insert(a);
	assert(mx - x >= 0 && mx - x < 16 && my - y >= 0 && my - y < 16);
}
void dfs(int idx, int x, int y, int pick, int m) {
	if (pick == m) {
		Area t;
		for (int i = 0; i < pick; i++)
			t.V.push_back(path[i]);
		storeArea(t);
		return ;
	}
	if (idx >= 2 * m)
		return;
	vector< pair<int,int> > test;
	for (int i = 0; i < 4; i++) {
		int tx = x + dx[i], 
			ty = y + dy[i];
		if (used[tx][ty])
			continue;
		pre[tx][ty] = make_pair(x, y);
		path[pick] = make_pair(tx, ty);
		used[tx][ty] = 1;
		dfs(idx+1, tx, ty, pick + 1, m);
		test.push_back(make_pair(tx, ty));
	}
	if (pre[x][y].first != -1) // stop on leaf
		dfs(idx+1, pre[x][y].first, pre[x][y].second, pick, m);
	for (int i = 0; i < test.size(); i++) {
		int tx = test[i].first,
			ty = test[i].second;
		used[tx][ty] = 0;
	}
}
int place(int x, int y, int n, int m, const Area &a) {
	int ox = x, oy = y;
	for (int i = 0; i < a.V.size(); i++) {
		x = ox + a.V[i].first;
		y = oy + a.V[i].second;
		if (x < 0 || y < 0 || x >= n || y >= m)	return 0;
	}
	return 1;
}

void rotate(Area &a) {
	int x, y;
	for (int i = 0; i < a.V.size(); i++) {
		x = a.V[i].first;
		y = a.V[i].second;
		a.V[i].first = -y;
		a.V[i].second = x;
	}
	formalArea(a);
}
void reflect(Area &a) {
	int x, y;
	for (int i = 0; i < a.V.size(); i++) {
		x = a.V[i].first;
		y = a.V[i].second;
		a.V[i].first = -x;
		a.V[i].second = y;
	}
	formalArea(a);
}
void print(Area a) {
	int mark[16][16] = {};
	for (int i = 0; i < a.V.size(); i++)
		mark[a.V[i].first][a.V[i].second] = 1;
	for (int i = 0; i < 4; i++, puts("")) {
		for (int j = 0; j < 4; j++) {
			if (mark[i][j])	printf("*");
			else			printf(" ");
		}
	}
}

int solve2(int R, int C, int ban[][16], int row2[], int X) {
	DLX.init(R * C);
	DLX.newrow(row2, X, 0, 0, 0, 0);
	
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < X; j++) {
			for (set<Area>::iterator it = shape[X][i][j].begin(); 
						it != shape[X][i][j].end(); it++) {
				Area a = *it;
				
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 2; j++) {
						//
						for (int p = 0; p < R; p++) {
							for (int q = 0; q < C; q++) {
								if (place(p, q, R, C, a)) {
									int row[32], ok = 1;
									for (int r = 0; r < a.V.size(); r++) {
										int x = p + a.V[r].first;
										int y = q + a.V[r].second;
										row[r] = x * C + y + 1;
										if (ban[x][y])
											ok = 0;
									}
									if (ok) {
										DLX.newrow(row, X, 0, 0, 0, 0);
									}
								}
							}
						}
						reflect(a);
					}
					rotate(a);
				}
				
				
			}
		}
	}
	
	DLX.found = 0;
	DLX.dfs(0);
	return DLX.found > 0;
}
int solve(Area a, int R, int C, int X) {
	if (R * C % a.V.size())
		return 0;
//	puts("search");
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			//
			for (int p = 0; p < R; p++) {
				for (int q = 0; q < C; q++) {
					if (place(p, q, R, C, a)) {
						int row[32];
						int ban[16][16] = {};
						for (int r = 0; r < a.V.size(); r++) {
							int x = p + a.V[r].first;
							int y = q + a.V[r].second;
							ban[x][y] = 1; // must used
							row[r] = x * C + y + 1;
						}
						
						int v = solve2(R, C, ban, row, X);
						if (v)
							return 1;
					}
				}
			}
			reflect(a);
		}
		rotate(a);
	}
	return 0;
}
int main() {	
	for (int i = 1; i <= 5; i++) {
		for (int j = 0; j < 32; j++)
			for (int k = 0; k < 32; k++)
				pre[j][k] = make_pair(-1, -1);
		pre[11][11] = make_pair(-1, -1);
		path[0] = make_pair(11, 11);
		used[11][11] = 1;
		dfs(1, 11, 11, 1, i);
		used[11][11] = 0;
		int sum = 0;
		for (int j = 0; j < i; j++) {
			for (int k = 0; k < i; k++)
				sum += shape[i][j][k].size();
		} 
//		printf("complete %d %d\n", i, sum);
	}

	int testcase, cases = 0;
	int X, R, C;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &X, &R, &C);
		
		int ret = 0;
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < X; j++) {
				for (set<Area>::iterator it = shape[X][i][j].begin(); 
						it != shape[X][i][j].end(); it++) {
					int t = solve(*it, R, C, X);
					if (t == 0)
						ret = 1;
				}
			}
		}
//		printf("%d\n", ret);
		printf("Case #%d: %s\n", ++cases, ret ? "RICHARD" : "GABRIEL");
	}
	return 0;
}
/*
*/
