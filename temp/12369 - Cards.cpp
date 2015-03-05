#include <stdio.h> 
#include <algorithm>
using namespace std;

int A, B, C, D;
int used[15][15][15][15][5][5], cases = 0;
double dp[15][15][15][15][5][5];
#define INF 1e+30
double dfs(int rA, int rB, int rC, int rD, int J1, int J2) {
	if (rA < 0 || rB < 0 || rC < 0 || rD < 0)
		return 0;
	int a, b, c, d;
	a = 13 - rA + (J1 == 1) + (J2 == 1);
	b = 13 - rB + (J1 == 2) + (J2 == 2);
	c = 13 - rC + (J1 == 3) + (J2 == 3);
	d = 13 - rD + (J1 == 4) + (J2 == 4);
	if (a >= A && b >= B && c >= C && d >= D)
		return 0;
	if (rA == 0 && rB == 0 && rC == 0 && rD == 0 && J1 != 0 && J2 != 0)
		return INF;
	double &ret = dp[rA][rB][rC][rD][J1][J2];
	if (used[rA][rB][rC][rD][J1][J2] == cases)
		return ret;
	used[rA][rB][rC][rD][J1][J2] = cases;
	
	double remain = rA + rB + rC + rD + (J1 == 0) + (J2 == 0);
	ret = 0;
	ret += rA / remain * (1 + dfs(rA - 1, rB, rC, rD, J1, J2));
	ret += rB / remain * (1 + dfs(rA, rB - 1, rC, rD, J1, J2));
	ret += rC / remain * (1 + dfs(rA, rB, rC - 1, rD, J1, J2));
	ret += rD / remain * (1 + dfs(rA, rB, rC, rD - 1, J1, J2));
	
	if (J1 == 0) {
		double mn = INF;
		for (int i = 1; i <= 4; i++)
			mn = min(mn, 1 / remain * (1 + dfs(rA, rB, rC, rD, i, J2)));
		ret += mn;
	}
	if (J2 == 0) {
		double mn = INF;
		for (int i = 1; i <= 4; i++)
			mn = min(mn, 1 / remain * (1 + dfs(rA, rB, rC, rD, J1, i)));
		ret += mn;
	}
	return ret;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d %d", &A, &B, &C, &D);
		++cases;
		double ret = dfs(13, 13, 13, 13, 0, 0);
		if (ret > 54)	ret = -1;
		printf("Case %d: %.3lf\n", cases, ret);
	}
	return 0;
}
