#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "utils.h"

void output(uint32_t presum[], int n) {
	uint32_t hash = 0;
	for (int i = 1; i <= n; i++)
		hash += presum[i] * i;
	printf("%" PRIu32 "\n", hash);
}

