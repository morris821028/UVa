#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

long long rnum, f[32] = {1};
int main() {
	for (int i = 1; i < 32; i++) // f[n] = sigma(C(n, i) * i!) = f[n-1] * n + 1;
		f[i] = f[i-1] * i + 1;
	char s[32], dictionary[32];
	int nextTest;
	scanf("%s", s);
	do {
		int n = strlen(s), used[26] = {};
		long long ways = 0;
		strcpy(dictionary, s);
		sort(dictionary, dictionary + n);
		for (int i = 0, l = n - 1; i < n; i++, l--) {
			int cnt = 0;
			for (int j = 0; j < n && dictionary[j] != s[i]; j++)
				if (used[j] == 0)
					cnt ++;
			used[s[i] - 'a'] = 1;
			ways += f[l] * cnt + 1;
		}
		printf("%lld\n", ways);
		while(nextTest) {
			nextTest = scanf("%s", s) == 1;
			if (!nextTest)	break;
			if (s[0] >= 'a' && s[0] <= 'z') {
				break;
			} else {
				sscanf(s, "%lld", &rnum);
				int used[26] = {};
				for (int i = n - 1; i >= 0 && rnum; i--) {
					int p = (rnum-1) / f[i], q = 0, j;
					rnum = (rnum-1) % f[i];
					for (j = 0; j < n && p != q; j++) {
						if (used[j] == 0)
							q++;
					}							
					while (used[j])	j++;
						used[j] = 1;
					printf("%c", dictionary[j]);
				}
				puts("");
			}
		}
	} while (nextTest);
	return 0;
}
