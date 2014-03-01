#include<stdio.h>
#include<math.h>
int gcd(int x, int y) {
	int t;
	while(x%y) {
		t = x, x = y, y = t%y;
	}
	return y;
}
long long P[5200], pt = 0;
void P_Sieve() {
	char mark[100000] = {};
	int a, b;
	P[pt++] = 2;
	for(a = 3; a <= 50000; a += 2)
		if(mark[a] == 0) {
			P[pt++] = a;
			for(b = 3; a*b <= 50000; b += 2)
				mark[a*b] = 1;
		}
}
main() {
	P_Sieve();
	int M, N, L, t, tx, a;
	while(scanf("%d %d %d", &M, &N, &L) == 3) {
		if(M + N + L == 0) break;
		tx = gcd(M, gcd(N, L)), M/=tx, N/=tx, L/=tx;
		if(M > L) t = M, M = L, L = t;
		if(N > L) t = N, N = L, L = t;
		if(M > N) t = N, N = M, M = t;
		long long V = N*L*N*L + M*M*(N*N+L*L);
		long long t1 = 1, t2 = V;
		for(a = 0; a < pt && t2 >= P[a]*P[a]; a++)
			while(t2%(P[a]*P[a]) == 0)
				t1 *= P[a], t2 /= P[a]*P[a];
		t1 *= tx * tx; 
		if(t1 == 1 && t2 != 1)
			printf("_/%lld\n", t2);
		else if(t2 != 1)
			printf("%lld_/%lld\n", t1, t2);
		else
			printf("%lld\n", t1);
	}
	return 0;
}
