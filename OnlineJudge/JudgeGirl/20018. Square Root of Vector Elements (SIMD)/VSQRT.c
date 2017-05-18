#include "VSQRT.h"
 
#include <stdint.h>
#include <math.h>
#include <x86intrin.h>
 
//#undef __AVX__
//#undef __SSE__
 
#if defined(__AVX__)
void sqrt2(float *a, float *end) {
    uint32_t offset = ((void *) a - (void *) 0);
    for (; a < end && (offset&31); a++, offset += sizeof(float))
        *a = sqrt(*a);
    __m256* ptr = (__m256*) a;
    for (; a + 8 <= end; a += 8, ptr++)
        _mm256_store_ps(a, _mm256_sqrt_ps(*ptr));
    for (; a < end; a++)
        *a = sqrt(*a);
}
#elif defined(__SSE__)
void sqrt2(float *a, float *end) {
    uint32_t offset = ((void *) a - (void *) 0);
    for (; a < end && (offset&15); a++, offset += sizeof(float))
        *a = sqrt(*a);
    __m128* ptr = (__m128*) a;
    for (; a + 4 <= end; a += 4, ptr++)
        _mm_store_ps(a, _mm_sqrt_ps(*ptr));
    for (; a < end; a++)
        *a = sqrt(*a);
}
#else
void sqrt2(float *begin, float *end) {
    for (; begin != end; begin++)
        *begin = sqrtf(*begin);
}
#endif
