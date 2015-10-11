#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		string line;
		getline(cin, line);
		stringstream sin(line);
		long long sum = 0, x;
		while (sin >> x)
			sum += x;
		printf("%lld\n", sum);
	}
	return 0;
}

