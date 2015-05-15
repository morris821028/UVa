#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
        int n;
        long long x, sum = 0;
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%lld", &x);
            sum += x;
        }
        puts(sum%2 ? "No" : "Yes");
    }
    return 0;
}

/*
 3
 1 1
 2 9 17
 3 12 15 19
*/