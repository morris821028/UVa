#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "elevator.h"

int main() {
	int testcase;
	assert(scanf("%d", &testcase) == 1);
	while (testcase--) {
		int u, d, F;
		char cmd[MAXL+5];
		assert(scanf("%d %d %d", &u, &d, &F) == 3);
		assert(scanf("%s", cmd) == 1);
		Elevator *e = newElevator(u, d, F);
		for (int i = 0; cmd[i]; i++) {
			int ret;
			if (cmd[i] == 'U') {
				ret = up(e);
			} else {
				ret = down(e);
			}
			if (ret == -1) {
				printf("Broken\n");
				break;
			}

			if (ret == 1)
				printf("Valid %d\n", getPosition(e));
			else if (ret == 0)
				printf("Invalid\n");
			else
				assert(0);
		}
		for (int i = 1; i <= F; i++) {
			if (visited(e, i))
				printf("%d\n", i);
		}
		free(e);
	}
	return 0;
}
