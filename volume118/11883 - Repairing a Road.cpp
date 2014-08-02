#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;
#define INF 1e+10
#define eps 1e-8
double g[128][128], a[128][128], e[128][128];
double ternary_search(double l, double r, double vi, double ai) {
	double mid, midmid, md, mmd;
	double ret = INF;
	while(fabs(l-r) > eps) {
		mid = (l+r)/2;
		midmid = (mid+r)/2;
		md = mid + vi * pow(ai, -mid);
		mmd = midmid + vi * pow(ai, -midmid);
		ret = min(ret, md);
		ret = min(ret, mmd);
		if(md < mmd)
			r = midmid;
		else
			l = mid;
	}
	return ret;
}
int main() {
	int n, m, x, y;
	double vi, ai;
	while(scanf("%d %d", &n, &m) == 2 && n+m) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				g[i][j] = INF;
			}
			g[i][i] = 0;
		}
		for(int i = 0; i < m; i++) {
			scanf("%d %d %lf %lf", &x, &y, &vi, &ai);
			g[x][y] = g[y][x] = min(g[x][y], vi);
			a[x][y] = a[y][x] = ai;
		}
		for(int i = 1; i <= n; i++) 
			for(int j = 1; j <= n; j++)
				e[i][j] = g[i][j];
		for(int k = 1; k <= n; k++)
			for(int i = 1; i <= n; i++)
				for(int j = 1; j <= n; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
		double ret = g[1][n];
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				// f(t) = g[1][i] + (t  - g[1][i]) + e[i][j] * a[i][j] ^ (-t) + g[j][n]
				if(e[i][j] >= INF)
					continue;
				ret = min(ret, g[j][n] + ternary_search(g[1][i], g[1][n], e[i][j], a[i][j]));
			}
		}
		printf("%.3lf\n", ret);
	}
	return 0;
}
