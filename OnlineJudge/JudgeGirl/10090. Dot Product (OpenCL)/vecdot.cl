__kernel void vecdot(__global int* matrixA, 
		  __global int* matrixB, 
		  __global int* matrixC)
{
	int idx = get_global_id(0);
	matrixC[idx] = matrixA[idx] * matrixB[idx];
}
