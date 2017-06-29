#define uint32_t unsigned int
#define int32_t int
inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}
#define BLK 256
__kernel void vecdot(int N, uint32_t keyA, uint32_t keyB, __global int* C) {
    __local int32_t buf[256];
    int globalId = get_global_id(0);
    int localId = get_local_id(0);
    int32_t sum = 0;
    int l = globalId*BLK;
	int r = l + BLK;
    if (r > N)	r = N;
    {
        for (int i = l; i < r; i++)
		    sum += encrypt(i, keyA) * encrypt(i, keyB);
    }
    buf[localId] = sum; 
    barrier(CLK_LOCAL_MEM_FENCE);
	if (localId < 128) { 
		buf[localId] += buf[localId + 128]; barrier(CLK_LOCAL_MEM_FENCE); 
		if (localId <  64) { 
			buf[localId] += buf[localId +  64]; barrier(CLK_LOCAL_MEM_FENCE); 
			if (localId <  32) {  
				buf[localId] += buf[localId + 32]; barrier(CLK_LOCAL_MEM_FENCE); 
				if (localId <  16) {  
					buf[localId] += buf[localId + 16]; barrier(CLK_LOCAL_MEM_FENCE); 
					if (localId <   8) {  
						buf[localId] += buf[localId +  8]; barrier(CLK_LOCAL_MEM_FENCE); 
						if (localId <   4) {  
							buf[localId] += buf[localId +  4]; barrier(CLK_LOCAL_MEM_FENCE); 
							if (localId <   2) {  
								buf[localId] += buf[localId +  2]; barrier(CLK_LOCAL_MEM_FENCE); 
								if (localId <   1) {  
									buf[localId] += buf[localId +  1]; C[get_group_id(0)] = buf[0]; 
								}
							}
						}
					}
				}
			}
		}
	}
}
