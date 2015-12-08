#include <stdio.h>
#include <string.h>
#include "expression.h"

char buf[1<<20];
int main() {
	while (scanf("%s", buf) == 1) {
		int ret = expression(buf);
		printf("%d\n", ret);
	}
	return 0;
}
/*
(4 + 3)
((3 * 4) + 5)
  - 5  
((3 + 3) / (2 - 2))
-(3+4)(4+6)
*/
