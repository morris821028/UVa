#include <stdio.h> 
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int n;
	char s[1024];
	while (scanf("%d", &n) == 1 && n) {
		vector<string> A;
		for (int i = 0; i < n; i++)
			scanf("%s", s), A.push_back(s);
		sort(A.begin(), A.end());
		string p = A[n/2-1], q = A[n/2];
		if (p.length() < q.length()) {
			for (int i = 0; i < p.length(); i++) {
				if (p[i] == q[i] || i == p.length() - 1) // equal.
					putchar(p[i]);
				else { // less
					putchar(p[i] + 1);
					break;
				}
			}
		} else {
			for (int i = 0; i < q.length(); i++) {
				if (p[i] == q[i])
					putchar(p[i]);
				else {
					if (i == q.length() - 1) {
						if (i == p.length() - 1) { // equal
							putchar(p[i]);
							break;
						}
						if (p[i] + 1 != q[i]) {
							putchar(p[i] + 1);
							break;
						} else {
							putchar(p[i]);
							for (int j = i+1; j < p.length(); j++) {
								if (j == p.length() - 1) // equal
									putchar(p[j]);
								else if (p[j] != 'Z') {
									putchar(p[j] + 1);
									break;
								} else
									putchar(p[j]);
							}
							break;
						}
					} else {
						putchar(p[i] + 1);
						break;
					}
				}
			}
		}
		puts("");
	} 
	return 0;
}
/*
4
FRED
SAM
JOE
MARGARET
2
FRED
FREDDIE
2
JOSEPHINE
JERRY
2
LARHONDA
LARSEN
2
ABA
AC
2
ABCA
AC
2
ABZA
AC
2
ABZCA
AC
0
*/
