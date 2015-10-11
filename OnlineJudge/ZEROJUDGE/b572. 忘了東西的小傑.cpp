#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int s1, s2, H, M;
		scanf("%d %d", &H, &M);
		s1 = H * 60 + M;
		scanf("%d %d", &H, &M);
		s2 = H * 60 + M;
		scanf("%d", &M);
		puts(s2 - s1 >= M ? "Yes" : "No");
	}
	return 0;
}

