#include <bits/stdc++.h>
using namespace std;

int main() {
	char s1[1024], s2[1024];
	while (scanf("%s %s", s1, s2) == 2)
		printf("%d\n", (((s2[0] - 'A') - (s1[0] - 'A'))%26 + 26)%26);
	return 0;
}
