#include <stdio.h>
#include <thrust/tabulate.h>
#include <thrust/functional.h>
#include <thrust/scan.h>
#include <thrust/execution_policy.h>

template<class T> struct MM {
	const char *base;
	MM(const char *base): base(base){};
	__host__ __device__ T operator() (const T& index) const {
		return map(base[index]);
	}

	__host__ __device__ T map(const char& c) const {
		return c == ' ' ? T(0) : T(1);
	}
};
void labeling(const char *cuStr, int *cuPos, int strLen){
	//step 1 but cuPos is set to 1 if base[index] is an alphabet and is set to 0 if base[index] is a space
	thrust::tabulate(thrust::device,cuPos,cuPos+strLen,MM<int32_t>(cuStr));
	//calculate the prefixsum of each 1 segment
	thrust::inclusive_scan_by_key(thrust::device,cuPos,cuPos+strLen,cuPos,cuPos);
}

