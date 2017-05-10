#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	static char s[1048576];
	const int DC = 5;
	const uint64_t TDC = 100000;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int64_t A[65536] = {};
		int n = strlen(s);
		int m = (n+DC-1)/DC;
		assert(m < 65536);
		for (int i = 0, pos = n-1; i < m; i++) {
			uint64_t v = 0, t = 1;
			for (int k = 0; k < DC && pos >= 0; k++, pos--)
				v = v + (s[pos]-'0')*t, t *= 10;
			A[i] = v;
		}
		A[0]--;
		for (int i = 0; i < m; i++) {
			while (A[i] < 0)
				A[i] += TDC, A[i+1]--;
		}
		
		for (int i = 0; i < 19*19; i++) {
			uint64_t v = 0;
			for (int j = m-1; j >= 0; j--)
				v = (v*TDC + A[j])%3;
			putchar(".WB"[v]);
			if (i%19 == 18)
				puts("");
			uint64_t t = 0;
			for (int j = m-1; j >= 0; j--) {
				t = (t*TDC + A[j]);
				A[j] = t/3, t %= 3;
			}
		}
		puts("");
	}
	return 0;
}

