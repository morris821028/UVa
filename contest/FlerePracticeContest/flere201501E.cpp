#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <string.h>
#include <vector>
using namespace std;

int main() {
    int testcase, n, x;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        unsigned long long ret = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", &x);
            ret = ret * 2 + x;
        }
        printf("%llu\n", ret);
    }
    return 0;
}
/*
 2
 3 
 1 2 3
 2
 3 3
*/