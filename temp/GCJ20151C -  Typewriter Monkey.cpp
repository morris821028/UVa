#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int K, L, S;
char keyboard[128], target[128];
double solve() {
	if (L > S)
		return 0;
	int a[128] = {};
	for (int i = 0; i < K; i++)
		a[keyboard[i]]++;
	for (int i = 0; i < L; i++)
		if (a[target[i]] == 0)
			return 0;
			
	double mx_banana = S / L, expect = 1;
	for (int i = 1; i < L; i++) {
		int ok = 1;
		for (int j = 0; target[i+j] && j < L; j++)
			ok &= target[j] == target[i+j];
		if (ok) {
			mx_banana = 1 + (S - L) / (i); 
			break;
		}
	}
	for (int i = 0; i < L; i++)
		expect = (expect * a[target[i]]) / K;
	return mx_banana - expect * (S - L + 1);
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &K, &L, &S);
		scanf("%s %s", keyboard, target);
		
		double ret = solve();
		printf("Case #%d: %lf\n", ++cases, ret);
	} 
	return 0;
}

