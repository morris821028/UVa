#include <cstdio>
int main() {
    unsigned long long a, b;
    while(scanf("%llu %llu", &a, &b) == 2)
        if(a < (1LL<<(b+1)))
            puts("yes");
        else
            puts("no");
    return 0;
}
