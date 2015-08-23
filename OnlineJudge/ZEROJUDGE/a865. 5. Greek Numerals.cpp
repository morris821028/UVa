#include <bits/stdc++.h>
using namespace std;

const char text[] = "ABGDE#ZYHIKLMNXOPQRSTUFC$W3";
const int C[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900};
int main() {
	int M[256];
	char s[128];
	for (int i = 0; text[i]; i++)
		M[text[i]] = C[i];
	while (scanf("%s", s) == 1 && s[0] != '.') {
		int n = 0;
		for (int i = 0; s[i]; i++)
			n += M[s[i]];
		printf("%d\n", n);
	}
	return 0;
}
