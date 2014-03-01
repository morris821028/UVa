#include<stdio.h>
int P[30001], R[30001];
int MakeInit(int N) {
	int i;
	for(i = 0; i <= N; i++)
		P[i] = i, R[i] = 1;
}
int FindP(int x) {
	if(P[x] != x)
		P[x] = FindP(P[x]);
	return P[x];
}
int Link(int x, int y) {
	if(R[x] > R[y])
		R[x] += R[y], P[y] = x;
	else
		R[y] += R[x], P[x] = y;
}
int Union(int x, int y) {
	x = FindP(x), y = FindP(y);
	if(x != y)
		Link(x, y);
}
int main() {
	int T, N, M, i, x, y;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &N, &M);
		MakeInit(N);
		while(M--) {
			scanf("%d %d", &x, &y);
			Union(x, y);
		}
		int max = 0;
		for(i = 1; i <= N; i++)
			max = max > R[i] ? max : R[i];
		printf("%d\n", max);
	} 
    return 0;
}
