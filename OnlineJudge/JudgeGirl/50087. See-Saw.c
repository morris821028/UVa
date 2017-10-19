#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

static int A[2048];
int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        
        for (int i = 0; i < n; i++) {
            int l = 0, r = 0, lw = 0, rw = 0;
            for (int j = 0; j < n; j++)
                r += A[j], rw += (j+1)*A[j];
            
            for (int j = 0; j < n; j++) {
                lw += l, rw -= r;
                l += A[j], r -= A[j];
                if (lw == rw) {
                    for (int k = 0; k < j; k++)
                        printf("%d ", A[k]);
                    printf("v");
                    for (int k = j+1; k < n; k++)
                        printf(" %d", A[k]);
                    puts("");
                    goto END;
                }
            }
            
            {int t = A[i]; A[i] = A[n-1-i], A[n-1-i] = t;}
        }
        END:;
    }
    return 0;
}

