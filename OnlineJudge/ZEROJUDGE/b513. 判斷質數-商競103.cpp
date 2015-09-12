#include <bits/stdc++.h>
using namespace std;

int isPrime(int n) {
	for (int i = 2; i*i <= n; i++)
		if (n%i == 0)
			return 0;
	return 1;
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		puts(isPrime(n) ? "Y" : "N");
	}
	return 0;
}