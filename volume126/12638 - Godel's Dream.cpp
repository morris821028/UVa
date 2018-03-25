#include <bits/stdc++.h>
using namespace std;
const int MAXS = 10005;
int greedy(char s[]) {
	int stkIdx = 1, ret = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] == '?')
			s[i] = '0';
		if (s[i] == '0') {
			if (stkIdx < 1)
				stkIdx++;
		} else {
			if (stkIdx > 0)
				stkIdx = -1;
			else
				stkIdx--;
		}
		if (stkIdx > 0)
			ret++;
	}
	if (stkIdx < 1)
		ret = 0;
	return ret;
}
int main() {
	char s[MAXS];
	while (scanf("%s", s) == 1)
		printf("%d\n", greedy(s));
	return 0;
}
/*
0
10100
??1?
?1??
1?010100
???1????
*/
