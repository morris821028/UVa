#include "labeling.h"
#include <thrust/tabulate.h>
#include <thrust/scan.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>

template<class T> struct MM {
	const char *base;
	MM(const char *base): base(base) {}
	__host__ __device__ T operator()(const T& index) const { return (base[index] > ' ') ? -1 : index; };
};
template<class T> struct NN {
	int32_t *base;
	NN(int32_t *base): base(base) {}
	__host__ __device__ T operator()(const T& index) const { return index-base[index]; };
};

void labeling(const char *cuStr, int *cuPos, int strLen) {
	thrust::tabulate(thrust::device, cuPos, cuPos+strLen, MM<int32_t>(cuStr));
	thrust::inclusive_scan(thrust::device, cuPos, cuPos+strLen, cuPos, thrust::maximum<int>());
	thrust::tabulate(thrust::device, cuPos, cuPos+strLen, NN<int32_t>(cuPos));
}

