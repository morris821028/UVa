#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <CL/cl.h>

#define MAXDEV 8
#define MAXPLAT 8
#define MAXN 2048
#define MAXSTRBUF 1024

// -- start working with OpenCL

#define CheckFailAndExit(status) \
	if (status != CL_SUCCESS) {\
		fprintf(stderr, "Error: Line %u in file %s\n\n", __LINE__, __FILE__); \
	}
#define clPrint(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)
int infoGPU() {
	size_t                 logLen;
	char                 logBuf[MAXSTRBUF];
	cl_int                clStat;
	cl_uint                clPlatN, clDevN;
	cl_platform_id        clPlatIDs[MAXPLAT], clPlatID;
	cl_device_id        clDevIDs[MAXDEV], clDevID;

	clGetPlatformIDs(MAXPLAT, clPlatIDs, &clPlatN);
	clPrint("%d platform found\n", clPlatN);
	for (int i = 0; i < clPlatN; i++) {
		clPlatID = clPlatIDs[i];
		const cl_platform_info clPlatInfoQuery[] = {
			CL_PLATFORM_NAME, CL_PLATFORM_VENDOR, 
			CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE
		};
		const cl_platform_info clPlatDevInfoQuery[] = {
			CL_DEVICE_TYPE_ALL, CL_DEVICE_TYPE_CPU, 
			CL_DEVICE_TYPE_GPU
		};
		const cl_platform_info clDevInfoQuery[] = {
			CL_DEVICE_GLOBAL_MEM_SIZE, CL_DEVICE_LOCAL_MEM_SIZE,
			CL_DEVICE_MAX_COMPUTE_UNITS, CL_DEVICE_MAX_WORK_GROUP_SIZE
		};
		const char const queryPlatFmt[][32] = {
			"Platform Name %s\n", "Platform Vendor %s\n", 
			"Platform Version %s\n", "Platform Profile %s\n"
		};
		const char const queryPlatDevFmt[][32] = {
			"%u Devices\n", "%u CPU Devices\n",
			"%u GPU Devices\n"
		};
		const char const queryDevFmt[][64] = {
			"Global memory size %lld\n", "Local memory size %lld\n",
			"# of compute units %lld\n", "max # of work items in a work group %lld\n"
		};
		const int platQcnt = sizeof(clPlatInfoQuery) / sizeof(cl_platform_info);
		const int platDevQcnt = sizeof(clPlatDevInfoQuery) / sizeof(cl_platform_info);
		const int devQcnt = sizeof(clDevInfoQuery) / sizeof(cl_platform_info);

		for (int j = 0; j < platQcnt; j++) {
			clStat = clGetPlatformInfo(clPlatID, clPlatInfoQuery[j], MAXSTRBUF, logBuf, &logLen);
			CheckFailAndExit(clStat);
			clPrint(queryPlatFmt[j], logBuf);            
		}

		for (int j = 0; j < platDevQcnt; j++) {
			clGetDeviceIDs(clPlatID, clPlatDevInfoQuery[j], MAXDEV, clDevIDs, &clDevN);
			clPrint(queryPlatDevFmt[j], clDevN);
			if (clPlatDevInfoQuery[j] == CL_DEVICE_TYPE_ALL)
				continue;
			for (int k = 0; k < clDevN; k++) {
				clDevID = clDevIDs[k];
				clStat = clGetDeviceInfo(clDevID, CL_DEVICE_NAME, MAXSTRBUF, logBuf, &logLen);
				CheckFailAndExit(clStat);
				clPrint("Device name %s\n", logBuf);
				for (int p = 0; p < devQcnt; p++) {
					cl_ulong clVal;
					clStat = clGetDeviceInfo(clDevID, clDevInfoQuery[p], sizeof(cl_ulong), &clVal, NULL);
					CheckFailAndExit(clStat);
					clPrint(queryDevFmt[p], clVal);
				}
			}
		}
	}
}

int main() {
	infoGPU();
	return 0;
}
