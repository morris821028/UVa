#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    unsigned long long x, y, z;
    while(scanf("%llu %llu %llu", &x, &y, &z) == 3)
        printf("%llu\n", x+y+z-2*min(x, min(y, z)));
    return 0;
}
