#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
	int cases = 0;
	int n, m, key;
	scanf("%d %d %d", &n, &m, &key);
	for (int it = 0; it < m; it++) {
		int ret = run(n, key);
		printf("Case #%d: %d\n", ++cases, ret);
		key++;
	}
	return 0;
}
