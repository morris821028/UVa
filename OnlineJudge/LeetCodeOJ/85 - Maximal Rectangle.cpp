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
    
    int maximalRectangle(vector< vector<char> >& matrix) {
        if (matrix.size() == 0)
        	return 0;
        int n = (int) matrix.size(), m = (int) matrix[0].size();
        vector< vector<int> > sum(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
        	int s = 0;
        	for (int j = 0; j < m; j++) {
        		if (matrix[i][j] == '0')
        			s = 0;
        		else
        			s ++;
        		sum[i][j] = s;
        	}
        }
        
        int ret = 0;
        for (int j = 0; j < m; j++) {
        	vector<int> h;
        	for (int i = 0; i < n; i++)
        		h.push_back(sum[i][j]);
        	ret = max(ret, largestRectangleArea(h));
        }
        return ret;
    }
};

int main() {
	Solution s;
	return 0;	
}
