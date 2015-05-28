#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int trap(vector<int>& H) {
        stack<int> stk;
        int ret = 0, n = H.size();
        
        stk.push(0);
        for (int i = 1; i < n; i++) {
            if (H[i] >= H[stk.top()]) {
                int h1 = H[stk.top()], h2;
                stk.pop();
                while (!stk.empty()) {
                    h2 = min(H[i], H[stk.top()]);
                    ret += (h2 - h1) * (i - stk.top() - 1);
                    if (H[stk.top()] > H[i])
                    	break;
                    stk.pop();
                    h1 = h2;
                }
            }
            stk.push(i);
        }
        return ret;
    }
};

int main() {
	Solution s;
	int A[] = {4,2,3};
	vector<int> v(A, A+3);
	printf("%d\n", s.trap(v));
	return 0;
}
