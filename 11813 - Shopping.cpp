#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#define none -1
using namespace std;
typedef struct {
	int to, v;
} Arc;
typedef vector<Arc>::iterator it;
vector<Arc>  link[100000];
void SPFA(int n, int st, int dis[]) {
	queue<int> Q;
	bool used[n];
	memset(used, 0, sizeof(used));
	
	for(it i = link[st].begin(); i != link[st].end(); i++) {
		if(dis[i->to] > i->v) {
			dis[i->to] = i->v;
			if(!used[i->to]) {
				used[i->to] = true;
				Q.push(i->to);
			}
		}
	}
	int tv;
	while(!Q.empty()) {
		tv = Q.front();
		Q.pop();
		used[tv] = false;
		for(it i = link[tv].begin(); i != link[tv].end(); i++) {
			if(dis[i->to] > dis[tv] + i->v) {
				dis[i->to] = dis[tv] + i->v;
				if(!used[i->to]) {
					used[i->to] = true;
					Q.push(i->to);
				}
			}
		}
	}
}
int map[11][11];
int DP[1<<11][11];
void build(int state, int last, int n) {
	if(state == 0)
		DP[state][last] = map[last][0];
	if(DP[state][last] != none)
		return;
	int i, min = 0xfffffff;
	for(i = 0; i < n; i++) {
		if(state&(1<<i)) {
			build(state^(1<<i), i, n);
			if(min > DP[state^(1<<i)][i]+map[last][i])
				min = DP[state^(1<<i)][i]+map[last][i];
		}
	}
	DP[state][last] = min;
}
void solve(int S[], int s, int n) {
	int i, j, dis[100000];
	for(i = 0; i < s; i++) {
		memset(dis, 127, n<<2);
		SPFA(n, S[i], dis);
		for(j = 0; j < s; j++) {
			map[i][j] = dis[S[j]];
		}
	}
	memset(DP, -1, sizeof(DP));
	build((1<<s)-2, 0, s);
	printf("%d\n", DP[(1<<s)-2][0]);
}
int main() {
	int t, n, m, i;
	int x, y, D, s, S[20];
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++) {
			link[i].clear();
		}
		Arc arc;
		while(m--) {
			scanf("%d %d %d", &x, &y, &D);
			arc.to = y, arc.v = D;
			link[x].push_back(arc);
			arc.to = x, arc.v = D;
			link[y].push_back(arc);
		}
		scanf("%d", &s);
		for(i = 1; i <= s; i++) {
			scanf("%d", &S[i]);
		}
		S[0] = 0;
		solve(S, s+1, n);
	}
    return 0;
}
