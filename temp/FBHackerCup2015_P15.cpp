#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
// $ awk '{ sub("\r$", ""); print }' out.txt > output.txt 
int main() {
	freopen("cooking_the_books.txt", "r", stdin);
	freopen("out.txt", "w+", stdout); 
	int testcase, cases = 0;
	char s[64];
	scanf("%d", &testcase);
	while (testcase--) {
		long long ret1, ret2, tmp;
		scanf("%s", s);
		sscanf(s, "%lld", &ret1);
		sscanf(s, "%lld", &ret2);
		int n = strlen(s);
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				swap(s[i], s[j]);
				sscanf(s, "%lld", &tmp);
				if (s[0] != '0') { 
					ret1 = min(ret1, tmp);
					ret2 = max(ret2, tmp);
				} 
				swap(s[i], s[j]);
			}
		}
		printf("Case #%d: %lld %lld", ++cases, ret1, ret2);
		putchar('\n');
	}
	return 0;
}
