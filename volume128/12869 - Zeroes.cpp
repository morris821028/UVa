#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
using namespace std;

int main() {
    long long L, R;
    while (scanf("%lld %lld", &L, &R) == 2 && L) {
        long long ret = R / 5 - L/5 + 1;
        printf("%lld\n", ret);
    }
    return 0;
}
/*
 1 10
 1 3
 0 0
*/