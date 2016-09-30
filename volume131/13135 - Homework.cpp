#include <bits/stdc++.h>
using namespace std;

int main() {
	map<int, int> R;
	for (int i = 0; ; i++) {
		int ways = (i+2)*(i+1)/2;
		if (ways > 50000000)
			break;
		R[ways] = i;
	}
	
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		if (R.count(n))
			printf("%d\n", R[n]);
		else
			printf("No solution\n");
	}
	return 0;
}

