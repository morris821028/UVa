#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (getchar() != '\n');
	while (testcase--) {
		char cmd[16];
		int fish = 0, bait = 0, NOP = 0;
		int ret = 0;
		while (gets(cmd) && cmd[0] != '\0') {
			if (!strcmp(cmd, "fish")) {
				if (bait >= 2 && ((NOP >= 7 && fish >= 2) || ret == 0)) {
					NOP = 0, fish = 0;
					bait -= 2;
					ret++;
				} else {
					fish++;
				}
				NOP++;
			} else if (!strcmp(cmd, "bait")) {
				bait = min(bait+1, 6);
				NOP++;
			} else if (!strcmp(cmd, "lunch")) {
				NOP++;
			}
		}
		printf("%d\n", ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1

fish
fish
lunch
bait
fish
bait
fish
bait
bait
fish
fish
fish
fish
lunch
lunch
lunch
lunch
fish
fish
fish
*/
