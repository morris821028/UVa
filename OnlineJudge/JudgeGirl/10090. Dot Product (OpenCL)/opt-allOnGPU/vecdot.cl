#define uint32_t unsigned int
inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}
#define BLK 256
__kernel void vecdot(int N, uint32_t keyA, uint32_t keyB, __global int* C) {
	__local uint32_t buf[256];
	int globalId = get_global_id(0);
	int groupId = get_group_id(0);
	int localId = get_local_id(0);

	uint32_t sum = 0;
	int l = globalId*BLK, r = (globalId+1)*BLK;
	if (r >= N)	
		r = N;
	{
		int i = l;
#define UNLOOP { \
	sum += encrypt(i, keyA) * encrypt(i, keyB), i++; \
}
#define UNLOOP4 {UNLOOP UNLOOP UNLOOP UNLOOP}
#define UNLOOP8 {UNLOOP4 UNLOOP4}
		for (i = l; i+8 <= r;)
			UNLOOP8;
		for (; i < r;)
			UNLOOP;
	}
	buf[localId] = sum; 
	barrier(CLK_LOCAL_MEM_FENCE);

	if (localId < 128) { buf[localId] += buf[localId + 128]; barrier(CLK_LOCAL_MEM_FENCE); }
	if (localId < 64) { buf[localId] += buf[localId + 64]; barrier(CLK_LOCAL_MEM_FENCE); }
	if (localId < 32) {
		buf[localId] += buf[localId + 32];
		barrier(CLK_LOCAL_MEM_FENCE);
		buf[localId] += buf[localId + 16];
		barrier(CLK_LOCAL_MEM_FENCE);
		buf[localId] += buf[localId +  8];
		barrier(CLK_LOCAL_MEM_FENCE);
		buf[localId] += buf[localId +  4];
		barrier(CLK_LOCAL_MEM_FENCE);
//		buf[localId] += buf[localId +  2];
//		barrier(CLK_LOCAL_MEM_FENCE);
//		buf[localId] += buf[localId +  1];
		if (localId == 0)
			C[groupId] = buf[0] + buf[1] + buf[2] + buf[3];
	}
}
__kernel void reduction(int N, __global uint32_t *A) {
	__local uint32_t buf[256];
	int globalId = get_global_id(0);
	int groupId = get_group_id(0);
	int localId = get_local_id(0);

	buf[localId] = globalId < N ? A[globalId] : 0; 
	barrier(CLK_LOCAL_MEM_FENCE);

	if (localId < 128) { buf[localId] += buf[localId + 128]; barrier(CLK_LOCAL_MEM_FENCE); }
	if (localId < 64) { buf[localId] += buf[localId + 64]; barrier(CLK_LOCAL_MEM_FENCE); }
	if (localId < 32) {
		buf[localId] += buf[localId + 32];
		barrier(CLK_LOCAL_MEM_FENCE);
		buf[localId] += buf[localId + 16];
		barrier(CLK_LOCAL_MEM_FENCE);
		buf[localId] += buf[localId +  8];
		barrier(CLK_LOCAL_MEM_FENCE);
		buf[localId] += buf[localId +  4];
		barrier(CLK_LOCAL_MEM_FENCE);
//		buf[localId] += buf[localId +  2];
//		barrier(CLK_LOCAL_MEM_FENCE);
//		buf[localId] += buf[localId +  1];
		if (localId == 0)
			A[groupId] = buf[0] + buf[1] + buf[2] + buf[3];
	}
}

