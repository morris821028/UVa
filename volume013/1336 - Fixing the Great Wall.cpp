#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 1024
#define INF 1000000005
struct Pos {
	int x, c, delta; // cost = c + t * delta
	bool operator<(const Pos &a) const {
		return x < a.x;
	}
} D[MAXN];
int sumD[MAXN];
double dp[MAXN][MAXN][2]; // [interval_length][l][stop interval left/right]

int main() {
	int N, X;
	double V;
	while (scanf("%d %lf %d", &N, &V, &X) == 3 && N) {
		for (int i = 1; i <= N; i++)
			scanf("%d %d %d", &D[i].x, &D[i].c, &D[i].delta);
		sort(D + 1, D + 1 + N);
		
		sumD[0] = 0;
		for (int i = 1; i <= N; i++)
			sumD[i] = sumD[i-1] + D[i].delta;

		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= N + 1; j++) {
				dp[i][j][0] = dp[i][j][1] = INF;
			}
		}
		for (int i = 1; i <= N; i++) {
			double cost = sumD[N] * (fabs(X - D[i].x) / V) + D[i].c;
			dp[1][i][0] = dp[1][i][1] = cost;
		}
		
		for (int i = 2; i <= N; i++) {
			for (int j = 1; j + i - 1 <= N; j++) {
				int l = j, r = j + i - 1;
				double fromL, fromR;
				fromL = fromR = INF;
				fromL = dp[i-1][l+1][0] + (sumD[l] + sumD[N] - sumD[r]) * ((D[l+1].x - D[l].x) / V) + D[l].c;
				fromR = dp[i-1][l+1][1] + (sumD[l] + sumD[N] - sumD[r]) * ((D[r].x - D[l].x) / V) + D[l].c;
				dp[i][l][0] = min(fromL, fromR);
				
				fromL = dp[i-1][l][0] + (sumD[l-1] + sumD[N] - sumD[r-1]) * ((D[r].x - D[l].x) / V) + D[r].c;
				fromR = dp[i-1][l][1] + (sumD[l-1] + sumD[N] - sumD[r-1]) * ((D[r].x - D[r-1].x) / V) + D[r].c;
				dp[i][l][1] = min(fromL, fromR);
			}
		}
		printf("%d\n", (int) min(dp[N][1][0], dp[N][1][1]));
	}
	return 0;
}
