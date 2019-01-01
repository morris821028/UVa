#include <bits/stdc++.h> 
using namespace std;

struct Event {
	int t, id;
	Event() {}
	Event(int t, int id):
		t(t), id(id) {}
	bool operator<(const Event &x) const {
		if (t != x.t)
			return t > x.t;
		return id > x.id;
	}
};
const int MAXN = 1005;
queue<int> Q[MAXN];
priority_queue<Event> EQ[MAXN];

int simulate(int n, int m) {
	int ret = 0;
	do {
		int update = 0, mntime = INT_MAX;
		for (int i = 0; i < m; i++) {
			if (EQ[i].empty())
				continue;
			update = 1;
			Event work = EQ[i].top();
			if (work.t > ret) {
				mntime = min(mntime, work.t);
				continue;
			}
			EQ[i].pop(), Q[work.id].pop();
			if (!Q[work.id].empty()) {
				work.t = ret+1;
				EQ[Q[work.id].front()].push(work);
			}
		}
		if (!update)
			break;
		ret++;
		if (ret < mntime)
			mntime = ret;
	} while (true);
	return ret;
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			int t, k, g;
			scanf("%d %d", &t, &k);
			for (int j = 0; j < k; j++) {
				scanf("%d", &g), g--;
				Q[i].push(g);
			}
			EQ[Q[i].front()].push(Event(t, i));
		}
		int ret = simulate(n, m);
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
5 3
1 3 3 2 1
0 7 2 3 1 1 1 1 2
2 1 1
1 2 3 3
4 3 1 1 1
5 10
3 1 6
2 3 3 2 8
2 1 4
2 4 7 9 9 6
0 2 8 7
*/
