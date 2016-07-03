#include <stdio.h> 
#include <assert.h>
#include <algorithm>
#include <string.h>
#include <vector>
#include <set>
using namespace std;

const int MAXN = 1024;
const int MAXD = 105;

struct Time {
	int st, ed;
	bool operator<(const Time &a) const {
		if (st != a.st)	
			return st < a.st;
		return ed < a.ed;
	}
} T[MAXN];
int visited[MAXD], match[MAXN];
vector<int> event[MAXD];
int event_move[MAXD][MAXD];
int dfs(int u, int place) {
	visited[u] = 1;
	if (event[u].size() < place - 1)
		return 1;
	for (int i = 1; i < MAXD; i++) {
		if (!visited[i]) {
			if (event_move[u][i] > 0) { // find a object to move i-day
				if (dfs(i, place)) {
					int id = -1, id_pos = -1;
					for (int j = 0; j < event[u].size(); j++) {
						id = event[u][j], id_pos = j;
						if (T[id].st <= i && i <= T[id].ed)
							break;
					}
					assert(id >= 0);
					for (int j = T[id].st; j <= T[id].ed; j++) {
						event_move[u][j]--;
						event_move[i][j]++;
					}
					match[id] = i;
					event[u].erase(event[u].begin() + id_pos);
					event[i].push_back(id);
					return 1;
				}
			}
		}
	}
	return 0;
}
int main() {
	int testcase, N;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d %d", &T[i].st, &T[i].ed);
		
		memset(event_move, 0, sizeof(event_move));
		for (int i = 0; i < MAXD; i++)
			event[i].clear();
		
		sort(T, T + N);
		for (int i = 0; i < N; i++) {
			int mn_day = T[i].st;
			for (int j = T[i].st; j <= T[i].ed; j++) {
				if (event[j].size() < event[mn_day].size())
					mn_day = j;
			}
			
			match[i] = mn_day, event[mn_day].push_back(i);
			for (int j = T[i].st; j <= T[i].ed; j++) {
				event_move[mn_day][j]++;
			}			
			
			memset(visited, 0, sizeof(visited));
			dfs(mn_day, event[mn_day].size());
		}
		
		int ret = 0;
		for (int i = 1; i < MAXD; i++)
			ret += event[i].size() * event[i].size();
		printf("%d\n", ret);
	}
	return 0;
}
/*
999
10
1 3
2 3
1 3
2 5
1 1
2 6
2 2
1 4
2 8
2 3

8
46 89
34 51
72 94
8 12
3 66
36 63
2 69
2 3
*/
/*
4
3
1 3
1 3
1 3
3
2 3
1 2
1 2
5
2 3
1 2
1 2
3 3
3 3
6
2 3
1 2
1 2
3 3
3 3
2 3
*/
