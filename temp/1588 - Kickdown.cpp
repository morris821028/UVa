#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	char s1[128], s2[128];
	while (scanf("%s %s", s1, s2) == 2) {
		int n1 = strlen(s1), n2 = strlen(s2);
		int ret = n1 + n2;
		for (int i = -n2; i <= n1; i++) {
			int ok = 1;
			for (int j = 0; j < n2 && ok; j++) {
				if (i + j >= 0 && i + j < n1)
					ok &= s1[i+j] - '0' + s2[j] - '0' <= 3;
			}
			if (ok)
				ret = min(ret, max(n1, i + n2) - min(i, 0));
		}
		printf("%d\n", ret);
	}
	return 0;
}
