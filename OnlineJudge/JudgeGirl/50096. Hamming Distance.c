#include <stdio.h>
#include <stdint.h>

int main() {
    int N, M, P;
    uint64_t _A[16];
    while (scanf("%d %d %d", &N, &M, &P) == 3) {
        for (int i = 0; i < M; i++) {
            scanf("%llu", &_A[i]);
        }
        uint8_t *A = (uint8_t *) _A, x;
        for (int it = 0; it < P; it++) {
            scanf("%hhu", &x);
            int ret = -1;
            for (int i = 0, t = 0; t < N; i += 8) {
                for (int j = 7; j >= 0 && t < N; j--, t++) {
                    uint8_t y = A[i+j];
                    y = x^y;
                    if (y == 0) {
                        ret = i+j;
                        goto END;
                    } else if ((y&(y-1)) == 0) {
                        ret = i+j;
                    }
                }
            }
        END:
            if (ret >= 0)
                printf("%hhu\n", A[ret]);
        }
    }
    return 0;
}
