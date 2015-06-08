#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& height) {
        stack< pair<int, int> > stk;
        int ret = 0;
        
        stk.push(make_pair(-1, -1));
        height.push_back(0);
        for (int i = 0; i < height.size(); i++) {
        	int e = i;
        	while (stk.top().first > height[i]) {
        		ret = max(ret, stk.top().first * (i - stk.top().second));
        		e = stk.top().second;
        		stk.pop();
        	}
        	stk.push(make_pair(height[i], e));
        }
        return ret;
    }
};

int main() {
	Solution s;
//	int A[] = {2,1,5,6,2,3};
//	vector<int> v(A, A+6);
	int A[] = {1};
	vector<int> v(A, A+1);
	printf("%d\n", s.largestRectangleArea(v));
	return 0;	
}
