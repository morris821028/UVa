#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <omp.h>
#include "utils.h"
 
#define MAXN 10000005
uint32_t prefix_sum[MAXN], block[128] = {};
int main() {
	omp_set_num_threads(4);
    int n;
    uint32_t key;
    while (scanf("%d %" PRIu32, &n, &key) == 2) {
		int MM = 4;
		int chunk = 1;
		#pragma omp parallel for
		for (int i = 0; i < MM; i++) {
			int l = i * n / MM + 1;
			int r = (i+1) * n / MM;
			uint32_t sum = 0;
			for (int j = l; j <= r; j++) {
				sum += encrypt(j, key);
				prefix_sum[j] = sum;
			}
			block[i+1] = sum;
		}
		for (int i = 1; i < MM; i++) {
			block[i] += block[i-1];
		}
		
		#pragma omp parallel for
		for (int i = 1; i < MM; i++) {
			int l = i * n / MM + 1;
			int r = (i+1) * n / MM;
			uint32_t sum = block[i];
			for (int j = l; j <= r; j++) {
				prefix_sum[j] += sum;
			}
		}
		
		output(prefix_sum, n);
	}
	return 0;
}
