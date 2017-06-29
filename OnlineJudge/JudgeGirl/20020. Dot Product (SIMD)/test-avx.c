#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <x86intrin.h>

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

static uint32_t SSE(int N, int off, uint32_t key1, uint32_t key2) {
	uint32_t sum = 0;
	for (int i = (N>>3)<<3; i < N; i++)
		sum += encrypt(i+off, key1) * encrypt(i+off, key2);
	__m256i s_i = _mm256_set_epi32(off, off+1, off+2, off+3, off+4, off+5, off+6, off+7);
	__m256i s_4 = _mm256_set_epi32(8, 8, 8, 8, 8, 8, 8, 8);
	__m256i s_k1 = _mm256_set_epi32(key1, key1, key1, key1, key1, key1, key1, key1);
	__m256i s_k2 = _mm256_set_epi32(key2, key2, key2, key2, key2, key2, key2, key2);
	uint32_t modk1 = key1&31;
	uint32_t modk2 = key2&31;
	uint32_t cmodk1 = 32 - modk1;
	uint32_t cmodk2 = 32 - modk2;
	__m256i s_ret = _mm256_set_epi32(0, 0, 0, 0, 0, 0, 0, 0);
	N >>= 3;
	for (int it = 0; it < N; it++) {
		__m256i r_1 = _mm256_or_si256(_mm256_slli_epi32(s_i, modk1), _mm256_srli_epi32(s_i, cmodk1));
		r_1 = _mm256_xor_si256(_mm256_add_epi32(r_1, s_k1), s_k1);
		__m256i r_2 = _mm256_or_si256(_mm256_slli_epi32(s_i, modk2), _mm256_srli_epi32(s_i, cmodk2));
		r_2 = _mm256_xor_si256(_mm256_add_epi32(r_2, s_k2), s_k2);
		__m256i r_m = _mm256_mullo_epi32(r_1, r_2);
		s_ret = _mm256_add_epi32(s_ret, r_m);
		s_i = _mm256_add_epi32(s_i, s_4);
	}
	{
		static int32_t tmp[8] __attribute__ ((aligned (32)));
		_mm256_store_si256((__m256i*) &tmp[0], s_ret);
		sum += tmp[0] + tmp[1] + tmp[2] + tmp[3];
		sum += tmp[4] + tmp[5] + tmp[6] + tmp[7];
	}
	return sum;
}
int main() {
	int N;
	uint32_t key1, key2;
	while (scanf("%d %" PRIu32 " %" PRIu32, &N, &key1, &key2) == 3) {
		uint32_t sum = SSE(N, 0, key1, key2);
		printf("%" PRIu32 "\n", sum);

	}
	return 0;
}

