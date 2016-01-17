#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int A[1048576];
int main() {
    int n, x;
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++)
            scanf("%d", &x), A[x] = i;
        int ret = 0, pos = A[1], dir = 1;
        for (int i = 1; i < n; i++) {
            if (pos > A[i+1] && dir == 1)
                ret++, dir = -dir;
            if (pos < A[i+1] && dir == -1)
                ret++, dir = -dir;
            pos = A[i+1];
        }
        printf("%d\n", ret);
    }
    return 0;
}
/*
 2
 1 2
 5
 1 4 2 5 3
 4
 4 3 2 1
*/