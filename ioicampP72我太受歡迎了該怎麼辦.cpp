#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;
struct Date {
	int l, r, w, idx;
	Date(int a=0, int b=0, int c=0, int d=0):
		l(a), r(b), w(c), idx(d) {}
	bool operator<(const Date& a) const {
		return l < a.l;
	}
};
struct Program {
	vector<int> right;
	bool operator<(const Program& a) const {
		for(int i = 0; i < right.size(); i++)
			if(right[i] != a.right[i])
				return right[i] < a.right[i];
		return false;
	}
	void adjust(int val) {
		for(int i = 0; i < right.size(); i++) {
			if(right[i] < val)
				right[i] = 0;
		}
		sort(right.begin(), right.end());
	}
};
int main() {
	int testcase;
	int N, K;
	int i, j, k;
	Date D[1005];
	scanf("%d", &testcase);
	while(testcase--)  {
		scanf("%d %d", &N, &K);
		for(i = 0; i < N; i++) {
			int s, t, h;
			scanf("%d %d %d", &s, &t, &h);
			D[i] = Date(s, s+t-1, h, i);
		}
		sort(D, D+N);
		map<Program, int> R1, R2;
		map<Program, vector<int> > S1, S2;
		Program init;
		for(i = 0; i < K; i++)
			init.right.push_back(0);
		R1[init] = 0;
		R2[init] = 0;
		S1[init] = vector<int>();
		S2[init] = vector<int>();
		int now_time = 0;
		int ret = 0;
		for(i = 0; i < N; i++) {
			now_time = D[i].l;
			for(map<Program, int>::iterator it = R1.begin();
				it != R1.end(); it++) {
				int best = it->second;
				Program r = it->first;
				for(k = 0; k < r.right.size(); k++) {
					if(r.right[k] < now_time) {
						Program p = r;
						p.right[k] = D[i].r;
						p.adjust(now_time);
						int &v = R2[p];
						if(v < best + D[i].w) {
							v = best + D[i].w;
							S2[p] = S1[r];
							S2[p].push_back(D[i].idx);
						}
					}
				}
			}
			R1 = R2;
			S1 = S2;
		}
		for(map<Program, int>::iterator it = R1.begin();
				it != R1.end(); it++) {
			ret = max(ret, it->second);
		}
		for(map<Program, int>::iterator it = R1.begin();
				it != R1.end(); it++) {
			if(it->second == ret) {
				vector<int>	solution = S1[it->first];
				int mark[1005] = {};
				for(i = 0; i < solution.size(); i++)
					mark[solution[i]] = 1;
				for(i = 0; i < N; i++)
					printf("%d%c", mark[i], i == N-1 ? '\n' : ' ');
				break;
			}
		}
		//printf("%d\n", ret);
	}
	return 0;
}
/*
3
5 3
1 6 3
2 4 2
6 1 2
1 9 10
5 8 10
5 3
1 6 4
2 4 2
6 1 2
1 9 10
5 8 10
4 2
1 4 4
6 4 4
1 5 3
5 5 3

24
24
14
*/
