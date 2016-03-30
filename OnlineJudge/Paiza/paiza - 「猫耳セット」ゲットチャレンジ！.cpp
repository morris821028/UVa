#include <cstdio>
#include <cstring>
using namespace std;

int main() {
	char s[128], t[128] = "cat";
	int m = strlen(t);
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int ok = 1;
			for (int j = 0; j < m && ok; j++)
				ok &= t[j] == s[i+j];
			ret += ok;
		}
		printf("%d\n", ret);
	}
	return 0;
}
