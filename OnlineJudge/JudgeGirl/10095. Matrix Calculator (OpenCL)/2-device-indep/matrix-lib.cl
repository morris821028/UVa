#define N %d
#define CTYPE unsigned int
#define UNLOOP 8


__kernel void matrixAdd(__global CTYPE *in1,
        __global CTYPE *in2,
        __global CTYPE *out) {
    int x = get_global_id(0);
	out[x] = in1[x] + in2[x];
}

__kernel void matrixMul(__global CTYPE *in1,
        __global CTYPE *in2,
        __global CTYPE *out) {
    CTYPE rbuf[N];
    int r = get_global_id(0);
    int localID = get_local_id(0);
    int localSz = get_local_size(0);
    __local CTYPE cbuf[N];
    for (int i = 0; i < N; i++)
        rbuf[i] = in1[r * N + i];
    for (int c = 0; c < N; c++) {
        for (int cr = localID; cr < N; cr += localSz)
            cbuf[cr] = in2[cr * N + c];
        barrier(CLK_LOCAL_MEM_FENCE);
        CTYPE sum = 0;
        for (int k = 0; k+UNLOOP-1 < N; k += UNLOOP) {
            sum += rbuf[k+0] * cbuf[k+0];
            sum += rbuf[k+1] * cbuf[k+1];
            sum += rbuf[k+2] * cbuf[k+2];
            sum += rbuf[k+3] * cbuf[k+3];
            sum += rbuf[k+4] * cbuf[k+4];
            sum += rbuf[k+5] * cbuf[k+5];
            sum += rbuf[k+6] * cbuf[k+6];
            sum += rbuf[k+7] * cbuf[k+7];
        }
        out[r * N + c] = sum;
    }
}
