#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	void dfs(int idx, vector<int>& A, vector<int>& B, vector<int>& S, int sum, vector< vector<int> > &ret) {
		if (sum == 0) {
			ret.push_back(S);
			return ;
		}		
		if (idx == A.size())
			return ;
		for (int i = idx; i < A.size() && A[i] <= sum; i++) {
			for (int j = 0; j < B[i] && A[i]*(j+1) <= sum; j++) {
				for (int k = 0; k <= j; k++)
					S.push_back(A[i]);
					
				dfs(i+1, A, B, S, sum - A[i]*(j+1), ret);
				
				for (int k = 0; k <= j; k++)
					S.pop_back();
			}
		}
	}
    vector< vector<int> > combinationSum2(vector<int>& A, int target) {
    	vector<int> B;
    	vector<int> S;
    	vector< vector<int> > ret;
    	
    	int m = 1;
    	sort(A.begin(), A.end());
    	B.push_back(1);
    	for (int i = 1; i < A.size(); i++) {
    		if (A[i] == A[m-1])
    			B[m-1]++;
    		else
    			A[m++] = A[i], B.push_back(1);
    	}
    	
    	A.resize(m);
        dfs(0, A, B, S, target, ret);
        return ret;
    }
};

int main() {
	Solution s;
	int A[] = {4,4,2,1,4,2,2,1,3};
	vector<int> v(A, A+9);
	vector< vector<int> > ret = s.combinationSum2(v, 6);
	for (int i = 0; i < ret.size(); i++) {
		for (int j = 0; j < ret[i].size(); j++)
			printf("%d ", ret[i][j]);
		puts("");
	}
	return 0;
}
