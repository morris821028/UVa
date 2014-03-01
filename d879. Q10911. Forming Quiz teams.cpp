#include<stdio.h>
#include<math.h>
struct coordinate {
	short x, y;
}D[16];
unsigned short lowbit[65537], next[65537];
char lowbits[65537], set[65537];
double Map[16][16], best[65537];
double DP(int N, int sum) {
	if(N == 0) return 0;
	if(best[N] != -1) {
		return best[N];
	}
	if(best[sum] == -1)
		best[sum] = DP(sum, 0);
		
	int e = lowbits[N], tn, t;
	double min = 2000, temp;
	sum += lowbit[N], tn = next[N], t = next[N];
	for(; t; t = next[t]) {
		temp = DP(tn-lowbit[t], sum+lowbit[t]);
		min = (min < Map[e][lowbits[t]] + temp) ? min : Map[e][lowbits[t]] + temp;
	}
	best[N] = min;
	return best[N];
}
int Input() { 
    char cha; 
    unsigned int x = 0; 
    while(cha = getchar()) 
        if(cha != ' ' && cha != '\n' || cha == EOF) break; 
    if(cha == EOF) return -1;
    x = cha-48; 
    while(cha = getchar()) { 
        if(cha == ' ' || cha == '\n') break; 
        x = x*10 + cha-48; 
    } 
    return x; 
}
main() {
	int N, a, b, s2[20] = {1}, C = 0;
	for(a = 1; a < 17; a++)	s2[a] = s2[a-1]*2, set[s2[a]] = a;
	for(a = 1; a <= 65536; a++)
		lowbit[a] = a & (-a), next[a] = a - lowbit[a], lowbits[a] = set[lowbit[a]];
	char name[30];
	while(scanf("%d", &N) == 1 && N) {
		N *= 2;
		for(a = 0; a < N; a++) {
			scanf("%s", name);
			D[a].x = Input(), D[a].y = Input();
		}
		for(a = 0; a < N; a++)
			for(b = a+1; b < N; b++)
				Map[a][b] = sqrt((D[a].x-D[b].x)*(D[a].x-D[b].x) + (D[a].y-D[b].y)*(D[a].y-D[b].y))
				, Map[b][a] = Map[a][b];
		for(a = 0; a < s2[N]; a++)	best[a] = -1;
		printf("Case %d: %.2lf\n", ++C, DP(s2[N]-1, 0));
	}
	return 0;
}
