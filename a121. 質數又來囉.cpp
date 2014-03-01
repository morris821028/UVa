#include<stdio.h>
#include<math.h>
int P[5200], pt = 0;
void P_Sieve() {
	char mark[100000] = {};
	int a, b;
	P[pt++] = 2;
	for(a = 3; a <= 10000; a += 2)
		if(mark[a] == 0) {
			P[pt++] = a;
			for(b = 3; a*b <= 10000; b += 2)
				mark[a*b] = 1;
		}
}
int Judge(int N) {
	if(N == 1) return 0;
	register int a, sq = (int)sqrt(N);
	for(a = 0; a < pt && P[a] <= sq; a++)
		if(N%P[a] == 0)	return 0;
	return 1;
}
main() {
	P_Sieve();
	int A, B, a;
	while(scanf("%d %d", &A, &B) == 2) {
		int Ans = 0;
		for(a = A; a <= B; a++)
			Ans += Judge(a);
		printf("%d\n", Ans);
	}
	return 0;
}
