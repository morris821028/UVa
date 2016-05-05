#define uint32_t unsigned int
inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}

__kernel void vecdot(uint32_t keyA, uint32_t keyB, __global int* C) {
	__local int buf[64];
	int globalId = get_global_id(0);
	int groupId = get_group_id(0);
	int localId = get_local_id(0);
	int localSz = get_local_size(0);

	buf[localId] = encrypt(globalId, keyA) * encrypt(globalId, keyB);
	barrier(CLK_LOCAL_MEM_FENCE);
	for (int i = localSz>>1; i; i >>= 1) {
		if (localId < i)
			buf[localId] += buf[localId + i];
		barrier(CLK_LOCAL_MEM_FENCE);
	}
	if (localId == 0)
		C[groupId] = buf[0];
}
