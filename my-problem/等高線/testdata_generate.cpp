#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <queue>
#include <set>
#include <map> 
#include <functional>
#include <math.h>
#include <string.h>
using namespace std;

double random() {
	int r = rand();
	return (double) r / RAND_MAX;
}

struct Rectangle {
	int lx, ly, rx, ry;
	Rectangle(int a = 0, int b = 0, int c = 0, int d = 0) :
		lx(a), ly(b), rx(c), ry(d) {
			
		}
	void read() {
		scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
	}
	int contain(Rectangle &a) {
		return lx <= a.lx && ly <= a.ly && rx >= a.rx && ry >= a.ry;
	}
	int contain(int x, int y) {
		return lx <= x && ly <= y && rx >= x && ry >= y;
	}
};
vector<Rectangle> D;
void dfs(int lx, int ly, int rx, int ry, int dep) {
	if (D.size() >= 30000 || dep > 10000)	
		return;
	if (lx >= rx || ly >= ry)	
		return;
	D.push_back(Rectangle(lx, ly, rx, ry));
	int div = rand()%2 + 1;
	int w = rand()%100 + 1;
	lx += w, rx -= w;
	w = rand()%100 + 1;
	ly += w, ry -= w;
	if (rand()%2) {
		int d = (rx - lx)/100 / div, last = lx;
//		for (int i = lx, j = 0; i + d <= rx && lx <= rx && j < div && d > 0; j++) {
//			dfs(i, ly, i + d, ry, dep+1), last = i + d + 1;
//			i += d + 1;
//		}
		dfs(last, ly, rx, ry, dep + 1);
	} else {
		int d = (rx - lx)/100 / div, last = ly;
//		for (int i = ly, j = 0; i + d <= ry && ly <= ry && j < div && d > 0; j++) {
//			dfs(lx, i, rx, i + d, dep+1), last = i + d + 1;
//			i += d + 1;
//		}
		dfs(lx, last, rx, ry, dep + 1);
	}
}
main() {
	int n, m, t, a, b, c, tmp;
	int x, y, z, i, j, k, l, p, q;
	srand ( time(NULL));
	freopen("in.txt", "w+t", stdout);

	int T = 1;
	int MAX_BOUND = 1000000;
	while (T--) {
		D.clear();
		dfs(0, 0, MAX_BOUND, MAX_BOUND, 0);
		printf("%d\n", D.size());
		for (int i = 0; i < D.size(); i++) {
			printf("%d %d %d %d\n", D[i].lx, D[i].ly, D[i].rx, D[i].ry);
		}
		m = rand()%10000 + 10000;
		printf("%d\n", m);
		for (int i = 0; i < m; i++)
			printf("%d %d\n", rand()%MAX_BOUND, rand()%MAX_BOUND);
		if (T)
			puts("");
	}
	return 0;
} 
