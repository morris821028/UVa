#include <stdio.h>
#include <string.h>

void buildSG() { // observe rule
	int mex[1024] = {}, SG[50];
	SG[0] = 0;
	for (int i = 1; i < 50; i++) {
		memset(mex, 0, sizeof(mex));
		for (int j = 1; j <= i/2; j++)
			mex[SG[i - j]] = 1;
		int sg = 0;
		for (sg = 0; mex[sg]; sg++);
		SG[i] = sg;
		printf("%d : %d\n", i, SG[i]);
	}
}

long long SG(long long x) {
	return x%2 == 1 ? SG(x/2) : x/2; 
}
int main() {
//	buildSG();
	int testcase, n;
	long long x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long ret = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			ret ^= SG(x);
		}
		puts(ret ? "YES" : "NO");
	}
	return 0;
}
