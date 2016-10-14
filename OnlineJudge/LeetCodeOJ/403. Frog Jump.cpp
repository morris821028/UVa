#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canCross(vector<int>& stones) {
        map<int, set<int> > R;
        int n = stones.size();
        
        for (auto e : stones)
            R[e] = set<int>();
        R[stones[0]].insert(1);
        
        for (int i = 0; i < n-1; i++) {
            for (auto k : R[stones[i]]) {
                if (R.count(stones[i]+k)) {
                    R[stones[i]+k].insert(k+1);
                    R[stones[i]+k].insert(k);
                    R[stones[i]+k].insert(k-1);
                }
            }
        }
        return R[stones[n-1]].size() > 0;
    }
};

int main() {
	int arr[] = {0,1,3,5,6,8,12,17};
	vector<int> vec(arr, arr+8);
	Solution sol;
	printf("%d\n", sol.canCross(vec));
	return 0;
}

