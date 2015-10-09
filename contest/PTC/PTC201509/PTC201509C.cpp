#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int MAXN = 1024;
struct Job {
	int st, ed, v;
	Job(int a = 0, int b = 0, int c = 0):
		st(a), ed(b), v(c) {}
	bool operator<(const Job &x) const {
		return st < x.st;
	}
};
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		vector<Job> A;
		for (int i = 0; i < n; i++) {
			int st, ed, v;
			scanf("%d %d %d", &st, &ed, &v);
			A.push_back(Job(st, ed, v));
		}
		sort(A.begin(), A.end());
		set< pair<int, int> > S;
		int prev = 0, ret = 0;
		for (int i = 0; i < A.size(); i++) {
			while (!S.empty() && S.begin()->first <= A[i].st)
				prev = max(prev, S.begin()->second), S.erase(S.begin());
			ret = max(ret, prev + A[i].v);
			S.insert(make_pair(A[i].ed, prev+A[i].v));
		}
		printf("%d\n", ret);
	}
	return 0;
}
