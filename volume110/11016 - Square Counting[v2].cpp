// Wrong Answer 

#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#define eps 1e-6
struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
        x(a), y(b) {}
    bool operator <(const Pt &a) const {
        if(x != a.x)       
            return x < a.x;
        return y < a.y;
    }   
    bool operator ==(const Pt &a) const {
        return x == a.x && y == a.y;
    }
};
/* */
int N;
Pt D[128];
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
long long cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
bool onSegment(Pt p, Pt s, Pt e) {
    if(p == s || p == e)    return 1;
    return cross(p, s, e) == 0
        && dot(Pt(s.x-p.x, s.y-p.y), Pt(e.x-p.x, e.y-p.y)) < 0;
}
bool onLine(Pt p, Pt s, Pt e) {
    return cross(p, s, e) == 0;
}
  
int inPolygon(Pt p[], int n, Pt q) {
    int i, j, cnt = 0;
    for(i = 0, j = n-1; i < n; j = i++) {
    	if(onSegment(q, p[i], p[j]))
            return 1;
        if(p[i].y > q.y != p[j].y > q.y &&
           q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/((double)(p[j].y-p[i].y)) + p[i].x)
           cnt++;
    }
    return cnt&1;
}

int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs)*cross(as, at, bt) <= 0 &&
       cross(at, as, bs)*cross(at, as, bt) <= 0 &&
       cross(bs, bt, as)*cross(bs, bt, at) <= 0 &&
       cross(bt, bs, as)*cross(bt, bs, at) <= 0)
        return 1;
    return 0;
}

int black, white;
void save(int lx, int ly, int rx, int ry) {
	int t = (rx - lx) * (ry - ly);
	if((lx + ly)%2) {
		white += t/2;
		black += t - t/2;
	} else {
		white += t - t/2;
		black += t/2;
	}
}
pair<double, double> getIntersection(Pt p, Pt q, Pt x, Pt y) {
	double a1, b1, c1, a2, b2, c2;
	double dx, dy, d;
	a1 = p.y - q.y,	b1 = q.x - p.x;
	c1 = (a1 * p.x + b1 * p.y);
	a2 = x.y - y.y,	b2 = y.x - x.x;
	c2 = (a2 * x.x + b2 * x.y);
	d = a1 * b2 - a2 * b1;
	dx = b2 * c1 - b1 * c2;
	dy = a1 * c2 - a2 * c1;
	if(fabs(d) < eps)
		return make_pair((double)min(p.x, q.x), (double)min(p.y, q.y));
//	printf("%lf %lf\n", dx/d, dy/d);
	return make_pair(dx / d, dy / d);
}
vector< pair<int, int> > getInterval(int y, int lx, int rx) {
	vector< pair<double, double> > in;
	vector< pair<int, int> > ret;
	pair<double, double> tmp;
	for(int i = 0, j = N-1; i < N; j = i++) {
		if(intersection(D[i], D[j], Pt(lx, y), Pt(rx, y))) {
			tmp = getIntersection(D[i], D[j], Pt(lx, y), Pt(rx, y));
//			printf("%lf %lf\n", tmp.first, tmp.second);			
			if(onLine(D[i], Pt(lx, y), Pt(rx, y)) && onLine(D[j], Pt(lx, y), Pt(rx, y))) {
//				puts("LINE");
				ret.push_back(make_pair(min(D[i].x, D[j].x), max(D[i].x, D[j].x)));
				continue;
			}
			if(fabs(tmp.first - D[i].x) > eps && fabs(tmp.second - D[i].y) > eps
				&& fabs(tmp.first - D[j].x) > eps && fabs(tmp.second - D[j].y) > eps)
				in.push_back(tmp);
			else {
				if(fabs(tmp.second - min(D[i].y, D[j].y)) <= eps) {
					in.push_back(tmp);
//					printf("down %lf %lf %d %d %d %d\n", tmp.first, tmp.second, 
//						D[i].x, D[i].y, D[j].x, D[j].y);
				}
			}			

		}
	}
	sort(in.begin(), in.end());
//	printf("[%d] size %d\n", y, in.size());
	for(int i = 0; i < in.size(); i += 2) {
		double px1 = in[i].first, px2 = in[i + 1].first;
		int l = ceil(px1), r = floor(px2);
		if(l >= r)	continue;
//		printf("[%d] %d %d\n", y, l, r);
		if(l < r)
			ret.push_back(make_pair(l, r));
	}
	sort(ret.begin(), ret.end());
//	puts("");
	return ret;
}
void solveSquare(int y, vector< pair<int, int> > &L, vector< pair<int, int> > &R) {
	if(L.size() == 0 || R.size() == 0)
		return;
	int idx1 = 0, idx2 = 0, l, r;
	l = max(L[0].first, R[0].first);
	while(idx1 < L.size() && idx2 < R.size()) {
		l = max(max(L[idx1].first, R[idx2].first), l);
		r = min(L[idx1].second, R[idx2].second);
		if(l <= r) {
			if(l < r) {
				save(l, y, r, y+1);
//				printf("%d %d %d\n", y, l, r);
			}
			if(L[idx1].second < R[idx2].second)
				idx1++;
			else
				idx2++;
		} else {
			if(L[idx1].first < R[idx2].first)
				idx1++;
			else
				idx2++;
		}
	}
}
int main() {
	while(scanf("%d", &N) == 1 && N) {
		int lx, ly, rx, ry;
		lx = ly = 10000;
		rx = ry = 0;
		for(int i = 0; i < N; i++) {
			scanf("%d %d", &D[i].x, &D[i].y);
			lx = min(lx, D[i].x);
			ly = min(ly, D[i].y);
			rx = max(rx, D[i].x);
			ry = max(ry, D[i].y);
		}
		
		white = black = 0;
		for(int i = ly; i <= ry; i++) {
			vector< pair<int, int> > L, R;
			L = getInterval(i, lx - 1, rx + 1);
			R = getInterval(i + 1, lx - 1, rx + 1);
			solveSquare(i, L, R);
		}
		if(white < black)
			swap(white, black);
		printf("%d %d\n", white, black);
	}
	return 0;
}
/*
11
2 1
6 4
10 1
15 3
13 8
15 11
9 9
11 5
7 11
1 7
4 8
4
0 0
0 1
1 1
1 0
0
*/
