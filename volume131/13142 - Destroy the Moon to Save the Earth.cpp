#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		double T, S, D;
		scanf("%lf %lf %lf", &T, &S, &D);
		T = T*60*60*24;
		D = D*1000*100*10;
		double v = D/T;
		if (floor(v) > 0)
			printf("Remove %d tons\n", (int) floor(v));
		else
			printf("Add %d tons\n", (int) floor(abs(v)));
	}
	return 0;
}

