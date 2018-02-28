#include <bits/stdc++.h>
using namespace std;
static char s[4096], *ptr;
int dfs(int dep) {
	int z = 0, o = 0;
	int ret = dep;
	for (int i = 0; i < 4; i++) {
		if (*ptr == '0') {
			z++, ptr++;
		} else if (*ptr == '1') {
			o++, ptr++;
		} else if (*ptr == '2') {
			ptr++;
			int t = dfs(dep+1);
			if (t < 0)
				return -1;
			ret = max(ret, t);
		} else {
			return -1;
		}
	}
	if ((z == 0 || o == 0) && z+o == 4)
		return -1;
	if (dep == 1 && *ptr != '\0')
		return -1;
	return ret;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		if (s[0] != '2') {
			if (s[1] == '\0')
				puts("2^0*2^0");
			else
				puts("Not Possible");
		} else {
			ptr = s+1;
			int ret = dfs(1);
			if (ret < 0)
				puts("Not Possible");
			else
				printf("2^%d*2^%d\n", ret, ret);
		}
	}
	return 0;
}
/*
4
2022111011111
2112002000001
20102102101010
1
*/
