#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8;
double f(double a, double b, int deuce) {
	double dp[MAXN][MAXN] = {};
	dp[0][0] = 1;
	for (int i = 0; i <= deuce+1; i++) {
		for (int j = 0; j <= deuce+1; j++) {
			if (i == deuce+1|| j == deuce+1)
				continue;
			if ((i+j)%2 == 0) {	// a wins
				dp[i+1][j] += dp[i][j]*a;
				dp[i][j+1] += dp[i][j]*(1-a);
			} else {
				dp[i+1][j] += dp[i][j]*b;
				dp[i][j+1] += dp[i][j]*(1-b);
			}
		}
	}
	double ret = 0;
	for (int i = 0; i < deuce; i++)
		ret += dp[deuce+1][i];
	/*
		deuce: lead #score
		d[-2] = 0	// lose
		d[-1] = d[0] b;
		d[ 0] = d[1] a + d[-1] (1-a);
		d[ 1] = b + d[0] (1-b);
		d[ 2] = 1	// win
		
		d[0] = (b + d[0] (1-b)) a + (d[0] b) (1-a)
		x = ab + x(a-ab) + xb - xab
		=> x = ab + (a+b-2ab) x => x = ab / (1-a-b+2ab)
	*/
	double x = a*b/(1-a-b+2*a*b);
	ret += dp[deuce][deuce]*x;
	return ret;
}
double solve(double p, double q) {
	double sp, sq, gp, gq;
	// win a game
	gp = f(p, p, 3);
	gq = f(q, q, 3);
	// win a set
	sp = f(gp, gq, 5);
	sq = f(gq, gp, 5);
	// win a match
	double ret = 0;
	double dp[MAXN][MAXN] = {};
	dp[0][0] = 1;
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 3; j++) {
			if (i == 3 || j == 3)
				continue;
			if ((i+j)%2 == 0) {
				dp[i+1][j] += dp[i][j]*sp;
				dp[i][j+1] += dp[i][j]*(1-sp);
			} else {
				dp[i+1][j] += dp[i][j]*sq;
				dp[i][j+1] += dp[i][j]*(1-sq);
			}
		}
	}
	ret = dp[3][0] + dp[3][1] + dp[3][2];
	return ret;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		double p, q;
		scanf("%lf %lf", &p, &q);
		p /= 100, q /= 100;
		printf("Case #%d: %.4lf%%\n", ++cases, solve(p, q)*100);
	}
	return 0;
}
/*
2
50  50
51  51
*/
