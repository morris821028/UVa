#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <assert.h>
#include <iostream>
using namespace std;

int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        int64_t n, m, ret = 0;
        scanf("%lld", &n);
        m = (n+1)/2;
        ret += (2 + (m-1)*2)*m/2;
        ret += (2 + (m-2)*2)*(m-1)/2;
        printf("%lld\n", ret);
    }
    return 0;
}

