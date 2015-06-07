#include <stdio.h>
#include <string.h>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

class Solution {
public:
    set<int>::iterator prev(set<int>::iterator it, set<int> &S) {
        return it == S.begin() ? it : --it;
    }
    set<int>::iterator next(set<int>::iterator it, set<int> &S) {
        return it == S.end() ? it : ++it;
    }
    bool containsNearbyAlmostDuplicate(vector<int>& A, int k, int t) {
        vector< pair<long long, int> > B;
        for (int i = 0; i < A.size(); i++)
            B.push_back(make_pair(A[i], i));
        sort(B.begin(), B.end());
        
        set<int> Idx;
        set<int>::iterator it, jt;
        int l, r;
        l = r = 0;
        for (; r < B.size(); r++) {
            while (l < r && B[r].first - B[l].first > t) {
                Idx.erase(B[l].second);
                l++;
            }
            Idx.insert(B[r].second);
            jt = Idx.find(B[r].second);
            it = prev(jt, Idx);
            if (it != Idx.end() && *it < B[r].second && B[r].second - *it <= k)
                return true;
            it = next(jt, Idx);
            if (it != Idx.end() && *it > B[r].second && *it - B[r].second <= k)
                return true;
        }
        return false;
    }
};

int main() {
    Solution s;
//    int A[] = {-1, -1};
//    vector<int> v(A, A+2);
//    printf("%d\n", s.containsNearbyAlmostDuplicate(v, 1, 0)); // true
    
//    int A[] = {2, 1};
//    vector<int> v(A, A+2);
//    printf("%d\n", s.containsNearbyAlmostDuplicate(v, 1, 1)); // true
    
//    int A[] = {-1, -1};
//    vector<int> v(A, A+2);
//    printf("%d\n", s.containsNearbyAlmostDuplicate(v, 1, -1)); // false

    int A[] = {-1,2147483647};
    vector<int> v(A, A+2);
    printf("%d\n", s.containsNearbyAlmostDuplicate(v, 1, 2147483647)); // false

    return 0;
}