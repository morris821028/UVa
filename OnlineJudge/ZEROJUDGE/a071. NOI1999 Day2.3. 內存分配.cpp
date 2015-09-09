#include <bits/stdc++.h>
using namespace std;
class Memory {
public:
	struct Node {
		int l, r;
		Node(int a = 0, int b = 0) {
			l = a, r = b;
		}
	};
	struct Event {
		int t, l, r;
		Event(int a = 0, int b = 0, int c = 0) {
			t = a, l = b, r = c;
		}
		bool operator<(const Event &x) const {
			return t < x.t || (t == x.t && l < x.l);
		}
	};
	int N, nowtime, qtime;
	set<Event> event;
	queue< pair<int, int> > Q;
	list<Node> mem;
	void init(int n) {
		N = n, nowtime = -1, qtime = 0;
		event.clear();
		mem.insert(mem.begin(), Node(0, n-1));
	}
	void merge() {
		list<Node>::iterator it, jt;
		for (it = mem.begin(), jt = it, jt++; it != mem.end() && jt != mem.end(); ) {
			if (it->r+1 == jt->l) {
				it->r = jt->r;
				mem.erase(jt++);
			} else {
				it++, jt++;
			}
		}
	}
	void recycle(Event e) {
		list<Node>::iterator it, jt;
		for (it = mem.begin(); it != mem.end(); it++) {
			if (it->l > e.r) {
				mem.insert(it, Node(e.l, e.r));
				merge();
				return ;
			}
		}
		mem.insert(mem.end(), Node(e.l, e.r));
		merge();
	}
	int find_empty(int M, int P) {
		list<Node>::iterator it;
		for (it = mem.begin(); it != mem.end(); it++) {
			if (it->r - it->l + 1 >= M) {
				event.insert(Event(nowtime+P, it->l, it->l+M-1));
				it->l += M;
				if (it->l > it->r)	mem.erase(it);
				return 1;
			} 
		}
		return 0;
	}
	void alloc(int T, int M, int P) {
		while (!event.empty() && event.begin()->t <= T) {
			nowtime = event.begin()->t;
			while (!event.empty() && event.begin()->t == nowtime) {
				recycle(*event.begin());
				event.erase(event.begin());
			}
			while (!Q.empty()) {
				pair<int, int> t = Q.front();
				if (find_empty(t.first, t.second)) {
					Q.pop();
				} else {
					break;
				}
			}
		}
		nowtime = T;
		if (!find_empty(M, P)) {
			Q.push({M, P}), qtime++;
		} else {
		}
	}
	void run_rest() {
		while (!event.empty()) {
			nowtime = event.begin()->t;
			while (!event.empty() && event.begin()->t == nowtime) {
				recycle(*event.begin());
				event.erase(event.begin());
			}
			while (!Q.empty()) {
				pair<int, int> t = Q.front();
				if (find_empty(t.first, t.second)) {
					Q.pop();
				} else {
					break;
				}
			}
		}
	}
	void dump() {
		printf("time [%3d]\n", nowtime);
		for (auto &x : mem)
			printf("[%d %d] ->", x.l, x.r);
		puts("");
	}
} mem;
int main() {
	int N, T, M, P;
	scanf("%d", &N);
	mem.init(N);
	while (scanf("%d %d %d", &T, &M, &P) == 3) {
		if (T == 0 && M == 0 && P == 0)
			break;
		mem.alloc(T, M, P);
	}
	mem.run_rest();
	printf("%d\n", mem.nowtime);
	printf("%d\n", mem.qtime);
	return 0;
}

