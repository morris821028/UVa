#include <stdio.h> 
#include <vector>
#include <limits.h>
#include <algorithm>
using namespace std;

class Solution {
public:
    int threeSumClosest(vector<int>& A, int target) {
    	int ret = INT_MAX;
    	
        sort(A.begin(), A.end());        
        for (int i = 0; i < A.size(); i++) {
        	while (i+1 < A.size() && A[i+1] == A[i])
        		i++;
        	int t = target - A[i];
        	int left = 0, right = i-1;
        	while (left < right) {
        		int diff = t - A[left] - A[right];
        		if (abs(diff) < abs(ret))
        			ret = diff;
        		if (diff == 0) {
        			return target;
        		} else if (diff > 0) {
        			left++;
        		} else {
        			right--;
        		}
        	}
        }
        
        return target - ret;
    }
};

int main() {
	Solution s;
	int S[] = {-1, 2, 1, -4};
	vector<int> A(S, S+4);
	int test = s.threeSumClosest(A, 1);
	printf("%d\n", test);
	return 0;
}
