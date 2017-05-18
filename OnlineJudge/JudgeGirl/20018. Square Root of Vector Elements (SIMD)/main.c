#include <stdio.h>
#include <memory.h>
#include <math.h>
#include <time.h>
#include "VSQRT.h"


static float a[1048576], b[1048576]; 
int main() {
	int N = 1048576;
	for (int i = 0; i < N; ++i) 
		a[i] = i;  

	for (int it = 0; it < 20; it++)
	{  
		memcpy(b, a, sizeof(a[0])*N);
		clock_t t = clock();
		for (int i = 0; i < 10; i++)
			sqrt2(b, b+N);
		t = clock() - t;
		fprintf(stderr, "It took me %f seconds.\n", ((float) t)/CLOCKS_PER_SEC);
		float sum = 0;
		for (int i = 0; i < N; i++)
			sum += b[i];
		printf("%f\n", sum);
	}  
	return 0;
}

