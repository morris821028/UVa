#include <bits/stdc++.h> 
using namespace std;

int main() {
	char s[1024];
	while (scanf("%s", s) == 1) {
		int A[1024] = {}, m, n = 0;
		if (scanf("%s", s) != 1)
			return 0;
		m = strlen(s);
		reverse(s, s + m);
		for (int i = 0; i < m; i++)
			A[i] += s[i] - 'A';
		n = max(n, m);
		
		if (scanf("%s", s) != 1)
			return 0;
		m = strlen(s);
		reverse(s, s + m);
		for (int i = 0; i < m; i++)
			A[i] += s[i] - 'A';
		n = max(n, m);
		
		for (int i = 0; i < n; i++) {
			if (A[i] >= 26) {
				A[i+1] += A[i]/26;
				A[i] %= 26;
				n = max(n, i+2);
			}
		}
		
		for (int i = n-1; i >= 0; i--)
			putchar(A[i] + 'A');
		puts("");
	}
	return 0;
}
