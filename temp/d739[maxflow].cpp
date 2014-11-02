#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
using namespace std;
#define MAXN 65536
#define MAXE (1<<23)
#define MAXV 524288
struct Node {
    int x, y;
	int cap, flow;// x->y, v
    int next;
} edge[MAXE];
int e, head[MAXN], prev[MAXN], record[MAXN];
int level[MAXN], visited[MAXN];
void addEdge(int x, int y, int v) {
    assert(e < MAXE);
    edge[e].x = x, edge[e].y = y, edge[e].cap = v, edge[e].flow = 0;
    edge[e].next = head[x], head[x] = e++;
    edge[e].x = y, edge[e].y = x, edge[e].cap = 0, edge[e].flow = 0;
    edge[e].next = head[y], head[y] = e++;
}
bool buildLevelGraph(int s, int t) {
    memset(level, 0, sizeof(level));
    queue<int> Q;
    Q.push(s), level[s] = 1;
    while(!Q.empty()) {
        int tn = Q.front();
        Q.pop();
        for(int i = head[tn]; i != -1; i = edge[i].next) {
            int y = edge[i].y;
            if(edge[i].cap > edge[i].flow && level[y] == 0) {
                level[y] = level[tn] + 1;
                Q.push(y);
            }
        }
    }
    return level[t] > 0;
}
int constructBlockingFlow(int s, int t) {
    int ret = 0;
    stack<int> stk;
    memset(visited, 0, sizeof(visited));
    stk.push(s);
    while(!stk.empty()) {
        int now = stk.top();
        if(now != t) {
            for(int i = head[now]; i != -1; i = edge[i].next) {
                int y = edge[i].y;
                if(visited[y] || level[y] != level[now] + 1)
                    continue;
                if(edge[i].cap > edge[i].flow) {
                    stk.push(y), prev[y] = now, record[y] = i;
                    break;
                }
            }
            if(stk.top() == now)
                stk.pop(), visited[now] = 1;
        } else {
            int flow = 0x3f3f3f3f, bottleneck;
            for(int i = t; i != s; i = prev[i]) {
                int ri = record[i];
                flow = min(flow, edge[ri].cap - edge[ri].flow);
            }
            for(int i = t; i != s; i = prev[i]) {
                int ri = record[i];
                edge[ri].flow += flow;
                edge[ri^1].flow -= flow;
                if(edge[ri].cap - edge[ri].flow == 0)
                    bottleneck = prev[i];
            }
            while(!stk.empty() && stk.top() != bottleneck)
                stk.pop();
            ret += flow;
        }
    }
    return ret;
}
int maxflowDinic(int s, int t) {
    int flow = 0;
    while(buildLevelGraph(s, t))
        flow += constructBlockingFlow(s, t);
    return flow;
}
vector<int> maxflowCut(int s, int t, int n) {
	buildLevelGraph(s, t);
	vector<int> ret;
	for (int i = 1; i <= n; i++) {
		for (int j = head[i]; j != -1; j = edge[j].next) {
			if (level[edge[j].x] && !level[edge[j].y] && edge[j].cap > 0 && edge[j].cap == edge[j].flow)
				ret.push_back(j);
		}
	}
	return ret;
}
int clearflow() {
	for (int i = 0; i < e; i++)
		edge[i].flow = 0;
}
int in[MAXN], out[MAXN], rank[MAXN];
int greedyPreflow(int source, int sink, int n) {
	buildLevelGraph(source, sink);
	vector< pair<int, int> > R;
	for (int i = 0; i < n; i++)
		R.push_back(make_pair(level[i], i));
	sort(R.begin(), R.end());
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	in[source] = 0x3f3f3f3f;
	for (int j = 0; j < n; j++) {
		int u = R[j].second;
		for (int i = head[u]; i != -1; i = edge[i].next)  {
			int y = edge[i].y;
			if (!(i&1) && in[u] > out[u]) {
				int f = min(edge[i].cap - edge[i].flow, in[u] - out[u]);
				in[y] += f, out[u] += f;
			}
		}
	}
	memset(in, 0, sizeof (in));
	in[sink] = 0x3f3f3f3f;
	int preflow = 0;
	for (int j = n - 1; j >= 0; j--) {
		int u = R[j].second;
		for (int i = head[u]; i != -1; i = edge[i].next)  {
			int y = edge[i].y;
			if ((i&1) && in[u] < out[u]) {
				int f = min(min(in[y], out[u] - in[u]), edge[i].cap - edge[i].flow);
				in[u] += f, in[y] -= f;
				edge[i].flow -= f, edge[i^1].flow += f;
				preflow += f;
			}
		}
	}
	return preflow;
}
int main() {
	int testcase, cases = 0;
	int N, M, x, y;
	while (scanf("%d %d", &N, &M) == 2 && N) {
		e = 0;
		memset(head, -1, sizeof(head));
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			addEdge(x, N + y, 1);
		}
        int source = 0, sink = 2 * N + 1;
        for (int i = 1; i <= N; i++)
        	addEdge(source, i, 1), addEdge(N + i, sink, 1);
   		int flow = greedyPreflow(source, sink, 2 * N + 2);
		flow += maxflowDinic(source, sink);
   		printf("%d\n", N - flow);
	}
    return 0;
}
/*
3
5
2 4 8 16 32
5
2 3 4 6 9
3
1 2 3

1000
3
7 35 105
*/

