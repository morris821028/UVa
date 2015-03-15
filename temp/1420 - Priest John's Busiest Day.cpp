#include <stdio.h>
#include <vector>
#include <algorithm> 
using namespace std;
struct Job {
	int st, ed, w;
	Job(int a = 0, int b = 0, int c = 0):
	st(a), ed(b), w(c) {}
	bool operator<(const Job &x) const {
		if (ed - w != x.ed - x.w)
			return ed - w < x.ed - x.w;
		return st < x.st;
	}
};
int main() {
	int n, st, ed;
	while (scanf("%d", &n) == 1 && n) {
		vector<Job> D;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &st, &ed);
			D.push_back(Job(st, ed, (ed - st)/2 + 1));
		}
		sort(D.begin(), D.end());
		int ret = 1, timeline = 0;
		for (int i = 0; i < n && ret; i++) {
			timeline = max(timeline, D[i].st);
			if (timeline + D[i].w > D[i].ed)
				ret = 0;
			else
				timeline += D[i].w;
		}
		puts(ret ? "YES" : "NO");
	}
	return 0;
}
