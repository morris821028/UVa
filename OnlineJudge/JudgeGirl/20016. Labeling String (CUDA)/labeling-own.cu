#include "labeling.h"
#include <stdint.h>
#include <stdio.h>
#define BLK 2
#define MAXK 500
__global__ void stage_prefix(int n, const char *str, int32_t *pos) {
    extern __shared__ int32_t tmp[];
    const int m = blockDim.x;
    const int tid = threadIdx.x;
    const int base = (blockDim.x*blockIdx.x)*2;
	const int init = base*BLK-1;
#define TRANS(index) ((index >= n || str[index] > ' ') ? init : index)
 	int pout = 0, pin = 1;
    int reg_pos[BLK*2], prev;
    {
        int mx = -1, off = (2*tid+0+base)*BLK;
        for (int i = 0; i < 2*BLK; i++) {
            int t = TRANS(off+i);
            if (t > mx)    mx = t;
            reg_pos[i] = mx;
        }
		tmp[pout*m + tid] = mx;
		prev = mx;
    }
    __syncthreads();
	for (int offset = 1; offset <= 128; offset <<= 1) {
		pout = 1 - pout, pin = 1 - pin;
		int t = tid >= offset ? max(tmp[pin*m + (tid-offset)], prev) : tmp[pin*m + tid];
		tmp[pout*m + tid] = prev = t;
    	__syncthreads();
	}	
    {
        int off = (2*tid+0+base)*BLK;
        int mx = tid ? tmp[pout*m + tid-1] : init;
		for (int i = min(2*BLK, n-off)-1; i >= 0; i--) {
            pos[off+i] = off+i-max(reg_pos[i], mx);
        }
    }
}
__global__ void stage_third(int n, int32_t *pos, int bsz) {
    const int tid = threadIdx.x;
    const int base = (blockDim.x*blockIdx.x)*2;
	int l = base*BLK;
	if (l >= n || l == 0 || 2*tid*BLK >= MAXK)
		return ;
	__shared__ int fixed;
	if (tid == 0)
		fixed = pos[l-1];
	__syncthreads();
	if (fixed <= 0)
		return ;
	if (2*tid*BLK+fixed >= MAXK)
		return ;
	int off = 2*tid*BLK + l;
	int r = min(2*BLK, n-off);
	int mx = fixed+1 + 2*tid*BLK;
	for (int i = 0, j = 2*tid*BLK+1; i < r && pos[off] == j; i++, j++) {
		pos[off] = mx+i, off++;
	}
}
void labeling(const char *cuStr, int32_t *cuPos, int strLen) {
	const int bsz = 256;
	int M = bsz*BLK*2;
	dim3 bb(bsz);
	dim3 gg((strLen+M-1)/M);
	stage_prefix<<<gg, bb, (bsz*2+1)*sizeof(int32_t)>>>(strLen, cuStr, cuPos);
	stage_third<<<gg, bb>>>(strLen, cuPos, bsz*2*BLK);
}
