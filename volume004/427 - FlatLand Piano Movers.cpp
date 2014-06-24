#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;
// http://www.cnblogs.com/newpanderking/archive/2011/08/25/2153777.html
const double pi = acos(-1);
#define eps 1e-6 
double ternary_search(double H, double W, double X, double Y) {
	double l = 0, r = pi /2, mid, midmid;
	double s1, h1, s2, h2;
	while(fabs(l - r) > eps) {
		mid = (l + r) /2;
		midmid = (mid + r) /2;
		s1 = H * cos(mid) + W * sin(mid) - X;
		h1 = s1 * tan(mid) + W * cos(mid);
		s2 = H * cos(midmid) + W * sin(midmid) - X;
		h2 = s2 * tan(midmid) + W * cos(midmid);
		if(h1 < h2)
			l = mid;
		else
			r = mid;
	}
	return h1;
}
int main() {
	char line[1024];
	while(gets(line)) {
		stringstream sin(line);
		string token;
		sin >> token;
		double H, W, X, Y;
		sscanf(token.c_str(), "%lf,%lf", &H, &W);
		if(H < W)
			swap(H, W);
		while(sin >> token) {
			sscanf(token.c_str(), "%lf,%lf", &X, &Y);
			double h = ternary_search(H, W, X, Y);
			printf("%c", h <= Y ? 'Y' : 'N');
		}
		puts("");
	}
	return 0;
}
