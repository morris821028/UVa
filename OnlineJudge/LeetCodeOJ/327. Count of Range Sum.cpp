#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	vector<int> BIT;
	void modifyAdd(int x, int val, int L) {
		while (x <= L && x > 0)
			BIT[x] += val, x -= x&(-x);
	}
	int query(int x, int L) {
		int ret = 0;
		while (x <= L && x > 0)
			ret += BIT[x], x += x&(-x);
		return ret;
	}
    int countRangeSum(vector<int>& A, int lower, int upper) {
    	int n = A.size();
        vector<long long> S(n+1, 0), qS;
        for (int i = 0, j = 1; i < n; i++, j++)
        	S[j] = S[j-1] + A[i];
        
        map<long long, int> R;
        for (int i = 0; i <= n; i++)
        	R[S[i]] = 0;
        
        qS.resize(R.size() + 1);
        qS[0] = LONG_LONG_MIN;
        int label = 0;
        for (auto &e : R)
        	e.second = ++label, qS[label] = e.first;
        
        int m = label + 5;
        BIT = vector<int>(m+1, 0);
        
        long long ret = 0;
        int idx;
		for (int i = 1; i <= n; i++) {
			if (S[i] >= lower && S[i] <= upper)
				ret++;
			int a, b;
			a = lower_bound(qS.begin(), qS.end(), S[i] - lower + 1) - qS.begin();
			b = lower_bound(qS.begin(), qS.end(), S[i] - upper - 0) - qS.begin();
			ret += query(b, m) - query(a, m);
			modifyAdd(R[S[i]], 1, m);
		}
		return ret;
    }
};

int main() {
	Solution t;
	
//	int A[] = {0, 0};
//	vector<int> vA(A, A+2);
//	int ret = t.countRangeSum(vA, 0, 0);
	
//	int A[] = {-2, 5, -1};
//	vector<int> vA(A, A+3);
//	int ret = t.countRangeSum(vA, -2, 2);
	
	int A[] = {1, 1, 1, 1};
	vector<int> vA(A, A+4);
	int ret = t.countRangeSum(vA, 0, 4);
	printf("%d\n", ret);
	return 0;
}

