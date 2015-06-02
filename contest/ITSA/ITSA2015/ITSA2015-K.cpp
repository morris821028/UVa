#include <stdio.h> 
#include <string.h>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072;
class SegmentTree {
public:
	struct Node {
		int cover;				// #cover
		int L, R;			// value in real line, cover [L, R]
		int clen;			// cover length
		void init(int a = 0, int b = 0, int c = 0, int d = 0) {
			cover = a, L = b, R = c, clen = d;
		}
	} nodes[MAXN];
	int Y[MAXN];
	void pushDown(int k, int l, int r) {

	}
	void pushUp(int k, int l, int r) {
		if (nodes[k].cover > 0) {
			nodes[k].clen = nodes[k].R - nodes[k].L;
		} else {
			if (l == r)
				nodes[k].clen = 0;
			else
				nodes[k].clen = nodes[k<<1].clen + nodes[k<<1|1].clen;
		}
	}
	void build(int k, int l, int r) { 
		nodes[k].init(0, Y[l], Y[r+1], 0);
		if (l == r)
			return ;
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
		pushUp(k, l, r);
	} 
	// operator, add
	void addUpdate(int k, int l, int r, int val) {
		nodes[k].cover += val;
		if (nodes[k].cover > 0) {
			nodes[k].clen = nodes[k].R - nodes[k].L;
		} else {
			if (l == r)
				nodes[k].clen = 0;
			else
				nodes[k].clen = nodes[k<<1].clen + nodes[k<<1|1].clen;
		}
	}
	void add(int k, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			addUpdate(k, l, r, val);
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			add(k<<1, l, mid, x, y, val);
		if (y > mid)
			add(k<<1|1, mid+1, r, x, y, val);
		pushUp(k, l, r);
	}
	// query 
	long long r_sum;
	void qinit() {
		r_sum = 0;
	}
	void query(int k, int l, int r, int x, int y) {
		if (x <= l && r <= y) {
			r_sum += nodes[k].clen;
			return ;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			query(k<<1, l, mid, x, y);
		if (y > mid)
			query(k<<1|1, mid+1, r, x, y);
		pushUp(k, l, r);
	}
} tree;
struct Event {
	long long x, yl, yr;
	int val;
	Event(long long a = 0, long long b = 0, long long c = 0, int d = 0):
	x(a), yl(b), yr(c), val(d) {}
	bool operator<(const Event &a) const {
		return x < a.x;
	}
};

const int MAXD = 32767;
int Lx[MAXD], Ly[MAXD], Rx[MAXD], Ry[MAXD];
long long X[MAXD], Y[MAXD];
double K[MAXD];

long long areaCoverAll(int N, int Lx[], int Ly[], int Rx[], int Ry[]) {
	vector<Event> events;
	vector<int> VY;
	map<int, int> RY;
	for (int i = 0; i < N; i++) {
		int x1, x2, y1, y2;
		x1 = Lx[i], x2 = Rx[i];
		y1 = Ly[i], y2 = Ry[i];
		if (x1 < x2 && y1 < y2) {
			events.push_back(Event(x1, y1, y2,  1));
			events.push_back(Event(x2, y1, y2, -1));
			VY.push_back(y1), VY.push_back(y2);
		}
	}
	
	sort(VY.begin(), VY.end());	
	VY.resize(unique(VY.begin(), VY.end()) - VY.begin());
	
	for (int i = 0; i < VY.size(); i++) {
		tree.Y[i] = VY[i];
		RY[VY[i]] = i;
	}
				
	if (VY.size() < 2)	
		return 0;
	tree.build(1, 0, VY.size()-2);
	
	sort(events.begin(), events.end());
	long long area = 0, prevX = 0;
	for (int i = 0, j; i < events.size(); ) {		
		if (i > 0) {
			tree.qinit();
			tree.query(1, 0, VY.size()-2, 0, VY.size()-2);
			area += (events[i].x - prevX) * tree.r_sum;
		}
		j = i;
		while (j < events.size() && events[j].x <= events[i].x) {
			tree.add(1, 0, VY.size()-2, RY[events[j].yl], RY[events[j].yr] - 1, events[j].val);
			j++;
		}
		prevX = events[i].x;
		i = j;
	}
	return area;
}
int main() {
	int testcase, cases = 0;
	long long W, H;
	int N;
	double sqrtK[128];
	for (int i = 0; i < 128; i++)
		sqrtK[i] = sqrt(i);
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld", &W, &H);
		scanf("%d", &N);
				
		for (int i = 0; i < N; i++) {
			int x, y, k;
			scanf("%d %d %d", &k, &x, &y);
			if (k < 1 || k > 100)
				return 0;
			X[i] = x, Y[i] = y, K[i] = sqrtK[k];
		}
				
		if (N < 1 || N > 20000 || W <= 0 || H <= 0 || W > 1e+7 || H > 1e+7)
			return 0;
			
		double l = 0.4, r = max(W, H), mid;
		int ret = -1;
		while (fabs(l - r) > 0.1) {
			mid = (l + r)/2;
			
			for (int i = 0; i < N; i++) {
				Lx[i] = min(max(round(X[i] - K[i] * mid), 0.0), (double) W);
				Rx[i] = min(max(round(X[i] + K[i] * mid), 0.0), (double) W);
				Ly[i] = min(max(round(Y[i] - K[i] * mid), 0.0), (double) H);
				Ry[i] = min(max(round(Y[i] + K[i] * mid), 0.0), (double) H);
			}
			
			long long area = areaCoverAll(N, Lx, Ly, Rx, Ry);
			if (area == W*H)
				r = mid, ret = ceil(mid*2);
			else
				l = mid;
		}
		
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
9999
9 9
1
1 0 0

1 1
1
4 0 0

2

12 8
3
4 2 2
16 8 4
4 2 6

12 8
3
4 2 2
10 8 4
4 2 6 
*/
