#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <CL/cl.h>

#define MAXS 1024
#define MAXD 24
#define MAXP 24
void startCL() {
	cl_uint pnum;
	cl_platform_id platforms[MAXP];
	clGetPlatformIDs(MAXP, platforms, &pnum);
	printf("%d platform found\n", pnum);
	for (int i = 0; i < pnum; i++) {
		char buf[MAXS];
		size_t len;
		cl_platform_id pid = platforms[i];

		clGetPlatformInfo(pid, CL_PLATFORM_NAME, 
							MAXS, buf, &len);
		printf("Platform Name %s\n", buf);
		clGetPlatformInfo(pid, CL_PLATFORM_VENDOR, 
							MAXS, buf, &len);
		printf("Platform Vendor %s\n", buf);
		clGetPlatformInfo(pid, CL_PLATFORM_VERSION, 
							MAXS, buf, &len);
		printf("Platform Version %s\n", buf);
		clGetPlatformInfo(pid, CL_PLATFORM_PROFILE, 
							MAXS, buf, &len);
		printf("Platform Profile %s\n", buf);
		
		cl_device_id devices[24];
		cl_uint dnum;

		clGetDeviceIDs(pid, CL_DEVICE_TYPE_ALL, 
						MAXD, devices, &dnum);
		printf("%u Devices\n", dnum);
		clGetDeviceIDs(pid, CL_DEVICE_TYPE_CPU, 
						MAXD, devices, &dnum);
		printf("%u CPU Devices\n", dnum);
		clGetDeviceIDs(pid, CL_DEVICE_TYPE_GPU, 
						MAXD, devices, &dnum);
		printf("%u GPU Devices\n", dnum);
		
		for (int j = 0; j < dnum; j++) {
			cl_device_id cid = devices[j];
			cl_ulong tmp;
      		clGetDeviceInfo(cid, CL_DEVICE_NAME, MAXS, buf, &len);
	  		printf("Device name %s\n", buf);
	  		clGetDeviceInfo(cid, CL_DEVICE_GLOBAL_MEM_SIZE, 
							sizeof(cl_ulong), &tmp, NULL);
	  		printf("Global memory size %lld\n", (long long) tmp);
			clGetDeviceInfo(cid, CL_DEVICE_LOCAL_MEM_SIZE, 
							sizeof(cl_ulong), &tmp, NULL);
			printf("Local memory size %lld\n", (long long) tmp);
			clGetDeviceInfo(cid, CL_DEVICE_MAX_COMPUTE_UNITS, 
							sizeof(cl_ulong), &tmp, NULL);
			printf("# of compute units %lld\n", (long long) tmp);
			clGetDeviceInfo(cid, CL_DEVICE_MAX_WORK_GROUP_SIZE, 
							sizeof(cl_ulong), &tmp, NULL);
			printf("max # of work items in a work group %lld\n", 
							(long long) tmp);
		}	
	}
}
int main() {
	startCL();
	return 0;
}
