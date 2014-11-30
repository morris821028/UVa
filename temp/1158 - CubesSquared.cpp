#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;

int dp[524288];
vector<int> D;
int main() {
	for (int i = 1; i*i*i <= 400000; i++)
		D.push_back(i*i*i);
	for (int i = 1, j = 1; j <= 400000; i++, j += i*i)
		D.push_back(j);
	memset(dp, 63, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i < D.size(); i++)
		for (int j = D[i]; j <= 400000; j++)
			dp[j] = min(dp[j], dp[j - D[i]] + 1);
	int n;
	while (scanf("%d", &n) == 1 && n >= 0) {
		printf("%d\n", dp[n]);
	}
	return 0;
}
