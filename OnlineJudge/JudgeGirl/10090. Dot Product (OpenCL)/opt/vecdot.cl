__kernel void vecdot(__global int* A, 
		  __global int* B, 
		  __global int* C) {
	__local int buf[64];
	int globalId = get_global_id(0);
	int groupId = get_group_id(0);
	int localId = get_local_id(0);
	int localSz = get_local_size(0);

	buf[localId] = A[globalId] * B[globalId];
	barrier(CLK_LOCAL_MEM_FENCE);
	for (int i = localSz>>1; i; i >>= 1) {
		if (localId < i)
			buf[localId] += buf[localId + i];
		barrier(CLK_LOCAL_MEM_FENCE);
	}
	if (localId == 0)
		C[groupId] = buf[0];
}
