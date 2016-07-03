#include <stdio.h> 
#include <algorithm>
#include <set>
using namespace std;

const int MAXN = 1024;
const int MAXD = 105;

struct Time {
	int st, ed;
	bool operator<(const Time &a) const {
		return ed < a.ed;
	}
} T[MAXN];
int main() {
	int testcase, N;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &T[i].st, &T[i].ed);
			
		sort(T, T + N);
		int ret = 0;
		int from[MAXD], assign[MAXN];
		set<int> event[MAXD];
		for (int i = 0; i < N; i++) {
			int l = T[i].st, r = T[i].ed;
			for (int j = r; j >= l; j--)						// argument path
				from[j] = i;
			
			int day = r;	// choose
			for (int j = r; j >= l; j--) {
				if (event[j].size() < event[day].size())
					day = j;
				if (event[day].size() == 0)
					break;
				for (set<int>::iterator it = event[j].begin();
					it != event[j].end(); it++) {
					if (T[*it].st < l) {
						for (int k = l-1; k >= T[*it].st; k--)	// argument path
							from[k] = *it;
						l = T[*it].st;
					}
				}
			}
			
			ret += event[day].size() * 2 + 1;
			while (true) {
				int u = from[day];
				int d = assign[u];
				event[day].insert(u), assign[u] = day;
				if (u == i)	break;
				event[d].erase(u), day = d;
			}
		}
		
		printf("%d\n", ret);
	}
	return 0;
}
