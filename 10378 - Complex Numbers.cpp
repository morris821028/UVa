#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
using namespace std;
#define eps 1e-6
bool cmp(pair<double, double> a, pair<double, double> b) {
	if(fabs(a.first - b.first) > eps)
		return a.first > b.first;
	if(fabs(a.second - b.second) < eps)
		return false;
	return a.second > b.second;
}
int main() {
    char s[50];
    const double pi = acos(-1);
    int n, i, cases = 0;
    double a, b;
    while(scanf("%s %d", s, &n) == 2) {
        if(sscanf(s, "%lf+%lfi", &a, &b) == 2)
            {}
        else
            sscanf(s, "%lf-%lfi", &a, &b), b = -b;
        double theta = atan2(b, a);
        double k = pow(sqrt(a*a+b*b), 1.0/n);
        double px, py;
        pair<double, double> D[128];
        for(i = 0; i < n; i++) {
            px = k*cos((theta + i*2*pi)/n);
            py = k*sin((theta + i*2*pi)/n);
            D[i] = make_pair(px, py);
        }
        sort(D, D+n, cmp);
        printf("Case %d:\n", ++cases);
        for(i = 0; i < n; i++) {
        	if(fabs(D[i].first) < 0.0005)	D[i].first = 0;
        	if(fabs(D[i].second) < 0.0005)	D[i].second = 0;
        	printf("%.3lf%+.3lfi\n", D[i].first, D[i].second);
        }
        puts("");
    }
    return 0;
}
