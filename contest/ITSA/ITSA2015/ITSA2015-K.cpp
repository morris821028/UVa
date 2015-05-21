#include <stdio.h> 
#include <string.h>
#include <map>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;
const int MAXN = 262144;
class SegmentTree {
public:
	struct Node {
		int cover;				// #cover
		double L, R;			// value in real line, cover [L, R]
		double clen;			// cover length
		pair<int, int> 	label; 	// delivery label
		void init(int a = 0, double b = 0, double c = 0, double d = 0) {
			cover = a, L = b, R = c, clen = d;
			label = make_pair(0, 0);
		}
	} nodes[MAXN];
	double Y[MAXN];
	void pushDown(int k, int l, int r) {
		int mid = (l + r)/2;
		if (nodes[k].label.first) {
			addUpdate(k<<1, l, mid, nodes[k].label.second);
			addUpdate(k<<1|1, mid+1, r, nodes[k].label.second);
			nodes[k].label = make_pair(0, 0);
		}
	}
	void pushUp(int k) {
		nodes[k].clen = nodes[k<<1].clen + nodes[k<<1|1].clen;
	}
	void build(int k, int l, int r) { 
		nodes[k].init(0, Y[l], Y[r+1], 0);
		if (l == r)
			return ;
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
		pushUp(k);
	} 
	// operator, add
	void addUpdate(int k, int l, int r, int val) {
		nodes[k].label.first = 1;
		nodes[k].label.second += val;
		nodes[k].cover += val;
		if (nodes[k].cover == 0)
			nodes[k].clen = 0;
		else
			nodes[k].clen = nodes[k].R - nodes[k].L;
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
		pushUp(k);
	}
	// query 
	double r_sum;
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
	}
} tree;
struct Event {
	double x, yl, yr;
	int val;
	Event(double a = 0, double b = 0, double c = 0, int d = 0):
	x(a), yl(b), yr(c), val(d) {}
	bool operator<(const Event &a) const {
		return x < a.x;
	}
};
double X[32767], Y[32767], K[32767];
double W, H;
int N;
int checkCoverAll(double c) {
	vector<Event> events;
	vector<double> VY;
	map<double, int> RY;
	for (int i = 0; i < N; i++) {
		double x1, x2, y1, y2;
		x1 = min(max(X[i] - round(K[i] * c), 0.0), W);
		x2 = min(max(X[i] + round(K[i] * c), 0.0), W);
		y1 = min(max(Y[i] - round(K[i] * c), 0.0), H);
		y2 = min(max(Y[i] + round(K[i] * c), 0.0), H);
		events.push_back(Event(x1, y1, y2,  1));
		events.push_back(Event(x2, y1, y2, -1));
		VY.push_back(y1), VY.push_back(y2);
	}
	
	sort(events.begin(), events.end());
	sort(VY.begin(), VY.end());	
	VY.resize(unique(VY.begin(), VY.end()) - VY.begin());
	
	for (int i = 0; i < VY.size(); i++) {
		tree.Y[i] = VY[i];
		RY[VY[i]] = i;
	}
	
	tree.build(1, 0, VY.size()-1);
	
	double area = 0, prevX = 0;
	for (int i = 0, j; i < events.size(); ) {		
		if (i > 0) {
			tree.qinit();
			tree.query(1, 0, VY.size()-1, 0, VY.size()-1);
			area += (events[i].x - prevX) * tree.r_sum;
//			printf("add area %lf, gapX %lf lenY %lf\n", (events[i].x - prevX) * tree.r_sum,
//						events[i].x - prevX, tree.r_sum);
		}
		j = i;
		while (j < events.size() && events[j].x <= events[i].x) {
//			printf("%lf [%lf, %lf] %2d\n", events[j].x, events[j].yl, events[j].yr, events[j].val);
//			printf("---- modify [%d, %d]\n", RY[events[j].yl], RY[events[j].yr] - 1);
			tree.add(1, 0, VY.size()-1, RY[events[j].yl], RY[events[j].yr] - 1, events[j].val);
			j++;
		}
		prevX = events[i].x;
		i = j;
	}
//	printf("area %lf\n", area);
	return fabs(area - W*H) < 1e-6;
}
int main() {
	int testcase, cases = 0;
	int sqrtK[128];
	for (int i = 1; i < 128; i++)
		sqrtK[i] = sqrt(i);
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf", &W, &H);
		scanf("%d", &N);
		for (int i = 0; i < N; i++) {
			int x, y, k;
			scanf("%d %d %d", &k, &x, &y);
			X[i] = x, Y[i] = y, K[i] = sqrtK[k];
		}
		
		int l = 1, r = max(W, H), mid;
		int ret = 0;
		while (l <= r) {
			mid = (l + r)/2;
			if (checkCoverAll(mid/2.0))
				r = mid - 1, ret = mid;
			else
				l = mid + 1;
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
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
