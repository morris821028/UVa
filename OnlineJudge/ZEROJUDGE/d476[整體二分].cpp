#include <bits/stdc++.h> 
using namespace std;

const int MAXQ = 65536;
const int MAXN = 65536;
const int INF = 0x3f3f3f3f;
class Offline {
public:
	struct Event {
		int x, y, k, qtype, qid;
		int calc; //
		Event(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0):
			x(a), y(b), k(c), qtype(d), qid(e), calc(f) {}
	};
	vector<Event> event;
	int N, ret[MAXQ];
	void init(int N) {
		this->N = N;
		event.clear();
	}
	void addEvent(int qtype, int qid, int x, int y, int k) {
		event.push_back(Event(x, y, k, qtype, qid));
	}
	void run() {
		DC(0, event.size()-1, 0, INF);
	}
private:
	// buffer
	int buf[MAXQ];
	Event ebuf1[MAXQ], ebuf2[MAXQ];
	// binary indexed tree
	int bit[MAXN];
	void add(int x, int val) {
		while (x <= N) {
			bit[x] += val;
			x += (x)&(-x);
		}
	}
	int query(int x) {
		int ret = 0;
		while (x) {
			ret += bit[x];
			x -= (x)&(-x);
		}
		return ret;
	}
	void DC(int q_l, int q_r, int val_l, int val_r) {
		if (q_l > q_r)	return ;
		if (val_l == val_r) {	// find
			for (int i = q_l; i <= q_r; i++)
				if (event[i].qtype == 2)
					ret[event[i].qid] = val_l;
			return ;
		}
		int mid = (val_l + val_r)/2;
		for (int i = q_l; i <= q_r; i++) {
			if (event[i].qtype == 0 && event[i].y <= mid)
				add(event[i].x, 1);
			else if (event[i].qtype == 1 && event[i].y <= mid)
				add(event[i].x, -1);
			else if (event[i].qtype == 2)
				buf[i] = query(event[i].y) - query(event[i].x-1);
		}
		for (int i = q_l; i <= q_r; i++) { // resume
			if (event[i].qtype == 0 && event[i].y <= mid)
				add(event[i].x, -1);
			else if (event[i].qtype == 1 && event[i].y <= mid)
				add(event[i].x, 1);
		}
		int lidx = 0, ridx = 0;
		for (int i = q_l; i <= q_r; i++) {
			if (event[i].qtype == 0 || event[i].qtype == 1) {
				if (event[i].y <= mid)
					ebuf1[lidx++] = event[i];
				else
					ebuf2[ridx++] = event[i];
			} else {
				if (event[i].calc + buf[i] > event[i].k - 1)
					ebuf1[lidx++] = event[i];
				else {
					event[i].calc += buf[i];
					ebuf2[ridx++] = event[i];
				}
			}
		}
		for (int i = 0; i < lidx; i++)
			event[q_l+i] = ebuf1[i];
		for (int i = 0; i < ridx; i++)
			event[q_l+lidx+i] = ebuf2[i];
		DC(q_l, q_l+lidx-1, val_l, mid);
		DC(q_l+lidx, q_r, mid+1, val_r);
	}
} off;

int main() {
	int n, m, x, y, k, v;
	int A[65536];
	char cmd[10];
	while (scanf("%d %d", &n, &m) == 2) {
		off.init(n);
		// qtype 0:add, 1:remove, 2: query
		for (int i = 1; i <= n; i++) {
			scanf("%d", &A[i]);
			off.addEvent(0, 0, i, A[i], 0);
		}
		
		int qid = 0;
		for (int i = 0; i < m; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'Q') {
				scanf("%d %d %d", &x, &y, &k);
				off.addEvent(2, qid++, x, y, k);
			} else {
				scanf("%d %d", &x, &v);
				off.addEvent(1, 0, x, A[x], 0);
				off.addEvent(0, 0, x, v, 0);
				A[x] = v;
			}
		}
		
		off.run();		
		for (int i = 0; i < qid; i++)
			printf("%d\n", off.ret[i]);
	}
	return 0;
}
