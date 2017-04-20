#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	int cost[128][3] = {};
	cost['M'][0] = cost['R'][0] = cost['B'][0] = cost['V'][0] = 1;
	cost['Y'][1] = cost['R'][1] = cost['B'][1] = cost['G'][1] = 1;
	cost['C'][2] = cost['V'][2] = cost['B'][2] = cost['G'][2] = 1;
	scanf("%d", &testcase);
	while (testcase--) {
		static char s[131072];
		int src[3];
		scanf("%d %d %d", src, src+1, src+2);
		scanf("%s", s);
		for (int i = 0; s[i]; i++) {
			src[0] -= cost[s[i]][0];
			src[1] -= cost[s[i]][1];
			src[2] -= cost[s[i]][2];
		}
		int ok = src[0] >= 0 && src[1] >= 0 && src[2] >= 0;
		if (ok)
			printf("YES %d %d %d\n", src[0], src[1], src[2]);
		else
			puts("NO");
	}
	return 0;
}

