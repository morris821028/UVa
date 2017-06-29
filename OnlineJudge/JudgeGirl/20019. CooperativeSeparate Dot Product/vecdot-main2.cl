#define uint32_t unsigned int
inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}
#define BLK 256
__kernel void vecdot(int N, uint32_t keyA, uint32_t keyB, __global int* C) {
	int globalId = get_global_id(0);
	int groupId = get_group_id(0);
	int localId = get_local_id(0);
	int localSz = get_local_size(0);
	int globalSz = get_global_size(0);

	uint32_t sum = 0;
	int l = globalId*BLK, r = (globalId+1)*BLK;
	if (r >= N)	
		r = N;
	for (int i = l; i < r; i++)
		sum += encrypt(i, keyA) * encrypt(i, keyB);
	atomic_add(&C[groupId], sum);
}
