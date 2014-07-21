#include <stdio.h>
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define eps 1e-6
struct Pt {
    int x, y, label;
    Pt(int a = 0, int b = 0, int c = 0):
    	x(a), y(b), label(c) {}
    bool operator<(const Pt &a) const {
        if(x != a.x)	return x < a.x;
        return y < a.y;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) < 0 &&
       cross(at, as, bs) * cross(at, as, bt) < 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) < 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) < 0)
        return 1;
    return 0;
}

int cmpX(Pt a, Pt b) {
	if(a.x != b.x)	return a.x < b.x;
	return a.y < b.y;
}
int cmpY(Pt a, Pt b) {
	if(a.y != b.y)	return a.y < b.y;
	return a.x < b.x;
}

vector<int> g[100005];
int visited[100005], dfsCnt;
void dfs(int u, int p) {
	visited[u] = 1, dfsCnt++;
	for(int i = g[u].size()-1; i >= 0; i--) {
		int v = g[u][i];
		if(v == p || visited[v])	continue;
		dfs(v, u);
	}
}

// http://www.csie.ntnu.edu.tw/~u91029/PointLinePlane2.html
struct seg {
	Pt s, e;
	seg(Pt a, Pt b):s(a), e(b) {}
};
struct Endpoint {
	int x, s, i;
	Endpoint(int a = 0, int b = 0, int c = 0):
		x(a), s(b), i(c) {}
	bool operator<(const Endpoint &a) const {
		return x < a.x || (x == a.x && s > a.s);
	}
};
struct CMP {
	static int x;
	
	double interpolate(const Pt& p1, const Pt& p2, int& x) {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
    
	bool operator()(const seg &i, const seg &j) {
		return interpolate(i.s, i.e, x) < interpolate(j.s, j.e, x);
	}
};
int CMP::x = 0;

set<seg, CMP>::iterator prevNode(set<seg, CMP>::iterator it, set<seg, CMP>& S) {
	return it == S.begin() ? it : --it;
}
set<seg, CMP>::iterator nextNode(set<seg, CMP>::iterator it, set<seg, CMP>& S) {
	return it == S.end() ? it : ++it;
}
bool segment_intersect(vector<seg> segs) {
	for(int i = 0; i < segs.size(); i++)
		if(segs[i].e < segs[i].s)
			swap(segs[i].s, segs[i].e);
			
	vector<Endpoint> e;
	set<seg, CMP> S;
	for(int i = 0; i < segs.size(); i++) {
		e.push_back(Endpoint(segs[i].s.x, 1, i));
		e.push_back(Endpoint(segs[i].e.x, -1, i));
	}
	sort(e.begin(), e.end());
	
	for(int i = 0; i < e.size(); i++) {
		CMP::x = e[i].x;
		if(e[i].s == 1) {
			set<seg, CMP>::iterator it, jt;
			it = S.lower_bound(segs[e[i].i]);
			jt = prevNode(it, S);
			if(it != S.end() && intersection(segs[e[i].i].s, segs[e[i].i].e, it->s, it->e))
				return 1;
			if(jt != S.end() && intersection(segs[e[i].i].s, segs[e[i].i].e, jt->s, jt->e))
				return 1;
			S.insert(segs[e[i].i]);
		} else {
			set<seg, CMP>::iterator it, jt, kt;
			it = S.lower_bound(segs[e[i].i]);
			jt = prevNode(it, S);
			kt = nextNode(it, S);
			if(jt != S.end() && kt != S.end() && intersection(kt->s, kt->e, jt->s, jt->e))
				return 1;
			if(it != S.end())
				S.erase(it);
		}
	} 
	return 0;
}
Pt D[100005], P[100005];
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		for(int i = 0; i < n; i++) {
			scanf("%d %d", &P[i].x, &P[i].y);
			D[i] = P[i], D[i].label = i;
		}
		
		int eflag = 0;
		for(int i = 0; i < n; i++)
			g[i].clear(), visited[i] = 0;
		sort(D, D+n, cmpX);		
		for(int i = 0; i < n && !eflag; i += 2) {
			if(i+1 < n && D[i].x == D[i+1].x) {
				g[D[i].label].push_back(D[i+1].label);
				g[D[i+1].label].push_back(D[i].label);
			} else
				eflag = 1;
		}
		sort(D, D+n, cmpY);
		for(int i = 0; i < n && !eflag; i += 2) {
			if(i+1 < n && D[i].y == D[i+1].y) {
				g[D[i].label].push_back(D[i+1].label);
				g[D[i+1].label].push_back(D[i].label);
			} else
				eflag = 1;
		}
		
		if(!eflag) { // only one component
			dfsCnt = 0;
			dfs(0, -1);
			if(dfsCnt != n)
				eflag = 1;
		}
		
		if(!eflag) {
			vector<seg> segs;
			for(int i = 0; i < n; i++) {
				for(int j = g[i].size()-1; j >= 0; j--) {
					segs.push_back(seg(P[i], P[g[i][j]]));
				}
			}
			eflag = segment_intersect(segs);
		}
		
		if(eflag)
			puts("-1");
		else {
			int para = 0;
			for(int i = 0; i < n; i++) {
				for(int j = g[i].size()-1; j >= 0; j--) {
					para += abs(P[i].x - P[g[i][j]].x) + abs(P[i].y - P[g[i][j]].y);
				}
			}
			printf("%d\n", para/2);
		}
	}
	return 0;
}
/*
5
6
68 81
65 33
32 94
52 80
63 44
11 41
*/
