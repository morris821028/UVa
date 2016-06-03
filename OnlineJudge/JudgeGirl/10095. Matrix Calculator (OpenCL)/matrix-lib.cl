#define N %d
#define CTYPE unsigned int

__kernel void matrixAdd(__global CTYPE *in1,
        __global CTYPE *in2,
        __global CTYPE *out) {
    int x = get_global_id(0);
	out[x] = in1[x] + in2[x];
}

__kernel void matrixMul(__global CTYPE *in1,
        __global CTYPE *in2,
        __global CTYPE *out) {
	int id = get_global_id(0);
	int x = id / N, y = id % N;
	CTYPE sum = 0;
	for (int i = 0; i < N; i++)
		sum += in1[x*N + i] * in2[i*N + y];
	out[x * N + y] = sum;
}
