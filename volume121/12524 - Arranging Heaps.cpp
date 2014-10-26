#include <stdio.h> 
#include <algorithm>
#include <string.h>
using namespace std;
#define MAXN 1024
long long dp[MAXN][MAXN], X[MAXN], W[MAXN];
long long sumW[MAXN] = {}, sumXW[MAXN] = {};
struct SlopeDP {
	int front, rear;
	long long X[MAXN], Y[MAXN];
	void init() {front = 0, rear = -1;}
	long long cross(long long x1, long long y1, long long x2, long long y2) {
		return x1 * y2 - y1 * x2;
	}
	int add(long long x, long long y) {
		while (front < rear && cross(X[rear]-X[rear-1], Y[rear]-Y[rear-1], x-X[rear-1], y-Y[rear-1]) < 0)
			rear--;
		rear++;
		X[rear] = x, Y[rear] = y;
	}
	long long get(long long m) {
		while (front < rear && Y[front+1]-Y[front] < (X[front+1]-X[front]) * m)
			front++;
		return Y[front] - m * X[front];
	}
} dpTool;
int main() {
	int N, M;
	while (scanf("%d %d", &N, &M) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%lld %lld", &X[i], &W[i]);
		for (int i = 1; i <= N; i++) {
			sumW[i] = sumW[i-1] + W[i];
			sumXW[i] = sumXW[i-1] + X[i] * W[i];
		}
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= M; j++) 
				dp[i][j] = 1LL<<60;
		dp[0][0] = 0;
//		for (int i = 1; i <= N; i++) {
//			for (int j = 1; j <= M; j++) {
//				for (int k = 0; k < i; k++)
//					dp[i][j] = min(dp[i][j], dp[k][j-1] + X[i] * (sumW[i] - sumW[k]) - (sumXW[i] - sumXW[k]));
//			}
//		}
		for (int i = 1; i <= M; i++) {
			dpTool.init();
			for (int j = i; j <= N; j++) {
				dpTool.add(sumW[j-1], dp[j-1][i-1] + sumXW[j-1]);
				long long val = dpTool.get(X[j]);
				dp[j][i] = val - (sumXW[j] - sumW[j] * X[j]);
			}
		}
		printf("%lld\n", dp[N][M]);
	}
	return 0;
}
/*
dp[i][j] = dp[k][j-1] + X[i] * (sumW[i] - sumW[k]) - (sumXW[i] - sumXW[k])
dp[k][j-1] + sumXW[k] = X[i] * sumW[k] + dp[i][j] + sumXW[i] - sumW[i] * X[i]
^^^^^^^^^^^^^^^^^^^^^   ^^^^   ^^^^^^^   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
y = a x + b, a : monotone increasing, maintain upper convex
*/
/*
3 1
20 1
30 1
40 1
3 1
11 3
12 2
13 1
6 2
10 15
12 17
16 18
18 13
30 10
32 1
6 3
10 15
12 17
16 18
18 13
30 10
32 1
*/
