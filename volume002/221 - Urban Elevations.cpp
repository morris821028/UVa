#include <stdio.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Building {
	int x, y;
	int width, depth, height, label;
	int in() {
		return scanf("%d %d %d %d %d", &x, &y, &width, &depth, &height) == 5;
	}
	bool operator<(const Building &a) const {
		if(make_pair(x, y) != make_pair(a.x, a.y))
			return make_pair(x, y) < make_pair(a.x, a.y);
		return depth < a.depth;
	}
}; 
int coverL(vector< pair<int, int> > interval, int l, int r) {
	sort(interval.begin(), interval.end());
	int y = l;
	for(int i = 0; i < interval.size(); i++) {
		if(interval[i].first <= y)
			y = max(y, interval[i].second);
		else
			return 0;
	}
	return y >= r;
}
void solve(Building D[], int n) {
	sort(D, D+n);
	int f = 0;
	for(int i = 0; i < n; i++) {
		vector< pair<int, int> > interval;
		for(int j = 0; j < n; j++) {
			if(j == i)	continue;
			if(D[i].height > D[j].height || D[i].y <= D[j].y)
				continue;
			int l = max(D[i].x, D[j].x), r = min(D[i].x+D[i].width, D[j].x+D[j].width);
			if(l < r)
				interval.push_back(make_pair(l, r));
		}
		if(!coverL(interval, D[i].x, D[i].x + D[i].width)) {
			if(f++)	putchar(' ');
			printf("%d", D[i].label + 1);
		}
	}
	puts("");
}
int main() {
	int n, cases = 0;
	Building D[128];
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++)
			D[i].in(), D[i].label = i;
		if(cases++)	puts("");
		printf("For map #%d, the visible buildings are numbered as follows:\n", cases);
		solve(D, n);
	}
	return 0;
}
/*
14
160 0 30 60 30
125 0 32 28 60
95 0 27 28 40
70 35 19 55 90
0 0 60 35 80
0 40 29 20 60
35 40 25 45 80
0 67 25 20 50
0 92 90 20 80
95 38 55 12 50
95 60 60 13 30
95 80 45 25 50
165 65 15 15 25
165 85 10 15 35
*/
