#include<stdio.h>
#define Max 201
struct link {
	int t, node[101], w[101];
}Map[101];
void SPFA (int N) {
	int a, b, c;
	int Queue[10001], Qt = 0, tn, tw;
	int Used[101] = {}, V[101] = {};
	
	for(a = 1; a<= N; a++)	V[a] = Max;
	Queue[0] = 1, Used[1] = 1, V[1] = 0;
	
	for(a = 0; a <= Qt; a++) {
		tn = Queue[a];
		for(b = 0; b < Map[tn].t; b++) {
			tw = (V[tn] > Map[tn].w[b]) ? V[tn] : Map[tn].w[b];
			if(tw < V[Map[tn].node[b]]) {
				V[Map[tn].node[b]] = tw;
				if(Used[Map[tn].node[b]] == 0) 
					Queue[++Qt] = Map[tn].node[b], Used[Map[tn].node[b]] = 1;
			}
		}
		Used[tn] = 0;
	}
	printf("%d\n", V[N]);
}
main() {
	int T, x, y, w, N, M, a;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &M);
		for(a = 1; a <= N; a++)	Map[a].t = 0;
		for(a = 0; a < M; a++) {
			scanf("%d %d %d", &x, &y, &w);
			Map[x].node[Map[x].t] = y, Map[x].w[Map[x].t] = w;
			Map[y].node[Map[y].t] = x, Map[y].w[Map[y].t] = w;
			Map[x].t++, Map[y].t++;
		}
		SPFA(N);
	}
	return 0;
}
