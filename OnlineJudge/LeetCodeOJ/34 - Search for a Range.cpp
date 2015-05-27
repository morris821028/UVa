#include <stdio.h> 
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& A, int target) {
        int L = (int) (lower_bound(A.begin(), A.end(), target) - A.begin());
        int R = (int) (upper_bound(A.begin(), A.end(), target) - A.begin());
        vector<int> ret;
        if (L >= R)
        	ret.push_back(-1), ret.push_back(-1);
        else
        	ret.push_back(L), ret.push_back(R-1);
        return ret;
    }
};

int main() {
	Solution s;
	int A[] = {1, 5};
	vector<int> v(A, A+2);
	s.searchRange(v, 4);
	return 0;
}
