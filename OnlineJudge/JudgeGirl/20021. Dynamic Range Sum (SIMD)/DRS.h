#ifndef __DRS_H
#define __DRS_H

#include <stdint.h>

typedef struct Rect {
	int32_t lx, ly, rx, ry;
} Rect;

int32_t search_range(Rect rect, int32_t x[], int32_t y[], 
		int32_t w[], int32_t n);

#endif


