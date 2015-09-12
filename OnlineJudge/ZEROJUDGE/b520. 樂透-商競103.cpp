#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		int R[128] = {}, x;
		char s1[1024], s2[1024];
		fgets(s1, 1024, stdin);
		fgets(s2, 1024, stdin);
		for (int i = 0; s1[i]; i++) {
			if (s1[i] == ',')
				s1[i] = ' ';
		}
		for (int i = 0; s2[i]; i++) {
			if (s2[i] == ',')
				s2[i] = ' ';
		}
		stringstream sin1(s1), sin2(s2);
		while (sin1 >> x)
			R[x] = 1;
		int ret = 0;
		while (sin2 >> x)
			ret += R[x];
		printf("%d\n", ret);
	}
	return 0;
}