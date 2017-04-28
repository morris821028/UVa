#include <bits/stdc++.h>
#include <thrust/device_vector.h>
#include <thrust/copy.h>
#include <thrust/tabulate.h>
#include <thrust/scan.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
const int MAXN = 16777216;

__global__ void stage_first(int n, char *str, int32_t *pos) {
	int idx = blockDim.x*blockIdx.x+threadIdx.x;
	if (idx >= n)
		return ;
	pos[idx] = str[idx] > ' ' ? -1 : idx;
}
__global__ void stage_second(int n, int32_t *pos) {
	extern __shared__ int32_t tmp[];
	int m = blockDim.x;
	int tid = threadIdx.x;
	int base = (blockDim.x*blockIdx.x)*2;
	int off = 1;
	tmp[2*tid] = pos[2*tid+base];
	tmp[2*tid+1] = pos[2*tid+1+base];
	for (int d = m; d > 0; d >>= 1, off <<= 1) {
		__syncthreads();
		if (tid < d) {
			int32_t ai = off*(2*tid+1)-1;
			int32_t bi = off*(2*tid+2)-1;
			tmp[bi] = tmp[bi] > tmp[ai] ? tmp[bi] : tmp[ai];
		}
	}
	if (tid == 0) {
		tmp[2*m] = tmp[2*m-1];
		tmp[2*m-1] = -1;
	}
	for (int d = 1; d < 2*m; d <<= 1) {
		off >>= 1;
		__syncthreads();
		if (tid < d) {
			int32_t ai = off*(2*tid+1)-1;
			int32_t bi = off*(2*tid+2)-1;
			int32_t t = tmp[ai];
			tmp[ai] = tmp[bi];
			tmp[bi] = t > tmp[bi] ? t : tmp[bi];
		}
	}
	__syncthreads();
	pos[2*tid+base] = tmp[2*tid+1];
	pos[2*tid+1+base] = tmp[2*tid+2];
}
__global__ void stage_fixed(int n, __global__ int32_t *pos, int bsz) {
	int idx = blockDim.x*blockIdx.x+threadIdx.x;
	if (idx >= n || idx/bsz == 0)
		return ;
	if (pos[idx] == -1)
		pos[idx] = pos[idx/bsz*bsz-1];
}
__global__ void stage_third(int n, int32_t *pos) {
	int idx = blockDim.x*blockIdx.x+threadIdx.x;
	if (idx >= n)
		return ;
	pos[idx] = idx - pos[idx];
}
void custom_sol(int n, char *cuStr, int32_t *cuPos) {
	const int bsz = 256;
	const int tsz = 512;
	dim3 bb(bsz);
	dim3 gg(((n+1)/2+bsz-1)/bsz);
	stage_first<<<(n+tsz-1)/tsz, tsz>>>(n, cuStr, cuPos);
	stage_second<<<gg, bb, (bsz*2+1)*sizeof(int32_t)>>>(n, cuPos);
	stage_fixed<<<(n+tsz-1)/tsz, tsz>>>(n, cuPos, bsz*2);
	stage_third<<<(n+tsz-1)/tsz, tsz>>>(n, cuPos);
}
template<class T> struct MM {
	char *base;
	MM(char *base): base(base) {}
	__host__ __device__ T operator()(const T& index) const { return (base[index] > ' ') ? -1 : index; };
};
template<class T> struct NN {
	int32_t *base;
	NN(int32_t *base): base(base) {}
	__host__ __device__ T operator()(const T& index) const { return index-base[index]; };
};
void thrust_sol(int n, char *cuStr, int32_t *cuPos) {
	thrust::tabulate(thrust::device, cuPos, cuPos+n, MM<int32_t>(cuStr));
	thrust::inclusive_scan(thrust::device, cuPos, cuPos+n, cuPos, thrust::maximum<int>());
	thrust::tabulate(thrust::device, cuPos, cuPos+n, NN<int32_t>(cuPos));
}
int main() {
	static char *cuStr;
	static int32_t *cuPos;
	cudaMalloc(&cuStr, sizeof(char)*MAXN);
	cudaMalloc(&cuPos, sizeof(int32_t)*MAXN);
	static char s[MAXN];
	static int ret[MAXN];
	int cases = 0;
	while (fgets(s, MAXN, stdin)) {
		int n = strlen(s);
		cudaMemcpy(cuStr, s, sizeof(char)*n, cudaMemcpyHostToDevice);
		clock_t st, ed;
		st = clock();
		for (int i = 0; i < 10; i++) {
			custom_sol(n, cuStr, cuPos);
//			thrust_sol(n, cuStr, cuPos);
		}
		cudaMemcpy(ret, cuPos, sizeof(int32_t)*n, cudaMemcpyDeviceToHost);
		ed = clock() - st;
		printf ("It took me %lf seconds.\n", ((float) ed)/CLOCKS_PER_SEC/10);
		puts("Checking");
		st = clock();
		for (int i = 0, sum = 0; i < n; i++) {
//			printf("%d%c", ret[i], " \n"[i==n-1]);
			if (s[i] > ' ')
				sum++;
			else
				sum = 0;
			assert(sum == ret[i]);
		}
		ed = clock() - st;
		printf ("It took me %lf seconds.\n", ((float) ed)/CLOCKS_PER_SEC);

		printf("Case #%d: PASS\n", ++cases);
	}
	cudaFree(cuPos);
	cudaFree(cuStr);
	return 0;
}


