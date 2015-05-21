#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

char s[65536][8];
int toIndex(int x) {
	if (x <= '9')
		return x - '0';
	return x + 10 - 'A';
}
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		int ret = 0;
		int same = 4 - m, diff = m;
		for (int i = 0; i < n; i++) {
			scanf("%s", s[i]);
			
			for (int j = 0; j < i; j++) {
				int d = 0;
				for (int k = 0; k < 4; k++)
					d += s[i][k] != s[j][k];
				if (d == m)
					ret++;
			}
		}
		
		printf("%d\n", ret);
	}
	return 0;
}
/*
1
6 2
ABCD
BC0D
DCAB
A5CF
ABFF
ABCB 
*/
