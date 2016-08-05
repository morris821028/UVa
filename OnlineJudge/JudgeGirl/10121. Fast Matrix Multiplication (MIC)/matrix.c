#include "matrix.h"
#define LOOP_UNROLL 8
__attribute__ ((target(mic)))
void transpose(int N, UINT A[][2048]) {
    UINT t;
    for (int i = 0; i < N; i++)
        for (int j = i+1; j < N; j++)
            t = A[i][j], A[i][j] = A[j][i], A[j][i] = t;
}
__attribute__ ((target(mic)))
void multiply(int N, UINT A[][2048], UINT B[][2048], UINT C[][2048]) {
    transpose(N, B);
    #pragma omp parallel for
	#pragma ivdep
    for (int i = N-1; i >= 0; i--) {
		#pragma simd
        for (int j = N-1; j >= 0; j--) {
            register UINT sum = 0;
            UINT *a = &A[i][0], *b = &B[j][0];
            int k = N;
            switch (k % LOOP_UNROLL) {
                case 0: do { sum += *a * *b, a++, b++;
                case 7: sum += *a * *b, a++, b++;
                case 6: sum += *a * *b, a++, b++;
                case 5: sum += *a * *b, a++, b++;
                case 4: sum += *a * *b, a++, b++;
                case 3: sum += *a * *b, a++, b++;
                case 2: sum += *a * *b, a++, b++;
                case 1: sum += *a * *b, a++, b++;
                } while ((k -= LOOP_UNROLL) > 0);
            }
            C[i][j] = sum;
        }
    }
}
