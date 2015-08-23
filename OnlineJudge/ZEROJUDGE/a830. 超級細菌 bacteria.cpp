#include <bits/stdc++.h>
using namespace std;

int main() {
	long long M, N, W, X, Y, Z;
	long long A[256] = {}, B[256] = {};
	scanf("%lld %lld %lld", &M, &N, &W);
	scanf("%lld %lld %lld", &X, &Y, &Z);
	A[0] = N, B[0] = M;
	for (int i = 0; i < W; i++) {
		for (int j = Y-1; j >= 0; j--)
			B[j+1] = B[j];
		for (int j = X-1; j >= 0; j--)
			A[j+1] = A[j];
		B[0] = B[Y] + A[X];
		A[0] = B[Y] * Z;
	}
	long long sum = 0;
	for (int i = 0; i < X; i++)
		sum += A[i];
	for (int i = 0; i < Y; i++)
		sum += B[i];
	printf("%lld\n", sum);
	return 0;
}
