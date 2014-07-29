#include <stdio.h>
#include <queue>
#include <algorithm>
#include <string.h>
using namespace std;

int gA[128][128], gB[128][128];
int spfa(int st, int ed, int n, double p) {
	double dist[128];
	int inq[128] = {}, u, v;
	queue<int> Q;
	for(int i = 0; i < n; i++)
		dist[i] = 1e+10;
	dist[st] = 0, Q.push(st);
	while(!Q.empty()) {
		u = Q.front(), Q.pop();
		inq[u] = 0;
		for(int i = 0; i < n; i++) {
			int wa = gA[u][i], wb = gB[u][i];
			double cost = 0;
			if(wa < 0 && wb < 0)	continue;
			if(wa >= 0 && wb >= 0)
				cost = wa * p + wb * (1-p);
			else
				cost = wa >= 0 ? wa : wb;
			if(dist[i] > dist[u] + cost) {
				dist[i] = dist[u] + cost;
				if(!inq[i])
					inq[i] = 1, Q.push(i);
			}
		}
	}
	return (int)dist[ed];
}
int main() {
	int N, Na, Nb, Q;
	int x, y, v;
	double p;
	while(scanf("%d %d %d %d", &N, &Na, &Nb, &Q) == 4 && N >= 0) {
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				gA[i][j] = gB[i][j] = -1;
		for(int i = 0; i < Na; i++) {
			scanf("%d %d %d", &x, &y, &v);
			if(gA[x][y] != -1)
				gA[x][y] = gA[y][x] = min(gA[x][y], v);
			else
				gA[x][y] = gA[y][x] = v;
		}
		for(int i = 0; i < Nb; i++) {
			scanf("%d %d %d", &x, &y, &v);
			if(gB[x][y] != -1)
				gB[x][y] = gB[y][x] = min(gB[x][y], v);
			else
				gB[x][y] = gB[y][x] = v;
		}
		for(int i = 0; i < Q; i++) {
			scanf("%lf", &p);
			printf("%d\n", spfa(0, N-1, N, p));
		}
	}
	return 0;
}
