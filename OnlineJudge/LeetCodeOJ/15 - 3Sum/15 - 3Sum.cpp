#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector< vector<int> > threeSum(vector<int>& A) {
    	vector< vector<int> > ret;
    	
        sort(A.begin(), A.end());        
        for (int i = 0; i < A.size(); i++) {
        	while (i+1 < A.size() && A[i+1] == A[i])
        		i++;
        	int target = -A[i];
        	int left = 0, right = i-1;
        	while (left < right) {
        		if (A[left] + A[right] == target) {
        			int v[3] = {A[left], A[right], A[i]};
        			vector<int> sol(v, v+3);
        			ret.push_back(sol);
        			left++, right--;
        			while (left < right && A[left] == A[left-1])
        				left++;
        			while (left < right && A[right] == A[right+1])
        				right--;
        		} else if (A[left] + A[right] < target) {
        			left++;
        		} else {
        			right--;
        		}
        	}
        }
        
        return ret;
    }
};

int main() {
	Solution s;
//	int S[] = {-1, 0, 1, 2, -1, -4};
//	vector<int> A(S, S+6);
	int S[] = {-2, 0, 0, 2, 2};
	vector<int> A(S, S+5);
	vector< vector<int> > test = s.threeSum(A);
	for (int i = 0; i < test.size(); i++)
		printf("%d %d %d\n", test[i][0], test[i][1], test[i][2]);
	return 0;
}
