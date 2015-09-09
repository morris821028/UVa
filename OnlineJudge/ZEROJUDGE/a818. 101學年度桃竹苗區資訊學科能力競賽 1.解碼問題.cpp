#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m, x;
	int A[32];
	char s[32];
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &x), A[x] = i;
	scanf("%s", s+1);
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		char s2[32];
		for (int j = 1; j <= n; j++)
			s2[A[j]] = s[j];
		for (int j = 1; j <= n; j++)
			s[j] = s2[j];
	}	
	for (int i = 1; i <= n; i++)
		putchar(s[i]);
	puts("");
	return 0;
}
/*
10
8 9 5 7 10 1 2 4 6 3
as*Ittca*i
2
*/

