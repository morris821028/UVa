#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 50005;
const int MAXV = 50005;
class Offline {
public:
	struct Event {
		static int PILE;
		int l, r, qid;
		Event(int a = 0, int b = 0, int c = 0):
			l(a), r(b), qid(c) {}
		bool operator<(const Event &x) const {
			if (l / PILE != x.l / PILE)
				return l < x.l;
			return r < x.r; 
		}
	};
	int A[MAXN], N, qsize;
	vector<Event> event;
	vector< pair<long long, long long> > ret;
	void init(int N) {
		this->N = N, qsize = 0;
		event.clear();
		memset(B, 0, sizeof(B));
		for (Event::PILE = 1; Event::PILE * Event::PILE < N; Event::PILE <<= 1);
	}
	void q_add(int l, int r) {
		event.push_back(Event(l, r, qsize));
		qsize++;
	}
	void run() {
		sort(event.begin(), event.end());
		ret.resize(event.size());
		
		int l = 1, r = 0;
		q_stat = 0;
		for (int i = 0; i < event.size(); i++) {
			while (r < event[i].r)	r++, update(A[r], 1);
			while (r > event[i].r)	update(A[r], -1), r--;
			while (l > event[i].l)	l--, update(A[l], 1);
			while (l < event[i].l)	update(A[l], -1), l++;
			long long a, b, len = event[i].r - event[i].l + 1;
			if (len > 1) {
				a = q_stat - len;
				b = len * (len - 1);
			} else {
				a = 0, b = 1;
			}
			ret[event[i].qid] = make_pair(a, b);
		}
	}
private:
	long long B[MAXV], q_stat;
	void update(int x, int val) {
		B[x] += val;
		q_stat += val * 2 * B[x] - 1;
	}
} off;
int Offline::Event::PILE = 16;

long long llgcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	int N, M, l, r;
	while (scanf("%d %d", &N, &M) == 2) {
		off.init(N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &off.A[i]);
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &l, &r);
			off.q_add(l, r);
		}
		off.run();
		for (int i = 0; i < off.ret.size(); i++) {
			long long a = off.ret[i].first;
			long long b = off.ret[i].second;
			long long g = llgcd(a, b);
			a /= g, b /= g;
			printf("%lld/%lld\n", a, b);
		}
	}
	return 0;
}
/*
1 1
5
1 1
*/
