#include <iostream>
#include <stdio.h> 
#include <string.h>
#include <vector>
#include <queue>
#include <map>
using namespace std;
typedef struct {
	int to, v;
} Arc;
typedef vector<Arc>::iterator it;
vector<Arc> Link[201];

int Min(int x, int y) {
	return x < y ? x : y;
}
int SPFA(int st, int ed, int n) {
	queue<int> Q;
	int dis[201];
	int used[201];
	memset(dis, 0, sizeof(dis));
	memset(used, 0, sizeof(used));
	dis[st] = 0xfffffff;
	for(it i = Link[st].begin(); i != Link[st].end(); i++) {
		if(dis[i->to] < Min(dis[st], i->v)) {
			dis[i->to] = Min(dis[st], i->v);
			if(used[i->to] == 0) {
				used[i->to] = 1;
				Q.push(i->to);
			}
		}
	}
	int tv;
	while(!Q.empty()) {
		tv = Q.front();
		Q.pop();
		used[tv] = 0;
		for(it i = Link[tv].begin(); i != Link[tv].end(); i++) {
			if(dis[i->to] < Min(dis[tv], i->v)) {
				dis[i->to] = Min(dis[tv], i->v);
				if(used[i->to] == 0) {
					used[i->to] = 1;
					Q.push(i->to);
				}
			}
		}
	}
	return dis[ed];
}
int main() {
	int n, r, Case = 0, i;
	while(scanf("%d %d", &n, &r) == 2) {
		if(n == 0 && r == 0)
			break;
		map<string, int> record;
		for(i = 0; i <= n; i++)
			Link[i].clear();
		int encode = 0, v, nx, ny;
		string x, y;
		while(r--) {
			cin >> x >> y >> v;
			if(record[x] == 0) { 
				encode ++;
				record[x] = encode;
			} 
			if(record[y] == 0) {
				encode++;
				record[y] = encode;
			}
			nx = record[x], ny = record[y];
			Arc arc;
			arc.to = ny, arc.v = v;
			Link[nx].push_back(arc);
			arc.to = nx, arc.v = v;
			Link[ny].push_back(arc);
		}
		cin >> x >> y; 
		printf("Scenario #%d\n", ++Case);
		nx = record[x], ny = record[y];
		printf("%d tons\n", SPFA(nx, ny, n));
		puts("");
	}
    return 0;
}
