#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

static uint32_t f(int N, int off, uint32_t key1, uint32_t key2) {
	uint32_t sum = 0;
	for (int i = 0, j = off; i < N; i++, j++) 
		sum += encrypt(j, key1) * encrypt(j, key2);
	return sum;
}
int main() {
	int N;
	uint32_t key1, key2;
	while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {
		uint32_t sum = f(N, 0, key1, key2);
		printf("%" PRIu32 "\n", sum);
	}
	return 0;
}

