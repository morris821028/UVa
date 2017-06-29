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
	for (int i = N/4*4; i < N; i++)
		sum += encrypt(i+off, key1) * encrypt(i+off, key2);
	__m128i s_i = _mm_set_epi32(off, off+1, off+2, off+3);
	__m128i s_4 = _mm_set_epi32(4, 4, 4, 4);
	__m128i s_k1 = _mm_set_epi32(key1, key1, key1, key1);
	__m128i s_k2 = _mm_set_epi32(key2, key2, key2, key2);
	uint32_t modk1 = key1&31;
	uint32_t modk2 = key2&31;
	uint32_t cmodk1 = 32 - modk1;
	uint32_t cmodk2 = 32 - modk2;
	__m128i s_ret = _mm_set_epi32(0, 0, 0, 0);
	N >>= 2;
	for (int it = 0; it < N; it++) {
		__m128i r_1 = _mm_or_si128(_mm_slli_epi32(s_i, modk1), _mm_srli_epi32(s_i, cmodk1));
		r_1 = _mm_xor_si128(_mm_add_epi32(r_1, s_k1), s_k1);
		__m128i r_2 = _mm_or_si128(_mm_slli_epi32(s_i, modk2), _mm_srli_epi32(s_i, cmodk2));
		r_2 = _mm_xor_si128(_mm_add_epi32(r_2, s_k2), s_k2);
		__m128i r_m = _mm_mullo_epi32(r_1, r_2);
		s_ret = _mm_add_epi32(s_ret, r_m);
		s_i = _mm_add_epi32(s_i, s_4);
	}
	{
		static int32_t tmp[4] __attribute__ ((aligned (16)));
		_mm_store_si128((__m128i*) &tmp[0], s_ret);
		sum += tmp[0] + tmp[1] + tmp[2] + tmp[3];
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

