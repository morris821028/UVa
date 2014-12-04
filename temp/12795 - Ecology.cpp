#include <stdio.h> 
#include <vector>
#include <map>
#include <algorithm>
#include <set> 
#include <string.h>
#include <assert.h>
using namespace std;
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

int place(int x, int y, int n, const Area &a) {
	int ox = x, oy = y;
	int sum = 0;
	for (int i = 0; i < a.V.size(); i++) {
		x = ox + a.V[i].first;
		y = oy + a.V[i].second;
		if (x < 0 || y < 0 || x >= n || y >= n)	return 0;
		sum += g[x][y];
	}
	return sum;
}
int main() {	
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	for (int i = 1; i <= 10; i++) {
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
	while (scanf("%d %d", &n, &m) == 2) {
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &g[i][j]);
			}
		}
		
		int ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int mx[16] = {}, mxx = 0, tmp;
				for (int p = 0; p < m && i + p <= n; p++) {
					mxx = 0;
					for (int q = 0; q < m && j + q <= n; q++) {
						mx[q] = max(mx[q], g[i+p][j+q]);
						mxx = max(mxx, mx[q]);
						if (mxx * m <= ret)	continue;
						vector<int> D;
						for (int a = i; a <= i+p; a++)
							for (int b = j; b <= j+q; b++) 
								D.push_back(g[a][b]);
						sort(D.begin(), D.end(), greater<int>());
						tmp = 0;
						for (int a = 0; a < m; a++)
							tmp += D[a];
						if (tmp <= ret)		continue;
						for (set<Area>::iterator it = shape[m][p][q].begin(); 
							it != shape[m][p][q].end(); it++) {
							ret = max(ret, place(i, j, n, *it));
						}
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
5 6
31 12 7 1 14
23 98 3 87 1
5 31 8 2 99
12 3 42 17 88
120 2 7 5 7
4 8
1 1 1 1
9 9 9 1
9 1 9 1
9 9 9 1
3 5
0 5 0
5 5 5
0 5 0

10 5
733 950 26 696 512 570 327 531 829 600 
499 459 728 877 673 464 368 438 566 599 
512 631 242 499 919 931 688 602 490 172 
587 745 704 453 475 370 47 439 705 844 
133 449 264 732 361 612 196 635 739 853 
944 872 938 228 74 296 604 677 801 27 
763 628 650 40 558 159 7 500 405 423 
450 455 26 543 881 87 292 431 74 546 
349 115 568 589 390 40 606 802 434 479 
732 890 361 334 208 439 118 18 494 894 
*/
