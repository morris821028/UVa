#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
class Unrolled {
public:
	struct Interval {
		long long l, r;
		int pid;
		Interval(long long a = 0, long long b = 0, int c = 0):
			l(a), r(b), pid(c) {}
		bool operator<(const Interval &x) const {
			return l < x.l || (l == x.l && r > x.r);
		}
		bool include(int x) const {
			return l <= x && x <= r;
		} 
	};
	long long PILE, mask;
	int shift;
	vector< set<Interval> > nodes;
	vector<int> dirty;
	void alloc(long long size) {
		nodes.clear(), dirty.clear();
		for (PILE = 1, shift = 0; PILE * PILE < size; PILE <<= 1, shift++);
		mask = PILE - 1;
		for (long long l = 0, r; l < size; l = r+1) {
			r = min(l+PILE-1, size-1);
			nodes.push_back(set<Interval>());
			dirty.push_back(INF);
		}
	}
	int operator[](const long long x) const {
		const set<Interval> &s = nodes[x>>shift];
		auto it = s.upper_bound(Interval(x, x));
		it = it == s.begin() ? it : --it;
		return it == s.end() || !(it->include(x)) ? INF : it->pid;
	}
	int empty(long long l, long long r) {
		int bl = l>>shift, br = r>>shift;
		int ret = INF;
		if (bl == br) {
			set<Interval> &s = nodes[bl];
			auto st = s.upper_bound(Interval(l, l));
			st = st == s.begin() ? st : --st;
			for (auto it = st; it != s.end(); it++) {
				if (max(l, it->l) <= min(r, it->r))
					ret = min(ret, it->pid);
				if (it->l > r)
					break;
			}
			return ret;
		}
		for (int i = bl+1; i < br; i++)
			ret = min(ret, dirty[i]);
		for (auto it = nodes[bl].rbegin(); it != nodes[bl].rend() && ret > dirty[bl]; it++) {
			if (max(l, it->l) <= min(r, it->r)) {
				ret = min(ret, it->pid);
			} else {
				break;
			}
		}
		for (auto it = nodes[br].begin(); it != nodes[br].end() && ret > dirty[br]; it++) {
			if (max(l, it->l) <= min(r, it->r)) {
				ret = min(ret, it->pid);
			} else {
				break;
			}
		}
		return ret;
	}
	void fill(long long l, long long r, int val) {
		int bl = l>>shift, br = r>>shift;
		for (int i = bl; i <= br; i++)
			dirty[i] = min(dirty[i], val);
		if (bl == br) {
			nodes[bl].insert(Interval(l, r, val));
			return ;
		}
		for (int i = bl+1; i < br; i++)
			nodes[i].insert(Interval(i*PILE, (i+1)*PILE-1, val));
		nodes[bl].insert(Interval(l, (bl+1) * PILE-1, val));
		nodes[br].insert(Interval(br*PILE, r, val));
	}
} mem;
int main() {
	int N;
	char cmd[8];
	while (scanf("%d", &N) == 1) {
		mem.alloc(1LL<<31);
		for (int i = 0; i < N; i++) {
			scanf("%s", &cmd);
			int a, b, c, t;
			if (cmd[0] == 'l') {
				scanf("%d", &a);
				t = mem[a];
				if (t == INF)
					printf("fail to load from %d\n", a);
				else
					printf("load from region %d\n", t);
			} else if (cmd[0] == 'm') {
				scanf("%d %d %d", &a, &b, &c);
				t = mem.empty(b, c);
				if (t != INF)
					printf("fail to create region %d, overlap with region %d\n", a, t);
				else
					printf("region %d created\n", a), mem.fill(b, c, a);
			} else {
				scanf("%d", &a);
				t = mem[a];
				if (t == INF)
					printf("fail to store to %d\n", a);
				else
					printf("store to region %d\n", t);
			}
		}
	}
	return 0;
}
/*
7
load 29
map 1 25 39
map 2 23 24
map 3 22 25
map 4 25 40
store 33   
store 22   
*/
