#include "array.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define OUTOFBOUND -2147483648
#define HAVENOTSET -2147483647
#define SETSUCCESS 1
void test_specall() {
	int n, l, r;
	int cmds, cmd, aid;
	int index, value;
	scanf("%d", &n);
	ARRAY *a = (ARRAY *) malloc(sizeof(ARRAY)*n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &l, &r);
		init(&a[i], l, r);
	}
	scanf("%d", &cmds);
	for (int i = 0; i < cmds; i++) {
		scanf("%d %d", &cmd, &aid);
		if (cmd == 1) {
			print(&a[aid]);
		} else if (cmd == 2) {
			scanf("%d %d", &index, &value);
			int ret = set(&a[aid], index, value);
			printf("ARRAY ID %d, set(%d, %d) %s\n", aid, index, value, 
				ret == SETSUCCESS ? "SUCCESS" : (ret == OUTOFBOUND ? "OUTOFBOUND" : "HAVENOTSET"));
		} else if (cmd == 3) {
			scanf("%d", &index);
			int ret = get(&a[aid], index);
			printf("ARRAY ID %d, get(%d) ", aid, index);
			if (ret == OUTOFBOUND)	
				printf(": OUTOFBOUND\n");
			else if (ret == HAVENOTSET)
				printf(": HAVENOTSET\n");
			else
				printf("= %d\n", ret);
		} else if (cmd == 4) {
			sort(&a[aid]);
		} else {
			assert(0);
		}
	}
}
int main() {
	int spec = 0;
	void (*FUNC[])() = {test_specall};
	FUNC[spec]();
	return 0;
}
/*
3
0 10
-5 0
1000 2000
999
1 0
2 0 2 4
2 0 3 9
2 0 5 25
1 0
2 1 -1 -1
2 1 -3 -9
2 1 0 0
1 1
3 0 5
3 1 -3
3 0 -1
3 1 1
2 0 -1 3
2 1 5 6
3 0 4
4 0
1 0
4 1
1 1
2 1 -3 514
1 1
4 1
1 1
*/
