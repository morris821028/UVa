#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <pthread.h>
#include "utils.h"
 
typedef struct Argu {
    int l, r;
    uint32_t *psum;
    uint32_t key;
} Argu;
void* subtask1(void *argu) {
    Argu data = *((Argu *) argu);
    int l = data.l, r = data.r;
    uint32_t sum = 0;
    for (int i = l, j = 0; i <= r; i++, j++) {
        sum += encrypt(i, data.key);
        data.psum[j] = sum;
    }
    free(argu);
}
void* subtask2(void *argu) {
    Argu data = *((Argu *) argu);
    int l = data.l, r = data.r;
    for (int i = l, j = 0; i <= r; i++, j++)
        data.psum[j] += data.key;
    free(argu);
}
#define MAXN 10000005
#define MAX_THREAD 4
uint32_t prefix_sum[MAXN];
int main() {
    int n;
    uint32_t key;
    while (scanf("%d %" PRIu32, &n, &key) == 2) {
        pthread_t threads[MAX_THREAD];
        for (int i = 0; i < MAX_THREAD; i++) {
            Argu *argu = (Argu *) malloc(sizeof(Argu));
            argu->l = i * n / MAX_THREAD + 1;
            argu->r = (i+1) * n / MAX_THREAD;
            argu->psum = prefix_sum + argu->l, argu->key = key;
            pthread_create(&threads[i], NULL, subtask1, argu);
        }
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_join(threads[i], NULL);
 
        uint32_t block_sum = 0;
        for (int i = 0; i < MAX_THREAD; i++) {
            Argu *argu = (Argu *) malloc(sizeof(Argu));
            argu->l = i * n / MAX_THREAD + 1;
            argu->r = (i+1) * n / MAX_THREAD;
            argu->psum = prefix_sum + argu->l, argu->key = block_sum;
            block_sum += prefix_sum[argu->r];
            pthread_create(&threads[i], NULL, subtask2, argu);
        }
        for (int i = 0; i < MAX_THREAD; i++)
            pthread_join(threads[i], NULL);

        output(prefix_sum, n);
    }
    return 0;
}
