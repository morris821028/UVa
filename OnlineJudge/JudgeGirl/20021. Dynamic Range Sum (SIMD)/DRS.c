#include "DRS.h"

#include <x86intrin.h>
/*
int32_t search_range(Rect rect, int32_t x[], int32_t y[], 
		int32_t w[], int32_t n) {
	int32_t ret = 0;
	for (int i = 0; i < n; i++) {
		if (rect.lx <= x[i] && x[i] <= rect.rx &&
			rect.ly <= y[i] && y[i] <= rect.ry) {
			ret += w[i];
		}
	}
	return ret;
}
*/
int32_t search_range(Rect rect, int32_t x[], int32_t y[], int32_t w[], int32_t n) {
	__m128i ret = _mm_set_epi32(0, 0, 0, 0);
	rect.lx--, rect.ly--;
	rect.rx++, rect.ry++;
	__m128i lx = _mm_broadcastd_epi32(*((__m128i *) &rect.lx));
	__m128i ly = _mm_broadcastd_epi32(*((__m128i *) &rect.ly));
	__m128i rx = _mm_broadcastd_epi32(*((__m128i *) &rect.rx));
	__m128i ry = _mm_broadcastd_epi32(*((__m128i *) &rect.ry));
	__m128i zo = _mm_set_epi32(0, 0, 0, 0);
	__m128i ic = _mm_set_epi32(3, 2, 1, 0);
	
	for (int i = 0; i+4 <= n; i += 4) {
		__m128i sx = _mm_load_si128((__m128i *) (x+i));
		__m128i sy = _mm_load_si128((__m128i *) (y+i));
		__m128i c1 = _mm_and_si128(_mm_cmplt_epi32(lx, sx), _mm_cmplt_epi32(sx, rx));
		__m128i c2 = _mm_and_si128(_mm_cmplt_epi32(ly, sy), _mm_cmplt_epi32(sy, ry));
		if (_mm_testz_si128(c1, c2) == 0) {
			__m128i cc = _mm_and_si128(c1, c2);
			__m128i vi = _mm_add_epi32(ic, _mm_set_epi32(i, i, i, i));
			__m128i rs = _mm_mask_i32gather_epi32(zo, w+i, ic, cc, 4);
			ret = _mm_add_epi32(ret, rs);
		}
	}
	
	int32_t sum = 0;
	for (int i = (n>>2)<<2; i < n; i++) {
		if (rect.lx <= x[i] && x[i] <= rect.rx &&
			rect.ly <= y[i] && y[i] <= rect.ry) {
			sum += w[i];
		}
	}
	static int32_t tmp[4] __attribute__ ((aligned (16)));
	_mm_store_si128((__m128i*) &tmp[0], ret);
	sum += tmp[0] + tmp[1] + tmp[2] + tmp[3];
	return sum;
}
