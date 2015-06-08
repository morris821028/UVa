#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    int minDistance(string A, string B) {
    	int n = (int) A.length();
    	int m = (int) B.length();
    	if (n == 0)	return m;
    	if (m == 0)	return n;
    	
        vector<int> dp((n+1)*(m+1), n+m);
        
        for (int i = 0; i <= n; i++)
        	dp[(i) * (m+1) + 0] = i;
        for (int j = 0; j <= m; j++)
        	dp[(0) * (m+1) + j] = j;
        for (int i = 1; i <= n; i++) {
        	for (int j = 1; j <= m; j++) {
        		int &val = dp[(i) * (m+1) + j];
        		if (A[i-1] == B[j-1])
        			val = min(val, dp[(i-1)*(m+1)+(j-1)]);
        		val = min(val, dp[(i-1)*(m+1)+(j-1)]+1);
        		val = min(val, dp[(i)*(m+1)+(j-1)]+1);
        		val = min(val, dp[(i-1)*(m+1)+(j)]+1);
        	}
        }
        return dp[n*(m+1) + m];
    }
};
int main() {
	Solution s;
	printf("%d\n", s.minDistance("a", "ab"));
	printf("%d\n", s.minDistance("sea", "eat"));
	return 0;	
}
