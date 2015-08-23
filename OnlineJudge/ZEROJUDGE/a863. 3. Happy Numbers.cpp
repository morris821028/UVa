#include <bits/stdc++.h>
using namespace std;

int test(int n) {
	char buf[32];
	set<int> C;
	while (true) {
		sprintf(buf, "%d", n);
		int m = 0;
		for (int i = 0; buf[i]; i++)
			m += (buf[i] - '0')*(buf[i] - '0');
		if (m == 1)
			return 1;
		if (C.count(m))
			return 0;
		C.insert(m), n = m;
	}
	return 0;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		if (test(n))
			printf("%d is a happy number\n", n);
		else
			printf("%d is an unhappy number\n", n);
	}
	return 0;
}
