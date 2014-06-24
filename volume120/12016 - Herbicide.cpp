#include <stdio.h>
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
int dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
int cross(Pt o, Pt a, Pt b) {
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
           q.x < (double)(p[j].x-p[i].x)*(q.y-p[i].y)/(double)(p[j].y-p[i].y) + p[i].x)
           cnt++;
    }
    return cnt&1;
}
Pt D[2048], C[2048], p;
int main() {
	int testcase, cases = 0;
	int N, M, K, x;
	scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%d", &N);
    	for(int i = 0; i < N; i++)
    		scanf("%d %d", &D[i].x, &D[i].y);
    	scanf("%d", &M);
    	printf("Case #%d:\n", ++cases);
    	while(M--) {
    		scanf("%d", &K);
    		int lx, ly, rx, ry;
#define INF 1048576
    		lx = ly = INF;
    		rx = ry = -INF;
    		int used[1005] = {};
    		for(int i = 0; i < K; i++) {
    			scanf("%d", &x);
    			x--;
    			C[i] = D[x];
    			lx = min(lx, C[i].x);
    			ly = min(ly, C[i].y);
    			rx = max(rx, C[i].x);
    			ry = max(ry, C[i].y);
    			used[x] = 1;
    		}
    		int ret = K;
    		for(int i = 0; i < N; i++) {
    			if(used[i])
    				continue;
    			if(D[i].x < lx || D[i].x > rx)
    				continue;
    			if(D[i].y < ly || D[i].y > ry)
    				continue;
    			ret += inPolygon(C, K, D[i]);
    		}
    		printf("%d\n", ret);
        }
    }
    return 0;
}
