#include <stdio.h> 
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define MAXN 1024
#define MAXS 526244
int isPower[MAXS] = {}, sum[MAXS];
vector<int> power;
int main() {
	for (int i = 2; i < MAXN; i++)
		for (int j = i*i; j < MAXS; j *= i)
			isPower[j] = 1, power.push_back(j);
	sort(power.begin(), power.end());
	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		vector<int> ret, dp;
		int invalid[MAXN] = {};
		dp.push_back(0);
		for (int i = a; i <= b; i++) {
			if (isPower[i] || invalid[i])
				continue;
			ret.push_back(i);
			int pre = dp.size();
			for (int j = 0; j < pre; j++) {
				int sub = dp[j] + i;
				if (sum[sub] == 0)
					sum[sub] = 1, dp.push_back(sub);
			}
			for (int j = pre; j < dp.size(); j++) {
				int pos = (int) (lower_bound(power.begin(), power.end(), dp[j]) - power.begin());
				for (int k = pos; power[k] - dp[j] <= b && k < power.size(); k++) {
					invalid[power[k] - dp[j]] = 1;
				}
			}
		}
		for (int i = 0; i < ret.size(); i++)
			printf("%d%c", ret[i], i == ret.size() - 1 ? '\n' : ' ');
		for (int i = 0; i < dp.size(); i++)
			sum[dp[i]] = 0;
	}
	return 0;
}
