#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
#include "VSQRT.h"
static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

static float a[1048576], b[1048576]; 
int main() {
	int N, key;
	while (scanf("%d %d", &N, &key) == 2) {
		for (int i = 0; i < N; ++i) 
			a[i] = encrypt(i, key);

		for (int it = 0; it < 20; it++)
		{  
			memcpy(b, a, sizeof(a[0])*N);
			for (int i = 0; i < 10; i++)
				sqrt2(b, b+N);
			float sum = 0;
			for (int i = 0; i < N; i++)
				sum += b[i];
			printf("%f\n", sum);
		}  
	}
	return 0;
}

