#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
#define eps 1e-6
struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
	Pt operator-(const Pt &a) const {
		Pt ret;
		ret.x = x - a.x;
		ret.y = y - a.y;
        return ret;
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double length(Pt a) {
	return hypot(a.x, a.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}

double distProjection(Pt as, Pt at, Pt s, double &div) {
	long long a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	div = a * a + b * b;
	return (a * s.x + b * s.y + c) /* / hypot(a, b) */;
}

int main() {
	int cases = 0, n, q;
	Pt D[32767], a, b;
	while(scanf("%d %d", &n, &q) == 2) {
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &D[i].x, &D[i].y);
		}
		for(int i = 0; i < q; i++) {
			scanf("%d %d", &a.x, &a.y);
			scanf("%d %d", &b.x, &b.y);
			
			vector<double> dist;
			double div;
			for(int j = 0; j < n; j++)
				dist.push_back(distProjection(a, b, D[j], div));
			sort(dist.begin(), dist.end());
			
			double sum = 0, ret;
			for(int j = 0; j < n; j++)
				sum += dist[j] - dist[0];
			ret = sum;
			for(int j = 1; j < n; j++) {
				sum = sum - (dist[j] - dist[j-1]) * (n - j) + (dist[j] - dist[j-1]) * j;
				ret = min(ret, sum);
			}
			printf("Case %d: %.0lf\n", ++cases, ret / sqrt(div));
		}
	}
	return 0;
}
