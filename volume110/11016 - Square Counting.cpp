// TLE
#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;
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
    if(cross(as, at, bs)*cross(as, at, bt) < 0 &&
       cross(at, as, bs)*cross(at, as, bt) < 0 &&
       cross(bs, bt, as)*cross(bs, bt, at) < 0 &&
       cross(bt, bs, as)*cross(bt, bs, at) < 0)
        return 1;
    return 0;
}

int rectInPolygon(int lx, int ly, int rx, int ry) {
	Pt a(lx, ly), b(lx, ry), c(rx, ry), d(rx, ly);
	int f;
	f = inPolygon(D, N, a) && inPolygon(D, N, b) 
		&& inPolygon(D, N, c) && inPolygon(D, N, d);
	if(!f)	return 0;
	for(int i = 0, j = N - 1; i < N; j = i++) {
		f = !intersection(D[i], D[j], a, b) &&
			!intersection(D[i], D[j], b, c) &&
			!intersection(D[i], D[j], c, d) &&
			!intersection(D[i], D[j], d, a);
		if(!f)	return 0;
	}
	return 1;
}
int checkPossible(int lx, int ly, int rx, int ry) {
	Pt a(lx, ly), b(lx, ry), c(rx, ry), d(rx, ly);
	int f;
	f = inPolygon(D, N, a) || inPolygon(D, N, b) 
		|| inPolygon(D, N, c) || inPolygon(D, N, d);
	if(f)	return 1;
	for(int i = 0, j = N - 1; i < N; j = i++) {
		f = lx <= D[i].x && D[i].x <= rx &&
				ly <= D[i].y && D[i].y <= ry;
		if(f)	return 1;
		f = intersection(D[i], D[j], a, b) ||
			intersection(D[i], D[j], b, c) ||
			intersection(D[i], D[j], c, d) ||
			intersection(D[i], D[j], d, a);
		if(f)	return 1;
	}
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
void dfs(int lx, int ly, int rx, int ry) {
	if(lx >= rx || ly >= ry)
		return ;
	int f;
	f = checkPossible(lx, ly, rx, ry);
	if(!f)	return;
//	printf("dfs %d %d %d %d\n", lx, ly, rx, ry);
	f = rectInPolygon(lx, ly, rx, ry);
	if(f) {
//		printf("square %d %d %d %d\n", lx, ly, rx, ry);
		save(lx, ly, rx, ry);
		return;
	}
	int mx, my;
	mx = (lx + rx)/2, my = (ly + ry)/2;
//	printf("%d %d\n", mx, my);
	if(lx + 1 != rx && ly + 1 != ry) {
//		puts("KIND A");
		dfs(lx, ly, mx, my);
		dfs(lx, my, mx, ry);
		dfs(mx, ly, rx, my);
		dfs(mx, my, rx, ry);
	} else if(lx + 1 != rx) {
//		puts("KIND B");
		dfs(lx, ly, mx, ry);
		dfs(mx, ly, rx, ry);
	} else if(ly + 1 != ry) {
//		puts("KIND C");
		dfs(lx, ly, rx, my);
		dfs(lx, my, rx, ry);
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
//		printf("%d %d %d %d\n", lx, ly, rx, ry);
		dfs(lx, ly, rx, ry);
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
