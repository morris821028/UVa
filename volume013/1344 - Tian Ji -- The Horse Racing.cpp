#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <string.h>
using namespace std;

int main() {
    int A[1024], B[1024], N;
    while (scanf("%d", &N) == 1 && N) {
        for (int i = 0; i < N; i++) {
            scanf("%d", &A[i]);
        }
        for (int i = 0; i < N; i++) {
            scanf("%d", &B[i]);
        }
        sort(A, A+N);
        sort(B, B+N);
        int la, lb, ra, rb;
        int win = 0;
        la = lb = 0, ra = rb = N-1;
        while (la <= ra && lb <= rb) {
            if (A[la] < B[lb]) {
                la++, rb--, win--;
            } else if (A[la] > B[lb]) {
                la++, lb++, win++;
            } else {
                if(A[ra] < B[rb]) {
                    la++, rb--, win--;
                } else if(A[ra] > B[rb]) {
                    ra--, rb--, win++;
                } else {
                    if (A[la] < B[rb])
                        win--;
                    la++, rb--;
                }
            }
        }
        printf("%d\n", win * 200);
    }
    return 0;
}