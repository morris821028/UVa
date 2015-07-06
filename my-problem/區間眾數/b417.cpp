#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
const int MAXV = 100005;
const int MAXQ = 1000005;
class Offline {
public:
	struct Event {
		static int PILE, belong[MAXV];
		int l, r, qid;
		Event(int a = 0, int b = 0, int e = 0):
			l(a), r(b), qid(e) {}
		bool operator<(const Event &x) const {
			if (belong[l] != belong[x.l])
				return l < x.l;
			return r < x.r; 
		}
	} event[MAXQ];
	int A[MAXN], N, qsize;
	int ret[MAXQ][2];
	void init(int N) {
		this->N = N, qsize = 0;
		memset(val_count, 0, sizeof(val_count));
		memset(mode_freq, 0, sizeof(mode_freq));
		mode_idx = 0;
		Event::PILE = sqrt(N);
		for (int i = N; i >= 1; i--)
			Event::belong[i] = i / Event::PILE;
	}
	void q_add(int l, int r) {
		event[qsize] = Event(l, r, qsize);
		qsize++;
	}
	void run() {
		sort(event, event+qsize);
		
		int l = 1, r = 0;
		for (int i = 0; i < qsize; i++) {
			while (r < event[i].r)	r++, update(A[r], 1);
			while (r > event[i].r)	update(A[r], -1), r--;
			while (l > event[i].l)	l--, update(A[l], 1);
			while (l < event[i].l)	update(A[l], -1), l++;
			ret[event[i].qid][0] = mode_idx;
			ret[event[i].qid][1] = mode_freq[mode_idx];
		}
	}
private:
	// unrolled
	int val_count[MAXV], mode_freq[MAXN], mode_idx;
	inline void update(int x, int val) {
		if (val == 1) {
			mode_freq[val_count[x]]--;
			val_count[x]++;
			mode_freq[val_count[x]]++;
			if (mode_freq[mode_idx+1] != 0)
				mode_idx++;
		} else if (val == -1) {
			mode_freq[val_count[x]]--;
			val_count[x]--;
			mode_freq[val_count[x]]++;
			if (mode_freq[mode_idx] == 0)
				mode_idx--;
		}
	}
} off;
int Offline::Event::PILE = 16, Offline::Event::belong[MAXV];

namespace mLocalStream {
	class M {
	public:
		static const int N = 1048576;
	    char buf[N], *p, *end;
		M() {
			p = buf, end = buf + N - 1;
		}
		void printInt(int x) {
			static char stk[16];
			int idx = 0;
			stk[idx++] = '\n';
			if (!x)	
				stk[idx++] = '0';
			while (x)
				stk[idx++] = x%10 + '0', x /= 10;
			while (idx) {
				if (p == end) {
					*p = '\0';
					printf("%s", buf), p = buf;
				}
				*p = stk[--idx], p++;
			}
		}	
		static inline int readchar() {
		    static char buf[N];
		    static char *p = buf, *end = buf;
		    if(p == end) {
		        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
		        p = buf;
		    }
		    return *p++;
		}
		static inline int ReadInt(int *x) {
		    static char c, neg;
		    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
		    neg = (c == '-') ? -1 : 1;
		    *x = (neg == 1) ? c-'0' : 0;
		    while((c = readchar()) >= '0')
		        *x = (*x << 3) + (*x << 1) + c-'0';
		    *x *= neg;
		    return 1;
		}
		~M() {
			*p = '\0';
			printf("%s", buf);
		}		
	} bprint;
}
int main() {
	int n, m, l, r, a, b;
	while (mLocalStream::M::ReadInt(&n)) {
		mLocalStream::M::ReadInt(&m);
		off.init(n);
		for (int i = 1; i <= n; i++)
			mLocalStream::M::ReadInt(&off.A[i]);
		for (int i = 0; i < m; i++) {
			mLocalStream::M::ReadInt(&l);
			mLocalStream::M::ReadInt(&r);
			off.q_add(l, r);
		}
		
		off.run();
		for (int i = 0; i < m; i++)
			printf("%d %d\n", off.ret[i][0], off.ret[i][1]);
	}
	return 0;
}

