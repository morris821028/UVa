#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];

int main() {
    int n, A[32768];
    while (scanf("%d", &n) == 1 && n) {
        memset(mark, 0, sizeof(mark));
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += A[i], SET(sum);
        }
        
        int ret = -1;
        for (int i = n; ret == -1 && i >= 3; i--) {
            if (sum%i)
                continue;
            int d = sum/i;
            for (int j = 0, st = 0; st <= d; st += A[j], j++) {
                int ok = 1;
                for (int k = st; ok && k < sum; k += d)
                    ok &= GET(k);
                if (ok) {
                    ret = n - i;
                    break;
                }
            }
        }
        printf("%d\n", ret);
    }
    return 0;
}

/*
 3
 1000 1000 1000
 6
 1 2 3 1 2 3
 3
 1 1 2
 10
 10 40 20 30 30 10 10 50 24 26
 0
 */