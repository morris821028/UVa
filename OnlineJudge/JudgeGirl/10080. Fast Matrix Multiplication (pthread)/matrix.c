#include "matrix.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOOP_UNROLL 8
#define MAXTHREAD 8
#define MAXN 2048
typedef struct Argu {
    int l, r, N;
    UINT *A, *B, *C;
} Argu;
static void transpose(int N, UINT A[][2048]) {
    UINT t;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++)
                t = A[i][j], A[i][j] = A[j][i], A[j][i] = t;
    }
}
void* thread_multiply(void *arg) {
    Argu data = * ((Argu *) arg);
    int l = data.l, r = data.r;
    int N = data.N;
    UINT *A = data.A, *B = data.B, *C = data.C;
    UINT stkA[MAXN];
    for (int i = l; i <= r; i++) {
        memcpy(stkA, A + (i * MAXN), sizeof(UINT) * N);
        for (int j = 0; j < N; j++) {
            UINT sum = 0;
//            UINT *a = A + (i * MAXN), *b = B + (j *  MAXN);
            UINT *a = stkA, *b = B + (j * MAXN);
            int k;
            for (k = 0; k+LOOP_UNROLL < N; k += LOOP_UNROLL) {
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
                sum += *a * *b, a++, b++;
            }
            for (; k < N; k++)
                sum += *a * *b, a++, b++;
            *(C + (i * MAXN + j)) = sum;
        }
    }
    return NULL;
}
void multiply(int N, UINT A[][2048], UINT B[][2048], UINT C[][2048]) {
    transpose(N, B);
 
    pthread_t *threads;
    threads = (pthread_t *) malloc(MAXTHREAD * sizeof(pthread_t));
 
    for (int i = 0; i < MAXTHREAD; i++) {
        Argu *data = (Argu *) malloc(sizeof(Argu));
        data->l = i * N / MAXTHREAD;
        data->r = (i+1) * N / MAXTHREAD - 1;
        data->N = N;
        data->A = &A[0][0], data->B = &B[0][0], data->C = &C[0][0];
        pthread_create(&threads[i], NULL, thread_multiply, (void *) (data));
    }
 
    for (int i = 0; i < MAXTHREAD; i++) 
        pthread_join(threads[i], NULL);
    return ;
}
