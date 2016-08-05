#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <errno.h>
int main() {
	char hostname[128];
	int threads;
	long cache_size, line_size;
	gethostname(hostname, sizeof(hostname));
	printf("Host: %s\n", hostname);
	printf("Host: %ld logical cores\n", sysconf(_SC_NPROCESSORS_ONLN));
#pragma omp parallel
	{
		#pragma omp single
		threads = omp_get_num_threads();
	}
	printf("Host: %d threads\n", threads);
	fflush(stdout);
	
#pragma offload target(mic)
	{
		char hostname[128];
		gethostname(hostname, sizeof(hostname));
		printf("MIC: %s\n", hostname);
		printf("MIC: %ld logical cores\n", sysconf(_SC_NPROCESSORS_ONLN));
#pragma omp parallel
		{
			#pragma omp single
			threads = omp_get_num_threads();
		}
		printf("MIC: %d threads\n", threads);
	}
	return 0;
}
