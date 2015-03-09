#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	char s[32767];
	int A[32767] = {};
	while (gets(s)) {
		int cnt = 0, n = strlen(s);
		for (int i = 0; i <= n; i++) {
			if (s[i] == 'x')
				cnt++;
			else
				A[cnt]++, cnt = 0;
		}
	}
	int n = 0, m = 0;
	for (int i = 3; i < 1024; i+=2) {
		n += A[i] /6;
		if (A[i])	m = i;
	}
	if (n == 0)
		puts("0");
	else
		printf("%d %d\n", n, m);
	return 0;
}
