#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	void dfs(int idx, vector<int>& A, vector<int>& S, int sum, vector< vector<int> > &ret) {
		if (sum == 0) {
			ret.push_back(S);
			return ;
		}		
		if (idx == A.size())
			return ;
		for (int i = idx; i < A.size() && A[i] <= sum; i++) {
			S.push_back(A[i]);
			dfs(i, A, S, sum - A[i], ret);
			S.pop_back();
		}
	}
    vector< vector<int> > combinationSum(vector<int>& A, int target) {
    	sort(A.begin(), A.end());
    	
    	vector<int> S;
    	vector< vector<int> > ret;
        dfs(0, A, S, target, ret);
        return ret;
    }
};

int main() {
	Solution s;
	int A[] = {2,3,6,7};
	vector<int> v(A, A+4);
	vector< vector<int> > ret = s.combinationSum(v, 7);
	for (int i = 0; i < ret.size(); i++) {
		for (int j = 0; j < ret[i].size(); j++)
			printf("%d ", ret[i][j]);
		puts("");
	}
	return 0;
}
