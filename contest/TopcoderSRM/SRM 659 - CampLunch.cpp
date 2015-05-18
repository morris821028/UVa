#include <stdio.h>
#include <vector>
#include <string.h>
#include <iostream>
#include <algorithm>
using namespace std;

const long long MOD = 1000000007;
const int MAXN = 17, MAXM = 17;
class CampLunch {
public:
	int dp[2][1<<MAXM];
	int count(int N, int M, vector <string> a) {
		memset(dp, 0, sizeof(dp));
		int flag = 0;
		dp[0][(1<<M)-1] = 1;
		for (int i = 0; i < N; i++) {			
			for (int j = 0; j < M; j++) {
				int p = flag, q = !flag;
				flag = 1 - flag;
				memset(dp[q], 0, sizeof(dp[q]));
				for (int k = (1<<M)-1; k >= 0; k--) {
					int L, U;
					int Lid, Uid;
					int ways = dp[p][k];
					
					if (ways == 0)
						continue;
					
					Lid = j == 0 ? -1 : (a[i][j-1] - 'A');
					Uid = a[i][j] - 'A';
					L = j == 0 ? 1 : ((k>>(Lid))&1);
					U = (k>>Uid)&1;
										
					if (L == 0 && U == 1) 	// plan 1, sit next to each other
						dp[q][k|(1<<Lid)] = (dp[q][k|(1<<Lid)] + ways)%MOD;
					if (U == 0) 			// plan 2, two consecutive days.
						dp[q][k|(1<<Uid)] = (dp[q][k|(1<<Uid)] + ways)%MOD;
					if (U == 1)				// plan 3, single
						dp[q][k|(1<<Uid)] = (dp[q][k|(1<<Uid)] + ways)%MOD;
					if (U == 1)				// reserve
						dp[q][k^(1<<Uid)] = (dp[q][k^(1<<Uid)] + ways)%MOD;
				}
			}
		}
		
		return dp[flag][(1<<M)-1];
	}
};

int main() {
	CampLunch cl;
	string v[] = {"ABC","ABC"};
	int vv = cl.count(2, 3, vector<string>(v, v+2));
	printf("%d\n", vv);
	return 0;
}
/*
 2
2
{"AB","AB"}

*/
