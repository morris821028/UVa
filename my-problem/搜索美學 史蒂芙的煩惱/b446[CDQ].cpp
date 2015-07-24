#include <bits/stdc++.h>
using namespace std;

const int MAXQ = 131072;
const int MAXN = 40000;
const int INF = INT_MAX;
class Offline {
public:
	struct Point {
		int x, y;
		Point(int a = 0, int b = 0):
			x(a), y(b) {}
		bool operator<(const Point &a) const {
			return x < a.x || (x == a.x && y < a.y);
		}
		void read() {
			scanf("%d %d", &x, &y);
			x++, y++;
		}
	};
	struct Event {
		Point p;
		int qtype, qid;
		Event(int a = 0, int b = 0, Point c = Point()):
			qtype(a), qid(b), p(c) {}
		bool operator<(const Event &e) const {
			if (p.x != e.p.x)	return p.x < e.p.x;
			return qid < e.qid;
		}
	};
	vector<Event> event;
	int ret[MAXQ], N;
	void init(int n) {
		event.clear();
		N = n; 
	}
	void addEvent(int qtype, int qid, Point x) {
		event.push_back(Event(qtype, qid, x));
	}
	void run() {
		for (int i = 0; i < event.size(); i++)
			ret[i] = 0x3f3f3f3f;		
		cases = 0;
		for (int i = 0; i <= N; i++)
			used[i] = 0;		
		sort(event.begin(), event.end());
		CDQ(0, event.size()-1);
	}
private:
	Event ebuf[MAXQ];
	int BIT[MAXN], used[MAXN];
	int cases = 0;
	void modify(int x, int val, int dir) {
		for (; x && x <= N; x += (x&(-x)) * dir) {
			if (used[x] != cases)
				BIT[x] = -0x3f3f3f3f, used[x] = cases;
			BIT[x] = max(BIT[x], val);
		}
	}
	int query(int x, int dir) {
		int ret = -0x3f3f3f3f;
		for (; x && x <= N; x += (x&(-x)) * dir) {
			if (used[x] == cases)
				ret = max(ret, BIT[x]);
		}
		return ret;
	}
	void merge(int l, int mid, int r) {
		cases++;
		for (int i = mid+1, j = l; i <= r; i++) {
			if (event[i].qtype == 0) {
				for (; j <= mid && event[j].p.x <= event[i].p.x; j++) {
					if (event[j].qtype == 1) 
						modify(event[j].p.y, event[j].p.x+event[j].p.y, 1);
				} 
				ret[event[i].qid] = min(ret[event[i].qid], event[i].p.x+event[i].p.y-query(event[i].p.y, -1));
			}
		}
		cases++;
		for (int i = mid+1, j = l; i <= r; i++) {
			if (event[i].qtype == 0) {
				for (; j <= mid && event[j].p.x <= event[i].p.x; j++) {
					if (event[j].qtype == 1)
						modify(event[j].p.y, event[j].p.x-event[j].p.y, -1);
				} 
				ret[event[i].qid] = min(ret[event[i].qid], event[i].p.x-event[i].p.y-query(event[i].p.y, 1));
			}
		}
		cases++;
		for (int i = r, j = mid; i > mid; i--) {
			if (event[i].qtype == 0) {
				for (; j >= l && event[j].p.x >= event[i].p.x; j--) {
					if (event[j].qtype == 1) 
						modify(event[j].p.y, event[j].p.y-event[j].p.x, 1);
				} 
				ret[event[i].qid] = min(ret[event[i].qid], event[i].p.y-event[i].p.x-query(event[i].p.y, -1));
			}
		}
		cases++;
		for (int i = r, j = mid; i > mid; i--) {
			if (event[i].qtype == 0) {
				for (; j >= l && event[j].p.x >= event[i].p.x; j--) {
					if (event[j].qtype == 1) 
						modify(event[j].p.y, -event[j].p.x-event[j].p.y, -1);
				} 
				ret[event[i].qid] = min(ret[event[i].qid], -event[i].p.x-event[i].p.y-query(event[i].p.y, 1));
			}
		}
	}
	void CDQ(int l, int r) {
		if (l == r)
			return ;
		int mid = (l + r)/2, lidx, ridx;
		lidx = l, ridx = mid+1;
		for (int i = l; i <= r; i++) {
			if (event[i].qid <= mid)
				ebuf[lidx++] = event[i];
			else
				ebuf[ridx++] = event[i];
		}
		for (int i = l; i <= r; i++)
			event[i] = ebuf[i];
			
		CDQ(l, mid);
		merge(l, mid, r);
		CDQ(mid+1, r);
		
		lidx = l, ridx = mid+1;
		for (int i = l; i <= r; i++) {
			if ((lidx <= mid && event[lidx] < event[ridx]) || ridx > r)
				ebuf[i]	= event[lidx++];
			else
				ebuf[i] = event[ridx++];
		}
		for (int i = l; i <= r; i++)
			event[i] = ebuf[i];
	}
} A, B;

int main() {
	int N;
	Offline::Point pt;
	while (scanf("%d", &N) == 1) {
		A.init(65536), B.init(65536);
		int max_y = 0;
		for (int i = 0; i < N; i++) {
			pt.read(), max_y = max(max_y, pt.y);
			B.addEvent(0, 2*i, pt);
			A.addEvent(1, 2*i, pt);
			pt.read(), max_y = max(max_y, pt.y);
			A.addEvent(0, 2*i+1, pt);
			B.addEvent(1, 2*i+1, pt);
		}
		A.N = B.N = max_y;	// y in [1, max_y]
		A.run(), B.run();
		for (int i = 0; i < N; i++) {
			if (i)	printf("%d\n", B.ret[2*i]);
			printf("%d\n", A.ret[2*i+1]);
		}
	}
	return 0;
}
