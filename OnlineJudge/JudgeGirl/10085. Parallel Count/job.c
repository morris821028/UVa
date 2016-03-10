#include "utils.h"

int ret[128];
int run(int n, int key) {
	int sum = 0;
	f(n, key, ret+0, ret+16, ret+32, ret+48);
	sum = ret[0] + ret[16] + ret[32] + ret[48];
	return sum;
}
