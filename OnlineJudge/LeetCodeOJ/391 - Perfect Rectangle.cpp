#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
	struct Rect {
		int lx, rx, ly, ry;
		Rect(int lx=0, int ly=0, int rx=0, int ry=0):
			lx(lx), ly(ly), rx(rx), ry(ry) {
		}
	};
	static bool cmpX(Rect a, Rect b) {
		if (a.lx != b.lx)
			return a.lx < b.lx;
		return a.ly < b.ly;
	}
    bool isRectangleCover(vector<vector<int>>& A) {
        int n = A.size();
        if (n == 0)
        	return true;
        int lx, ly, rx, ry, sum = 0;
        lx = ly = INT_MAX;
        rx = ry = INT_MIN;
        for (int i = 0; i < n; i++) {
            sum += (A[i][2] - A[i][0]) * (A[i][3] - A[i][1]);
            lx = min(lx, A[i][0]);
            rx = max(rx, A[i][2]);
            ly = min(ly, A[i][1]);
            ry = max(ry, A[i][3]);
        }
    	if (sum != (rx - lx) * (ry - ly))
    		return false;
    		
    	vector<Rect> B;
    	vector<int> X;
    	for (int i = 0; i < n; i++) {
    		B.push_back(Rect(A[i][0], A[i][1], A[i][2], A[i][3]));
    		X.push_back(A[i][0]);
    		X.push_back(A[i][2]);
    	}
    	sort(B.begin(), B.end(), Solution::cmpX);
    	sort(X.begin(), X.end());
    	X.resize(unique(X.begin(), X.end()) - X.begin());
    	
    	set< pair<int, int> > S;
    	set< pair<int, int> > T;
    	
    	for (int i = 0, xidx = 0; xidx < X.size(); xidx++) {
    		int spX = X[xidx];
    		while (T.size() > 0 && T.begin()->first == spX) {
    			int idx = T.begin()->second;
    			S.erase(make_pair(B[idx].ly, B[idx].ry));
    			T.erase(T.begin());
			}
    		while (i < n && B[i].lx == spX) {
    			set< pair<int, int> >::iterator it, jt;
				it = S.lower_bound(make_pair(B[i].ly, B[i].ly));
				if (it != S.begin())	it--;
				if (it != S.end() && it->first <= B[i].ly && B[i].ly < it->second)
					return false;
				jt = S.lower_bound(make_pair(B[i].ry, B[i].ry));
				if (jt != S.begin())	jt--;
				if (jt != S.end())
				if (jt != S.end() && jt->first < B[i].ry && B[i].ry <= jt->second)
					return false;
    			S.insert(make_pair(B[i].ly, B[i].ry));
    			T.insert(make_pair(B[i].rx, i));
    			i++;
			}
		}
    	return true;
    }
};

int main() {
//	int A[10][10] = {
//	  {1,1,3,3},
//	  {3,1,4,2},
//	  {3,2,4,4},
//	  {1,3,2,4},
//	  {2,3,3,4}
//	};
//	int n = 5;
//	int A[10][10] = {
//	  {1,1,2,3},
//	  {1,3,2,4},
//	  {3,1,4,2},
//	  {3,2,4,4}
//	};
//	int n = 4;
//	int A[12][10] = {{0,0,4,1},{7,0,8,2},
//	{6,2,8,3},{5,1,6,3},
//	{4,0,5,1},{6,0,7,2},
//	{4,2,5,3},{2,1,4,3},
//	{0,1,2,2},{0,2,2,3},
//	{4,1,5,2},{5,0,6,1}};
//	int n = 12;
	int A[12][10] = {{0,0,1,1},{0,1,3,2},{1,0,2,2}};
	int n = 3;
	vector< vector<int> > B;
	for (int i = 0; i < n; i++) {
		vector<int> t;
		for (int j = 0; j < 4; j++)
			t.push_back(A[i][j]);
		B.push_back(t);
	}
	Solution sol;
	int ret = sol.isRectangleCover(B);
	printf("%d\n", ret);
	return 0;
}

