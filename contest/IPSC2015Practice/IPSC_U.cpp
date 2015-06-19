#include <bits/stdc++.h> 
using namespace std;

double get(int a, int b, int c) {
	double r1 = (1.0 * a / (a + b)) * (1.0 * b / (a + b - c - 1));  
    double r2 = (1.0 * b / (a + b)) * (1.0 * (b - 1) / (a + b - c - 1));   
    return r1 + r2;
}
double getTired(int n) {
	double r1 = 1.0 * (n-1) / n * (1.0 / (n-1) + 1.0 * (n-2) / (n-1) / (n-1));
	double r2 = 1.0 * 1 / n * (1.0 / (n-1));
    return r1 + r2;
}
int main() {
	int testcase;
	int n;
	double p;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %lf", &n, &p);
		double v = get(n-1, 1, 1) * (1 - p) + getTired(n) * p;
		printf("%.10lf\n", v);
	}
	return 0;
}
