#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main() {
	char s[1024];
	while (scanf("%s", s) == 1) {
		int n = strlen(s);
		int C[128] = {};
		for (int i = 0; i < n; i++)
			C[s[i]]++;
		printf("%d\n", min(C['c'], min(C['a'], C['t'])));
		int ex = max(C['c'], max(C['a'], C['t']));
		printf("%d\n", ex - C['c']);
		printf("%d\n", ex - C['a']);
		printf("%d\n", ex - C['t']);
	}
	return 0;
}

