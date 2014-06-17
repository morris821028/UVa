#include<stdio.h>
#include<math.h>
struct coordinate {
	int x, y; 
}D[200]; 
struct link {
	double t;
	int index; 
}Map[200][200]; 
double SPFA(int n) {
	double V[200], t;
	int a, b, Queue[40000], Qt = 0, Used[200] = {}, tn;
	for(a = 0; a < n; a++)	V[a] = 2000; 
	Queue[0] = 0, V[0] = 0;
	for(a = 0; a <= Qt; a++) {
		tn = Queue[a], Used[tn] = 0;
		for(b = 0; b < n; b++) {
			t = V[tn] > Map[tn][b].t ? V[tn] : Map[tn][b].t;
			if(V[Map[tn][b].index] > t) {
				V[Map[tn][b].index] = t;
				if(Used[Map[tn][b].index] == 0) {
					Used[Map[tn][b].index] = 1, Queue[++Qt] = Map[tn][b].index; 
				} 
			} 
		} 
	} 
	return V[1]; 
}
main() {
	int n, a, b, c, C = 0; 
	while(scanf("%d", &n) == 1 && n) {
		for(a = 0; a < n; a++)
			scanf("%d %d", &D[a].x, &D[a].y); 
		for(a = 0; a < n; a++) { 
			for(b = 0; b < n; b++) {
				Map[a][b].t = sqrt((D[a].x-D[b].x)*(D[a].x-D[b].x) + (D[a].y-D[b].y)*(D[a].y-D[b].y));
				Map[a][b].index = b; 
			} 
		} 
		printf("Scenario #%d\n", ++C); 
		printf("Frog Distance = %.3lf\n\n", SPFA(n));
	}
	return 0; 
}
