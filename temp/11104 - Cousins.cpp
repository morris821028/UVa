#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	char a[128], b[128];
	while (scanf("%s %s", a, b) == 2 && a[0] != '0') {
		int dp[128][128] = {};
		int la = strlen(a), lb = strlen(b);
		for (int i = 0; i < la; i++)
			for (int j = 0; j < lb; j++)
				if (a[i] == b[j])
					dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j] + 1);
				else
					dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
		int lcs = dp[la][lb];
		int ret = 1, len = lcs;
		if (la > lb)	swap(la, lb);
		while (len + len < lb) {
			len += la, la <<= 1;
			ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
condition of first cousin for string a, b
* LCS(a, b) = maximum length LCS.
=> check if LCS(a, b) * 2 > a.len && LCS(a, b) * 2 > b.len, then output first cousin.
=> if not, we know string a and string xa which length is LCS(a, b) + a.len.

xa : __LCS(a, b)__ + a.str
	 ^^^^^^^^^^^^^ // any letters., LCS(a, xa) = a.len, LCS(a, b) <= a.len, so xa and a are first cousins.
and so on, make string x2a which length is LCS(a, b) + 3 * a.len
x2a : __LCS(a, b)__ + a.str + a.str + a.str
	  ^^^^^^^^^^^^^^^^^^^^^ // any letters., LCS(a, xa) = 2 * a.len, so xa and x2a are first cousisn.
above xa, x2a shown by letter consist, not order.
when x?a can become string b first cousin ? => __LCS(a, b)__ + (? * a.str) = half of b.
*/
