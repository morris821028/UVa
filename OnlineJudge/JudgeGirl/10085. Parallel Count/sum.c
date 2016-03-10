#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include "utils.h"

typedef struct Argu {
    int *result;
    int L, R, key;
} Argu;

static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
	    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
	    return (rotate_left(m, key&31) + key)^key;
}

static void* subtask(void* argu) {
    Argu *ptr = (Argu *) argu;
    *(ptr->result) = 0;
    for (int i = ptr->L; i <= ptr->R; i++)
        *(ptr->result) += encrypt(i, ptr->key);
}

void f(int n, int key, int *p1, int *p2, int *p3, int *p4) {
    pthread_t threads[4];
    int *output[4] = {p1, p2, p3, p4};
    for (int i = 0; i < 4; i++) {
            Argu *argu = (Argu *) malloc(sizeof(Argu));
            argu->result = output[i];
            argu->L = i * (n / 4) + 1;
            argu->R = argu->L + n / 4 - 1;
			argu->key = key;
            if (i == 3) argu->R = n;
            pthread_create(&threads[i], NULL, subtask, argu);
    }

    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);
}

