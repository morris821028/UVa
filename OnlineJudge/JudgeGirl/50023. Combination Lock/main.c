#include "locker.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define UNLOCK 0
#define LOCKED 1
#define OPERROR -1
#define PEERROR 10000

void test_spec0() {
	int n, cmds, cmd, lid, combination;
	scanf("%d", &n);
	Lock *locker[32];
	for (int i = 0; i < n; i++)
		locker[i] = (Lock *) malloc(sizeof(Lock));
	for (int i = 0; i < n; i++)
		init(locker[i]);
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d %d", &cmd, &lid);
		if (cmd == 1) {
			int ret = isLocked(locker[lid]);
			printf("isLocked %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" : 
				((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
		} else {
			assert(0);
		}
	}
}
void test_spec1() {
	int n, cmds, cmd, lid, combination;
	scanf("%d", &n);
	Lock *locker[32];
	for (int i = 0; i < n; i++)
		locker[i] = (Lock *) malloc(sizeof(Lock));
	for (int i = 0; i < n; i++)
		init(locker[i]);
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d %d", &cmd, &lid);
		if (cmd == 1) {
			int ret = isLocked(locker[lid]);
			printf("isLocked %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" : 
				((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
		} else if (cmd == 2) {
			scanf("%d", &combination);
			int ret = lock(locker[lid], combination);
			assert(ret != PEERROR);
			if (ret == OPERROR)
				printf("lock %d %s\n", lid, "NOTHING HAPPENED");
			else if (ret == PEERROR)
				printf("lock %d %s\n", lid, "INVALID COMBINATION");
			else
				printf("lock %d new pwd: %d\n", lid, ret);
		} else {
			assert(0);
		}
	}
}
void test_spec2() {
	int n, cmds, cmd, lid, combination;
	scanf("%d", &n);
	Lock *locker[32];
	for (int i = 0; i < n; i++)
		locker[i] = (Lock *) malloc(sizeof(Lock));
	for (int i = 0; i < n; i++)
		init(locker[i]);
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d %d", &cmd, &lid);
		if (cmd == 1) {
			int ret = isLocked(locker[lid]);
			printf("isLocked %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" : 
				((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
		} else if (cmd == 2) {
			scanf("%d", &combination);
			int ret = lock(locker[lid], combination);
			if (ret == OPERROR)
				printf("lock %d %s\n", lid, "NOTHING HAPPENED");
			else if (ret == PEERROR)
				printf("lock %d %s\n", lid, "INVALID COMBINATION");
			else
				printf("lock %d new pwd: %d\n", lid, ret);
		} else {
			assert(0);
		}
	}
}
void test_spec3() {
	int n, cmds, cmd, lid, combination;
	scanf("%d", &n);
	Lock *locker[32];
	for (int i = 0; i < n; i++)
		locker[i] = (Lock *) malloc(sizeof(Lock));
	for (int i = 0; i < n; i++)
		init(locker[i]);
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d %d", &cmd, &lid);
		if (cmd == 1) {
			int ret = isLocked(locker[lid]);
			printf("isLocked %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" : 
				((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
		} else if (cmd == 2) {
			scanf("%d", &combination);
			int ret = lock(locker[lid], combination);
			if (ret == OPERROR)
				printf("lock %d %s\n", lid, "NOTHING HAPPENED");
			else if (ret == PEERROR)
				printf("lock %d %s\n", lid, "INVALID COMBINATION");
			else
				printf("lock %d new pwd: %d\n", lid, ret);
		} else if (cmd == 3) {
			scanf("%d", &combination);
			int ret = unlock(locker[lid], combination);
			printf("unlock %d %s\n", lid, ret == OPERROR ? "NOTHING HAPPENED" : 
				((ret == LOCKED) ? "LOCKED" : (ret == UNLOCK ? "UNLOCK" : "INVALID VALUE")));
		} else {
			assert(0);
		}
	}
}


int main() {
	int spec;
	void (*FUNC[])() = {test_spec0, test_spec1, test_spec2, test_spec3};
	while (scanf("%d", &spec) == 1) {
		FUNC[spec]();
	}
	return 0;
}
/*
3
3 12
2 0 9999
3 1 1234
1 0
1 2
3 0 1234
3 0 10000
2 0 514
3 0 9999
2 0 514
3 0 9999
1 0
1 1
*/
