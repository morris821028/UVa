#include <bits/stdc++.h>
using namespace std;
map<string, double> T;
void table() {
	T["Cu"] = 1.730, T["Zn"] = 1.130;
	T["H2O"] = 3.720, T["Fe"] = 0.410;
	T["Si"] = 0.320, T["Mg"] = 3.460;
	T["C"] = 2.750, T["Pt"] = 25000;
	T["Au"] = 12260, T["Ag"] = 190.629;
}
int main() {
	table();
	int FI, FB, BV;
	int f, w;
	char s[1024];
	while (scanf("%d %d %d", &FI, &FB, &BV) == 3) {
		double dp[8192] = {};
		int used[8192] = {};
		used[0] = 1;
		FI -= FB;
		while (scanf("%d %s %d", &f, s, &w) == 3 && f) {
			if (FI >= f) {
				double val = T[s];
				for (int i = BV - w; i >= 0; i--) {
					if (used[i]) {
						dp[i+w] = max(dp[i+w], dp[i] + val * w);
						used[i+w] = 1;
					}
				}
				FI -= f;
			} else {
				FI = -1;
			}
		}
		
		int kg = -1;
		for (int i = BV; i >= 0; i--) {
			if (used[i] && (kg == -1 || dp[i] > dp[kg]))
				kg = i;
		}
		printf("kg=%d value=%.1lf\n", kg, dp[kg]);
	}
	return 0;
}

