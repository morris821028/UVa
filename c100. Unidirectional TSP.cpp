#include<stdio.h>
#define Maxv 10000000 
main() {
	int n, m;
	while(scanf("%d %d", &n, &m) == 2) {
		int Map[10][100], a, b, c, min;
		int next[10][100], t[3]; 
		for(a = 0; a < n; a++) 
			for(b = 0; b < m; b++) 
				scanf("%d", &Map[a][b]); 
		for(b = m-2; b >=0; b--) {
			for(a = 0; a < n; a++) {
				min = Maxv; 
				t[0] = (a+n-1)%n, t[1] = a, t[2] = (a+1)%n;
				for(c = 0; c < 3; c++) {
					if(min > Map[t[c]][b+1]) 
						min = Map[t[c]][b+1], next[a][b] = t[c]; 
					else if(min == Map[t[c]][b+1]) 
						next[a][b] = (next[a][b] < t[c]) ? next[a][b] : t[c]; 
				}
				Map[a][b] += min; 
			} 
		} 
		min = Maxv;
		int st = 0; 
		for(a = 0; a < n; a++) 
			if(min > Map[a][0]) { 
				min = Map[a][0], st = a; 
			} 
		printf("%d", st+1); 
		for(a = 0; a < m-1; a++) {
			printf(" %d", next[st][a]+1); 
			st = next[st][a]; 
		} 
		printf("\n%d\n", min); 
	}
	return 0; 
}
