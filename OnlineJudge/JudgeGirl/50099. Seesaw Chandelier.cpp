#include <stdio.h>
#include <stdint.h>
#define MAXN 32768
static int n, A[MAXN];
static int64_t S[MAXN], M[MAXN];

void print(int l, int r) {
    if (r-l < 2)
        return ;
    int64_t s = S[r] - S[l-1], m = M[r] - (M[l-1] + (r-l+1)*S[l-1]);
    if (s == 0 || m%s)    return ;
    int pos = r-(int) (m/s);
    print(l, pos-1);
    printf("%d\n", pos-1);
    print(pos+1, r);
}
int main() {
    while (scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        for (int i = 1; i <= n; i++) {
            M[i] = M[i-1] + S[i-1];
            S[i] = S[i-1] + A[i];
        }
        print(1, n);
    }
    return 0;
}
