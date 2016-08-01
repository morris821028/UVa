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
struct Seg {
	Pt s, e;
	int id;
	Seg(Pt a = Pt(), Pt b = Pt(), int c = 0):
		s(a), e(b), id(c) {}
	void print() {
		printf("Seg %d %d - %d %d\n", s.x, s.y, e.x, e.y);
	}
};
struct Endpoint {
	int x, s, id, qkind;
	Endpoint(int a = 0, int b = 0, int c = 0, int d = 0):
		x(a), s(b), id(c), qkind(d) {}
	bool operator<(const Endpoint &a) const {
		if (x != a.x)	return x < a.x;
		if (s != a.s)	return s > a.s;
		return qkind < a.qkind;
	}
};
struct CMP {
	static int x;
	
	double interpolate(const Pt& p1, const Pt& p2, int& x) {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
    
	bool operator() (const Seg &i, const Seg &j) {
		return interpolate(i.s, i.e, x) < interpolate(j.s, j.e, x);
	}
};
int CMP::x = 0;
set<Seg, CMP>::iterator prevNode(set<Seg, CMP>::iterator it, set<Seg, CMP>& S) {
	return it == S.begin() ? it : --it;
}
set<Seg, CMP>::iterator nextNode(set<Seg, CMP>::iterator it, set<Seg, CMP>& S) {
	return it == S.end() ? it : ++it;
}

const int MAXN = 131072;
int toward[MAXN], stopX[MAXN], stopY[MAXN];
int touch[MAXN];
void process(vector<Seg> segs, int Qx[], int Q) {
	int N = segs.size();
	for (int i = 0; i < N; i++) {
		toward[i] = stopX[i] = -1;
		if (segs[i].e < segs[i].s)
			swap(segs[i].s, segs[i].e);
		
		if (segs[i].s.y == segs[i].e.y)
			toward[i] = i, stopY[i] = segs[i].s.y;
		else if (segs[i].s.y > segs[i].e.y)
			stopX[i] = segs[i].s.x, stopY[i] = segs[i].s.y;
		else
			stopX[i] = segs[i].e.x, stopY[i] = segs[i].e.y;
	}
	
	vector<Endpoint> e;
	set<Seg, CMP> S;
		
	for (int i = 0; i < Q; i++) {
		e.push_back(Endpoint(Qx[i], 1, i, 2));
		touch[i] = -1;
	}
	for (int i = 0; i < N; i++) {
		int qs = segs[i].s.y > segs[i].e.y;
		int qe = segs[i].s.y < segs[i].e.y;
		e.push_back(Endpoint(segs[i].s.x, 1, i, qs));
		e.push_back(Endpoint(segs[i].e.x, -1, i, qe));
	}
	sort(e.begin(), e.end());
	
	set<Seg, CMP>::iterator it, jt, kt;
	for (int i = 0; i < e.size(); i++) {
		CMP::x = e[i].x;
		if (e[i].qkind == 2) {
			it = S.begin();
			if (it != S.end())	
				touch[e[i].id] = it->id;
			continue;
		}
		if (e[i].qkind == 1) {
			it = S.lower_bound(segs[e[i].id]);
			jt = prevNode(it, S);
			kt = nextNode(it, S);
			if (it != S.end() && it->id != e[i].id)
				toward[e[i].id] = it->id;
			else if (kt != S.end() && kt->id != e[i].id)
				toward[e[i].id] = kt->id;
		}
		// 
		if (e[i].s == 1) {
			S.insert(segs[e[i].id]);
		} else {
			it = S.lower_bound(segs[e[i].id]);
			if(it != S.end())	S.erase(it);
		}
	}
	
	//
	vector< pair<int, int> > TQ;
	for (int i = 0; i < N; i++) {
		TQ.push_back(make_pair(stopY[i], i));
	} 
	sort(TQ.begin(), TQ.end());
	for (int j = N-1; j >= 0; j--) {
		int i = TQ[j].second;
		if (toward[i] != -1) {
			if (toward[toward[i]] != toward[i])
				stopX[i] = stopX[toward[i]];
			stopY[i] = stopY[toward[i]];
			toward[i] = toward[toward[i]];
		}
//		printf("%d : toward %d X %d Y %d\n", i, toward[i], stopX[i], stopY[i]);
	}
	
	for (int i = 0; i < Q; i++) {
//		printf("%d touch %d\n", i, touch[i]);
		if (touch[i] == -1)
			printf("%d\n", Qx[i]);
		else {
			int u = touch[i];
			if (toward[u] == -1)
				printf("%d\n", stopX[u]);
			else if (toward[u] == u)
				printf("%d %d\n", Qx[i], stopY[u]);
			else 
				printf("%d %d\n", stopX[u], stopY[u]);
		}
	}
}
int main() {
	int N, C, Qx[MAXN];
	while (scanf("%d %d", &N, &C) == 2) {
		vector<Seg> segs;
		for (int i = 0; i < N; i++) {
			int x1, x2, y1, y2;
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			segs.push_back(Seg(Pt(x1, y1), Pt(x2, y2), i));
		}
		
		for (int i = 0; i < C; i++)
			scanf("%d", &Qx[i]);
			
		process(segs, Qx, C);
	}
	return 0;
}
/*
4 1
3 1 12 4
5 2 2 3
1 4 4 4
7 5 14 5
4

3 3
5 5 10 4
2 2 6 4
0 3 4 4
0
1 
2

4 4
0 1 3 3
1 5 6 5
5 3 2 4
7 4 10 2
2
5
8
6

4 3
1 3 4 2
10 3 7 4
2 3 8 3
3 5 5 4
4
9
8

*/
