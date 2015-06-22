#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = (int) prices.size();
        int ret = 0;
        vector<int> L(n+1, 0), R(n+1, 0);
        for (int i = 0, t = 0, s = INT_MAX; i < n; i++) {
            s = min(s, prices[i]);
            t = max(t, prices[i] - s);
            L[i] = t;
        }
        for (int i = n-1, t = 0, s = INT_MIN; i >= 0; i--) {
            s = max(s, prices[i]);
            t = max(t, s - prices[i]);
            R[i] = t;
        }
        for (int i = 0; i < n; i++) {
            ret = max(ret, L[i] + R[i+1]);
        }
        return ret;
    }
};

int main() {
	Solution s;
	int A[] = {2,4,1};
	vector<int> v(A, A+3);
	s.maxProfit(v);
	return 0;
}
