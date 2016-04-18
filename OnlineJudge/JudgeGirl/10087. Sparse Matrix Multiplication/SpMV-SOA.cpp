#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <algorithm>
using namespace std;
#define MAXN 1048576
#define MAXL (MAXN<<2)
 
static inline uint32_t rotate_left(uint32_t x, uint32_t n) {
    return  (x << n) | (x >> (32-n));
}
static inline uint32_t encrypt(uint32_t m, uint32_t key) {
    return (rotate_left(m, key&31) + key)^key;
}
typedef struct ELE {
    int i[MAXL], j[MAXL];
    uint32_t v[MAXL];
} ELE;
ELE LA, LB, LT;
int D[MAXL];
void SpMV(int N, int M, int R, ELE &LA, int na, ELE &LB, int nb) {
    int ma = 0, mb = 0;
    static int aoff[MAXN], boff[MAXN];
 
    for (int i = 0, p = -1; i < na; i++) {
        if (LA.i[i] != p)
            aoff[ma++] = i, p = LA.i[i];
    }
    for (int i = 0, p = -1; i < nb; i++) {
        if (LB.i[i] != p)
            boff[mb++] = i, p = LB.i[i];
    }
 
    uint32_t hash = 0;
    aoff[ma] = na, boff[mb] = nb;
    #pragma omp parallel for reduction(+: hash)
    for (int i = 0; i < ma; i++) {
        for (int j = 0; j < mb; j++) {
            int idx1 = aoff[i], idx2 = boff[j];
            int top1 = aoff[i+1], top2 = boff[j+1];
            uint32_t sum = 0;
            int r = LA.i[idx1], c = LB.i[idx2];
            while (idx1 < top1 && idx2 < top2) {
                if (LA.j[idx1] < LB.j[idx2])
                    idx1++;
                else if (LA.j[idx1] > LB.j[idx2])
                    idx2++;                    
                else
                    sum += LA.v[idx1] * LB.v[idx2], idx1++, idx2++;
            }
 
            if (sum)
                hash += encrypt((r+1)*(c+1), sum);
        }
    }
    printf("%u\n", hash);
}
bool cmp(int a, int b) {
    if (LT.i[a] != LT.i[b])
        return LT.i[a] < LT.i[b];
    return LT.j[a] < LT.j[b];
}
int main() {
    int N, M, R, nA, nB;
    while (scanf("%d %d %d", &N, &M, &R) == 3) {
        scanf("%d %d", &nA, &nB);
        for (int i = 0; i < nA; i++)
            scanf("%d %d %d", &LA.i[i], &LA.j[i], &LA.v[i]);
        for (int i = 0; i < nB; i++)
            scanf("%d %d %d", <.j[i], <.i[i], <.v[i]);
        for (int i = 0; i < nB; i++)
            D[i] = i;
        sort(D, D+nB, cmp);
        for (int i = 0; i < nB; i++)
            LB.i[i] = LT.i[D[i]], LB.j[i] = LT.j[D[i]], LB.v[i] = LT.v[D[i]];
        SpMV(N, M, R, LA, nA, LB, nB);
    }
    return 0;
}
