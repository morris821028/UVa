#include <bits/stdc++.h> 
using namespace std;

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
public:
    vector<Interval> insert(vector<Interval>& A, Interval B) {
    	vector<Interval> ret;
    	int in = 0;
        for (int i = 0; i < A.size(); i++) {
        	if (!in && A[i].start > B.end)
        		in = 1, ret.push_back(B);
        	if (min(A[i].end, B.end) >= max(A[i].start, B.start)) {
        		in = 1;
        		int l = min(A[i].start, B.start), r = max(A[i].end, B.end);
        		while (i < A.size() && r >= A[i].start) {
        			r = max(r, A[i].end);
        			i++;
        		}
        		ret.push_back(Interval(l, r));
        		while (i < A.size()) {
        			ret.push_back(A[i]);
        			i++;
        		}
        		break;
        	} else {
        		ret.push_back(A[i]);
			} 
        }
        if (!in)	ret.push_back(B);
        return ret;
    }
};
int main() {
	Solution s;
	int A[][2] = {{1,2},{3,5},{6,7},{8,10},{12,16}};
	vector<Interval> v;
	for (int i = 0; i < 5; i++) {
		v.push_back(Interval(A[i][0], A[i][1]));
	}
	s.insert(v, Interval(4, 9));
	return 0;	
}
