#include <bits/stdc++.h> 
using namespace std;

int safe(int a[], int b[], int n) {
	int f = 1;
	for (int i = 0; i <= n; i++) {
		if (a[i] == 4) {
			a[i]--;
			b[i]++;
			f = 0;
			break;
		}
	}
	if (f == 1)
	for (int i = 0; i <= n; i++) {
		if (b[i] == 4) {
			a[i]--;
			b[i]++;
			f = 0;
			break;
		}
	}
	for (int i = 0; i <= n; i++) {
		if (b[i] >= 10)
			b[i+1] /= 10, b[i] %= 10;
	}
	return f;
}
int main() {
	int testcase, cases = 0;
	char s[128];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", &s);
		printf("Case #%d: ", ++cases);
		int a[128] = {}, b[128] = {};
		int n = strlen(s);
		for (int i = n-1, j = 0; i >= 0; i--, j++)
			a[j] = s[i] - '0';
		int x = 0;
		for (int i = n-1; i >= 0; i--) {
			x = x*10 + a[i];
			a[i] = x/2, x %= 2;
		}
		memcpy(b, a, sizeof(a));
		if (x == 1)
			b[0]++;
		for (int i = 0; i <= n; i++) {
			if (b[i] >= 10)
				b[i+1] += b[i]/10, b[i] %= 10;
		}
		
		while (!safe(a, b, n));
		
		int ia = n+1, ib = n+1;
		while (ia > 0 && a[ia] == 0)
			ia--;
		while (ia >= 0)
			printf("%d", a[ia]), ia--;
		printf(" ");
		while (ib > 0 && b[ib] == 0)
			ib--;
		while (ib >= 0)
			printf("%d", b[ib]), ib--;
		printf("\n");
	}
	return 0;
}
