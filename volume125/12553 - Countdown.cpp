#include <stdio.h> 
#include <stdlib.h>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;
struct operation {
	int a, b, o;
	operation(int x=0, int y=0, int z=0):
		a(x), b(y), o(z) {}
	int calc() {
		if (o == '+')	return a + b;
		if (o == '-')	return a - b;
		if (o == '*')	return a * b;
		if (o == '/')	return a / b;
		return -1;
	}
};
struct state {
	vector<long long> v;
	void normal() {
		sort(v.begin(), v.end());
	} 
	bool operator<(const state &a) const {
		if (v.size() != a.v.size()) 
			return v.size() < a.v.size();
		for (int i = 0; i < v.size(); i++)
			if (v[i] != a.v[i])
				return v[i] < a.v[i];
		return false;
	}
};
int main() {
	int testcase, x, target;
	scanf("%d", &testcase);
	while (testcase--) {
		state init, u, v, backstate;
		operation op;
		for (int i = 0; i < 6; i++) {
			scanf("%d", &x);
			init.v.push_back(x);
		}
		scanf("%d", &target);
		init.normal();
		int diff = 0x3f3f3f3f, ret = 0;
		queue<state> Q;
		map<state, pair<state, operation> > R;
		Q.push(init), R[init] = make_pair(init, operation());
		while (!Q.empty()) {
			u = Q.front(), Q.pop();
			for (int i = 0; i < u.v.size(); i++) {
				if (llabs(u.v[i] - target) < diff)
					diff = llabs(u.v[i] - target), ret = u.v[i], backstate = u;
			}
			if (diff == 0)	break;
			for (int i = 0; i < u.v.size(); i++) {
				for (int j = 0; j < u.v.size(); j++) {
					if (i == j)	continue;
					if (i < j) { // + *
						v = u;
						v.v[i] = u.v[i] + u.v[j];
						v.v.erase(v.v.begin() + j);
						v.normal();
						if (R.find(v) == R.end()) {
							R[v] = make_pair(u, operation(u.v[i], u.v[j], '+'));
							Q.push(v);
						}
						v = u;
						v.v[i] = u.v[i] * u.v[j];
						v.v.erase(v.v.begin() + j);
						v.normal();
						if (R.find(v) == R.end()) {
							R[v] = make_pair(u, operation(u.v[i], u.v[j], '*'));
							Q.push(v);
						}
					}
					if (u.v[i] > u.v[j]) { // -
						v = u;
						v.v[i] = u.v[i] - u.v[j];
						v.v.erase(v.v.begin() + j), 
						v.normal();
						if (R.find(v) == R.end()) {
							R[v] = make_pair(u, operation(u.v[i], u.v[j], '-'));
							Q.push(v);
						}
					}
					if (u.v[j] && u.v[i]%u.v[j] == 0) { // /
						v = u;
						v.v[i] = u.v[i] / u.v[j];
						v.v.erase(v.v.begin() + j);
						v.normal();
						if (R.find(v) == R.end()) {
							R[v] = make_pair(u, operation(u.v[i], u.v[j], '/'));
							Q.push(v);
						}
					}
				}
			}
		}
		
		pair<state, operation> pre;
		vector<operation> D;
		while (backstate.v.size() != 6) {
			pre = R[backstate];
			backstate = pre.first;
			D.push_back(pre.second);
		}
		
		printf("Target: %d\n", target);
		for (int i = D.size() - 1; i >= 0; i--)
			printf("%d %c %d = %d\n", D[i].a, D[i].o, D[i].b, D[i].calc());
		printf("Best approx: %d\n\n", ret);
	}
	return 0;
}
/*
3
1 75 100 5 3 25 25
100 100 100 100 100 75 345
1 3 1 10 100 75 345
*/
