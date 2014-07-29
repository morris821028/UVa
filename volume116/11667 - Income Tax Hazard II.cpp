// Wrong Answer, but I think it has accepted. All compute in integer, and what's happened ?
#include <stdio.h> 

long long sum1(long long n) {
	return n * (n+1)/2;
}
long long sum2(long long n) {
	return n * (n+1) * (n*2 + 1)/6;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	long long M, L, R;
	int cases = 0;
	while(scanf("%lld %lld %lld", &M, &L, &R) == 3) {
		if(M + L + R == 0)
			break;
		printf("Case %d: ", ++cases);
		if(M < L) {
			printf("%.2lf\n", 0);
		} else if(M > R) {
			long long N = R - L + 1, TOT = N * (N - 1)/2 + N;
			long long ret = 0;
			// [S1, S2] < M
			// 0.1 * sigma(i * (n-i)), n = R - L + 1
			ret += (sum1(N) * (N) - sum2(N)) * 1;
			// 0.2 * sigma(i * (M - R + n - i))
			ret += (sum1(N) * (M - R + N) - sum2(N)) * 2;
			printf("%.2lf\n", ret/10.0/TOT);
		} else {
			long long N = R - L + 1, TOT = N * (N - 1)/2 + N;
			long long ret = 0;
//			for(int S1 = L; S1 <= R; S1++) {
//				for(int S2 = S1; S2 <= R; S2++) {
//					if(M < S1) {
//					}
//					else if(S1 <= M && M <= S2)
//						ret += (M - S1) * 0.1;
//					else if(S2 < M)
//						ret += (M - S2) * 0.2 + (S2 - S1) * 0.1;
//				}
//			}
			// S1 <= M <= S2
			// 0.1 * sigma(i)
			ret += (R - M + 1) * sum1(M - L) * 1;
			// [S1, S2] < M
			R = M-1, N = R - L + 1;
			// 0.1 * sigma(i * (n-i)), n = R - L + 1
			ret += (sum1(N) * N - sum2(N)) * 1;
			// 0.2 * sigma(i * (M - R + N - i))
			ret += (sum1(N) * (M - R + N) - sum2(N)) * 2;
			printf("%.2lf\n", ret/10.0/TOT);
		}
	}
	return 0;
}
/*
243087 85024 180864
132889 100174 100172
120000 50000 100000
10000 50000 50002
70000 50000 80000
0 0 0
*/
