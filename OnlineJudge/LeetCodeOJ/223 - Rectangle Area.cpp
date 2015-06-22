#include <bits/stdc++.h> 
using namespace std;

class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
    	if (A > C)	swap(A, C);
    	if (B > D)	swap(B, D);
    	if (E > G)	swap(E, G);
    	if (F > H)	swap(F, H);
        long long areaX, areaY, common;
        areaX = (long long) (C - A) * (D - B);
        areaY = (long long) (G - E) * (H - F);
        common = 0;
        
        int lx, ly, rx, ry;
        lx = max(A, E), rx = min(C, G);
        ly = max(B, F), ry = min(D, H);
        if (lx < rx && ly < ry)
            common = (long long) (rx - lx) * (ry - ly);
        return areaX + areaY - common;
    }
};

int main() {
	Solution s;
	s.computeArea(-2, -2, 2, 2, -3, 3, -4, 4);
	return 0;
}
