#include <stdio.h>

int main() {
    long long n, a, b;
    while(scanf("%lld %lld %lld", &n, &a, &b) == 3) {
        long long next1 = 0, next2 = 0;
        int ret = n;
        while(true) {
            next1 = (a*(next1*next1%n)%n + b)%n;
            next2 = (a*(next2*next2%n)%n + b)%n;
            next2 = (a*(next2*next2%n)%n + b)%n;
            if(next2 == next1)
                break;
        }
        do {
            next1 = (a*(next1*next1%n)%n + b)%n;
            ret--;
        } while(next1 != next2);
        printf("%d\n", ret);
    }
    return 0;
}
