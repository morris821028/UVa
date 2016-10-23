#include <bits/stdc++.h>
using namespace std;

const int n = 10000000;
int m2[1024] = {};
void run() {
	for (int i = 0; i < 30; i++)
		m2[i*i] = 1;
	int cnt = 0;
	for (long long i = 16; i < n; i++) {
		long long t = i*i;
		int sum = 0;
		while (t)
			sum += t%10, t /= 10;
		if (m2[sum] == 1) {
			cnt++;
			if (cnt == 7) {
				printf("%d\n", i);
				exit(0);
			}
		} else {
			cnt = 0;
		}
	}
}
int main() {
//	run();
	for (int i = 10005-6; i <= 10005; i++) {
		printf("%d %lld\n", i, 1LL*i*i);
	}
	return 0;
}

