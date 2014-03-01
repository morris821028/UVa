#include <stdio.h>
#include <map>
#include <iostream>
using namespace std;

int main() {
    long long n, a, b;
    while(scanf("%lld %lld %lld", &n, &a, &b) == 3) {
        map<int, int> COUNT;
        long long next = 0;
        int ret = n;
        while(true) {
            next = (a*(next*next%n)%n + b)%n;
            int &v = COUNT[next];
            v++;
            if(v == 2)  ret--;
            if(v == 3)  break;
        }
        printf("%d\n", ret);
    }
    return 0;
}
