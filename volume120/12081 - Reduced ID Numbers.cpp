#include <stdio.h>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <string.h>
#include <assert.h>
using namespace std;

int used[1048576];
int main() {
    int testcase;
    int n, A[512];
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &A[i]);
        for (int i = 1; ; i++) {
            int ok = 1;
            for (int j = 0; j < i; j++)
                used[j] = 0;
            for (int j = 0; j < n; j++) {
                int &v = used[A[j]%i];
                ok &= !v, v = 1;
            }
            if (ok) {
                printf("%d\n", i);
                break;
            }
        }
    }
    return 0;
}

/*
 2
 1
 124866
 3
 124866
 111111
 987651
 */